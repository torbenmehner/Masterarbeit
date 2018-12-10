/*
 * ringbuffer.c
 *
 *  Created on: 28.10.2014
 *      Author: czimmer
 *      Beta taken from wiki
 *
 *      NOTE: when using the buffer with the EFM32LG the use of the buffer
 *      was causing some hard faults. It's not sure whether the problem relies in this
 *      implementation or in the libraries provided by Energy Micro that deal with
 *      memory management (or some conflict with another function).
 *
 */


#include "ringbuffer.h"

//deprecated, use FreeRTOS_StreamBuffer instead
