/*
 * lpc11u6x.h
 *
 *  Created on: Mar 11, 2015
 *      Author: Cody
 */

#ifndef LPC11U6X_H_
#define LPC11U6X_H_


#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */


/**
 * Power down configuration values
 */
#define SYSCTL_POWERDOWN_IRCOUT_PD (1 << 0)		/*!< IRC oscillator output power down */
#define SYSCTL_POWERDOWN_IRC_PD    (1 << 1)		/*!< IRC oscillator power-down */
#define SYSCTL_POWERDOWN_FLASH_PD  (1 << 2)		/*!< Flash power down */
#define SYSCTL_POWERDOWN_BOD_PD    (1 << 3)		/*!< BOD power down */
#define SYSCTL_POWERDOWN_ADC_PD    (1 << 4)		/*!< ADC power down */
#define SYSCTL_POWERDOWN_SYSOSC_PD (1 << 5)		/*!< System oscillator power down */
#define SYSCTL_POWERDOWN_WDTOSC_PD (1 << 6)		/*!< Watchdog oscillator power down */
#define SYSCTL_POWERDOWN_SYSPLL_PD (1 << 7)		/*!< System PLL power down */
#define SYSCTL_POWERDOWN_USBPLL_PD (1 << 8)		/*!< USB PLL power-down */
#define SYSCTL_POWERDOWN_USBPAD_PD (1 << 10)	/*!< USB transceiver power-down */
#define SYSCTL_POWERDOWN_TS_PD     (1 << 13)	/*!< Temperature Sensor power-down */


/* PDRUNCFG register mask */
#define PDRUNCFGUSEMASK 0x0000C800
#define PDRUNCFGMASKTMP 0x000025FF

typedef unsigned long uint32_t;
//typedef unsigned int uint16_t;
typedef unsigned char uint8_t;

typedef int bool;
#define true 1
#define false 0

typedef volatile unsigned int * vp;

//#include "core/rom_api/rom_structs.h"

// ------------------------------------------------------------------------------------------------
// -----                                        SYSCON                                        -----
// ------------------------------------------------------------------------------------------------

