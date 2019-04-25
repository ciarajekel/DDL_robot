/*
 * dma.h
 *
 *  Created on: Apr 4, 2019
 *      Author: amabo
 */

#ifndef SRC_DMA_H_
#define SRC_DMA_H_

#include "dma.h"
#include "main.h"
#include <stdint.h>

#define TX_DMA_CHANNEL 0
#define RX_DMA_CHANNEL 1

void dma_TX_init(char * string, uint32_t len);
void dma_init();
void start_rx();


#endif /* SRC_DMA_H_ */
