#include "mini_uart.h"
#include "utils.h"
#include <stddef.h>
#include <mailbox.h>
#include <reboot.h>
#include <cpio.h>

#define BUFFER_MAX_SIZE 256u

void read_command(char *buffer)
{
    size_t index = 0;
    while (1)
    {
        buffer[index] = uart_recv();
        uart_send(buffer[index]);

        if(buffer[index] == ' ') 
            buffer[index] = '\0';

        if(buffer[index] == '\n' || buffer[index] == '\r')
            break;

        index ++;
    }
    buffer[index] = '\0';   
}

void ls()
{
    for (int i = 0; i < cpio_file_count; i++) {
        uart_send_string(cpio_files[i].filename);
        uart_send('\r\n');
    }
}
void cat(char *filename){
    int find = -1;
    for (int i = 0; i < cpio_file_count; i++) {
        if(utils_str_compare(filename, cpio_files[i].filename))
        {
            find = i;
            break;
        }
    }

    if (find == -1)
    {
        uart_send_string("No such file or directory\r\n");
    }
    else
    {
        uart_send_string("file name: ");
        uart_send_string(cpio_files[find].filename);
        uart_send_string("\r\n");
        unsigned int size = cpio_files[find].filesize;
        unsigned char *data = cpio_files[find].data;
        for(int i = 0; i < size; i++)
        {
            if(data[i] != '\n')uart_send(data[i]);
            else uart_send_string("\r\n"); 
        }
    }
}

void help()
{
    uart_send_string("help     :");
    uart_send_string("print this help menu\r\n");
    uart_send_string("hello    :");
    uart_send_string("print Hello World!\r\n");
    uart_send_string("HW info  :");
    uart_send_string("print hardware information\r\n");
    uart_send_string("ls  :");
    uart_send_string("list files\r\n");
    uart_send_string("cat  file name:");
    uart_send_string("catch file\r\n");
    uart_send_string("reboot   :");
    uart_send_string("reboot system\r\n");
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
    else if(utils_str_compare(buffer, "HW info"))
        get_HW_info();
    else if(utils_str_compare(buffer, "reboot"))
        reset(16);
    else if(utils_str_compare(buffer, "ls"))
        ls();
    else if(utils_str_compare(buffer, "cat"))
        cat(buffer + 4);
    else 
        uart_send_string("unknow command\r\n");
}

void shell(){
    while(1){
        char buffer[BUFFER_MAX_SIZE];
        uart_send_string("$ ");
        read_command(buffer);
        uart_send_string("$ ");
        uart_send_string(buffer);
        uart_send_string("\r\n");
        parse_command(buffer);
    }
}
