#include "timer.h"
#include "motor.h"

void timer0_init(void){
	TIMER_Init_TypeDef timer0settings = TIMER_INIT_DEFAULT;
//	timer0settings.enable=false;
	TIMER_Init(TIMER0,&timer0settings);

	TIMER0->TOP = MOTOR_MAX_SPEED; //TODO kinda arbitrary, should push as high as possible without seeing jerking on motors
	TIMER0->ROUTEPEN = TIMER_ROUTEPEN_CC1PEN | TIMER_ROUTEPEN_CC0PEN;     		/**< I/O Routing Pin Enable Register  */
	TIMER0->ROUTELOC0 = TIMER_ROUTELOC0_CC0LOC_LOC31 | TIMER_ROUTELOC0_CC1LOC_LOC26;			/**< I/O Routing Location Register  */
	/* right motor on cc0, left on cc1 */

	TIMER0->CC[0].CTRL = TIMER_CC_CTRL_MODE_PWM;		/**< CC Channel Control Register  */
	TIMER0->CC[0].CCV = 0;			/**< CC Channel Value Register  */

	TIMER0->CC[1].CTRL = TIMER_CC_CTRL_MODE_PWM;		/**< CC Channel Control Register  */
	TIMER0->CC[1].CCV = 0;			/**< CC Channel Value Register  */

}
/*
 *
 *


	TIMER0->CC[0]->CCVB;		//use to change value  < CC Channel Buffer Register
	TIMER0->CC[1]->CCVB;		//use to change value  < CC Channel Buffer Register

 */
