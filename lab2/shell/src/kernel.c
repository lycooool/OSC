#include "mini_uart.h"
#include "shell.h"
#include "cpio.h"

void kernel_main (void)
{
    uart_init();
    cpio_file_count = parse_cpio((char *)0x8000000);
    uart_send_string("Hello, world! \r\n");
    shell();
}