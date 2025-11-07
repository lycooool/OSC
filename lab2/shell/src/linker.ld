SECTIONS
{
    . = 0x80000;
	.text.boot : { *(.text.boot) }:text
	.text : { *(.text) }:text
	.rodata : { *(.rodata) }:rodata
	.data : { *(.data) }:data
	. = ALIGN(0x8);
	bss_begin = .;
	.bss : { *(.bss*) } :data
	bss_end = .;
}
PHDRS {
    text   PT_LOAD FLAGS(5);  /* R + X = 4 + 1 */
    rodata PT_LOAD FLAGS(4);  /* R only */
    data   PT_LOAD FLAGS(6);  /* R + W = 4 + 2 */
} 