/*
 * msg.c
 *
 *  Created on: Apr 11, 2019
 *      Author: amabo
 */

#include "msg.h"

extern struct entry com_table[COM_SIZE];

//Initialize the buffer size to hold the full message +1 to include the start character
uint8_t rx_buf [RX_BUFFER_SIZE+1];
uint8_t msg_in [RX_BUFFER_SIZE];

//The official buffer of all commands.  In order to add a new command, add a new string, increment COM_SIZE and
//Add it to the appropriate place in the com_enum in msg.h
uint8_t cmds [COM_SIZE][RX_BUFFER_SIZE] = {
		"mfw",
		"mbw",
		"stp",
		"tul",
		"tur",
		"lef",
		"rig",
		"for",
		"cen",
		"sol"
};

//Our simple hashFunc adds the ascii codes of every char in our strings
int hashFunc(uint8_t * msg){
	int temp = 0;
	for (int i = 0; i < RX_BUFFER_SIZE; i ++){
		temp += msg[i];
	}
	return temp;
}

//Attempt to find the message in our dictionary of commands
//If a command is found return its enumerated value.
int32_t decode_msg(uint8_t * msg){
	int32_t key = hashFunc(msg);
	for(int i = 0; i < COM_SIZE; i++){
		if( com_table[i].key == key){
			return com_table[i].com;
		}
	}
	return -1;

}

//Constructor function to create a new entry for our hash table.  Takes the hash key and the corresponding command
//And returns the struct.
struct entry new_entry(uint32_t key, com com){
	struct entry new;
	new.key = key;
	new.com = com;
	return new;
}

//This function iterates through each commands and corresponding enums in our lists and initializes our dictionary
void build_hash(){
	for (int i = 0; i < COM_SIZE; i ++){
		uint32_t temp = hashFunc(cmds[i]);
		com_table[i]  = new_entry(temp,i);
	}
}

//If we are debugging, we also want to include a function that makes sure the tables were made without
//Any errors or collisions.  This function iterates through each command and calls decode before comparing
//To the expected enum.
#ifdef DEBUG
void test_dec_msg(){
	for(int i = 0; i < COM_SIZE; i++){
		uint8_t test = decode_msg(cmds[i]);
		if(test != i){
			while(1);
		}
	}
}
#endif
