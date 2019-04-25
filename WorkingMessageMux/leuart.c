/*
 * leuart.c
 *
 *  Created on: Feb 26, 2019
 *      Author: amabo
 */
#include "leuart.h"
#include "main.h"
#include "em_leuart.h"
#include "sleep.h"

//Saved byte to transmit
uint8_t to_transmit = 0;

uint8_t last_d = 0;
uint8_t convert = 0;
uint8_t change_conv = 0;

//LEUART0 Interrupt Handler
void LEUART0_IRQHandler(){
	uint32_t flags = LEUART0->IF & LEUART0->IEN;

	if(flags & LEUART_IF_STARTF){
		LEUART0->IEN |= LEUART_IEN_SIGF | LEUART_IEN_RXDATAV;
		LEUART0->CMD = LEUART_CMD_RXBLOCKDIS | LEUART_CMD_CLEARRX;
		LEUART0->IFC = LEUART_IFC_STARTF;
	}
	if(flags & LEUART_IF_SIGF){
		LEUART0->IEN &= ~(LEUART_IEN_SIGF | LEUART_IEN_RXDATAV);
		LEUART0->CMD = LEUART_CMD_RXBLOCKEN;
		if(change_conv){
			convert = !convert;
		}
		change_conv = 0;
		LEUART0->IFC  = LEUART_IFC_SIGF;
	}
	if(flags & LEUART_IF_TXC){
		//Turn off the interrupt
		LEUART0->IFC  =  LEUART_IF_TXC;
		LEUART0->IEN &= ~LEUART_IEN_TXC;
		LEUART0->CTRL &= ~LEUART_CTRL_TXDMAWU;
	}
	if(flags & LEUART_IF_TXBL){
		while(LEUART0->SYNCBUSY & LEUART_SYNCBUSY_TXDATA);
		//Load the newest bit
		leuart_write_byte(to_transmit);
	}

	//Hold if RX Overflowed
	if(flags & LEUART_IF_RXOF){
		while(1);
	}

	//Process the new messages
	if(flags & LEUART_IF_RXDATAV){
		uint8_t msg = LEUART0->RXDATA;
		//if the last message was a d, we might want to change the scale
		if(last_d){
			if((msg == 'c' || msg == 'C' )&& convert == 1){
				change_conv = 1;
			}
			else if((msg == 'f' || msg == 'F') && convert == 0){
				change_conv = 1;
			}
			else{
				change_conv = 0;
			}
		}

		//Store if the last char was a d
		if(msg == 'd' || msg == 'D'){
			last_d = 1;
		}
		else{
			last_d = 0;
		}
	}
}

/*
 * Initialize the LEUART0 to communicate with the bluetooth module
 * It takes no inputs, and only serves to configure the peripheral registers
 */
void leuart_init(){
	LEUART_Init_TypeDef init = LEUART_INIT_DEFAULT;
	init.baudrate = LEUART0_BAUD_RATE;
	//Use the default 8 bits, no parity and 1 stop bit setup
	LEUART_Init(LEUART0, &init);

	//Route the UART pins the gpio pins d10 and d11
	LEUART0->ROUTELOC0 = LEUART_ROUTELOC0_RXLOC_LOC18 | LEUART_ROUTELOC0_TXLOC_LOC18;
	LEUART0->ROUTEPEN  = LEUART_ROUTEPEN_RXPEN | LEUART_ROUTEPEN_TXPEN;

	LEUART0->CTRL |= LEUART_CTRL_SFUBRX;

	//Enable RX and TX pins
	LEUART0->CMD = LEUART_CMD_RXEN | LEUART_CMD_TXEN | LEUART_CMD_RXBLOCKEN;

	//Set the StartFrame character to a ?
	LEUART0->STARTFRAME = '?';

	//Set the EndFrame character to a #
	//LEUART0->SIGFRAME = '#';

	//LEUART0->IEN |= LEUART_IEN_STARTF | LEUART_IEN_RXOF;

	NVIC_EnableIRQ(LEUART0_IRQn);
}

/*
 * Write a single byte bit over the UART Connection
 * Input bit to be written
 */
inline void leuart_write_byte(uint8_t byte){
	LEUART0->TXDATA = byte;
}

/*
 * Transmit a string over UART
 * Input: string to be transmitted
 */
void leuart_write_string(uint8_t * msg,uint32_t length){
	Sleep_Block_Mode(EM3_STOP);

	//Write the first byte of information
	while(LEUART0->SYNCBUSY & LEUART_SYNCBUSY_TXDATA);
	leuart_write_byte(msg[0]);

	//If I want to write more than one byte of information enable interrupts and keep transmitting the string
	if(length >= 1){
		//Enable interrupt
		LEUART0->IEN |= LEUART_IEN_TXBL;

		//Iterate through the string storing each byte in a transmit register
		for(int n = 1; n < length -1; n++){
			to_transmit = msg[n];

			//Go to sleep until the writing has finished
			Enter_Sleep();
		}
	}

	//After transmitting the final byte, interrupt off of TXC rather than TXC
	LEUART0->IEN &= ~LEUART_IEN_TXBL;
	LEUART0->IFC |=  LEUART_IFC_TXC;

	//Go to sleep until the last byte is transfered
	Enter_Sleep();

	//Turn off the interrupt and unblock sleep
	LEUART0->IEN &= ~LEUART_IEN_TXC;


	Sleep_UnBlock_Mode(EM3_STOP);
}

void dist_f_2_a(char * str, double dist){
	str[4] = '\0';
	uint32_t num = 10*dist;
	str[3] = '0'+num%10;
	str[2] = '.';
	num /= 10;
	str[1] = '0'+num%10;
	num /= 10;
	str[0] = '0'+num%10;
}


