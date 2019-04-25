#include "letimer0.h"
#include "main.h"
#include <em_letimer.h>
#include "gpio.h"

//Global flags to pass information from main to the letimer
uint8_t enable_si7021_flag;
uint8_t read_temp;

//LETIMER0 irq handler
void LETIMER0_IRQHandler(void){
	//Read Interrupt Flag
	int flag = LETIMER0->IF;

	//If COMP0, turn on the LED
	if(flag & LETIMER_IF_COMP1){
		enable_si7021_flag = 1;
		//GPIO_PinOutSet(LED0_port, LED0_pin);
		LETIMER0->IFC = LETIMER_IFC_COMP1;
	}
	//If COMP1 turn off the LED
	else if(flag & LETIMER_IF_UF){
		//GPIO_PinOutClear(LED0_port, LED0_pin);
		read_temp = 1;
		LETIMER0->IFC = LETIMER_IFC_UF;
	}
}

//This function initializes the LETIMER according to the period and on-time defined in main.h
void letimer0_init(double on, double period){
	//Initialize the divider level (prescalar value) to zero and store the equivalent power of two in divider amount
	int divider_level  = 0;
	int divider_amount = 1;

	//Calculate the current max period countable in the register, and compare it to that the requested
	while(period > (divider_amount * MAX_PERIOD))
	{
		divider_amount = 2 << divider_level;
		divider_level++;
	}

	//Calculate the fraction of the total possible period that we want
	int available_seconds = MAX_PERIOD*divider_amount;
	double on_fraction    = on/available_seconds;
	double total          = period/available_seconds;

	//The On  Count Value
	int count_ON     = LETIMER_MAX*on_fraction;
	//The Off Count Value
	int count_PERIOD = LETIMER_MAX*total - 1;

	LETIMER_CompareSet(LETIMER0, 0, count_PERIOD);
	LETIMER_CompareSet(LETIMER0, 1, count_ON    );

	CMU->LFAPRESC0 = divider_level;

	LETIMER0->CTRL = LETIMER_CTRL_COMP0TOP;
	LETIMER0->IFC  = LETIMER_IFC_COMP1 + LETIMER_IFC_UF;
	LETIMER0->IEN  = LETIMER_IEN_COMP1 + LETIMER_IEN_UF;

	LETIMER0->CMD |= LETIMER_CMD_START;
	NVIC_EnableIRQ(LETIMER0_IRQn);

}
