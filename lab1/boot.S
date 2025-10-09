
#include "mm.h"                // define constant (bss_begin, bss_end...)

.section ".text.boot" 

.globl _start 
_start: // entry point
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

    mov    sp, #LOW_MEMORY    // copy #LOW_MEMORY (define in mm.h) to sp (set sp = LOW_MEMORY)
    bl    kernel_main         // call kernel_main