/*
 * startup_lpc11u6x.c
 *
 *  Created on: Mar 8, 2015
 *      Author: Cody
 */

#include "startup_lpc11u6x.h"


#define FIXED_STACKHEAP_SIZE
#define	StackMem 0x10000000
#define STACK_SIZE 0x8000

__attribute__ ((section("isr_vector_table")))
void (* const Vectors[])(void) = {
#ifdef FIXED_STACKHEAP_SIZE
  (void (*)(void))(StackMem + STACK_SIZE),          // The initial stack pointer
#else
  (void (*)(void))&__StackTop,
#endif
  Reset_Handler,                    // The reset handler
  NMI_Handler,                      // The NMI handler
  HardFault_Handler,                // The hard fault handler
  0,                                // Reserved
  0,                                // Reserved
  0,                                // Reserved
  0,                                // Reserved
  0,                                // Reserved
  0,                                // Reserved
  0,                                // Reserved
  SVC_Handler,                      // SVCall handler
  0,                                // Reserved
  0,                                // Reserved
  PendSV_Handler,                   // The PendSV handler
  SysTick_Handler,                  // The SysTick handler

  // LPC11U specific handlers
  FLEX_INT0_IRQHandler,             //  0 - GPIO pin interrupt 0
  FLEX_INT1_IRQHandler,             //  1 - GPIO pin interrupt 1
  FLEX_INT2_IRQHandler,             //  2 - GPIO pin interrupt 2
  FLEX_INT3_IRQHandler,             //  3 - GPIO pin interrupt 3
  FLEX_INT4_IRQHandler,             //  4 - GPIO pin interrupt 4
  FLEX_INT5_IRQHandler,             //  5 - GPIO pin interrupt 5
  FLEX_INT6_IRQHandler,             //  6 - GPIO pin interrupt 6
  FLEX_INT7_IRQHandler,             //  7 - GPIO pin interrupt 7
  GINT0_IRQHandler,                 //  8 - GPIO GROUP0 interrupt
  GINT1_IRQHandler,                 //  9 - GPIO GROUP1 interrupt
  0,                                // 10 - Reserved
  0,                                // 11 - Reserved
  0,                                // 12 - Reserved
  0,                                // 13 - Reserved
  SSP1_IRQHandler,                  // 14 - SPI/SSP1 Interrupt
  I2C_IRQHandler,                   // 15 - I2C0
  TIMER16_0_IRQHandler,             // 16 - CT16B0 (16-bit Timer 0)
  TIMER16_1_IRQHandler,             // 17 - CT16B1 (16-bit Timer 1)
  TIMER32_0_IRQHandler,             // 18 - CT32B0 (32-bit Timer 0)
  TIMER32_1_IRQHandler,             // 19 - CT32B1 (32-bit Timer 1)
  SSP0_IRQHandler,                  // 20 - SPI/SSP0 Interrupt
  UART_IRQHandler,                  // 21 - UART0
  USB_IRQHandler,                   // 22 - USB IRQ
  USB_FIQHandler,                   // 23 - USB FIQ
  ADC_IRQHandler,                   // 24 - ADC (A/D Converter)
  WDT_IRQHandler,                   // 25 - WDT (Watchdog Timer)
  BOD_IRQHandler,                   // 26 - BOD (Brownout Detect)
  FMC_IRQHandler,                   // 27 - IP2111 Flash Memory Controller
  0,                                // 28 - Reserved
  0,                                // 29 - Reserved
  USBWakeup_IRQHandler,             // 30 - USB wake-up interrupt
  0,                                // 31 - Reserved
};

//*****************************************************************************
// Reset entry point for your code.
// Sets up a simple runtime environment and initializes the C/C++
// library.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void Reset_Handler(void)
{
  /*
   * Only Initialize Internal SRAM
   * USB RAM is used for USB purpose
   */
  //unsigned int *src, *dst;

  /* Copy data section from flash to RAM */
  //src = &__data_load_addr;
  //dst = &__data_start;
  //while (dst < &__data_end)
  //  *dst++ = *src++;

  /* Zero fill the bss section */
  //dst = &__bss_start;
  //while (dst < &__bss_end)
  //  *dst++ = 0;

	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 26) | (1 <<27);
  //SystemInit();

  main();
  while (1);
}


__attribute__ ((weak, section(".after_vectors")))
void NMI_Handler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void HardFault_Handler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void SVC_Handler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void PendSV_Handler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void SysTick_Handler(void)
{
	main();
    while(1);
}

//*****************************************************************************
//
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
//
//*****************************************************************************
__attribute__ ((weak, section(".after_vectors")))
void FLEX_INT0_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void FLEX_INT1_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void FLEX_INT2_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void FLEX_INT3_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void FLEX_INT4_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void FLEX_INT5_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void FLEX_INT6_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void FLEX_INT7_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void GINT0_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void GINT1_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void SSP1_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void I2C_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void TIMER16_0_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void TIMER16_1_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void TIMER32_0_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void TIMER32_1_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void SSP0_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void UART_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void USB_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void USB_FIQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void ADC_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void WDT_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void BOD_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void FMC_IRQHandler(void)
{
	main();
    while(1);
}

__attribute__ ((weak, section(".after_vectors")))
void USBWakeup_IRQHandler(void)
{
	main();
    while(1);
}

