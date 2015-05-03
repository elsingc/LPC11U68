/*
 * main.c
 *
 *  Created on: Mar 4, 2015
 *      Author: Cody
 */


#include "main.h"
//#include <stdint.h>
#include <string.h>

//TODO: Device ID read register for USB id

//TODO: Get SysTick timer working
//TODO: Get Timer16 working for delay
//TODO: Get Timer interrupt working
//TODO: Get interrupt handlers set to weak types
//TODO: Get 32 bit timer working
//TODO: Get fancy code for timer stuff working (see arduino)
//TODO: work on getting frequency and duty cycle control working for pwm output to 4 pins
//TODO: Get usb working
//TODO: Get adc working
//TODO: Get adc interrupts working
//TODO: develop filter setup

//#define USB_TEST_CODE


const  USBD_API_T *g_pUsbApi;

static uint8_t g_rxBuff[256];

/** @ingroup EXAMPLES_USBDROM_11U6X_CDC
 * @{
 */

#define VCOM_RX_BUF_SZ      512
#define VCOM_TX_CONNECTED   _BIT(8)		/* connection state is for both RX/Tx */
#define VCOM_TX_BUSY        _BIT(0)
#define VCOM_RX_DONE        _BIT(0)
#define VCOM_RX_BUF_FULL    _BIT(1)
#define VCOM_RX_BUF_QUEUED  _BIT(2)
#define VCOM_RX_DB_QUEUED   _BIT(3)

/** @defgroup CMSIS_11U6X_IRQ CHIP_LPC11U6X: CHIP_LPC11U6X peripheral interrupt numbers
 * @{
 */

typedef enum {
	NonMaskableInt_IRQn           = -14,	/*!< 2 Non Maskable Interrupt                         */
	HardFault_IRQn                = -13,	/*!< 3 Cortex-M0 Hard Fault Interrupt                 */
	SVCall_IRQn                   = -5,		/*!< 11 Cortex-M0 SV Call Interrupt                   */
	PendSV_IRQn                   = -2,		/*!< 14 Cortex-M0 Pend SV Interrupt                   */
	SysTick_IRQn                  = -1,		/*!< 15 Cortex-M0 System Tick Interrupt               */

	PIN_INT0_IRQn                 = 0,		/*!< Pin Interrupt 0                                  */
	PIN_INT1_IRQn                 = 1,		/*!< Pin Interrupt 1                                  */
	PIN_INT2_IRQn                 = 2,		/*!< Pin Interrupt 2                                  */
	PIN_INT3_IRQn                 = 3,		/*!< Pin Interrupt 3                                  */
	PIN_INT4_IRQn                 = 4,		/*!< Pin Interrupt 4                                  */
	PIN_INT5_IRQn                 = 5,		/*!< Pin Interrupt 5                                  */
	PIN_INT6_IRQn                 = 6,		/*!< Pin Interrupt 6                                  */
	PIN_INT7_IRQn                 = 7,		/*!< Pin Interrupt 7                                  */
	GINT0_IRQn                    = 8,		/*!< GPIO interrupt status of port 0                  */
	GINT1_IRQn                    = 9,		/*!< GPIO interrupt status of port 1                  */
	I2C1_IRQn                     = 10,		/*!< I2C1 Interrupt                                   */
	USART1_4_IRQn                 = 11,		/*!< Combined USART1 and USART4 interrupts            */
	USART2_3_IRQn                 = 12,		/*!< Combined USART2 and USART3 interrupts            */
	SCT0_1_IRQn                   = 13,		/*!< Combined SCT0 and SCT1 interrupts                */
	SSP1_IRQn                     = 14,		/*!< SSP1 Interrupt                                   */
	I2C0_IRQn                     = 15,		/*!< I2C0 Interrupt                                   */
	TIMER_16_0_IRQn               = 16,		/*!< 16-bit Timer0 Interrupt                          */
	TIMER_16_1_IRQn               = 17,		/*!< 16-bit Timer1 Interrupt                          */
	TIMER_32_0_IRQn               = 18,		/*!< 32-bit Timer0 Interrupt                          */
	TIMER_32_1_IRQn               = 19,		/*!< 32-bit Timer1 Interrupt                          */
	SSP0_IRQn                     = 20,		/*!< SSP0 Interrupt                                   */
	USART0_IRQn                   = 21,		/*!< USART0 interrupt                                 */
	USB0_IRQn                     = 22,		/*!< USB IRQ interrupt                                */
	USB0_FIQ_IRQn                 = 23,		/*!< USB FIQ interrupt                                */
	ADC_A_IRQn                    = 24,		/*!< ADC_A Converter Interrupt                        */
	RTC_IRQn                      = 25,		/*!< RTC Interrupt                                    */
	BOD_WDT_IRQn                  = 26,		/*!< Shared Brown Out Detect(BOD) and WDT Interrupts  */
	FMC_IRQn                      = 27,		/*!< FLASH Interrupt                                  */
	DMA_IRQn                      = 28,		/*!< DMA Interrupt                                    */
	ADC_B_IRQn                    = 29,		/*!< ADC_B Interrupt                                  */
	USB_WAKEUP_IRQn               = 30,		/*!< USB wake-up interrupt Interrupt                  */
	RESERVED31_IRQn               = 31,
} IRQn_Type;