typedef struct {                            /*!< (@ 0x40048000) SYSCON Structure       */
  __IO uint32_t SYSMEMREMAP;                /*!< (@ 0x40048000) System memory remap    */
  __IO uint32_t PRESETCTRL;                 /*!< (@ 0x40048004) Peripheral reset control */
  __IO uint32_t SYSPLLCTRL;                 /*!< (@ 0x40048008) System PLL control     */
  __I  uint32_t SYSPLLSTAT;                 /*!< (@ 0x4004800C) System PLL status      */
  __IO uint32_t USBPLLCTRL;                 /*!< (@ 0x40048010) USB PLL control        */
  __I  uint32_t USBPLLSTAT;                 /*!< (@ 0x40048014) USB PLL status         */
  __I  uint32_t RESERVED0[2];
  __IO uint32_t SYSOSCCTRL;                 /*!< (@ 0x40048020) System oscillator control */
  __IO uint32_t WDTOSCCTRL;                 /*!< (@ 0x40048024) Watchdog oscillator control */
  __I  uint32_t RESERVED1[2];
  __IO uint32_t SYSRSTSTAT;                 /*!< (@ 0x40048030) System reset status register */
  __I  uint32_t RESERVED2[3];
  __IO uint32_t SYSPLLCLKSEL;               /*!< (@ 0x40048040) System PLL clock source select */
  __IO uint32_t SYSPLLCLKUEN;               /*!< (@ 0x40048044) System PLL clock source update enable */
  __IO uint32_t USBPLLCLKSEL;               /*!< (@ 0x40048048) USB PLL clock source select */
  __IO uint32_t USBPLLCLKUEN;               /*!< (@ 0x4004804C) USB PLL clock source update enable */
  __I  uint32_t RESERVED3[8];
  __IO uint32_t MAINCLKSEL;                 /*!< (@ 0x40048070) Main clock source select */
  __IO uint32_t MAINCLKUEN;                 /*!< (@ 0x40048074) Main clock source update enable */
  __IO uint32_t SYSAHBCLKDIV;               /*!< (@ 0x40048078) System clock divider   */
  __I  uint32_t RESERVED4[1];
  __IO uint32_t SYSAHBCLKCTRL;              /*!< (@ 0x40048080) System clock control   */
  __I  uint32_t RESERVED5[4];
  __IO uint32_t SSP0CLKDIV;                 /*!< (@ 0x40048094) SSP0 clock divider     */
  __IO uint32_t UARTCLKDIV;                 /*!< (@ 0x40048098) UART clock divider     */
  __IO uint32_t SSP1CLKDIV;                 /*!< (@ 0x4004809C) SSP1 clock divider     */
  __I  uint32_t RESERVED6[8];
  __IO uint32_t USBCLKSEL;                  /*!< (@ 0x400480C0) USB clock source select */
  __IO uint32_t USBCLKUEN;                  /*!< (@ 0x400480C4) USB clock source update enable */
  __IO uint32_t USBCLKDIV;                  /*!< (@ 0x400480C8) USB clock source divider */
  __I  uint32_t RESERVED7[5];
  __IO uint32_t CLKOUTSEL;                  /*!< (@ 0x400480E0) CLKOUT clock source select */
  __IO uint32_t CLKOUTUEN;                  /*!< (@ 0x400480E4) CLKOUT clock source update enable */
  __IO uint32_t CLKOUTDIV;                  /*!< (@ 0x400480E8) CLKOUT clock divider   */
  __I  uint32_t RESERVED8[5];
  __I  uint32_t PIOPORCAP0;                 /*!< (@ 0x40048100) POR captured PIO status 0 */
  __I  uint32_t PIOPORCAP1;                 /*!< (@ 0x40048104) POR captured PIO status 1 */
  __I  uint32_t RESERVED9[18];
  __IO uint32_t BODCTRL;                    /*!< (@ 0x40048150) Brown-Out Detect       */
  __IO uint32_t SYSTCKCAL;                  /*!< (@ 0x40048154) System tick counter calibration */
  __I  uint32_t RESERVED10[6];
  __IO uint32_t IRQLATENCY;                 /*!< (@ 0x40048170) IQR delay */
  __IO uint32_t NMISRC;                     /*!< (@ 0x40048174) NMI Source Control     */
  __IO uint32_t PINTSEL[8];                 /*!< (@ 0x40048178) GPIO Pin Interrupt Select register 0 */
  __IO uint32_t USBCLKCTRL;                 /*!< (@ 0x40048198) USB clock control      */
  __I  uint32_t USBCLKST;                   /*!< (@ 0x4004819C) USB clock status       */
  __I  uint32_t RESERVED11[25];
  __IO uint32_t STARTERP0;                  /*!< (@ 0x40048204) Start logic 0 interrupt wake-up enable register 0 */
  __I  uint32_t RESERVED12[3];
  __IO uint32_t STARTERP1;                  /*!< (@ 0x40048214) Start logic 1 interrupt wake-up enable register 1 */
  __I  uint32_t RESERVED13[6];
  __IO uint32_t PDSLEEPCFG;                 /*!< (@ 0x40048230) Power-down states in deep-sleep mode */
  __IO uint32_t PDAWAKECFG;                 /*!< (@ 0x40048234) Power-down states for wake-up from deep-sleep */
  __IO uint32_t PDRUNCFG;                   /*!< (@ 0x40048238) Power configuration register */
  __I  uint32_t RESERVED14[110];
  __I  uint32_t DEVICE_ID;                  /*!< (@ 0x400483F4) Device ID              */
} LPC_SYSCON_Type;



// ------------------------------------------------------------------------------------------------
// -----                                        GPIO                                          -----
// ------------------------------------------------------------------------------------------------

