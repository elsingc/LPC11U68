/**************************************************************************/
/*!
    @file     projectconfig.h
    @author   K. Townsend (microBuilder.eu)

    @brief    Indicates which board should be used during the build process
    @ingroup  Board/HW Abstration Layer

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2012, 2013 K. Townsend
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/
#ifndef _PROJECTCONFIG_H_
#define _PROJECTCONFIG_H_

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
#include "asserts.h"
#include "binary.h"

#include "LPC11Uxx.h"
#define CFG_MCU_FAMILY_LPC11UXX
#define CFG_ENABLE_USB
#define CFG_LED_PORT                  (1)
#define CFG_LED_PIN                   (31)
#define CFG_LED_ON                    (0)
#define CFG_LED_OFF                   (1)

#define CFG_USB_STRING_MANUFACTURER       "microBuilder.eu"
#define CFG_USB_STRING_PRODUCT            "RF1GHZUSB"
#define CFG_USB_VENDORID                  (0x1FC9)
#define CFG_USB_CDC
#define CFG_USB

/*=========================================================================*/
/*=========================================================================*/
/*=========================================================================
    PRINTF REDIRECTION
    -----------------------------------------------------------------------

    CFG_PRINTF_MAXSTRINGSIZE  Maximum size of string buffer for printf
    CFG_PRINTF_UART           Will cause all printf statements to be
                              redirected to UART
    CFG_PRINTF_USBCDC         Will cause all printf statements to be
                              redirect to USB Serial
    CFG_PRINTF_DEBUG          Use the debug interface for printf
    CFG_PRINTF_NEWLINE        This is typically "\r\n" for Windows or
                              "\n" for *nix

    Note: If no printf redirection definitions are present, all printf
    output will be ignored.
    -----------------------------------------------------------------------*/
#define CFG_PRINTF_MAXSTRINGSIZE    (255)
#define CFG_PRINTF_USBCDC

#ifdef CFG_PRINTF_DEBUG
	#define CFG_PRINTF_NEWLINE          "\n"
#else
	#define CFG_PRINTF_NEWLINE          "\r\n"
#endif
/*=========================================================================*/

#ifdef __cplusplus
}
#endif

#endif