/* Manifest constants defining interface numbers and endpoints used by a
   particular interface in this application.
 */
#define USB_CDC_CIF_NUM         0
#define USB_CDC_DIF_NUM         1
#define USB_CDC_IN_EP           0x81
#define USB_CDC_OUT_EP          0x01
#define USB_CDC_INT_EP          0x82

/**
 * Global variable to hold Virtual COM port control data.
 */
/**
 * Structure containing Virtual Comm port control data
 */
typedef struct VCOM_DATA {
	USBD_HANDLE_T hUsb;
	USBD_HANDLE_T hCdc;
	uint8_t *rx_buff;
	uint16_t rx_rd_count;
	uint16_t rx_count;
	volatile uint16_t tx_flags;
	volatile uint16_t rx_flags;
} VCOM_DATA_T;
VCOM_DATA_T g_vCOM;
//TODO: redefine in the board file
/* Set up and initialize all required blocks and functions related to the
   board hardware */
void Board_Init(void)
{
	/* Sets up DEBUG UART */
	//DEBUGINIT();

	/* Initialize GPIO */
	gpioInit();

	/* Initialize LEDs */
	//Board_LED_Init();
}
/** \brief  Enable External Interrupt

    The function enables a device-specific interrupt in the NVIC interrupt controller.

    \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  NVIC->ISER[0] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/** \brief  Disable External Interrupt

    The function disables a device-specific interrupt in the NVIC interrupt controller.

    \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  NVIC->ICER[0] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

int main(void)
{

	//SystemCoreClockUpdate();
	/* Initialize board and chip */
	//Board_Init();

	/* enable clocks and pinmux */
	//enableUSBClock();

	SystemInit();

	USBD_API_INIT_PARAM_T usb_param;
	USB_CORE_DESCS_T desc;
	ErrorCode_t ret = LPC_OK;
	uint32_t prompt = 0;//, rdCnt = 0;

	/* initialize USBD ROM API pointer. */
	g_pUsbApi = (const USBD_API_T *) LPC_ROM_API->pUSBD;

	/* initialize call back structures */
	memset((void *) &usb_param, 0, sizeof(USBD_API_INIT_PARAM_T));
	usb_param.usb_reg_base = LPC_USB_BASE;
	/*	WORKAROUND for artf44835 ROM driver BUG:
	    Code clearing STALL bits in endpoint reset routine corrupts memory area
	    next to the endpoint control data. For example When EP0, EP1_IN, EP1_OUT,
	    EP2_IN are used we need to specify 3 here. But as a workaround for this
	    issue specify 4. So that extra EPs control structure acts as padding buffer
	    to avoid data corruption. Corruption of padding memory doesn�t affect the
	    stack/program behaviour.
	 */
	usb_param.max_num_ep = 3 + 1;
	usb_param.mem_base = USB_STACK_MEM_BASE;
	usb_param.mem_size = USB_STACK_MEM_SIZE;

	/* Set the USB descriptors */
	desc.device_desc = (uint8_t *) &USB_DeviceDescriptor;
	desc.string_desc = (uint8_t *) &USB_StringDescriptor;
	/* Note, to pass USBCV test full-speed only devices should have both
	   descriptor arrays point to same location and device_qualifier set to 0.
	 */
	desc.high_speed_desc = (uint8_t *) &USB_FsConfigDescriptor;
	desc.full_speed_desc = (uint8_t *) &USB_FsConfigDescriptor;
	desc.device_qualifier = 0;

	/* USB Initialization */
	ret = USBD_API->hw->Init(&g_hUsb, &desc, &usb_param);
	if (ret == LPC_OK) {

		/*	WORKAROUND for artf32219 ROM driver BUG:
		    The mem_base parameter part of USB_param structure returned
		    by Init() routine is not accurate causing memory allocation issues for
		    further components.
		 */
		usb_param.mem_base = USB_STACK_MEM_BASE + (USB_STACK_MEM_SIZE - usb_param.mem_size);
		/* Init VCOM interface */
		ret = vcom_init(g_hUsb, &desc, &usb_param);
		if (ret == LPC_OK) {
			/*  enable USB interrupts */
			//TODO: make interrupts pretty
			NVIC_EnableIRQ(USB0_IRQn);
			/* now connect */
			USBD_API->hw->Connect(g_hUsb, 1);
		}

	}

		//DEBUGSTR("USB CDC class based virtual Comm port example!\r\n");

	while (1) {
		/* Check if host has connected and opened the VCOM port */
		if ((vcom_connected() != 0) && (prompt == 0)) {
			vcom_write("Hello World!!\r\n", 16);
			prompt++;
		}
		/* If VCOM port is opened echo whatever we receive back to host. */
		if (prompt) {
			uint32_t rdCnt = 0;
			rdCnt = vcom_bread(&g_rxBuff[0], 256);
			if (rdCnt) {
				vcom_write(&g_rxBuff[0], rdCnt);
			}
		}
	}



