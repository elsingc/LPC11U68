/*
 * sysclock.c
 *
 *  Created on: Mar 14, 2015
 *      Author: Cody
 */

#ifndef CORE_SYSCLOCK_SYSCLOCK_C_
#define CORE_SYSCLOCK_SYSCLOCK_C_
#include "system.h"
#include "../usb/usb_clock.h"

/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock2 = __IRC_OSC_CLK;		/*!< System Clock Frequency (Core Clock)*/ //start at irc i think //TODO: verify clock start speed
//uint32_t PLLClock = 0;

//TODO: System core clock update stuff, determines system clock
/* PDRUNCFG register mask */
#define PDRUNCFGUSEMASK 0x0000C800
#define PDRUNCFGMASKTMP 0x000025FF

void setupPLL(){

	//power up pll (enable?)
	enableSysOsc();

	//wait for changes to take effect
	for (int i = 0; i < 200; i++);// __NOP();

	//select pll input
	setPLLSrc(SYSPLL_INTERNAL);
	setClockPLLVal(3, PLL_DIV_TWO);
	enablePLL();
//TODO: wdt setup implement this in wdt init
#if (((MAINCLKSEL_Val & 0x03) == 2) )
  LPC_SYSCON->WDTOSCCTRL    = WDTOSCCTRL_Val;
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 6);          /* Power-up WDT Clock       */
  for (i = 0; i < 200; i++) __NOP();
#endif

  LPC_SYSCON->SYSAHBCLKDIV  = 1;

  //setClockSource(MAINCLKSEL_PLL_OUTPUT);
  //TODO: setup ahb clock divider here
  enableUSBClock();
}

void enableSysOsc(){
	LPC_SYSCON->PDRUNCFG &= ~(PDRUNCFG_SYSOSC_PD) | PDRUNCFG_MUST_WRITE;		/* Power-up System Osc      */
	LPC_SYSCON->SYSOSCCTRL = SYSOSCCTRL_NO_BYPASS | SYSOSCCTRL_LOW_FREQ;
}

void disableSysOsc(){
	LPC_SYSCON->PDRUNCFG |= (PDRUNCFG_SYSOSC_PD) | PDRUNCFG_MUST_WRITE;
}

//TODO: make non blocking, but make it return a system error
void enablePLL(){
	LPC_SYSCON->PDRUNCFG &= ~(PDRUNCFG_SYSPLL_PD) | PDRUNCFG_MUST_WRITE;		/* Power-up System Osc      */
	while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));	      							/* Wait Until PLL Locked    */
}

void disablePLL(){
	LPC_SYSCON->PDRUNCFG |= (PDRUNCFG_SYSPLL_PD) | PDRUNCFG_MUST_WRITE;
}

void setClockPLLVal(uint32_t multiply, uint32_t divide){
	LPC_SYSCON->SYSPLLCTRL = (multiply | divide);//SYSPLLCTRL_Val;
	LPC_SYSCON->PDRUNCFG &= ~(PDRUNCFG_SYSPLL_PD) | PDRUNCFG_MUST_WRITE;          /* Power-up SYSPLL          */
	while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));	      /* Wait Until PLL Locked    */
}

void setPLLSrc(uint32_t pll){
	LPC_SYSCON->SYSPLLCLKSEL  = pll;
	updatePLLClkSrc();
}

void updatePLLClkSrc(){
	LPC_SYSCON->SYSPLLCLKUEN  = 0x01;               /* Update Clock Source      */
	LPC_SYSCON->SYSPLLCLKUEN  = 0x00;               /* Toggle Update Register   */
	LPC_SYSCON->SYSPLLCLKUEN  = 0x01;
	while (!(LPC_SYSCON->SYSPLLCLKUEN & 0x01));     /* Wait Until Updated       */
}

uint32_t getClockPLL(){
	return 0;
}

uint32_t getClockSource(){
	return LPC_SYSCON->MAINCLKSEL;
}

uint32_t getClockSpeed(){
	return SystemCoreClock2;
}

void setClockSource(uint32_t src){
	LPC_SYSCON->MAINCLKSEL    = src;     /* Select PLL Clock Output  */
	updateMainClkSrc();
}

void updateMainClkSrc(){
	LPC_SYSCON->MAINCLKUEN    = 0x01;               /* Update MCLK Clock Source */
	LPC_SYSCON->MAINCLKUEN    = 0x00;               /* Toggle Update Register   */
	LPC_SYSCON->MAINCLKUEN    = 0x01;
	while (!(LPC_SYSCON->MAINCLKUEN & 0x01));       /* Wait Until Updated       */
}













































//#if ((USBCLKDIV_Val & 0x1FF) != 0)                /* USB clock is used        */
//  LPC_SYSCON->PDRUNCFG     &= ~(1 << 10);         /* Power-up USB PHY         */
//
//  /* Regardless USB PLL is used as USB clock or not, USB PLL needs to be configured. */
//  LPC_SYSCON->PDRUNCFG     &= ~(1 <<  8);         /* Power-up USB PLL         */
//  LPC_SYSCON->USBPLLCLKSEL  = USBPLLCLKSEL_Val;   /* Select PLL Input         */
//  LPC_SYSCON->USBPLLCLKUEN  = 0x01;               /* Update Clock Source      */
//  LPC_SYSCON->USBPLLCLKUEN  = 0x00;               /* Toggle Update Register   */
//  LPC_SYSCON->USBPLLCLKUEN  = 0x01;
//  while (!(LPC_SYSCON->USBPLLCLKUEN & 0x01));     /* Wait Until Updated       */
//  LPC_SYSCON->USBPLLCTRL    = USBPLLCTRL_Val;
//  while (!(LPC_SYSCON->USBPLLSTAT   & 0x01));     /* Wait Until PLL Locked    */
//
//  LPC_SYSCON->USBCLKSEL  = USBCLKSEL_Val;         /* Select USB Clock         */
//  LPC_SYSCON->USBCLKUEN  = 0x00;                  /* Toggle Update Register   */
//  LPC_SYSCON->USBCLKUEN  = 0x01;
//  LPC_SYSCON->USBCLKDIV  = USBCLKDIV_Val;         /* Set USB clock divider    */
//
//#if ((USBCLKSEL_Val & 0x003) != 0)
///* Wait for clock switch to happen */
//  for (i = 0; i < 200; i++) __NOP();
///* Turn-off USB PLL to save power */
//  LPC_SYSCON->PDRUNCFG     |=  (1 <<  8);         /* Power-down USB PLL       */
//#endif
//
//#else                                             /* USB clock is not used    */
//  LPC_SYSCON->PDRUNCFG     |=  (1 << 10);         /* Power-down USB PHY       */
//  LPC_SYSCON->PDRUNCFG     |=  (1 <<  8);         /* Power-down USB PLL       */
//#endif
//
//#endif


#endif /* CORE_SYSCLOCK_SYSCLOCK_C_ */
