/*
 * leuart.h
 *
 *  Created on: Feb 26, 2019
 *      Author: amabo
 */

#ifndef SRC_LEUART_H_
#define SRC_LEUART_H_

#include <stdint.h>

#define	LEUART0_BAUD_RATE		9600

/*
 * Initialize the LEUART0 to communicate with the bluetooth module
 * It takes no inputs, and only serves to configure the peripheral registers
 */
void leuart_init();

/*
 * Write a single byte bit over the UART Connection
 */
void leuart_write_byte(uint8_t byte);

/*
 * Transmit a string over UART
 * Input: string to be transmitted
 */
void leuart_write_string(uint8_t * msg,uint32_t length);

//Convert the distance in centimeters to a four character float 'X.X'
void dist_f_2_a(char * str, double dist);

#endif /* SRC_LEUART_H_ */