#if defined(use)
	SystemInit();
	LPC_GPIO->PIN[3] = 129;
	gpioSetDirPin(PORT2, 16, OUTPUT);
	gpioSetDirPin(PORT2, 17, OUTPUT);
	gpioSetDirPin(PORT2, 18, OUTPUT);
	gpioSetDirPin(PORT0, 16, INPUT);
	gpioSet(PORT2);



	while (1)
	{
//#define PIN_16
#define PIN_17
//#define PIN_18
#if defined(PIN_16)

		if(gpioGetPin(PORT0, 16)){
			gpioPinSet(PORT2, 16);
		}else{
			gpioPinClr(PORT2, 16);
		}

#endif
#if defined(PIN_17)
		gpioPinToggle(PORT2, 17);
		for(int x = 0; x < 500000; x++);
#endif
#if defined(PIN_18)
		if(delayGetTicks() < 10){
			gpioPinToggle(PORT2, 18);
		}
#endif

#if defined(USB_TEST_CODE)
		if(delayGetTicks() < 10){
			testUSB();
		}
#endif
	}
#endif
}

/* Virtual com port init routine */
ErrorCode_t vcom_init(USBD_HANDLE_T hUsb, USB_CORE_DESCS_T *pDesc, USBD_API_INIT_PARAM_T *pUsbParam)
{
	USBD_CDC_INIT_PARAM_T cdc_param;
	ErrorCode_t ret = LPC_OK;
	uint32_t ep_indx;

	g_vCOM.hUsb = hUsb;
	memset((void *) &cdc_param, 0, sizeof(USBD_CDC_INIT_PARAM_T));
	cdc_param.mem_base = pUsbParam->mem_base;
	cdc_param.mem_size = pUsbParam->mem_size;
	cdc_param.cif_intf_desc = (uint8_t *) find_IntfDesc(pDesc->high_speed_desc, CDC_COMMUNICATION_INTERFACE_CLASS);
	cdc_param.dif_intf_desc = (uint8_t *) find_IntfDesc(pDesc->high_speed_desc, CDC_DATA_INTERFACE_CLASS);
	cdc_param.SetLineCode = VCOM_SetLineCode;

	ret = USBD_API->cdc->init(hUsb, &cdc_param, &g_vCOM.hCdc);

	if (ret == LPC_OK) {
		/* allocate transfer buffers */
		g_vCOM.rx_buff = (uint8_t *) cdc_param.mem_base;
		cdc_param.mem_base += VCOM_RX_BUF_SZ;
		cdc_param.mem_size -= VCOM_RX_BUF_SZ;

		/* register endpoint interrupt handler */
		ep_indx = (((USB_CDC_IN_EP & 0x0F) << 1) + 1);
		ret = USBD_API->core->RegisterEpHandler(hUsb, ep_indx, VCOM_bulk_in_hdlr, &g_vCOM);
		if (ret == LPC_OK) {
			/* register endpoint interrupt handler */
			ep_indx = ((USB_CDC_OUT_EP & 0x0F) << 1);
			ret = USBD_API->core->RegisterEpHandler(hUsb, ep_indx, VCOM_bulk_out_hdlr, &g_vCOM);

		}
		/* update mem_base and size variables for cascading calls. */
		pUsbParam->mem_base = cdc_param.mem_base;
		pUsbParam->mem_size = cdc_param.mem_size;
	}

	return ret;
}