typedef struct {
  union {
    struct {
      __IO uint8_t B0[32];                       /*!< (@ 0xA0000000) Byte pin registers port 0; pins PIO0_0 to PIO0_31 */
      __IO uint8_t B1[32];                       /*!< (@ 0xA0000020) Byte pin registers port 1 */
    };
    __IO uint8_t B[64];                       /*!< (@ 0xA0000000) Byte pin registers port 0/1 */
  };
  __I  uint32_t RESERVED0[1008];
  union {
    struct {
      __IO uint32_t W0[32];                      /*!< (@ 0xA0001000) Word pin registers port 0 */
      __IO uint32_t W1[32];                      /*!< (@ 0xA0001080) Word pin registers port 1 */
    };
    __IO uint32_t W[64];                       /*!< (@ 0xA0001000) Word pin registers port 0/1 */
  };
       uint32_t RESERVED1[960];
  __IO uint32_t DIR[2];			/* 0x2000 */
       uint32_t RESERVED2[30];
  __IO uint32_t MASK[2];		/* 0x2080 */
       uint32_t RESERVED3[30];
  __IO uint32_t PIN[2];			/* 0x2100 */
       uint32_t RESERVED4[30];
  __IO uint32_t MPIN[2];		/* 0x2180 */
       uint32_t RESERVED5[30];
  __IO uint32_t SET[2];			/* 0x2200 */
       uint32_t RESERVED6[30];
  __O  uint32_t CLR[2];			/* 0x2280 */
       uint32_t RESERVED7[30];
  __O  uint32_t NOT[2];			/* 0x2300 */
} LPC_GPIO_Type;

