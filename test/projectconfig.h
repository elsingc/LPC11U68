/*
 * projectconfig.h
 *
 *  Created on: Mar 27, 2015
 *      Author: Cody
 */

#ifndef PROJECTCONFIG_H_
#define PROJECTCONFIG_H_


#ifdef __cplusplus
extern "C" {
#endif



/* ========================================================================
    ABOUT THIS FILE
    -----------------------------------------------------------------------
    This file contains global config settings that apply to any board
    or project.

    Any board-specific config settings should be placed in individual
    config files in the 'boards/' sub-directory, and the settings will be
    includes in any file via 'projectconfig.h'.
   ========================================================================*/

#include "sysdefs.h"
#include "errors.h"
//#include "asserts.h"
#include "binary.h"
#include "lpc11u6x.h"
#include "lpc11u68_clock.h"
#include <stdint.h>

#define CFG_USB_STRING_MANUFACTURER "test"
#define CFG_USB_STRING_PRODUCT "anio"
#define CFG_USB_STRING_SERIAL "abcdefghijklmnopqrstuvwxyz123456"
#define CFG_USB_CDC
#define CFG_USB
#define CFG_MCU_FAMILY_LPC11UXX

/*=========================================================================
    CODE BASE VERSION SETTINGS

    Please do not modify this version number.  To set a version number
    for your project or firmware, change the values in your 'boards/'
    config file.
    -----------------------------------------------------------------------*/
    #define CFG_CODEBASE_VERSION_MAJOR      (0)
    #define CFG_CODEBASE_VERSION_MINOR      (9)
    #define CFG_CODEBASE_VERSION_REVISION   (1)
/*=========================================================================*/

#define USBPLLCTRL_Val        0x00000000//23              // Reset: 0x000
#define USBPLLCLKSEL_Val      0x00000001              // Reset: 0x000
#define USBCLKSEL_Val         0x00000000              // Reset: 0x000
#define USBCLKDIV_Val         0x00000001              // Reset: 0x001

/* The following manifest constants are used to define this memory area to be used
   by USBD ROM stack.
 */
#define USB_STACK_MEM_BASE      0x20004000
#define USB_STACK_MEM_SIZE      0x0800

//TODO: add board includes
//TODO: add chip include here


#ifdef __cplusplus
}
#endif


#endif /* PROJECTCONFIG_H_ */
