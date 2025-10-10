#include "mini_uart.h"
#include "utils.h"
#include <stddef.h>

#define BUFFER_MAX_SIZE 256u

void read_command(char *buffer)
{
    size_t index = 0;
    while (1)
    {
        buffer[index] = uart_recv();
        uart_send(buffer[index]);

        if(buffer[index] == '\n' || buffer[index] == '\r')
            break;

        index ++;
    }
    buffer[index] = '\0';   
}

void help()
{
    uart_send_string("help     :");
    uart_send_string("print this help menu\r\n");
    uart_send_string("hello    :");
    uart_send_string("print Hello World!\r\n");
}

void hello()
{
    uart_send_string("Hello World!\r\n");
}

void parse_command (char *buffer){
    if(utils_str_compare(buffer, "help"))
        help();
    else if(utils_str_compare(buffer, "hello"))
        hello();
    else 
        uart_send_string("unknow command\r\n");
}

void shell(){
    while(1){
        char buffer[BUFFER_MAX_SIZE];
        uart_send_string("$ ");
        read_command(buffer);
        parse_command(buffer);
    }
}
