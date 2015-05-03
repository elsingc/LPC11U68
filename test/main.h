/*
 * main.h
 *
 *  Created on: Mar 4, 2015
 *      Author: Cody
 */

#ifndef MAIN_H_
#define MAIN_H_

#define LPC11U6x
#define USB_TEST_CODE
#include "lpc11u6x.h"
#include "core/gpio/gpio.h"
#include "core/gpio/iocon.h"
#include "core/delay/delay.h"
#include "core/system/system.h"

#include "core/usb/usbd.h"
#include "core/usb/usb_cdc.h"
#include "core/power_api.h"
#include "core/usb/romdriver/mw_usbd_rom_api.h"

//TODO: add reset controls for each component


int main(void);
void SystemInit (void);
void testUSBInit();
void testUSB();

void Board_SetupMuxing(void);
void Board_SetupClocking(void);


ErrorCode_t vcom_init(USBD_HANDLE_T hUsb, USB_CORE_DESCS_T *pDesc, USBD_API_INIT_PARAM_T *pUsbParam);
ErrorCode_t VCOM_SetLineCode(USBD_HANDLE_T hCDC, CDC_LINE_CODING *line_coding);
ErrorCode_t VCOM_bulk_in_hdlr(USBD_HANDLE_T hUsb, void *data, uint32_t event);
ErrorCode_t VCOM_bulk_out_hdlr(USBD_HANDLE_T hUsb, void *data, uint32_t event);
uint32_t vcom_connected(void);
uint32_t vcom_write(char *pBuf, uint32_t len);
uint32_t vcom_bread(uint8_t *pBuf, uint32_t buf_len);

void USB_IRQHandler(void);
USB_INTERFACE_DESCRIPTOR *find_IntfDesc(const uint8_t *pDesc, uint32_t intfClass);

#endif /* MAIN_H_ */
