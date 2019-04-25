/**************************************************************************//**
 * @file     sleep.c
 * @brief    File controlling EM Sleep modes
 * @version  V5.0.3
 * @date     16. January 2018
 ******************************************************************************/
/*
 * Copyright (c) 2009-2017 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdint.h>
#include "em_emu.h"
#include "sleep.h"
#include "em_device.h"
#include "em_core.h"
#include "em_emu.h"

//Counter to determine which sleep mode is blocked
volatile uint32_t sleep_block_counter[SLEEP_STATE_COUNT]= {0,0,0,0,0};

//Function to block the sleep mode for critical sections
//Takes in the sleepState enum being blocked/unblocked
void Sleep_Block_Mode(sleepState EMODE){
	CORE_ATOMIC_IRQ_DISABLE();
	sleep_block_counter[EMODE] += 1;
	CORE_ATOMIC_IRQ_ENABLE();
}

//Function to unblock the sleep mode at the end of critical sections
//Takes in the sleepState enum being blocked/unblocked
void Sleep_UnBlock_Mode(sleepState EMODE){
	CORE_ATOMIC_IRQ_DISABLE();
	if(EMODE > 0){
		sleep_block_counter[EMODE] -= 1;
	}
	CORE_ATOMIC_IRQ_ENABLE();
}

//Function to call the enter sleep functions
//Takes takes no inputs, but references global variable sleep_block_counter
void Enter_Sleep(void){
	if	   (sleep_block_counter[EM0_AWAKE]  > 0){
		//If we don't want to enter awake, stay awake?
		return;
	}
	else if(sleep_block_counter[EM1_ASLEEP] > 0){
		//If we can't enter EM1 sleep, stay awake
		return;
	}
	else if(sleep_block_counter[EM2_DEEPSLEEP] > 0){
		//If we can enter EM1, but not EM2, enter EM2
		EMU_EnterEM1();
	}
	else if(sleep_block_counter[EM3_STOP] > 0){
		//If we can enter EM2, but not EM3, enter EM2
		EMU_EnterEM2(true);
	}
	else{
		//If we can enter EM1, but not EM2, enter EM2
		EMU_EnterEM3(true);
	}
}
