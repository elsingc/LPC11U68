/*
 * gpio.c
 *
 *  Created on: Mar 13, 2015
 *      Author: Cody
 */

#include "gpio.h"

//initialize GPIO pins
//TEST:
void gpioInit(){
	  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
	  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);
}
//TEST:
void gpioSetDir(uint32_t port, uint32_t value){
	LPC_GPIO->DIR[port] = value;
}

void gpioSetDirPin(uint32_t port, uint32_t pin, uint32_t direction){
	if(direction){
		LPC_GPIO->DIR[port] |= (1<<pin);
	}else{
		LPC_GPIO->DIR[port] &= ~(1<<pin);
	}
}
//TEST:
uint32_t gpioGetDir(uint32_t port){
	return LPC_GPIO->DIR[port];
}
uint32_t gpioGetDirPin(uint32_t port, uint32_t pin){
	return (LPC_GPIO->DIR[port] >> pin) & 0x00000001;
}


//TEST:
void gpioSetPort(uint32_t port, uint32_t value){
	LPC_GPIO->PIN[port] = value;
}


//TEST:
uint32_t gpioGetPort(uint32_t port){
	return LPC_GPIO->PIN[port];
}

uint32_t gpioGetPin(uint32_t port, uint32_t pin){
	return ((LPC_GPIO->PIN[port]>>pin) & 0x00000001);
}

//TEST:
void gpioSetMask(uint32_t port, uint32_t value){
	LPC_GPIO->MASK[port] = value;
}
//TEST:
uint32_t gpioGetMask(uint32_t port){
	return LPC_GPIO->MASK[port];
}
//TEST:
void gpioPinMask(uint32_t port, uint32_t pin, uint32_t value){
	if(value){
		LPC_GPIO->DIR[port] |= (1<<pin);
	}else{
		LPC_GPIO->DIR[port] &= ~(1<<pin);
	}
}
//TEST:
void gpioPinSet(uint32_t port, uint32_t pin){
	LPC_GPIO->SET[port] = (1<<pin);
}

void gpioSet(uint32_t port){
	LPC_GPIO->SET[port] = 0xFFFFFFFF;
}

//TEST:
void gpioPinClr(uint32_t port, uint32_t pin){
	LPC_GPIO->CLR[port] = (1<<pin);
}

void gpioClr(uint32_t port){
	LPC_GPIO->CLR[port] = 0xFFFFFFFF;
}
//TEST:
void gpioPinToggle(uint32_t port, uint32_t pin){
	LPC_GPIO->NOT[port] = (1<<pin);
}

void gpioToggle(uint32_t port){
	LPC_GPIO->NOT[port] = 0xFFFFFFFF;
}