// ------------------------------------------------------------------------------------------------
// -----                                       IOCONFIG                                       -----
// ------------------------------------------------------------------------------------------------
//TODO: Verify IOCONFIG register maps
typedef struct {                            /*!< (@ 0x40044000) IOCONFIG Structure     */
  __IO uint32_t RESET_PIO0_0;               /*!< (@ 0x40044000) I/O configuration for pin RESET/PIO0_0 */
  __IO uint32_t PIO0_1;                     /*!< (@ 0x40044004) I/O configuration for pin PIO0_1/CLKOUT/CT32B0_MAT2/USB_FTOGGLE */
  __IO uint32_t PIO0_2;                     /*!< (@ 0x40044008) I/O configuration for pin PIO0_2/SSEL0/CT16B0_CAP0 */
  __IO uint32_t PIO0_3;                     /*!< (@ 0x4004400C) I/O configuration for pin PIO0_3/USB_VBUS */
  __IO uint32_t PIO0_4;                     /*!< (@ 0x40044010) I/O configuration for pin PIO0_4/SCL */
  __IO uint32_t PIO0_5;                     /*!< (@ 0x40044014) I/O configuration for pin PIO0_5/SDA */
  __IO uint32_t PIO0_6;                     /*!< (@ 0x40044018) I/O configuration for pin PIO0_6/USB_CONNECT/SCK0 */
  __IO uint32_t PIO0_7;                     /*!< (@ 0x4004401C) I/O configuration for pin PIO0_7/CTS */
  __IO uint32_t PIO0_8;                     /*!< (@ 0x40044020) I/O configuration for pin PIO0_8/MISO0/CT16B0_MAT0 */
  __IO uint32_t PIO0_9;                     /*!< (@ 0x40044024) I/O configuration for pin PIO0_9/MOSI0/CT16B0_MAT1 */
  __IO uint32_t SWCLK_PIO0_10;              /*!< (@ 0x40044028) I/O configuration for pin SWCLK/PIO0_10/ SCK0/CT16B0_MAT2 */
  __IO uint32_t TDI_PIO0_11;                /*!< (@ 0x4004402C) I/O configuration for pin TDI/PIO0_11/AD0/CT32B0_MAT3 */
  __IO uint32_t TMS_PIO0_12;                /*!< (@ 0x40044030) I/O configuration for pin TMS/PIO0_12/AD1/CT32B1_CAP0 */
  __IO uint32_t TDO_PIO0_13;                /*!< (@ 0x40044034) I/O configuration for pin TDO/PIO0_13/AD2/CT32B1_MAT0 */
  __IO uint32_t TRST_PIO0_14;               /*!< (@ 0x40044038) I/O configuration for pin TRST/PIO0_14/AD3/CT32B1_MAT1 */
  __IO uint32_t SWDIO_PIO0_15;              /*!< (@ 0x4004403C) I/O configuration for pin SWDIO/PIO0_15/AD4/CT32B1_MAT2 */
  __IO uint32_t PIO0_16;                    /*!< (@ 0x40044040) I/O configuration for pin PIO0_16/AD5/CT32B1_MAT3/ WAKEUP */
  __IO uint32_t PIO0_17;                    /*!< (@ 0x40044044) I/O configuration for pin PIO0_17/RTS/CT32B0_CAP0/SCLK */
  __IO uint32_t PIO0_18;                    /*!< (@ 0x40044048) I/O configuration for pin PIO0_18/RXD/CT32B0_MAT0 */
  __IO uint32_t PIO0_19;                    /*!< (@ 0x4004404C) I/O configuration for pin PIO0_19/TXD/CT32B0_MAT1 */
  __IO uint32_t PIO0_20;                    /*!< (@ 0x40044050) I/O configuration for pin PIO0_20/CT16B1_CAP0 */
  __IO uint32_t PIO0_21;                    /*!< (@ 0x40044054) I/O configuration for pin PIO0_21/CT16B1_MAT0/MOSI1 */
  __IO uint32_t PIO0_22;                    /*!< (@ 0x40044058) I/O configuration for pin PIO0_22/AD6/CT16B1_MAT1/MISO1 */
  __IO uint32_t PIO0_23;                    /*!< (@ 0x4004405C) I/O configuration for pin PIO0_23/AD7 */
  __IO uint32_t PIO1_0;                 /*!< Offset: 0x060 */
  __IO uint32_t PIO1_1;
  __IO uint32_t PIO1_2;
  __IO uint32_t PIO1_3;
  __IO uint32_t PIO1_4;                 /*!< Offset: 0x070 */
  __IO uint32_t PIO1_5;                     /*!< (@ 0x40044074) I/O configuration for pin PIO1_5/CT32B1_CAP1 */
  __IO uint32_t PIO1_6;
  __IO uint32_t PIO1_7;
  __IO uint32_t PIO1_8;                 /*!< Offset: 0x080 */
  __IO uint32_t PIO1_9;
  __IO uint32_t PIO1_10;
  __IO uint32_t PIO1_11;
  __IO uint32_t PIO1_12;                /*!< Offset: 0x090 */
  __IO uint32_t PIO1_13;                    /*!< (@ 0x40044094) I/O configuration for pin PIO1_13/DTR/CT16B0_MAT0/TXD */
  __IO uint32_t PIO1_14;                    /*!< (@ 0x40044098) I/O configuration for pin PIO1_14/DSR/CT16B0_MAT1/RXD */
  __IO uint32_t PIO1_15;                    /*!< (@ 0x4004409C) I/O configuration for pin PIO1_15/DCD/ CT16B0_MAT2/SCK1 */
  __IO uint32_t PIO1_16;                    /*!< (@ 0x400440A0) I/O configuration for pin PIO1_16/RI/CT16B0_CAP0 */
  __IO uint32_t PIO1_17;
  __IO uint32_t PIO1_18;
  __IO uint32_t PIO1_19;                    /*!< (@ 0x400440AC) I/O configuration for pin PIO1_19/DTR/SSEL1 */
  __IO uint32_t PIO1_20;                    /*!< (@ 0x400440B0) I/O configuration for pin PIO1_20/DSR/SCK1 */
  __IO uint32_t PIO1_21;                    /*!< (@ 0x400440B4) I/O configuration for pin PIO1_21/DCD/MISO1 */
  __IO uint32_t PIO1_22;                    /*!< (@ 0x400440B8) I/O configuration for pin PIO1_22/RI/MOSI1 */
  __IO uint32_t PIO1_23;                    /*!< (@ 0x400440BC) I/O configuration for pin PIO1_23/CT16B1_MAT1/SSEL1 */
  __IO uint32_t PIO1_24;                    /*!< (@ 0x400440C0) I/O configuration for pin PIO1_24/ CT32B0_MAT0 */
  __IO uint32_t PIO1_25;                    /*!< (@ 0x400440C4) I/O configuration for pin PIO1_25/CT32B0_MAT1 */
  __IO uint32_t PIO1_26;                    /*!< (@ 0x400440C8) I/O configuration for pin PIO1_26/CT32B0_MAT2/ RXD */
  __IO uint32_t PIO1_27;                    /*!< (@ 0x400440CC) I/O configuration for pin PIO1_27/CT32B0_MAT3/ TXD */
  __IO uint32_t PIO1_28;                    /*!< (@ 0x400440D0) I/O configuration for pin PIO1_28/CT32B0_CAP0/ SCLK */
  __IO uint32_t PIO1_29;                    /*!< (@ 0x400440D4) I/O configuration for pin PIO1_29/SCK0/ CT32B0_CAP1 */
  __IO uint32_t PIO1_30;
  __IO uint32_t PIO1_31;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t reserved_E0;
  __IO uint32_t reserved_E4;
  __IO uint32_t reserved_E8;
  __IO uint32_t reserved_EC;
  __IO uint32_t PIO2_0;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_1;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_2;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_3;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_4;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_5;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_6;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_7;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_8;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_9;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_10;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_11;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_12;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_13;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_14;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_15;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_16;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_17;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_18;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_19;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_20;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_21;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_22;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
  __IO uint32_t PIO2_23;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */

  //TODO: need to add the rest for port 2
  // PIO0_0 to PIO0_23 PIO1_0 to PIO1_31 PIO2_0 to PIO2_23
} LPC_IOCON_Type;


