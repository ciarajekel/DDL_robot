/*
 * msg.h
 *
 *  Created on: Apr 11, 2019
 *      Author: amabo
 */

#ifndef SRC_MSG_H_
#define SRC_MSG_H_

#include <stdint.h>

//The defined message width is a constant three characters
#define RX_BUFFER_SIZE 			3

//The official count of commands in cmds.  Must be equal to cmds.length
#define COM_SIZE  				10


//Create an enum for received commands
typedef enum com_enum{
	Move_Forward,
	Move_Backward,
	Stop,
	Turn_Left,
	Turn_Right,
	Left_Distance,
	Right_Distance,
	Forward_Distance,
	Center,
	Solve
}com;

//Define the message, com dictionary entries
struct entry{
	uint32_t key;
	uint8_t com;
};

//Define the hash table
struct entry com_table[COM_SIZE];

//This is the function used to initialize the hash function
void build_hash();

//This is the function used to decode any RX_BUFFER_SIZE character string
int32_t decode_msg(uint8_t * msg);

//If we want to debug, we also need to define our debug function
#define DEBUG

#ifdef DEBUG
//This function goes through each attempted hash command and checks for collisions
void test_dec_msg();
#endif

#endif /* SRC_MSG_H_ */