/* Set line coding call back routine */
ErrorCode_t VCOM_SetLineCode(USBD_HANDLE_T hCDC, CDC_LINE_CODING *line_coding)
{
	VCOM_DATA_T *pVcom = &g_vCOM;

	/* Called when baud rate is changed/set. Using it to know host connection state */
	pVcom->tx_flags = (1<<8);//VCOM_TX_CONNECTED;	/* reset other flags */

	return LPC_OK;
}


/* VCOM bulk EP_IN endpoint handler */
ErrorCode_t VCOM_bulk_in_hdlr(USBD_HANDLE_T hUsb, void *data, uint32_t event)
{
	VCOM_DATA_T *pVcom = (VCOM_DATA_T *) data;

	if (event == USB_EVT_IN) {
		pVcom->tx_flags &= ~0x1;
	}
	return LPC_OK;
}

/* VCOM bulk EP_OUT endpoint handler */
ErrorCode_t VCOM_bulk_out_hdlr(USBD_HANDLE_T hUsb, void *data, uint32_t event)
{
	VCOM_DATA_T *pVcom = (VCOM_DATA_T *) data;

	switch (event) {
	case USB_EVT_OUT:
		pVcom->rx_count = USBD_API->hw->ReadEP(hUsb, USB_CDC_OUT_EP, pVcom->rx_buff);
		if (pVcom->rx_flags & (1<<2)) {
			pVcom->rx_flags &= ~(1<<2);
			if (pVcom->rx_count != 0) {
				pVcom->rx_flags |= (1<<1);
			}

		}
		else if (pVcom->rx_flags & (1<<3)) {
			pVcom->rx_flags &= ~(1<<3);
			pVcom->rx_flags |= (1<<0);
		}
		break;

	case USB_EVT_OUT_NAK:
		/* queue free buffer for RX */
		if ((pVcom->rx_flags & ((1<<1) | (1<<2))) == 0) {
			USBD_API->hw->ReadReqEP(hUsb, USB_CDC_OUT_EP, pVcom->rx_buff, VCOM_RX_BUF_SZ);
			pVcom->rx_flags |= (1<<2);
		}
		break;

	default:
		break;
	}

	return LPC_OK;
}



/**
 * @brief	Check if Vcom is connected
 * @return	Returns non-zero value if connected.
 */
uint32_t vcom_connected(void) {

	return g_vCOM.tx_flags & (1<<8);
}


/* Virtual com port write routine*/
uint32_t vcom_write(char *pBuf, uint32_t len)
{
	VCOM_DATA_T *pVcom = &g_vCOM;
	uint32_t ret = 0;

	if ( (pVcom->tx_flags & (1<<8)) && ((pVcom->tx_flags & (1<<0)) == 0) ) {
		pVcom->tx_flags |= (1<<0);

		/* enter critical section */
		NVIC_DisableIRQ(USB0_IRQn);
		ret = USBD_API->hw->WriteEP(pVcom->hUsb, USB_CDC_IN_EP, pBuf, len);
		/* exit critical section */
		NVIC_EnableIRQ(USB0_IRQn);
	}

	return ret;
}


