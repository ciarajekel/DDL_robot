/*
 * motor.h
 *
 *  Created on: Apr 23, 2019
 *      Author: Ciara
 */

#ifndef SRC_MOTOR_H_
#define SRC_MOTOR_H_
#include "em_device.h"
#include "em_chip.h"
#include "em_core.h"
#include "timer.h"

/*
 DIR    PWM
 0       0      Stop
 1       0      Stop
 0       1     Forward
 1       1      Back
*/
#define SWITCH_MOTOR_SIDES 1

#if SWITCH_MOTOR_SIDES
#define RIGHT_MOTOR_DIR		6//TODO
#define LEFT_MOTOR_DIR		2//TODO
#define RIGHT_MOTOR_PWM		7//TODO
#define LEFT_MOTOR_PWM		3//TODO

#else
#define RIGHT_MOTOR_DIR		2//TODO
#define LEFT_MOTOR_DIR		0//TODO
#define RIGHT_MOTOR_PWM		3//TODO
#define LEFT_MOTOR_PWM		1//TODO
#endif
#define MOTOR_PORT		gpioPortF //TODO
#define MOTOR_DEFAULT	0
#define MOTOR_SPEED 	5000
#define MOTOR_MAX_SPEED	15000

void motor_gpio_init();
void robot_forward(void);
void robot_stop(void);
void robot_backward(void);
void robot_left(void);
void robot_right(void);


#endif /* SRC_MOTOR_H_ */
