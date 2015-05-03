/*
 * usb_clock.h
 *
 *  Created on: Apr 6, 2015
 *      Author: Cody
 */

#ifndef CORE_USB_USB_CLOCK_H_
#define CORE_USB_USB_CLOCK_H_


/**
 * Clock sources for USB PLL
 */
typedef enum CHIP_SYSCTL_USBPLLCLKSRC {
	SYSCTL_USBPLLCLKSRC_IRC = 0,		/*!< Internal oscillator in */
	SYSCTL_USBPLLCLKSRC_MAINOSC,		/*!< Crystal (main) oscillator in */
	SYSCTL_USBPLLCLKSRC_SYSOSC = SYSCTL_USBPLLCLKSRC_MAINOSC,
	SYSCTL_USBPLLCLKSRC_RESERVED1,		/*!< Reserved */
	SYSCTL_USBPLLCLKSRC_RESERVED2,		/*!< Reserved */
} CHIP_SYSCTL_USBPLLCLKSRC_T;

/**
 * Clock sources for USB
 */
typedef enum CHIP_SYSCTL_USBCLKSRC {
	SYSCTL_USBCLKSRC_PLLOUT = 0,	/*!< USB PLL out */
	SYSCTL_USBCLKSRC_MAINSYSCLK,	/*!< Main system clock */
} CHIP_SYSCTL_USBCLKSRC_T;

void enableUSBClock();
void Chip_Clock_SetUSBPLLSource(CHIP_SYSCTL_USBPLLCLKSRC_T src);
void Chip_Clock_SetupUSBPLL(uint8_t msel, uint8_t psel);
void Chip_SYSCTL_PowerUp_USB(uint32_t powerupmask);
bool Chip_Clock_IsUSBPLLLocked(void);
void Chip_Clock_SetUSBClockSource(CHIP_SYSCTL_USBCLKSRC_T src, uint32_t div);
void Chip_Clock_EnablePeriphClock_USB(CHIP_SYSCTL_CLOCK_T clk);

#endif /* CORE_USB_USB_CLOCK_H_ */
