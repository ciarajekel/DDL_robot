//***********************************************************************************
// Include files
//***********************************************************************************
#include "gpio.h"

//***********************************************************************************
// defined files
//***********************************************************************************


//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// function prototypes
//***********************************************************************************


//***********************************************************************************
// functions
//***********************************************************************************
//Function to initialize all of the gpio pins in the system
void gpio_init(void){

	// Set LED ports to be standard output drive with default off (cleared)
	GPIO_DriveStrengthSet(LED0_port, gpioDriveStrengthStrongAlternateStrong);
	GPIO_PinModeSet(LED0_port, LED0_pin, gpioModePushPull, LED0_default);

	GPIO_DriveStrengthSet(LED1_port, gpioDriveStrengthStrongAlternateStrong);
	GPIO_PinModeSet(LED1_port, LED1_pin, gpioModePushPull, LED1_default);

	GPIO_DriveStrengthSet(I2C_GATE_PORT, gpioDriveStrengthStrongAlternateStrong);
	GPIO_PinModeSet(I2C_GATE_PORT, I2C_GATE_PIN, gpioModePushPull, I2C_GATE_DEFAULT);

	//Enable the LEUART Pins for Bluetooth
	GPIO_PinModeSet(LEUART_RX_PORT, LEUART_RX_PIN, gpioModeInput, LEUART_RX_DEFAULT);

	GPIO_DriveStrengthSet(LEUART_TX_PORT, gpioDriveStrengthWeakAlternateWeak);
	GPIO_PinModeSet(LEUART_TX_PORT, LEUART_TX_PIN, gpioModePushPull, LEUART_TX_DEFAULT);

}
