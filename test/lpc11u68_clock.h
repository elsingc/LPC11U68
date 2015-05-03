
/*
 * lpc11u68_clock.h
 *
 *  Created on: Apr 6, 2015
 *      Author: Cody
 */

#ifndef LPC11U68_CLOCK_H_
#define LPC11U68_CLOCK_H_


/**
 * System and peripheral clocks
 */
typedef enum CHIP_SYSCTL_CLOCK {
	SYSCTL_CLOCK_SYS = 0,				/*!< 0: System clock */
	SYSCTL_CLOCK_ROM,					/*!< 1:  ROM clock */
	SYSCTL_CLOCK_RAM0,					/*!< 2: RAM0 clock */
	SYSCTL_CLOCK_FLASHREG,				/*!< 3: FLASH register interface clock */
	SYSCTL_CLOCK_FLASHARRAY,			/*!< 4: FLASH array access clock */
	SYSCTL_CLOCK_I2C0,					/*!< 5: I2C0 clock */
	SYSCTL_CLOCK_GPIO,					/*!< 6: GPIO clock */
	SYSCTL_CLOCK_CT16B0,				/*!< 7: 16-bit Counter/timer 0 clock */
	SYSCTL_CLOCK_CT16B1,				/*!< 8: 16-bit Counter/timer 1 clock */
	SYSCTL_CLOCK_CT32B0,				/*!< 9: 32-bit Counter/timer 0 clock */
	SYSCTL_CLOCK_CT32B1,				/*!< 10: 32-bit Counter/timer 1 clock */
	SYSCTL_CLOCK_SSP0,					/*!< 11: SSP0 clock */
	SYSCTL_CLOCK_UART0,					/*!< 12: UART0 clock */
	SYSCTL_CLOCK_ADC,					/*!< 13: ADC clock */
	SYSCTL_CLOCK_USB,					/*!< 14: USB clock */
	SYSCTL_CLOCK_WDT,					/*!< 15: Watchdog timer clock */
	SYSCTL_CLOCK_IOCON,					/*!< 16: IOCON block clock */
	SYSCTL_CLOCK_RESERVED17,			/*!< 17: Reserved */
	SYSCTL_CLOCK_SSP1,					/*!< 18: SSP1 clock */
	SYSCTL_CLOCK_PINT,					/*!< 19: GPIO Pin int register interface clock */
	SYSCTL_CLOCK_USART1,				/*!< 20: USART1 clock */
	SYSCTL_CLOCK_USART2,				/*!< 21: USART2 clock */
	SYSCTL_CLOCK_USART3_4,				/*!< 22: USART3_4 clock */
	SYSCTL_CLOCK_P0INT,					/*!< 23: GPIO GROUP1 interrupt register clock */
	SYSCTL_CLOCK_GROUP0INT = SYSCTL_CLOCK_P0INT,/*!< 23: GPIO GROUP0 interrupt register interface clock */
	SYSCTL_CLOCK_P1INT,					/*!< 24: GPIO GROUP1 interrupt register clock */
	SYSCTL_CLOCK_GROUP1INT = SYSCTL_CLOCK_P1INT,/*!< 24: GPIO GROUP1 interrupt register interface clock */
	SYSCTL_CLOCK_I2C1,					/*!< 25: I2C1 clock */
	SYSCTL_CLOCK_RAM1,					/*!< 26: SRAM block clock */
	SYSCTL_CLOCK_USBRAM,				/*!< 27: USB SRAM block clock */
	SYSCTL_CLOCK_CRC,					/*!< 25: CRC clock */
	SYSCTL_CLOCK_DMA,					/*!< 25: DMA clock */
	SYSCTL_CLOCK_RTC,					/*!< 25: RTC clock */
	SYSCTL_CLOCK_SCT0_1,				/*!< 25: SCT 0/1 clock */
} CHIP_SYSCTL_CLOCK_T;


/**
 * Clock sources for system PLL
 */
typedef enum CHIP_SYSCTL_PLLCLKSRC {
	SYSCTL_PLLCLKSRC_IRC = 0,		/*!< Internal oscillator in */
	SYSCTL_PLLCLKSRC_MAINOSC,		/*!< Crystal (main) oscillator in */
	SYSCTL_PLLCLKSRC_SYSOSC = SYSCTL_PLLCLKSRC_MAINOSC,
	SYSCTL_PLLCLKSRC_RESERVED1,		/*!< Reserved */
	SYSCTL_PLLCLKSRC_RTC32K,		/*!< RTC 32KHz clock */
} CHIP_SYSCTL_PLLCLKSRC_T;


/**
 * Clock sources for main system clock
 */
typedef enum CHIP_SYSCTL_MAINCLKSRC {
	SYSCTL_MAINCLKSRC_IRC = 0,		/*!< Internal oscillator */
	SYSCTL_MAINCLKSRC_PLLIN,		/*!< System PLL input */
	SYSCTL_MAINCLKSRC_WDTOSC,		/*!< Watchdog oscillator rate */
	SYSCTL_MAINCLKSRC_PLLOUT,		/*!< System PLL output */
} CHIP_SYSCTL_MAINCLKSRC_T;


void SystemCoreClockUpdate(void);
uint32_t Chip_Clock_GetSystemClockRate(void);
uint32_t Chip_Clock_GetMainClockRate(void);

void Chip_Clock_EnablePeriphClock(CHIP_SYSCTL_CLOCK_T clk);
bool Chip_Clock_IsSystemPLLLocked(void);
void Chip_SetupXtalClocking(void);
void Chip_SYSCTL_PowerUp(uint32_t powerupmask);
void Chip_Clock_SetSystemPLLSource(CHIP_SYSCTL_PLLCLKSRC_T src);
void Chip_FMC_SetFLASHAccess(FMC_FLASHTIM_T clks);
void Chip_Clock_SetupSystemPLL(uint8_t msel, uint8_t psel);
void Chip_Clock_SetSysClockDiv(uint32_t div);
void Chip_Clock_SetMainClockSource(CHIP_SYSCTL_MAINCLKSRC_T src);
void Chip_SYSCTL_PowerDown(uint32_t powerdownmask);
#endif /* LPC11U68_CLOCK_H_ */