/**
 * @brief FLASH Access time definitions
 */
typedef enum {
	FLASHTIM_1CLK_CPU = 0,		/*!< Flash accesses use 1 CPU clocks */
	FLASHTIM_2CLK_CPU = 1,		/*!< Flash accesses use 2 CPU clocks */
} FMC_FLASHTIM_T;

//TODO: Add GPIO Group Int


// ------------------------------------------------------------------------------------------------
// -----                                        SysTick                                       -----
// ------------------------------------------------------------------------------------------------

typedef struct {
    uint32_t RESERVED1[4];
    __IO uint32_t SYST_CSR; 		//R/W 0x010 System Timer Control and status register 0x000 0000 Table 349
	__IO uint32_t SYST_RVR; 		//R/W 0x014 System Timer Reload value register 0 Table 350
	__IO uint32_t SYST_CVR; 		//R/W 0x018 System Timer Current value register 0 Table 351
	__IO uint32_t SYST_CALIB;		//R/W 0x01C System Timer Calibration value register 0x4
} LPC_SYSTICK_Type;


// ------------------------------------------------------------------------------------------------
// -----                                        Timer                                       -----
// ------------------------------------------------------------------------------------------------


/**
  * @brief Product name title=UM10462 Chapter title=LPC11U1x 32-bitcounter/timers CT32B0/1 Modification date=3/16/2011 Major revision=0 Minor revision=3
  */

