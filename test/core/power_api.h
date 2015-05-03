/*
 * power_api.h
 *
 *  Created on: Mar 28, 2015
 *      Author: Cody
 */

#ifndef CORE_POWER_API_H_
#define CORE_POWER_API_H_


#ifdef __cplusplus
 extern "C" {
#endif

//#include "usb/romdriver/mw_usbd_rom_api.h"
#include "usb/romdriver/mw_usbd_rom_api.h"
typedef	struct _PWRD {
  void (*set_pll)(unsigned int cmd[], unsigned int resp[]);
  void (*set_power)(unsigned int cmd[], unsigned int resp[]);
}  PWRD;



typedef	struct _ROM {
   USBD_API_T * pUSBD;
   const unsigned p_clib;
   const unsigned p_cand;
   const PWRD * pPWRD;
   const unsigned p_dev1;
   const unsigned p_dev2;
   const unsigned p_dev3;
   const unsigned p_dev4;
}  ROM;


/* Pointer to ROM API function address */
#define LPC_ROM_API_BASE_LOC	0x1FFF1FF8
#define LPC_ROM_API		(*(ROM * *) LPC_ROM_API_BASE_LOC)

//PLL setup related definitions
#define	CPU_FREQ_EQU  		0       //main PLL freq must be equal to the specified
#define	CPU_FREQ_LTE		1       //main PLL freq must be less than or equal the specified
#define	CPU_FREQ_GTE		2       //main PLL freq must be greater than or equal the specified
#define	CPU_FREQ_APPROX		3       //main PLL freq must be as close as possible the specified

#define	PLL_CMD_SUCCESS		0       //PLL setup successfully found
#define	PLL_INVALID_FREQ	1       //specified freq out of range (either input or output)
#define	PLL_INVALID_MODE	2       //invalid mode (see above for valid) specified
#define	PLL_FREQ_NOT_FOUND	3       //specified freq not found under specified conditions
#define	PLL_NOT_LOCKED		4       //PLL not locked => no changes to the PLL setup

//power setup elated definitions
#define	PARAM_DEFAULT			0   //default power settings (voltage regulator, flash interface)
#define	PARAM_CPU_PERFORMANCE	1   //setup for maximum CPU performance (higher current, more computation)
#define	PARAM_EFFICIENCY		2   //balanced setting (power vs CPU performance)
#define	PARAM_LOW_CURRENT		3   //lowest active current, lowest CPU performance

#define	PARAM_CMD_SUCCESS		0   //power setting successfully found
#define	PARAM_INVALID_FREQ		1   //specified freq out of range (=0 or > 50 MHz)
#define	PARAM_INVALID_MODE		2   //specified mode not valid (see above for valid)

#define MAX_CLOCK_KHZ_PARAM                50000

#ifdef __cplusplus
}
#endif


#endif /* CORE_POWER_API_H_ */
