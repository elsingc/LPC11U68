/*
 * lpc11u68_clock.c
 *
 *  Created on: Apr 6, 2015
 *      Author: Cody
 */

#include "projectconfig.h"
#include "lpc11u68_clock.h"


/* System Clock Frequency (Core Clock) */
uint32_t SystemCoreClock;

/* Update system core clock rate, should be called if the system has
   a clock rate change */
void SystemCoreClockUpdate(void)
{
	/* CPU core speed */
	//TODO: fix system core clock update
	SystemCoreClock = 48000000;//Chip_Clock_GetSystemClockRate();
}

/* Return system clock rate */
//uint32_t Chip_Clock_GetSystemClockRate(void)
//{
//	/* No point in checking for divide by 0 */
//	return Chip_Clock_GetMainClockRate() / LPC_SYSCON->SYSAHBCLKDIV;
//}

/* Return main clock rate */
/*uint32_t Chip_Clock_GetMainClockRate(void)
{
	uint32_t clkRate = 0;

	switch ((CHIP_SYSCTL_MAINCLKSRC_T) (LPC_SYSCON->MAINCLKSEL & 0x3)) {
	case SYSCTL_MAINCLKSRC_IRC:
		clkRate = Chip_Clock_GetIntOscRate();
		break;

	case SYSCTL_MAINCLKSRC_PLLIN:
		clkRate = Chip_Clock_GetSystemPLLInClockRate();
		break;

	case SYSCTL_MAINCLKSRC_WDTOSC:
		clkRate = Chip_Clock_GetWDTOSCRate();
		break;

	case SYSCTL_MAINCLKSRC_PLLOUT:
		clkRate = Chip_Clock_GetSystemPLLOutClockRate();
		break;
	}

	return clkRate;
}*/

/*uint32_t Chip_Clock_GetIntOscRate(void)
{
	return SYSCTL_IRC_FREQ;
}

*/

/**
 * @brief	Enable a system or peripheral clock
 * @param	clk	: Clock to enable
 * @return	Nothing
 */
void Chip_Clock_EnablePeriphClock(CHIP_SYSCTL_CLOCK_T clk)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << clk);
}


/* Clock and PLL initialization based on the external oscillator */
void Chip_SetupXtalClocking(void)
{
	volatile int i;
#if defined(USE_ROM_API)
	uint32_t cmd[4], resp[2];
#endif

	/* Powerup main oscillator */
	Chip_SYSCTL_PowerUp(SYSCTL_POWERDOWN_SYSOSC_PD);

	/* Wait for at least 580uS for osc to stabilize */
	for (i = 0; i < 2500; i++) {}

	/* Set system PLL input to main oscillator */
	Chip_Clock_SetSystemPLLSource(SYSCTL_PLLCLKSRC_MAINOSC);

	/* Setup FLASH access to 2 clocks */
	Chip_FMC_SetFLASHAccess(FLASHTIM_2CLK_CPU);

#if defined(USE_ROM_API)
	/* Use ROM API for setting up PLL */
	cmd[0] = Chip_Clock_GetMainOscRate() / 1000;	/* in KHz */
	cmd[1] = 48000000 / 1000;	/* 48MHz system clock rate */
	cmd[2] = CPU_FREQ_EQU;
	cmd[3] = 48000000 / 10000;	/* Timeout */
	LPC_PWRD_API->set_pll(cmd, resp);

	/* Dead loop on fail */
	while (resp[0] != PLL_CMD_SUCCESS) {}
#else
	/* Power down PLL to change the PLL divider ratio */
	Chip_SYSCTL_PowerDown(SYSCTL_POWERDOWN_SYSPLL_PD);

	/* Setup PLL for main oscillator rate (FCLKIN = 12MHz) * 4 = 48MHz
	   MSEL = 3 (this is pre-decremented), PSEL = 1 (for P = 2)
	   FCLKOUT = FCLKIN * (MSEL + 1) = 12MHz * 4 = 48MHz
	   FCCO = FCLKOUT * 2 * P = 48MHz * 2 * 2 = 192MHz (within FCCO range) */
	Chip_Clock_SetupSystemPLL(3, 1);

	/* Powerup system PLL */
	Chip_SYSCTL_PowerUp(SYSCTL_POWERDOWN_SYSPLL_PD);

	/* Wait for PLL to lock */
	while (!Chip_Clock_IsSystemPLLLocked()) {}

	/* Set system clock divider to 1 */
	Chip_Clock_SetSysClockDiv(1);

	/* Set main clock source to the system PLL. This will drive 48MHz
	   for the main clock and 48MHz for the system clock */
	Chip_Clock_SetMainClockSource(SYSCTL_MAINCLKSRC_PLLOUT);
#endif
}

