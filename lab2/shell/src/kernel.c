#include "mini_uart.h"
#include "shell.h"
#include "cpio.h"
#include "utils.h"
#include "kernel.h"
#include <stdint.h>

extern void *_dtb_ptr;

void kernel_main ()
{
    uart_init();

    // 2. 直接讀取 ASM 存好的全域變數
    char *dtb = (char *)_dtb_ptr; 

    char buf[32];
    uart_send_string("DTB address from _dtb_ptr: ");
    utils_uint2str_hex((unsigned long)dtb, buf);
    uart_send_string(buf);
    uart_send_string("\r\n");

    // 3. 驗證 Magic Number
    // 確保讀取指標指向的記憶體內容
    uint32_t magic = *(uint32_t *)dtb;
    uart_send_string("DTB magic: ");
    utils_uint2str_hex(magic, buf);
    uart_send_string(buf);
    uart_send_string("\r\n");
    /* ============================ */
    cpio_file_count = parse_cpio((char *)0x8000000);
    uart_send_string("Hello, world! \r\n");
    shell();
}