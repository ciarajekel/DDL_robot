//***********************************************************************************
// Include files
//***********************************************************************************
#ifndef __GPIO_H__
#define __GPIO_H__

#include "main.h"
#include "em_gpio.h"

//***********************************************************************************
// defined files
//***********************************************************************************

// LED0 pin is
#define	LED0_port		gpioPortF
#define LED0_pin		4
#define LED0_default	false 	// off
// LED1 pin is
#define LED1_port		gpioPortF
#define LED1_pin		5
#define LED1_default	false	// off

//SDA Pin Definitions
#define I2C_SDA_PORT		gpioPortC
#define I2C_SDA_PIN			10
#define I2C_SDA_DEFAULT		true

//SCL Pin Definitions
#define I2C_SCL_PORT		gpioPortC
#define I2C_SCL_PIN			11
#define I2C_SCL_DEFAULT		true

//I2C Sensor_Gate GPIO
#define I2C_GATE_PORT		gpioPortB
#define I2C_GATE_PIN		10
#define I2C_GATE_DEFAULT	false

//Define the RX for LEUART
#define LEUART_RX_PORT		gpioPortD
#define LEUART_RX_PIN		11
#define LEUART_RX_DEFAULT	true

//Define the TX for LEUART
#define LEUART_TX_PORT		gpioPortD
#define LEUART_TX_PIN		10
#define LEUART_TX_DEFAULT	true




//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// function prototypes
//***********************************************************************************
//Function to initialize all of the gpio pins in the system
void gpio_init(void);

#endif

