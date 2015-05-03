/*
 * iocon.c
 *
 *  Created on: Apr 6, 2015
 *      Author: Cody
 */

#include "iocon.h"

/*Set all I/O Control pin muxing*/
void Chip_IOCON_SetPinMuxing(LPC_IOCON_Type_fix *pIOCON, const PINMUX_GRP_Type* pinArray, uint32_t arrayLength)
{
	uint32_t ix;

	for (ix = 0; ix < arrayLength; ix++ ) {
		Chip_IOCON_PinMuxSet(pIOCON, pinArray[ix].port, pinArray[ix].pin, pinArray[ix].modefunc);
	}
}



/* Sets I/O Control pin mux */
void Chip_IOCON_PinMuxSet(LPC_IOCON_Type_fix *pIOCON, uint8_t port, uint8_t pin, uint32_t modefunc)
{
	switch (port) {
	case 0:
		pIOCON->PIO0[pin] = modefunc;
		break;

	case 1:
		pIOCON->PIO1[pin] = modefunc;
		break;

	case 2:
		if (pin >= 2) {
			pIOCON->PIO2B[pin - 2] = modefunc;
		}
		else {
			pIOCON->PIO2A[pin] = modefunc;
		}
		break;

	default:
		break;
	}
}
