//***********************************************************************************
// Include files
//***********************************************************************************
#include "cmu.h"
#include "main.h"
//***********************************************************************************
// defined files
//***********************************************************************************


//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// function prototypes
//***********************************************************************************
/*
 * Function to initialize all of the clock trees in the system
 */
void cmu_init(void){

		CMU_OscillatorEnable(cmuOsc_HFRCO, true, true);	// using LFXO or ULFRCO
		CMU_ClockSelectSet(cmuClock_HFPER, cmuSelect_HFRCO);
		CMU_ClockEnable(cmuClock_HFPER, true);


		// By default, LFRCO is enabled
		CMU_OscillatorEnable(cmuOsc_LFRCO, false, false);	// using LFXO or ULFRCO

		//Enable HFXO autostart
		CMU_HFXOAutostartEnable(true, false, false);

		//Enable LFXO clock branch
		CMU_OscillatorEnable(cmuOsc_LFXO, true, true);		// Disable LFXO

//Configure the clocks according to the current energy state
#if (LOWEST_ENERGY_MODE == 3)
		CMU_OscillatorEnable(cmuOsc_ULFRCO, true, true);
		CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_ULFRCO);	// routing clock to LFA

#else
		// Route LF clock to the LF clock tree
		CMU_OscillatorEnable(cmuOsc_ULFRCO, false, false);
		CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);	// routing clock to LFA
#endif

		//Connect the LFB clock to the LFXO
		CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);

		//Enable our clock trees
		CMU_ClockEnable(cmuClock_LFA, true);
		CMU_ClockEnable(cmuClock_LFB, true);
		CMU_ClockEnable(cmuClock_CORELE, true);


		// Peripheral clocks enabled
		CMU_ClockEnable(cmuClock_GPIO, true);
		CMU_ClockEnable(cmuClock_LETIMER0, true);
		CMU_ClockEnable(cmuClock_LEUART0, true);
		CMU_ClockEnable(cmuClock_LDMA, true);

}

