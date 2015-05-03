/*
 * LPC11u68 linker script file.
 * This linker is intended to use with libc.
 */
ENTRY(Reset_Handler)

MEMORY
{
  irom  (rx)      : ORIGIN = 0x0,         LENGTH = 256K /*0x40000  256k */
  isram (rwx)     : ORIGIN = 0x10000000,  LENGTH = 32K /*0x8000   36k   */
}

SECTIONS
{
  . = ORIGIN(irom);
  .text : {
    KEEP(* (isr_vector_table));
	. = ALIGN(4);
	__vec_end__ = .;
    *(.after_vectors*)
	. = ALIGN(4);
	
    *(.text*)
    . = ALIGN(4);
		__end_text__ = .;
  } > irom
}
__end = .;
PROVIDE(etext = __end_text__);
PROVIDE(end = .);




















