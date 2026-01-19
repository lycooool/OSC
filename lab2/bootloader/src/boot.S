#include "memzero.h"  

.section ".text.relocation"

.globl _start
_start:
    adr x9, .    // source 
    ldr x10, =__bootloader_start     // dest   
    ldr x11, =__bootloader_size 

copy_loop:
    ldrb w12, [x9], #1   // load 1 byte from x9 to w12, x9 + 1
    strb w12, [x10], #1   // write w12 to x10, x10 + 1
    subs x11, x11, #1     // x11 --
    bne copy_loop // if z (前一次計算的值是否為 0 的 flag) false, jump

ldr x9, =__bootloader_entry    //jump to boot part 
br  x9


.section ".text.boot"

bootloader_relocated:
    ldr x19, =_dtb              // x19 = &dtb
    str x0, [x19]               // save x9 to x 19
    mrs    x9, mpidr_el1       // load mpidr_el1(CPU info) to x9
    and    x9, x9,#0xFF        // Check processor id (lowest 8 bit in mpidr_el1)
    cbz    x9, master          // if x9 = 0 (first cpu) jump to master
    b    proc_hang

proc_hang: 
    b proc_hang                // if not cpu0, loop

master:
    adr    x9, __bss_begin       // load bss_begin to x9 (bss_begin define in linker script)
    adr    x10, __bss_end         // load bss_end to x10  (bss_end define in linker script)
    sub    x10, x10, x9          // save x10-x9 to x10
    bl     memzero             // call memzero (func) 把 x9 開始長度 x10 的記憶體位址全部清零

    mov    sp, #LOW_MEMORY    // copy #LOW_MEMORY (define in mm.h) to sp (set sp (Stack Pointer Register) = LOW_MEMORY)
    bl    kernel_main         // call kernel_main

.global _dtb
.section .data
_dtb: .dc.a 0x0 // .dc = define constant .a = address-sized, default 0