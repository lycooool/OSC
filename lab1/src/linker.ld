SECTIONS
{
    . = 0x80000; // location counter, next section start here
	.text.boot : { *(.text.boot) }:text 
	// 把 input file 的 .text.boot 搜集起來，並放到 text 這個 segment
	.text : { *(.text) }:text 
	.rodata : { *(.rodata) }:rodata
	.data : { *(.data) }:data
	. = ALIGN(0x8); // 目前位置對齊到 8 byte，bss 為 8 byte 對齊
	bss_begin = .; // 建立 bss begin symbol，值為現在位置，之後可透過 extern 呼叫
	.bss : { *(.bss*) } :data
	bss_end = .;
}
PHDRS {
    text   PT_LOAD FLAGS(5);  /* R + X = 4 + 1 */
    rodata PT_LOAD FLAGS(4);  /* R only */
    data   PT_LOAD FLAGS(6);  /* R + W = 4 + 2 */
} 
