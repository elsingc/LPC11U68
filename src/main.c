#include "projectconfig.h"
#include "../driver/usb/usbd.h"
#include "../driver/usb/usb_cdc.h"
#include "../driver/gpio.h"
#include "../driver/delay.h"

__IO uint32_t TimeTick = 0;
__IO uint8_t Cur_State = 0;

int main (void)
{
	SystemCoreClockUpdate();
	delayInit();
	GPIOInit();
	GPIOSetDir( PORT1, 31, 1 );
	delay(500);
	usb_init();
	delay(500);
	uint8_t cdc_char;
	while(1)
	{
		if (usb_isConfigured())
		{
			if( usb_cdc_getc(&cdc_char) )
			{
				if(cdc_char <= 122 && cdc_char >= 97)
					cdc_char=cdc_char - 32;
				usb_cdc_putc(cdc_char);
			}
		}
		TimeTick++;
		if(TimeTick >= 0xFFFF)
		{
			if (Cur_State == 1)
			{
				GPIOSetBitValue(PORT1,31,1);
				Cur_State = 0;
			}
			else
			{
				GPIOSetBitValue(PORT1,31,0);
				Cur_State = 1;
			}
			TimeTick=0;
		}
	}
}
