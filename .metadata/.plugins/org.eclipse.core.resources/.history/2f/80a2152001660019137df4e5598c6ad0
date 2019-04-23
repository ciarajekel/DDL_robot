/*
 * motor.c
 *
 *  Created on: Apr 23, 2019
 *      Author: Ciara
 */

#include "motor.h"


void motor_gpio_init(){

	GPIO_DriveStrengthSet(MOTOR_PORT, gpioDriveStrengthWeakAlternateWeak);
	GPIO_PinModeSet(MOTOR_PORT, RIGHT_MOTOR_DIR, gpioModePushPull, MOTOR_DEFAULT);
	GPIO_PinModeSet(MOTOR_PORT, RIGHT_MOTOR_PWM, gpioModePushPull, MOTOR_DEFAULT);
	GPIO_PinModeSet(MOTOR_PORT, LEFT_MOTOR_DIR, gpioModePushPull, MOTOR_DEFAULT);
	GPIO_PinModeSet(MOTOR_PORT, LEFT_MOTOR_PWM, gpioModePushPull, MOTOR_DEFAULT);

}
//robot forward
void robot_forward(void){
	TIMER0->CMD = TIMER_CMD_START;
	GPIO_PinOutClear(MOTOR_PORT, RIGHT_MOTOR_DIR);
	GPIO_PinOutClear(MOTOR_PORT, LEFT_MOTOR_DIR);
	TIMER0->CC[0].CCV=MOTOR_SPEED;		//right //use to change value  < CC Channel Buffer Register
	TIMER0->CC[1].CCV=MOTOR_SPEED;		//left //use to change value  < CC Channel Buffer Register


}

//motor off
void robot_stop(void){
	TIMER0->CMD = TIMER_CMD_STOP;
	TIMER0->CC[0].CCV=0;	//right	//use to change value  < CC Channel Buffer Register
	TIMER0->CC[1].CCV=0;	//left	//use to change value  < CC Channel Buffer Register

//	GPIO_PinOutClear(MOTOR_PORT, RIGHT_MOTOR_PWM);
	GPIO_PinOutClear(MOTOR_PORT, RIGHT_MOTOR_DIR);
//	GPIO_PinOutClear(MOTOR_PORT, LEFT_MOTOR_PWM);
	GPIO_PinOutClear(MOTOR_PORT, LEFT_MOTOR_DIR);
}
//robot backward
void robot_backward(void){

//	GPIO_PinOutSet(MOTOR_PORT, RIGHT_MOTOR_PWM);
	GPIO_PinOutSet(MOTOR_PORT, RIGHT_MOTOR_DIR);
//	GPIO_PinOutSet(MOTOR_PORT, LEFT_MOTOR_PWM);
	GPIO_PinOutSet(MOTOR_PORT, LEFT_MOTOR_DIR);
}
//robot left
void robot_left(void){
//	GPIO_PinOutSet(MOTOR_PORT, RIGHT_MOTOR_PWM);
	GPIO_PinOutSet(MOTOR_PORT, RIGHT_MOTOR_DIR);
//	GPIO_PinOutSet(MOTOR_PORT, LEFT_MOTOR_PWM);
	GPIO_PinOutClear(MOTOR_PORT, LEFT_MOTOR_DIR);
}
//robot right
void robot_right(void){
//	GPIO_PinOutSet(MOTOR_PORT, RIGHT_MOTOR_PWM);
	GPIO_PinOutClear(MOTOR_PORT, RIGHT_MOTOR_DIR);
//	GPIO_PinOutSet(MOTOR_PORT, LEFT_MOTOR_PWM);
	GPIO_PinOutSet(MOTOR_PORT, LEFT_MOTOR_DIR);
}
