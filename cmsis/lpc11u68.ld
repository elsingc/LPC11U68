/*
 * LPC11u68 linker script file.
 * This linker is intended to use with libc.
 */
MEMORY
{
  irom  (rx)      : ORIGIN = 0x0,         LENGTH = 256K /*0x40000  256k */
  isram (rwx)     : ORIGIN = 0x10000000,  LENGTH = 32K /*0x8000   36k   */
}

__StackTop = ORIGIN(isram) + LENGTH(isram);

ENTRY(Reset_Handler)

SECTIONS
{
	.text : ALIGN(4)
	{
		__text_start = .;
		FILL(0xff)
		/* Always keep this vector table */
		KEEP(*(.isr_vector_table))
		*(.after_vectors*)
		*(.text*)
		*(.rodata .rodata.*)
		. = ALIGN(4);
		__text_end = .;
	} > irom
	
	/* MAIN BSS SECTION */
	.bss 0x10000100: ALIGN(4)
	{
		__bss_start = .;
		*(.bss*)
		*(COMMON)
		*(.heap)
		__fixed_heap_end = .;
		*(.stack)
		. = ALIGN(4) ;
		__bss_end = .;
		PROVIDE(end = .);
	} > isram
	
	__data_load_addr = LOADADDR (.data);
	
	.data : ALIGN(4)
	{
		FILL(0xff)
		__data_start = .;
		*(.data*)
		. = ALIGN(4) ;
		__data_end = .;
	} > isram AT>irom
	
	/* Define a symbol for the start of heap */
	/* It won't be used if user defined FIXED_STACKHEAP_SIZE */
	PROVIDE(_pvHeapStart = .);
	
}