/* Virtual com port buffered read routine */
uint32_t vcom_bread(uint8_t *pBuf, uint32_t buf_len)
{
	VCOM_DATA_T *pVcom = &g_vCOM;
	uint16_t cnt = 0;
	/* read from the default buffer if any data present */
	if (pVcom->rx_count) {
		cnt = (pVcom->rx_count < buf_len) ? pVcom->rx_count : buf_len;
		memcpy(pBuf, pVcom->rx_buff, cnt);
		pVcom->rx_rd_count += cnt;

		/* enter critical section */
		NVIC_DisableIRQ(USB0_IRQn);
		if (pVcom->rx_rd_count >= pVcom->rx_count) {
			pVcom->rx_flags &= ~(1<<1);
			pVcom->rx_rd_count = pVcom->rx_count = 0;
		}
		/* exit critical section */
		NVIC_EnableIRQ(USB0_IRQn);
	}
	return cnt;
}





/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit (void) {
	/* Setup system clocking and muxing */
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 26) | (1 <<27);
	Board_SetupMuxing();/* Muxing first as it sets up ext oscillator pins */
	Board_SetupClocking();
	SystemCoreClockUpdate();
	gpioInit();

	enableUSBClock();

	delayInit();
}

/* Sets up system pin muxing */
void Board_SetupMuxing(void)
{
	/* Enable IOCON clock */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);

	Chip_IOCON_SetPinMuxing(LPC_IOCON_fix, pinmuxing, sizeof(pinmuxing) / sizeof(PINMUX_GRP_Type));
}

/* Set up and initialize clocking prior to call to main */
void Board_SetupClocking(void)
{
	Chip_SetupXtalClocking();
}




/**
 * @brief	Handle interrupt from USB0
 * @return	Nothing
 */
void USB_IRQHandler(void)
{
	uint32_t *addr = (uint32_t *) LPC_USB->EPLISTSTART;

	/*	WORKAROUND for artf32289 ROM driver BUG:
	    As part of USB specification the device should respond
	    with STALL condition for any unsupported setup packet. The host will send
	    new setup packet/request on seeing STALL condition for EP0 instead of sending
	    a clear STALL request. Current driver in ROM doesn't clear the STALL
	    condition on new setup packet which should be fixed.
	 */
	if ( LPC_USB->DEVCMDSTAT & (1<<8) ) {	/* if setup packet is received */
		addr[0] &= ~((1<<29));	/* clear EP0_OUT stall */
		addr[2] &= ~((1<<29));	/* clear EP0_IN stall */
	}
	USBD_API->hw->ISR(g_hUsb);
}

/* Find the address of interface descriptor for given class type. */
USB_INTERFACE_DESCRIPTOR *find_IntfDesc(const uint8_t *pDesc, uint32_t intfClass)
{
	USB_COMMON_DESCRIPTOR *pD;
	USB_INTERFACE_DESCRIPTOR *pIntfDesc = 0;
	uint32_t next_desc_adr;

	pD = (USB_COMMON_DESCRIPTOR *) pDesc;
	next_desc_adr = (uint32_t) pDesc;

	while (pD->bLength) {
		/* is it interface descriptor */
		if (pD->bDescriptorType == USB_INTERFACE_DESCRIPTOR_TYPE) {

			pIntfDesc = (USB_INTERFACE_DESCRIPTOR *) pD;
			/* did we find the right interface descriptor */
			if (pIntfDesc->bInterfaceClass == intfClass) {
				break;
			}
		}
		pIntfDesc = 0;
		next_desc_adr = (uint32_t) pD + pD->bLength;
		pD = (USB_COMMON_DESCRIPTOR *) next_desc_adr;
	}

	return pIntfDesc;
}










void testUSBInit(){
	//uint32_t USB_ID = LPC_SYSCON->DEVICE_ID;
	usb_init();
	//cliInit();
}


#if defined(USB_TEST_CODE)
void testUSB(){
	//USB_Send_Data(data);
	//cliPoll();
}
#endif
