/*
 * delay.c
 *
 *  Created on: Mar 14, 2015
 *      Author: Cody
 */

#include "delay.h"

void delayInit (void){
	//TODO: load the SYST RVR register so timer works
	delaySetRelod(10000000);		//setting it to rollover .1 seconds assuming 50mhz clock
	//enable the timer
	LPC_SYSTICK->SYST_CSR |= (1<<SYSTICK_ENABLE_POS);
}

void delaySetClkSrc(uint32_t src){
	if(src == SYSTICK_SYS_CLK){
		LPC_SYSTICK->SYST_CSR |= (1<<SYSTICK_CLKSOURCE_POS);
	}else{
		LPC_SYSTICK->SYST_CSR &= ~(1<<SYSTICK_CLKSOURCE_POS);
	}
}

void delayEnableInt(){
	LPC_SYSTICK->SYST_CSR |= (1<<SYSTICK_TICKINT_POS);
}

void delayDisableInt(){
	LPC_SYSTICK->SYST_CSR &= ~(1<<SYSTICK_TICKINT_POS);
}

void delay(uint32_t ticks){
	//TODO: implement
	uint32_t currentCount = delayGetTicks() + ticks;
	while(delayGetTicks()!= currentCount);

}

uint32_t delayGetTicks(void){
	return LPC_SYSTICK->SYST_CVR;
}

void delaySetRelod(uint32_t ticks){
	LPC_SYSTICK->SYST_RVR = ticks;
}

uint32_t delayCheckOverflow(void){
	return ((LPC_SYSTICK->SYST_CSR >> SYSTICK_ENABLE_POS) & 0x00000001);
}











//TODO: the below requires implementation of the interrupt
uint32_t delayGetRollovers(void){
	return ((LPC_SYSTICK->SYST_CSR >> SYSTICK_ENABLE_POS) & 0x00000001);
}

uint32_t delayGetSecondsActive(void){
	//TODO: implement
	//not sure how to implement this without using the interrupt
	return 0;
}

