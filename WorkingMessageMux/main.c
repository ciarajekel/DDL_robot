/***************************************************************************//**
 * @file
 * @brief Simple LED Blink Demo for SLSTK3402A
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

#include <string.h>
#include <stdlib.h>


#include "em_device.h"
#include "em_core.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "bsp.h"
#include "main.h"
#include "gpio.h"
#include "cmu.h"
#include "letimer0.h"
#include "sleep.h"

#include "leuart.h"

#include "dma.h"

#include "msg.h"

extern uint8_t enable_si7021_flag;
extern uint8_t read_temp;
extern uint8_t message_flag;
extern uint8_t msg_in [RX_BUFFER_SIZE];


int main(void)
{
  EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_DEFAULT;
  CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_DEFAULT;

  /* Chip errata */
  CHIP_Init();

  /* Init DCDC regulator and HFXO with kit specific parameters */
  EMU_DCDCInit(&dcdcInit);
  CMU_HFXOInit(&hfxoInit);

  //Initialize DCDC in low-noise mode
  EMU_EM23Init_TypeDef em23Init = EMU_EM23INIT_DEFAULT;
  em23Init.vScaleEM23Voltage = emuVScaleEM23_LowPower;
  EMU_EM23Init(&em23Init);

  /* Switch HFCLK to HFXO and disable HFRCO */
  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
  CMU_OscillatorEnable(cmuOsc_HFRCO, false, false);

  /* Initialize clocks */
  cmu_init();

  /* Initialize GPIO */
  gpio_init();

  /* Initialize LETIMER0 according to values in *****MAIN.H*****/
  letimer0_init(1,5);

  //Global Interrupt Enable
  CORE_ATOMIC_IRQ_ENABLE();

  //BLOCK EM ACCORDING TO THE DEFINED VALUE IN ******MAIN.h*******
  Sleep_Block_Mode(LOWEST_ENERGY_MODE+1);

  //Initialize the LEUART0 peripheral
  leuart_init();

  //Initialize the ldma generally and enable reception
  dma_init();

  //Initialize the Hash table used for decoding
  build_hash();
#ifdef DEBUG
  //If the debug flag is defined,
  test_dec_msg();
#endif



  //Write the new name to the bluetooth
  //Add a delay loop to make sure everything is set up properly
  //for(int i = 0; i < 100000;i++);
  //leuart_write_string("AT+NAMEavan\n\r",13);

  //Malloc one large transmission string to communicate out with
  char * transm = (char *) malloc(sizeof(uint8_t)*100);



  //NOTE WRITE_FLAG IS SET IN LETIMER0 SO THE REGISTERIS CONFIGURED EVERY 3.5 SECONDS
  while (1){
	  //When the enable flag is raised(by the LETIMER interrupt), turn on the power gate
	  if(enable_si7021_flag){
		  enable_si7021_flag = 0;
	  }
	  //When the temperature read flag is raised(by LETIMER) read the temperature and calculate the ledop
	  if(read_temp){
		  dma_TX_init("1234567\n",8);
		  read_temp = 0;
	  }
	  if(message_flag){
		  //Our message is defined in the msg_in, check to see if it is a known command
		  int32_t dec = (decode_msg(msg_in));
		  //if(dec < 0){
			//  dma_TX_init("That was not a known command\n",29);
		  //}

		  double dist;
  		  char dist_s[5];
  		  transm[0] = '\0';

		  switch(dec){
		  	  case Move_Forward:
		  	      //Call the move forward function to go forward
		  		  dma_TX_init("Moving Forward\n",14);

		  		  break;
		  	  case  Move_Backward:
		  		  //Call the move forward function to go forward
		  		  dma_TX_init("Moving Backwards\n",16);

		  		  break;
		  	  case Stop:
		  		  //Stop whatever command is currently running
		  		  dma_TX_init("Stopping\n",8);
		  		  break;
		  	  case Turn_Left:
		  		  //Rotate to the left
		  		  dma_TX_init("Turning Left\n",13);

		  		  break;
		  	  case Turn_Right:
		  		  //Rotate to the right
		  		  dma_TX_init("Turning right\n",14);

		  		  break;
		  	  case Left_Distance:
		  		  //Find the distance to the left
		  		  dist = 5;
		  		  dist_f_2_a(dist_s, dist);

		  		  strcat(transm,"The left wall is ");
		  		  strcat(transm,dist_s);
		  		  strcat(transm,"cm away\n");

		  		  dma_TX_init(transm,29);
		  		  break;
		  	  case Right_Distance:
		  		  //Find the distance to the right
		  		  dist = 15;
		  		  dist_f_2_a(dist_s, dist);

		  		  strcat(transm,"The right wall is ");
		  		  strcat(transm,dist_s);
		  		  strcat(transm,"cm away\n");

		  		  dma_TX_init(transm,30);
		  		  break;
		  	  case Forward_Distance:
		  		  //Find the distance to the right
		  		  dist = 6.3;
		  		  dist_f_2_a(dist_s, dist);

		  		  strcat(transm,"The front wall is ");
		  		  strcat(transm,dist_s);
		  		  strcat(transm,"cm away\n");

		  		  dma_TX_init(transm,30);
		  		  break;
		  	  case Center:
		  		  dma_TX_init("Centering",9);

		  		  break;
		  	  case Solve:
		  		  dma_TX_init("Solving",7);

		  		  break;
		  	  default:
		  		  //The command was not recognized, tell that to the user
			  	  dma_TX_init("That was not a known command\n",29);
		  	  	  break;
		   }


		  message_flag = 0;
	  }
	  //If we aren't doing anything, just go to sleep
	  if((!read_temp) & (!enable_si7021_flag) & (!message_flag))
		  Enter_Sleep();
  }
}
