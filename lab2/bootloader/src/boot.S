#include "memzero.h"                // define constant (bss_begin, bss_end...)

.section ".text.boot" 


.equ RELOCATE_ADDR, 0x40000      // bootloader 搬到的位置（可改成你喜歡的）

.globl _start
_start:
    ldr x0, =__bootloader_start   // load boot start addr to x0
    ldr x1, =RELOCATE_ADDR  // load relocate addr to x1
    ldr x2, =__bootloader_end     // load boot end addr to x0
    sub x2, x2, x0 // bootloader size

copy_loop:
    ldrb w3, [x0], #1   // load 1 byte from x0 to w3, x0 + 1
    strb w3, [x1], #1   // write w3 to x1, x1 + 1
    subs x2, x2, #1     // x2 --
    bne copy_loop // if z (前一次計算的值是否為 0 的 flag) false, jump

ldr x0, =_start_relocated
ldr x1, =__bootloader_start
sub x0, x0, x1                 // offset, x0 = _start_relocated - __bootloader_start
add x0, x0, #RELOCATE_ADDR     // 搬移後  _start_relocated 開始的 address
br  x0

_start_relocated:  // entry point
    mrs    x0, mpidr_el1       // load mpidr_el1(CPU info) to x0
    and    x0, x0,#0xFF        // Check processor id (lowest 8 bit in mpidr_el1)
    cbz    x0, master          // if x0 = 0 (first cpu) jump to master
    b    proc_hang

proc_hang: 
    b proc_hang                // if not cpu0, loop

master:
    adr    x0, bss_begin       // load bss_begin to x0 (bss_begin define in linker script)
    adr    x1, bss_end         // load bss_end to x1  (bss_end define in linker script)
    sub    x1, x1, x0          // save x1-x0 to x1
    bl     memzero             // call memzero (func) 把 x0 開始長度 x1 的記憶體位址全部清零

    mov    sp, #LOW_MEMORY    // copy #LOW_MEMORY (define in mm.h) to sp (set sp (Stack Pointer Register) = LOW_MEMORY)
    bl    kernel_main         // call kernel_main