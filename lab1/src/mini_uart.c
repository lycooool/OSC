#include "utils.h"
#include "peripherals/mini_uart.h"
#include "peripherals/gpio.h"

void uart_init (void)
{
    // GPIO 14, 15 func setting
    unsigned int selector;
    selector = get32(GPFSEL1);
    selector &= ~(7<<12);  
    // 7 binary 是 111 ，把 111 右移 12 bit (12-14 bit 為 111 )，之後翻轉 (~) 得到只有 12-14 bit 是 0，其他是 1 的 mask
    // selector 與此 mask 做 and (&) 可將 selector 12-14 bit 清 0 (GPIO 14 功能設定)
    selector |= (2<<12);    // 把 12-14 bit 設成 010 (select alternate function 5)
    selector &= ~(7<<15);   // GPIO 15 功能設定清 0
    selector |= (2<<15);    // GPIP 15 func setting
    put32(GPFSEL1, selector);

    //disable GPIO pull up/ down
    put32(GPPUD, 0); //disable pull-up/down
    delay(150);
    put32(GPPUDCLK0,(1<<14)|(1<<15)); // gpio 14,15 use gppud setting
    delay(150);
    put32(GPPUD, 0);
	put32(GPPUDCLK0,0);

    //uart setting
    put32(AUXENB,1); //enable mini uart
    put32(AUX_MU_CNTL_REG,0);
    put32(AUX_MU_IER_REG,0);
    put32(AUX_MU_LCR_REG,3);
    put32(AUX_MU_MCR_REG,0);
    put32(AUX_MU_BAUD, 270);
    put32(AUX_MU_IIR_REG,6);
    put32(AUX_MU_CNTL_REG,3);

}

char uart_recv()
{
    while(1) 
    {
		if(get32(AUX_MU_LSR_REG)&0x01) //ready 才 read
			break;
	}
    return (get32(AUX_MU_IO_REG)&0xFF); // uart 只有 low 8 bit 有效
}

void uart_send(char c)
{
    while (1)
    {
        if(get32(AUX_MU_LSR_REG) & 0x20) // transmitter have at leat 1 empty field
            break;   
    }
    put32(AUX_MU_IO_REG, c);
}

void uart_send_string (char* str)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        uart_send((char)str[i]);
    }
}

