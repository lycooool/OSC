ENTRY(_start)
SECTIONS
{
  . = 0x60000;
  __bootloader_start = .;
  .text : { 
    *(.text.relocation)
    __bootloader_entry = .;
    *(.text.boot)
    *(.text) 
    *(.rodata) 
  }
  . = ALIGN(0x1000);

  .data : { *(.data) }
  . = ALIGN(0x1000);

  
  __bss_begin = .;
  .bss : { *(.bss*) } 
  . = ALIGN(0x1000);
  __bss_end = .;  

  __bootloader_size =  __bss_end -  __bootloader_start;
}
