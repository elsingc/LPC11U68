/*
 * usb_clock.c
 *
 *  Created on: Apr 6, 2015
 *      Author: Cody
 */

#include "../../projectconfig.h"
#include "usb_clock.h"


void enableUSBClock(){
	/* Set USB PLL input to main oscillator */
	Chip_Clock_SetUSBPLLSource(SYSCTL_USBPLLCLKSRC_MAINOSC);
	/* Setup USB PLL  (FCLKIN = 12MHz) * 4 = 48MHz
	   MSEL = 3 (this is pre-decremented), PSEL = 1 (for P = 2)
	   FCLKOUT = FCLKIN * (MSEL + 1) = 12MHz * 4 = 48MHz
	   FCCO = FCLKOUT * 2 * P = 48MHz * 2 * 2 = 192MHz (within FCCO range) */
	Chip_Clock_SetupUSBPLL(3, 1);

	/* Powerup USB PLL */
	Chip_SYSCTL_PowerUp_USB(SYSCTL_POWERDOWN_USBPLL_PD);

	/* Wait for PLL to lock */
	while (!Chip_Clock_IsUSBPLLLocked()) {}

	/* enable USB main clock */
	Chip_Clock_SetUSBClockSource(SYSCTL_USBCLKSRC_PLLOUT, 1);
	/* Enable AHB clock to the USB block and USB RAM. */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_USB);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_USBRAM);
	/* power UP USB Phy */
	Chip_SYSCTL_PowerUp_USB(SYSCTL_POWERDOWN_USBPAD_PD);

}


/* Set USB PLL clock source */
void Chip_Clock_SetUSBPLLSource(CHIP_SYSCTL_USBPLLCLKSRC_T src)
{
	LPC_SYSCON->USBPLLCLKSEL  = (uint32_t) src;
	LPC_SYSCON->USBPLLCLKUEN  = 0;
	LPC_SYSCON->USBPLLCLKUEN  = 1;
}

/**
 * @brief	Set USB PLL divider values
 * @param	msel    : PLL feedback divider value. M = msel + 1.
 * @param	psel    : PLL post divider value. P = (1<<psel).
 * @return	Nothing
 * @note	See the user manual for how to setup the PLL.
 */
void Chip_Clock_SetupUSBPLL(uint8_t msel, uint8_t psel)
{
	LPC_SYSCON->USBPLLCTRL = (msel & 0x1F) | ((psel & 0x3) << 5);
}


/* Power up one or more blocks or peripherals */
void Chip_SYSCTL_PowerUp_USB(uint32_t powerupmask)
{
	uint32_t pdrun;

	pdrun = LPC_SYSCON->PDRUNCFG & PDRUNCFGMASKTMP;
	pdrun &= ~(powerupmask & PDRUNCFGMASKTMP);

	LPC_SYSCON->PDRUNCFG = (pdrun | PDRUNCFGUSEMASK);
}

/**
 * @brief	Read USB PLL lock status
 * @return	true of the PLL is locked. false if not locked
 */
bool Chip_Clock_IsUSBPLLLocked(void)
{
	return (bool) ((LPC_SYSCON->USBPLLSTAT & 1) != 0);
}

/* Set USB clock source and divider */
void Chip_Clock_SetUSBClockSource(CHIP_SYSCTL_USBCLKSRC_T src, uint32_t div)
{
	LPC_SYSCON->USBCLKSEL = (uint32_t) src;
	LPC_SYSCON->USBCLKUEN = 0;
	LPC_SYSCON->USBCLKUEN = 1;
	LPC_SYSCON->USBCLKDIV = div;
}

/**
 * @brief	Enable a system or peripheral clock
 * @param	clk	: Clock to enable
 * @return	Nothing
 */
void Chip_Clock_EnablePeriphClock_USB(CHIP_SYSCTL_CLOCK_T clk)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << clk);
}

