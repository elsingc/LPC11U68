/*
 * startup_lpc11u6x.h
 *
 *  Created on: Mar 8, 2015
 *      Author: Cody
 */

#ifndef CMSIS_STARTUP_LPC11U6X_H_
#define CMSIS_STARTUP_LPC11U6X_H_
#include "../main.h"

//#define WEAK __attribute__ ((weak))
//#define ALIAS(f) __attribute__ ((weak, alias (#f)))
//#define ALIAS(f) __attribute__ ((alias (#f)))
//TODO: make this file after this is all done
//#include "LPC11Uxx.h"

extern unsigned int __data_load_addr;
extern unsigned int __data_start;
extern unsigned int __data_end;
extern unsigned int __bss_start;
extern unsigned int __bss_end;
extern unsigned int __StackTop;

#define FIXED_STACKHEAP_SIZE
#define	StackMem 0x10000000
#define STACK_SIZE 0x8000

//TODO: make the below work differently
/*
#ifdef FIXED_STACKHEAP_SIZE
#define STACK_SIZE  (800)
#define HEAP_SIZE  (200)
unsigned char StackMem[STACK_SIZE] __attribute__ ((section(".stack")));
unsigned char HeapMem[HEAP_SIZE] __attribute__ ((section(".heap"), align(8)));
#endif
*/


__attribute__ ((section(".after_vectors")))
void Reset_Handler(void);
__attribute__ ((section(".after_vectors")))
void NMI_Handler(void);
__attribute__ ((section(".after_vectors")))
void HardFault_Handler(void);
__attribute__ ((section(".after_vectors")))
void SVC_Handler(void);
__attribute__ ((section(".after_vectors")))
void PendSV_Handler(void);
__attribute__ ((section(".after_vectors")))
void SysTick_Handler(void);
__attribute__ ((section(".after_vectors")))
void FLEX_INT0_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void FLEX_INT1_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void FLEX_INT2_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void FLEX_INT3_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void FLEX_INT4_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void FLEX_INT5_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void FLEX_INT6_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void FLEX_INT7_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void GINT0_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void GINT1_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void SSP1_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void I2C_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void TIMER16_0_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void TIMER16_1_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void TIMER32_0_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void TIMER32_1_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void SSP0_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void UART_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void USB_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void USB_FIQHandler(void);
__attribute__ ((section(".after_vectors")))
void ADC_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void WDT_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void BOD_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void FMC_IRQHandler(void);
__attribute__ ((section(".after_vectors")))
void USBWakeup_IRQHandler(void);


#endif /* CMSIS_STARTUP_LPC11U6X_H_ */
