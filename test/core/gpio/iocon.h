/*
 * iocon.h
 *
 *  Created on: Apr 6, 2015
 *      Author: Cody
 */

#ifndef CORE_GPIO_IOCON_H_
#define CORE_GPIO_IOCON_H_

#include "../../projectconfig.h"

/**
 * @brief Array of IOCON pin definitions passed to Chip_IOCON_SetPinMuxing() must be in this format
 */
typedef struct {
	uint32_t port : 8;			/* Pin port */
	uint32_t pin : 8;			/* Pin number */
	uint32_t modefunc : 16;		/* Function and mode */
} PINMUX_GRP_Type;


/**
 * @brief LPC11u6x IO Configuration Unit register block structure
 */
typedef struct {			/*!< LPC11U6X IOCON Structure */
	__IO uint32_t  PIO0[24];
	__IO uint32_t  PIO1[32];
	__I  uint32_t  reserved[4];
	__IO uint32_t  PIO2A[2];/* PIO2_0/1 only */
	__I  uint32_t  reserved1[1];
	__IO uint32_t  PIO2B[22];	/* PIO2_2 to PIO_2_23 */
}  LPC_IOCON_Type_fix;
#define LPC_IOCON_BASE_fix            	(0x40044000)
#define LPC_IOCON_fix					((LPC_IOCON_Type_fix          	*) LPC_IOCON_BASE_fix)


//TODO:------------fix all below this line, it needs to be defined per the cmsis stuff-----------

/**
 * IOCON function and mode selection definitions
 * See the User Manual for specific modes and functions supported by the
 * various LPC11u6x pins.
 */
#define IOCON_FUNC0             0x0				/*!< Selects pin function 0 */
#define IOCON_FUNC1             0x1				/*!< Selects pin function 1 */
#define IOCON_FUNC2             0x2				/*!< Selects pin function 2 */
#define IOCON_FUNC3             0x3				/*!< Selects pin function 3 */
#define IOCON_FUNC4             0x4				/*!< Selects pin function 4 */
#define IOCON_FUNC5             0x5				/*!< Selects pin function 5 */
#define IOCON_FUNC6             0x6				/*!< Selects pin function 6 */
#define IOCON_FUNC7             0x7				/*!< Selects pin function 7 */
#define IOCON_MODE_INACT        (0x0 << 3)		/*!< No addition pin function */
#define IOCON_MODE_PULLDOWN     (0x1 << 3)		/*!< Selects pull-down function */
#define IOCON_MODE_PULLUP       (0x2 << 3)		/*!< Selects pull-up function */
#define IOCON_MODE_REPEATER     (0x3 << 3)		/*!< Selects pin repeater function */
#define IOCON_HYS_EN            (0x1 << 5)		/*!< Enables hysteresis */
#define IOCON_INV_EN            (0x1 << 6)		/*!< Enables invert function on input */
#define IOCON_ADMODE_EN         (0x0 << 7)		/*!< Enables analog input function (analog pins only) */
#define IOCON_DIGMODE_EN        (0x1 << 7)		/*!< Enables digital function (analog pins only) */
#define IOCON_SFI2C_EN          (0x0 << 8)		/*!< I2C standard mode/fast-mode */
#define IOCON_STDI2C_EN         (0x1 << 8)		/*!< I2C standard I/O functionality */
#define IOCON_FASTI2C_EN        (0x2 << 8)		/*!< I2C Fast-mode Plus */
#define IOCON_FILT_DIS          (0x1 << 8)		/*!< Disables noise pulses filtering (10nS glitch filter) */
#define IOCON_OPENDRAIN_EN      (0x1 << 10)		/*!< Enables open-drain function */
#define IOCON_S_MODE_0CLK       (0x0 << 11)		/*!< Bypass input filter */
#define IOCON_S_MODE_1CLK       (0x1 << 11)		/*!< Input pulses shorter than 1 filter clock are rejected */
#define IOCON_S_MODE_2CLK       (0x2 << 11)		/*!< Input pulses shorter than 2 filter clock2 are rejected */
#define IOCON_S_MODE_3CLK       (0x3 << 11)		/*!< Input pulses shorter than 3 filter clock2 are rejected */
#define IOCON_S_MODE(clks)      ((clks) << 11)	/*!< Select clocks for digital input filter mode */
#define IOCON_CLKDIV(div)       ((div) << 13)	/*!< Select peripheral clock divider for input filter sampling clock, 0 -6 */


