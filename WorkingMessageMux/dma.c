/*
 * dma.c
 *
 *  Created on: Apr 4, 2019
 *      Author: amabo
 */
#include "dma.h"
#include "em_ldma.h"
#include "msg.h"
#include "em_leuart.h"

extern uint8_t rx_buf [RX_BUFFER_SIZE+1];
extern uint8_t msg_in [RX_BUFFER_SIZE];

uint8_t message_flag;

void LDMA_IRQHandler()
{
  uint32_t flags = (LDMA_IntGet() & LDMA->IEN);

  if(flags & (1 << TX_DMA_CHANNEL))
    {
  	  LDMA->IEN &= ~(1<<TX_DMA_CHANNEL);
  	  LEUART0->IEN |=  LEUART_IEN_TXC;
  	  LDMA->IFC = (1 << TX_DMA_CHANNEL);
    }

  if(flags & (1 << RX_DMA_CHANNEL))
    {
  	  LDMA->IFC = (1 << RX_DMA_CHANNEL);
  	  LEUART0->CMD = LEUART_CMD_RXBLOCKEN| LEUART_CMD_CLEARRX;
  	  while(LEUART0->SYNCBUSY);
  	  //Copy out the message to another buffer
  	  for(int i = 1; i < RX_BUFFER_SIZE+1; i++){
  		  msg_in[i-1] = rx_buf[i];
  	  }
  	  start_rx();

  	  message_flag = 1;
    }
}

void dma_TX_init(char * string, uint32_t len){
	LDMA->IEN |= (1<<TX_DMA_CHANNEL);

	// LDMA descriptor and config for transferring TxBuffer
	LDMA_Descriptor_t  ldmaTXDescriptor = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_SINGLE_M2P_BYTE(string, &(LEUART0->TXDATA), len);
	LDMA_TransferCfg_t ldmaTXConfig     = (LDMA_TransferCfg_t)LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_LEUART0_TXBL);                  // Setting the transfer to trigger once there is room in the USART1_TXDATA buffer

	LEUART0->CTRL |= LEUART_CTRL_TXDMAWU;

	LDMA_StartTransfer(TX_DMA_CHANNEL, &ldmaTXConfig, &ldmaTXDescriptor);
}

//
inline void start_rx(){
	// LDMA descriptor and config for receiving data from the slave
	LDMA_Descriptor_t  ldmaRXDescriptor = (LDMA_Descriptor_t) LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(&(LEUART0->RXDATA), rx_buf, RX_BUFFER_SIZE+1); // Source: USART1->RXDATA, Destination: RxBuffer, Bytes to receive: 10
	LDMA_TransferCfg_t ldmaRXConfig     = (LDMA_TransferCfg_t)LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_LEUART0_RXDATAV);         // Setting the transfer to trigger whenever data comes into USART1_RXDATAV

	LEUART0->CTRL |= LEUART_CTRL_RXDMAWU;

	LDMA_StartTransfer(RX_DMA_CHANNEL, &ldmaRXConfig, &ldmaRXDescriptor);
}

void dma_init(){
	// Initializing the DMA
	LDMA_Init_t ldmaInit = LDMA_INIT_DEFAULT;
	LDMA_Init(&ldmaInit);

	start_rx();
}


