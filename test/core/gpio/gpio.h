/*
 * gpio.h
 *
 *  Created on: Mar 13, 2015
 *      Author: Cody
 */

#ifndef CORE_GPIO_GPIO_H_
#define CORE_GPIO_GPIO_H_

//TODO: add single pin functions for IOCON


//#if defined(LPC11U6x)
#include "../../lpc11u6x.h"
//TODO: it would be nice to have a set of defines to get over each dir/port/pin register
//#else
//#error no configuration file selected
//#endif

#define 	INPUT		0
#define 	OUTPUT 		1

#define		HIGH		1
#define		LOW			0

#define		PORT0		0
#define		PORT1		1
#define		PORT2		2

//initialize GPIO pins
void gpioInit();

void gpioSetDir(uint32_t port, uint32_t value);
void gpioSetDirPin(uint32_t port, uint32_t pin, uint32_t direction);
uint32_t gpioGetDir(uint32_t port);
uint32_t gpioGetDirPin(uint32_t port, uint32_t pin);

void gpioSetPort(uint32_t port, uint32_t value);
uint32_t gpioGetPort(uint32_t port);
uint32_t gpioGetPin(uint32_t port, uint32_t pin);

void gpioSetMask(uint32_t port, uint32_t value);
void gpioSetMaskPin(uint32_t port, uint32_t pin, uint32_t value);
uint32_t gpioGetMask(uint32_t port);
uint32_t gpioGetMaskPin(uint32_t port, uint32_t pin, uint32_t value);

void gpioPinSet(uint32_t port, uint32_t pin);
void gpioSet(uint32_t port);

void gpioPinClr(uint32_t port, uint32_t pin);
void gpioClr(uint32_t port);

void gpioPinToggle(uint32_t port, uint32_t pin);
void gpioToggle(uint32_t port);


#endif /* CORE_GPIO_GPIO_H_ */
