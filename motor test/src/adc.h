/*
 * adc.h
 *
 *  Created on: Apr 23, 2019
 *      Author: Ciara
 */

#ifndef SRC_ADC_H_
#define SRC_ADC_H_

#include "em_device.h"
#include "em_chip.h"
#include "em_core.h"
#include "em_cmu.h"
#include "em_adc.h"
#include "adc.h"

void adc_init(void);
void adc_gpio_init(void);

#define SENSOR_PORT		gpioPortA
#define SENSOR_PIN		3

#endif /* SRC_ADC_H_ */
