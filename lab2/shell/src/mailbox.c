#include "mailbox.h"
#include "utils.h"
#include "mini_uart.h"

volatile unsigned int  __attribute__((aligned(16))) mailbox[12];

int mailbox_call(unsigned char channel)
{
    unsigned int r = (((unsigned int)((unsigned long)&mailbox)&~0xF) | (channel&0xF)); // combine message address and channel
    do{asm volatile("nop");} while(*MAILBOX_STATUS & MAILBOX_FULL); // busy wait until not full
    *MAILBOX_WRITE = r; // write to mailbox1 wake up gpu
    while (1)
    {
        do{asm volatile("nop");} while(*MAILBOX_STATUS & MAILBOX_EMPTY);
        
        if(*MAILBOX_READ == r) return mailbox[1];
    }
    return 0;
    
}

/*
mailbox buffer format
u32: buffer size in bytes (including the header values, the end tag and padding)
u32: buffer request/response code
u8...: sequence of concatenated tags // 可放多個 tag
u32: 0x0 (end tag)

Tag format:

u32: tag identifier
u32: value buffer size in bytes
u32:
Request codes:
b31 clear: request
b30-b0: reserved
Response codes:
b31 set: response
b30-b0: value length in bytes
u8...: value buffer
u8...: padding to align the tag to 32 bits.

unsigned int mailbox[n]
mailbox[0] buffer size in bytes
mailbox[1] request/response code
mailbox[2 to n-2] tags area
mailbox[n] end of tags
*/

void get_HW_info(){
    mailbox[0] = (2u + 4u + 5u + 1u) * 4u; // buffer size in bytes
    mailbox[1] = REQUEST_CODE;
    // tag1 begin total 4 
    mailbox[2] = GET_BOARD_REVISION; // tag identifier
    mailbox[3] = 4u; //  value buffer size in bytes
    mailbox[4] = TAG_REQUEST_CODE;
    mailbox[5] = 0u; // reply
    // tag 2 begin // total 5
    mailbox[6] = GET_ARM_MEMORY; 
    mailbox[7] = 8u; //  value buffer size in bytes
    mailbox[8] = TAG_REQUEST_CODE; 
    mailbox[9] = 0u; // reply
    mailbox[10] = 0u; // reply
    // tags end
    mailbox[11] = END_TAG;

    mailbox_call(8); // use channel 8  
    
    char tmp_buffer[256];
    // board vision
    utils_uint2str_hex(mailbox[5], tmp_buffer);
    uart_send_string("board vision      : ");
    uart_send_string(tmp_buffer);
    uart_send_string("\r\n");;
    // mem base address
    uart_send_string("mem base address  : ");
    utils_uint2str_hex(mailbox[9], tmp_buffer);
    uart_send_string(tmp_buffer);
    uart_send_string("\r\n");
    // mem base size
    uart_send_string("mem size          : ");
    utils_uint2str_dec(mailbox[10], tmp_buffer);
    uart_send_string(tmp_buffer);
    uart_send_string("\r\n");
}