/* Pin muxing table, only items that need changing from their default pin
   state are in this table. Not every pin is mapped. */
static const PINMUX_GRP_Type pinmuxing[] = {
	/* LPCXpresso pin			- Base board function		- Mapped function */
	/* RESET-PIO0_0				- PIO/RESET (pin 4)			- Reset */
	/* PIO0_1-ISP_EN			- PIO (pin 51)				- GPIO input */
	/* PIO0_2-SSP0_SSEL			- PIO/SSEL (pin 8)			- GPIO output for SSP0 CS */
	/* PIO0_3-VBUS				-                           - USB VBUS */
	{0, 3,  (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO0_4-I2C_SCL			- PIO/I2C-SCL (pin 41)		- I2C0 SCL */
	{0, 4,  (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO0_5-I2C_SDA			- PIO/I2C-SDA (pin 40)		- I2C0 SDA */
	{0, 5,  (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO0_6					-                           - GPIO */
	/* PIO0_7					- PIO (pin 11)				- GPIO */
	/* PIO0_8-SSP0_MISO			- PIO/MISO (pin 6)			- SSP0 MISO */
	{0, 8,  (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO0_9-SSP0_MOSI			- PIO/MOSI (pin 5)			- SSP0 MOSI */
	{0, 9,  (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* SWCLK-PIO0_10			-                           - SWCLK */
	/* PIO0_11-ADC_9			- PIO/AD5 (pin 20)			- ADC_9 */
	{0, 11, (IOCON_FUNC2 | IOCON_MODE_INACT)},
	/* PIO0_12-ADC_8			- PIO/AD4/SWDIO (pin 19)	- ADC_8 */
	{0, 12, (IOCON_FUNC2 | IOCON_MODE_INACT)},
	/* PIO0_13-ADC_7			- PIO/AD3 (pin 18)			- ADC_7 */
	{0, 13, (IOCON_FUNC2 | IOCON_MODE_INACT)},
	/* PIO0_14-ADC_6			- PIO/AD2 (pin 17)			- ADC_6 */
	{0, 14, (IOCON_FUNC2 | IOCON_MODE_INACT)},
	/* PIO0_16-WAKEUP			-                           - GPIO input */
	/* PIO0_17					- PIO (pin 12)				- GPIO */
	/* TO_MUX_PIO0_18-ISP_RX	- PIO/RXD (pin 10)			- UART0 RX */
	{0, 18, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO0_19-ISP_TX			- PIO/TXD (pin 9)			- UART0 TX */
	{0, 19, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO0_20					- PIO (pin 13)				- GPIO */
	/* PIO0_21					- PIO (pin 14)				- GPIO */
	/* PIO0_22					- PIO (pin 21)				- GPIO */
	/* PIO0_23-ADC_1			- PIO/AD1 (pin 16)			- ADC_1 */
	{0, 23, (IOCON_FUNC1 | IOCON_MODE_INACT)},
	/* PIO1_0					- PIO (pin 22)				- GPIO */
	/* PIO1_1					- PIO/USB_CONNECT (pin 23)	- GPIO */
	/* PIO1_2					- PIO/SWCLK (pin 24)		- SWCLK */
	/* PIO1_3					- PIO (pin 25)				- GPIO */
	/* PIO1_4					- PIO (pin 26)				- GPIO */
	/* PIO1_5					- PIO (pin 27)				- GPIO */
	/* PIO1_6					- PIO (pin 53)				- GPIO */
	/* PIO1_7					- PIO (pin 52)				- GPIO */
	/* PIO1_8					- PIO (pin 50)				- GPIO */
	/* PIO1_9-ADC_0				- PIO/AD0 (pin 15)			- ADC_0 */
	{1, 9,  (IOCON_FUNC1 | IOCON_MODE_INACT)},
	/* PIO1_10					- PIO (pin 49)				- GPIO */
	/* PIO1_11-I2C1_SCL			-                           - I2C1 SCL */
	{1, 11, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_12					- PIO/USB_VBUS (pin 39)		- GPIO input */
	/* PIO1_13					- PIO (pin 38)				- GPIO output */
	/* PIO1_14-I2C_SDA			-                           - I2C SDA */
	{1, 14, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_15					- PIO (pin 48)				- GPIO */
	/* PIO1_16					-                           - GPIO */
	/* PIO1_17					-                           - GPIO */
	/* PIO1_18					-                           - GPIO input, with pullup */
	/* PIO1_19					-                           - GPIO */
	/* PIO1_20-SSP1_SCK			-                           - SSP1 CLK */
	{1, 20, (IOCON_FUNC2 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_21-SSP1_MISO		-                           - SSP1 MISO */
	{1, 21, (IOCON_FUNC2 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_22-SSP1_MOSI		-                           - SSP1 MOSI */
	{1, 22, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_23-SSP1_SSEL		-                           - SSP1 SSEL */
	{1, 23, (IOCON_FUNC2 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_24-CT32B0_MAT0		-                           - GPIO input, with pullup */
	/* PIO1_25					-                           - GPIO */
	/* PIO1_26-CT32B0_MAT2		-                           - CT32B0_MAT2 */
	{1, 26, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_27-CT32B0_MAT3		-                           - CT32B0_MAT3 */
	{1, 27, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_28					-                           - GPIO */
	/* PIO1_29-SSP0_SCK			- PIO/SCK (pin 7)			- SSP0 CLK */
	{1, 29, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_30					-                           - GPIO */
	/* PIO1_31					-                           - GPIO */
	/* PIO2_0					-                           - XTALIN */
	{2, 0,  (IOCON_FUNC1 | IOCON_MODE_INACT)},
	/* PIO2_1					-                           - XTALOUT */
	{2, 1,  (IOCON_FUNC1 | IOCON_MODE_INACT)},
	/* PIO2_2-SCT0_OUT1			- PIO (pin 46)				- GPIO */
	/* PIO2_3-CT32B0_MAT1		-                           - CT32B0_MAT1 */
	{2, 3,  (IOCON_FUNC2 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO2_4					-                           - GPIO */
	/* PIO2_5					-                           - GPIO */
	/* PIO2_6					-                           - GPIO */
	/* PIO2_7-SCT0_OUT2			- PIO (pin 47)				- GPIO */
	/* PIO2_8					-                           - GPIO */
	/* PIO2_9					-                           - GPIO */
	/* PIO2_10					-                           - GPIO */
	/* PIO2_11					-                           - GPIO */
	/* PIO2_12					-                           - GPIO */
	/* PIO2_13					-                           - GPIO */
	/* PIO2_14					-                           - GPIO */
	/* PIO2_15					-                           - GPIO */
	/* PIO2_16-SCT1_OUT0		- PIO/MAT=PWM (pin 42)		- LED1 GREEN */
	/* PIO2_17-SCT1_OUT1		- PIO/MAT=PWM (pin 43)		- LED0 RED */
	/* PIO2_18-SCT1_OUT2		- PIO (pin 44)				- LED2 BLUE */
	/* PIO2_19-SCT1_OUT3		- PIO (pin 45)				- GPIO */
	/* PIO2_20					-                           - GPIO */
	/* PIO2_21					-                           - GPIO */
	/* PIO2_22					-                           - GPIO */
	/* PIO2_23					-                           - GPIO */
};

void Chip_IOCON_SetPinMuxing(LPC_IOCON_Type_fix *pIOCON, const PINMUX_GRP_Type* pinArray, uint32_t arrayLength);
void Chip_IOCON_PinMuxSet(LPC_IOCON_Type_fix *pIOCON, uint8_t port, uint8_t pin, uint32_t modefunc);


#endif /* CORE_GPIO_IOCON_H_ */
