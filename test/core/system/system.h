/*
 * sysclock.h
 *
 *  Created on: Mar 15, 2015
 *      Author: Cody
 */

#ifndef CORE_SYSTEM_SYSTEM_H_
#define CORE_SYSTEM_SYSTEM_H_


//#if defined(LPC11U6x)
#include "../../lpc11u6x.h"
#include "../../projectconfig.h"
//#else
//#error no configuration file selected
//#endif

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define		__XTAL					(12000000UL)		/* Oscillator frequency             */
#define		__SYS_OSC_CLK 			(__XTAL)			/* Main oscillator frequency        */
#define		__IRC_OSC_CLK			(12000000UL)		/* Internal RC oscillator frequency */
//#define	__SYSTEM_CLOCK			(__IRC_OSC_CLK)

//These defines handle the ock
#define		SYSPLL_INTERNAL 		0x0
#define		SYSPLL_EXTERNAL			0x1
#define		SYSPLL_RTC				0x3

//These defines handle the core clock
#define		CORECLOCK_INTERNAL		0x0
#define		CORECLOCK_PLL_INPUT		0x1
#define		CORECLOCK_WDT			0x2
#define		CORECLOCK_PLL_OUTPU		0x3


// PDRUNCFG bits and defines
#define		PDRUNCFG_MUST_WRITE		0x0000C800
#define		PDRUNCFG_IRCOUT_PD		0x00000001
#define		PDRUNCFG_IRC_PD			0x00000002
#define		PDRUNCFG_FLASH_PD		0x00000004
#define		PDRUNCFG_BOD_PD			0x00000008
#define		PDRUNCFG_ADC_PD			0x00000010
#define		PDRUNCFG_SYSOSC_PD		0x00000020
#define		PDRUNCFG_WDTOSC_PD		0x00000040
#define		PDRUNCFG_SYSPLL_PD		0x00000080
#define		PDRUNCFG_USBPLL_PD		0x00000100
#define		PDRUNCFG_USBPAD_PD		0x00000400
#define		PDRUNCFG_TEMPSENSE_PD	0x00002000


#define		PLL_DIV_ONE				0x00000000
#define		PLL_DIV_TWO				0x00000020
#define		PLL_DIV_FOUR			0x00000040
#define		PLL_DIV_EIGHT			0x00000050

//MAINCLKSEL bits and defines
#define		MAINCLKSEL_IRC			0x00000000
#define		MAINCLKSEL_PLL_INPUT	0x00000001
#define		MAINCLKSEL_WDT_OSC		0x00000002
#define		MAINCLKSEL_PLL_OUTPUT	0x00000003

#define		SYSOSCCTRL_NO_BYPASS	0x00000000
#define		SYSOSCCTRL_BYPASS		0x00000001
#define		SYSOSCCTRL_LOW_FREQ		0x00000000
#define		SYSOSCCTRL_HIGH_FREQ	0x00000002

//TODO: add defines for pll
//TODO: add usb clocking stuff stuff
//TODO: add wakeup configuration stuff
//TODO: #defines for watchdog timer
//TODO: setup rtc clock
//TODO: setup watchdog timer

/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void setupPLL();
void enableUSBClock();
void enableSysOsc();
void disableSysOsc();

void enablePLL();
void disablePLL();

void setClockPLLVal(uint32_t multiply, uint32_t divide);

void setPLLSrc(uint32_t pll);
void updatePLLClkSrc();


void setClockSource(uint32_t src);
void updateMainClkSrc();
uint32_t getClockSource();

uint32_t getClockPLL();
uint32_t getClockSpeed();



#endif /* CORE_SYSTEM_SYSTEM_H_ */
