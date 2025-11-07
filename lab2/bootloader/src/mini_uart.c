#include "utils.h"
#include "peripherals/mini_uart.h"
#include "peripherals/gpio.h"

void uart_init (void)
{
    // GPIO 14, 15 func setting
    unsigned int selector;
    selector = *GPFSEL1;
    selector &= ~(7u<<12);  
    // 7 binary 是 111 ，把 111 右移 12 bit (12-14 bit 為 111 )，之後翻轉 (~) 得到只有 12-14 bit 是 0，其他是 1 的 mask
    // selector 與此 mask 做 and (&) 可將 selector 12-14 bit 清 0 (GPIO 14 功能設定)
    selector |= (2u<<12);    // 把 12-14 bit 設成 010 (select alternate function 5)
    selector &= ~(7u<<15);   // GPIO 15 功能設定清 0
    selector |= (2u<<15);    // GPIP 15 func setting
    *GPFSEL1 = selector;

    //disable GPIO pull up/ down
    *GPPUD = 0u; //disable pull-up/down
    delay(150);
    *GPPUDCLK0 = (1u<<14)|(1u<<15); // gpio 14,15 use gppud setting
    delay(150u);
    *GPPUD = 0u;
	*GPPUD = 0u;

    //uart setting
    *AUXENB = 1u; //enable mini uart
    *AUX_MU_CNTL_REG = 0u;
    *AUX_MU_IER_REG = 0u;
    *AUX_MU_LCR_REG = 3u;
    *AUX_MU_MCR_REG = 0u;
    *AUX_MU_BAUD = 270u;
    *AUX_MU_IIR_REG = 6u;
    *AUX_MU_CNTL_REG = 3u;

}

char uart_recv()
{
    while(1) 
    {
		if(*AUX_MU_LSR_REG & 0x01) //ready 才 read
			break;
	}
    return (*AUX_MU_IO_REG & 0xFF); // uart 只有 low 8 bit 有效
}

void uart_send(char c)
{
    while (1)
    {
        if(*AUX_MU_LSR_REG & 0x20) // transmitter have at leat 1 empty field
            break;   
    }
    *AUX_MU_IO_REG = c;
}

void uart_send_string (char* str)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        uart_send((char)str[i]);
    }
}