/**
 * @brief	Read System PLL lock status
 * @return	true of the PLL is locked. false if not locked
 */
bool Chip_Clock_IsSystemPLLLocked(void)
{
	return (bool) ((LPC_SYSCON->SYSPLLSTAT & 1) != 0);
}

/* Power up one or more blocks or peripherals */
void Chip_SYSCTL_PowerUp(uint32_t powerupmask)
{
	uint32_t pdrun;

	pdrun = LPC_SYSCON->PDRUNCFG & PDRUNCFGMASKTMP;
	pdrun &= ~(powerupmask & PDRUNCFGMASKTMP);

	LPC_SYSCON->PDRUNCFG = (pdrun | PDRUNCFGUSEMASK);
}


/* Set System PLL clock source */
void Chip_Clock_SetSystemPLLSource(CHIP_SYSCTL_PLLCLKSRC_T src)
{
	LPC_SYSCON->SYSPLLCLKSEL  = (uint32_t) src;
	LPC_SYSCON->SYSPLLCLKUEN  = 0;
	LPC_SYSCON->SYSPLLCLKUEN  = 1;
}

/**
 * @brief	Set FLASH access time in clocks
 * @param	clks	: Clock cycles for FLASH access (minus 1)
 * @return	Nothing
 */
void Chip_FMC_SetFLASHAccess(FMC_FLASHTIM_T clks)
{
	uint32_t tmp = LPC_FMC->FLASHTIM & (~(0x3));

	/* Don't alter upper bits */
	LPC_FMC->FLASHTIM = tmp | clks;
}


/* Power down one or more blocks or peripherals */
void Chip_SYSCTL_PowerDown(uint32_t powerdownmask)
{
	uint32_t pdrun;

	pdrun = LPC_SYSCON->PDRUNCFG & PDRUNCFGMASKTMP;
	pdrun |= (powerdownmask & PDRUNCFGMASKTMP);

	LPC_SYSCON->PDRUNCFG = (pdrun | PDRUNCFGUSEMASK);
}



/**
 * @brief	Set System PLL divider values
 * @param	msel    : PLL feedback divider value. M = msel + 1.
 * @param	psel    : PLL post divider value. P =  (1<<psel).
 * @return	Nothing
 * @note	See the user manual for how to setup the PLL.
 */
void Chip_Clock_SetupSystemPLL(uint8_t msel, uint8_t psel)
{
	LPC_SYSCON->SYSPLLCTRL = (msel & 0x1F) | ((psel & 0x3) << 5);
}


/**
 * @brief	Set system clock divider
 * @param	div	: divider for system clock
 * @return	Nothing
 * @note	Use 0 to disable, or a divider value of 1 to 255. The system clock
 * rate is the main system clock divided by this value.
 */
void Chip_Clock_SetSysClockDiv(uint32_t div)
{
	LPC_SYSCON->SYSAHBCLKDIV  = div;
}

/* Set main system clock source */
void Chip_Clock_SetMainClockSource(CHIP_SYSCTL_MAINCLKSRC_T src)
{
	LPC_SYSCON->MAINCLKSEL  = (uint32_t) src;
	LPC_SYSCON->MAINCLKUEN  = 0;
	LPC_SYSCON->MAINCLKUEN  = 1;
}

