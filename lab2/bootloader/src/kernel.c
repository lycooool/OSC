#include "mini_uart.h"
#include "kernel.h"
#include "utils.h"
#include <stdint.h>

extern char *_dtb;

void kernel_main(void)
{
    uart_init();
    uart_send_string("Waiting for img \r\n");
    load_img();
}

void load_img(void){

    uart_send_string("waiting for img\r\n");


    unsigned int magic = 0; //32bit
    while (magic != 0x544F4F42) {   // 'BOOT'
        magic = (magic >> 8) | ((unsigned int)uart_recv() << 24);
    }


    char info [50];

    unsigned int size = 0;
    size |= uart_recv();
    size |= uart_recv() << 8 ;
    size |= uart_recv() << 16 ;
    size |= uart_recv() << 24 ;

    uart_send_string("img size: ");
    utils_uint2str_dec(size, info);
    uart_send_string(info);
    uart_send_string("\r\n");

    unsigned int check_sum = 0;
    check_sum |= uart_recv();
    check_sum |= uart_recv() << 8 ;
    check_sum |= uart_recv() << 16 ;
    check_sum |= uart_recv() << 24 ;

    unsigned char *dst = (unsigned char *)0x80000;
    unsigned int sum = 0;

    for(int i = 0; i < size; i++)
    {      
        *dst = uart_recv();
        sum += *dst;
        dst++;
    }

    if(sum != check_sum){
        uart_send_string("deserved check sum:  \r\n");
        utils_uint2str_dec(check_sum, info);
        uart_send_string(info);
        uart_send_string("\r\n");
        uart_send_string("calculated check sum:  \r\n");
        utils_uint2str_dec(sum, info);
        uart_send_string(info);
        uart_send_string("\r\n");
        return;
    }

    // 【新增測試】印出 Bootloader 認為的 DTB 位址
    uart_send_string("Bootloader passing arg: ");
    utils_uint2str_hex((unsigned long)_dtb, info);
    uart_send_string(info);
    uart_send_string("\r\n");
    
    uart_send_string("booting... \r\n");
    
    void (*kernel_entry)(char *) = (void (*)(char *))0x80000;
    kernel_entry(_dtb);
}