typedef struct {                            /*!< (@ 0x40014000) CT32B0 Structure        */
  __IO uint32_t IR;                         /*!< (@ 0x40014000) Interrupt Register      */
  __IO uint32_t TCR;                        /*!< (@ 0x40014004) Timer Control Register  */
  __IO uint32_t TC;                         /*!< (@ 0x40014008) Timer Counter 		*/
  __IO uint32_t PR;                         /*!< (@ 0x4001400C) Prescale Register  	*/
  __IO uint32_t PC;                         /*!< (@ 0x40014010) Prescale Counter	 */
  __IO uint32_t MCR;                        /*!< (@ 0x40014014) Match Control Register */
  union {
  __IO uint32_t MR[4];                      /*!< (@ 0x40014018) Match Register */
  struct{
  __IO uint32_t MR0;                        /*!< (@ 0x40018018) Match Register. MR0 */
  __IO uint32_t MR1;                        /*!< (@ 0x4001801C) Match Register. MR1 */
  __IO uint32_t MR2;                        /*!< (@ 0x40018020) Match Register. MR2 */
  __IO uint32_t MR3;                        /*!< (@ 0x40018024) Match Register. MR3 */
  };
  };
  __IO uint32_t CCR;                        /*!< (@ 0x40014028) Capture Control Register */
  union{
  __I  uint32_t CR[4];                      /*!< (@ 0x4001402C) Capture Register  */
    struct{
  __I  uint32_t CR0;			    /*!< (@ 0x4001802C) Capture Register. CR 0 */
  __I  uint32_t CR1;			    /*!< (@ 0x40018030) Capture Register. CR 1 */
  __I  uint32_t CR2;			    /*!< (@ 0x40018034) Capture Register. CR 2 */
  __I  uint32_t CR3;			    /*!< (@ 0x40018038) Capture Register. CR 3 */
  };
  };
__IO uint32_t EMR;                        /*!< (@ 0x4001403C) External Match Register */
  __I  uint32_t RESERVED0[12];
  __IO uint32_t CTCR;                       /*!< (@ 0x40014070) Count Control Register */
  __IO uint32_t PWMC;                       /*!< (@ 0x40014074) PWM Control Register */
} LPC_CTxxBx_Type;

typedef struct {                            /*!< (@ 0x40080000) USB Structure          */
  __IO uint32_t DEVCMDSTAT;                 /*!< (@ 0x40080000) USB Device Command/Status register */
  __IO uint32_t INFO;                       /*!< (@ 0x40080004) USB Info register      */
  __IO uint32_t EPLISTSTART;                /*!< (@ 0x40080008) USB EP Command/Status List start address */
  __IO uint32_t DATABUFSTART;               /*!< (@ 0x4008000C) USB Data buffer start address */
  __IO uint32_t LPM;                        /*!< (@ 0x40080010) Link Power Management register */
  __IO uint32_t EPSKIP;                     /*!< (@ 0x40080014) USB Endpoint skip      */
  __IO uint32_t EPINUSE;                    /*!< (@ 0x40080018) USB Endpoint Buffer in use */
  __IO uint32_t EPBUFCFG;                   /*!< (@ 0x4008001C) USB Endpoint Buffer Configuration register */
  __IO uint32_t INTSTAT;                    /*!< (@ 0x40080020) USB interrupt status register */
  __IO uint32_t INTEN;                      /*!< (@ 0x40080024) USB interrupt enable register */
  __IO uint32_t INTSETSTAT;                 /*!< (@ 0x40080028) USB set interrupt status register */
  __IO uint32_t INTROUTING;                 /*!< (@ 0x4008002C) USB interrupt routing register */
  __I  uint32_t RESERVED0[1];
  __I  uint32_t EPTOGGLE;                   /*!< (@ 0x40080034) USB Endpoint toggle register */
} LPC_USB_Type;


typedef struct {		/*!< FMC Structure */
	__I  uint32_t  RESERVED1[4];
	__IO uint32_t  FLASHTIM;
	__I  uint32_t  RESERVED2[3];
	__IO uint32_t  FMSSTART;
	__IO uint32_t  FMSSTOP;
	__I  uint32_t  RESERVED3;
	__I  uint32_t  FMSW[1];
} LPC_FMC_T;


/** \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct
{
  __IO uint32_t ISER[1];                 /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register           */
       uint32_t RESERVED0[31];
  __IO uint32_t ICER[1];                 /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register          */
       uint32_t RSERVED1[31];
  __IO uint32_t ISPR[1];                 /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register           */
       uint32_t RESERVED2[31];
  __IO uint32_t ICPR[1];                 /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register         */
       uint32_t RESERVED3[31];
       uint32_t RESERVED4[64];
  __IO uint32_t IP[8];                   /*!< Offset: 0x300 (R/W)  Interrupt Priority Register              */
}  NVIC_Type;


// ------------------------------------------------------------------------------------------------
// -----                                 Peripheral memory map                                -----
// ------------------------------------------------------------------------------------------------

