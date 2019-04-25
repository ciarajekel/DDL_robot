/**************************************************************************//**
 * @file     sleep.h
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
#ifndef SRC_SLEEP_H_
#define SRC_SLEEP_H_

#include "main.h"

//Create an enum for each sleep state
typedef enum sleepState_enum{
	EM0_AWAKE,
	EM1_ASLEEP,
	EM2_DEEPSLEEP,
	EM3_STOP,
	EM4_HIBERNATE
}sleepState;
//Define the size of the enums
#define SLEEP_STATE_COUNT 5

//Function to block sleep modes, takes enumerated sleep mode to be blocked
void Sleep_Block_Mode(sleepState EMODE);
//Function to unblock sleep modes, takes enumerated sleep mode to be unlocked
void Sleep_UnBlock_Mode(sleepState EMODE);
//Function to enter the deepest enabled sleep mode
void Enter_Sleep(void);

#endif /* SRC_SLEEP_H_ */
