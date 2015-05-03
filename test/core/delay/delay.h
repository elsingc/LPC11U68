/*
 * delay.h
 *
 *  Created on: Mar 14, 2015
 *      Author: Cody
 */

#ifndef CORE_DELAY_DELAY_H_
#define CORE_DELAY_DELAY_H_


//#if defined(LPC11U6x)
#include "../../lpc11u6x.h"
//TODO: set it up to count every microsecond
//TODO: set it up to be able to provide millisecond based on microseconds
//TODO: seconds active would be awesome
//TODO: rollover detect for things like hearbeat
//#else
//#error no configuration file selected
//#endif


#define SYSTICK_SYS_CLK				0
#define SYSTICK_SYS_CLK_DIV_2		1

/*
---------------------------------------------------------------------------------
-----								bit positions							-----
---------------------------------------------------------------------------------
 */
#define SYSTICK_ENABLE_POS			0
#define SYSTICK_TICKINT_POS			1
#define SYSTICK_CLKSOURCE_POS		2
#define SYSTICK_COUNTFLAG_POS		16


void delayInit (void);
void delaySetClkSrc(uint32_t src);
void delayEnableInt();
void delayDisableInt();
void delay (uint32_t ticks);
uint32_t delayGetTicks(void);
void delaySetRelod(uint32_t ticks);
uint32_t delayCheckOverflow(void);

uint32_t delayGetRollovers(void);
uint32_t delayGetSecondsActive(void);


#endif /* CORE_DELAY_DELAY_H_ */
