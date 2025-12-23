SECTIONS
{
    . = 0x80000;
	
	__bootloader_start = .; /* boot loader start address */

	.text.boot : { *(.text.boot) }
	.text : { *(.text) }
	.rodata : { *(.rodata) }
	.data : { *(.data) }
	
	__bootloader_end = .;

	. = ALIGN(0x8);
	bss_begin = .;
	.bss : { *(.bss*) } 
	bss_end = .;
}
