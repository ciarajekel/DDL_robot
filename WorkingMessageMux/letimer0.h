//***********************************************************************************
// Include files
//***********************************************************************************
#ifndef __LETIMER0_H__
#define __LETIMER0_H__


#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "sleep.h"
//***********************************************************************************
// defined files
//***********************************************************************************



//***********************************************************************************
// global variables
//***********************************************************************************
//The highest countable number in the LETIMER COUNT Register
#define LETIMER_MAX  65535

//THE PERIOD IN SECONDS WHEN USING DIFFERENT BASE CLOCKS
#if (LOWEST_ENERGY_MODE == 3)
#define MAX_PERIOD		  65.535
#else
#define MAX_PERIOD  	  2
#endif

//***********************************************************************************
// function prototypes
//***********************************************************************************
//Takes in on time and full period in milliseconds
void letimer0_init(double on, double period);

#endif