#define LPC_I2C_BASE              	(0x40000000)
#define LPC_WWDT_BASE             	(0x40004000)
#define LPC_USART_BASE            	(0x40008000)
#define LPC_CT16B0_BASE           	(0x4000C000)
#define LPC_CT16B1_BASE           	(0x40010000)
#define LPC_CT32B0_BASE           	(0x40014000)
#define LPC_CT32B1_BASE           	(0x40018000)
#define LPC_ADC_BASE              	(0x4001C000)
#define LPC_PMU_BASE              	(0x40038000)
#define LPC_FLASHCTRL_BASE        	(0x4003C000)
#define LPC_SSP0_BASE             	(0x40040000)
#define LPC_SSP1_BASE             	(0x40058000)
#define LPC_IOCON_BASE            	(0x40044000)
#define LPC_SYSCON_BASE           	(0x40048000)
#define LPC_GPIO_PIN_INT_BASE     	(0x4004C000)
#define LPC_GPIO_GROUP_INT0_BASE  	(0x4005C000)
#define LPC_GPIO_GROUP_INT1_BASE  	(0x40060000)
#define LPC_USB_BASE              	(0x40080000)
#define LPC_GPIO_BASE             	(0xA0000000)
#define LPC_SYSTICK_BASE			(0xE000E000)
#define LPC_FLASH_BASE           	(0x4003C000)

#define NVIC_BASE           (0xE000E100UL)                    /*!< NVIC Base Address                 */
// ------------------------------------------------------------------------------------------------
// -----                                Peripheral declaration                                -----
// ------------------------------------------------------------------------------------------------

#define LPC_I2C						((LPC_I2C_Type				*) LPC_I2C_BASE)
#define LPC_WWDT					((LPC_WWDT_Type           	*) LPC_WWDT_BASE)
#define LPC_USART					((LPC_USART_Type          	*) LPC_USART_BASE)
#define LPC_CT16B0					((LPC_CTxxBx_Type         	*) LPC_CT16B0_BASE)
#define LPC_CT16B1					((LPC_CTxxBx_Type         	*) LPC_CT16B1_BASE)
#define LPC_CT32B0					((LPC_CTxxBx_Type         	*) LPC_CT32B0_BASE)
#define LPC_CT32B1					((LPC_CTxxBx_Type         	*) LPC_CT32B1_BASE)
#define LPC_ADC						((LPC_ADC_Type            	*) LPC_ADC_BASE)
#define LPC_PMU						((LPC_PMU_Type            	*) LPC_PMU_BASE)
#define LPC_FLASHCTRL				((LPC_FLASHCTRL_Type      	*) LPC_FLASHCTRL_BASE)
#define LPC_SSP0					((LPC_SSPx_Type           	*) LPC_SSP0_BASE)
#define LPC_SSP1					((LPC_SSPx_Type           	*) LPC_SSP1_BASE)
#define LPC_IOCON					((LPC_IOCON_Type          	*) LPC_IOCON_BASE)
#define LPC_SYSCON					((LPC_SYSCON_Type         	*) LPC_SYSCON_BASE)
#define LPC_GPIO_PIN_INT			((LPC_GPIO_PIN_INT_Type   	*) LPC_GPIO_PIN_INT_BASE)
#define LPC_GPIO_GROUP_INT0			((LPC_GPIO_GROUP_INTx_Type	*) LPC_GPIO_GROUP_INT0_BASE)
#define LPC_GPIO_GROUP_INT1			((LPC_GPIO_GROUP_INTx_Type	*) LPC_GPIO_GROUP_INT1_BASE)
#define LPC_USB						((LPC_USB_Type            	*) LPC_USB_BASE)
#define LPC_GPIO					((LPC_GPIO_Type           	*) LPC_GPIO_BASE)
#define LPC_SYSTICK					((LPC_SYSTICK_Type			*) LPC_SYSTICK_BASE)
#define LPC_FMC                   	((LPC_FMC_T            		*) LPC_FLASH_BASE)

#define NVIC                		((NVIC_Type     			*) NVIC_BASE)   /*!< NVIC configuration struct          */
#endif /* LPC11U6X_H_ */
