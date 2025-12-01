#include <stdint.h>
#include <stddef.h> 

#include "utils.h"

/*
string part
*/
int utils_str_compare(char *a, char *b){ //if same return 1
    char aa, bb;
    while(1)
    {
        aa = (char)*a++;
        bb = (char)*b++;
        if (aa != bb)
            return 0;
        if (aa == '\0')
            return 1;
    }
}

void utils_uint2str_hex(unsigned int num, char *str){

    // write 0x
    *str = '0';
    str++;
    *str = 'x';
    str++;
    unsigned int temp = num;
    int digit = -1;

    if (num == 0) {         
        *str = '0';
        str ++;
        *str = '\0';
        return;
    }

    while (temp > 0)
    {
        temp /= 16;
        digit++;
    }
    for (int i = digit; i >= 0; i--)
    {
        int t = 1;
        for (int j = 0; j < i; j++)
        {
            t *= 16;
        }
        if (num / t >= 10) *str = 'a' + (num / t - 10);
        else *str = '0' + num / t;
        num = num % t;
        str++;
    }
    *str = '\0';
}

void utils_uint2str_dec(unsigned int num, char *str)
{

    unsigned int temp = num;
    int digit = -1;
    while (temp > 0)
    {
        temp /= 10;
        digit++;
    }
    for (int i = digit; i >= 0; i--)
    {
        int t = 1;
        for (int j = 0; j < i; j++)
        {
            t *= 10;
        }
        *str = '0' + num / t;
        num = num % t;
        str++;
    }
    *str = '\0';
}

unsigned int utils_ascii_hex2dec(int num_of_digits, char *str)
{
    unsigned int value = 0;

    for (int i = 0; i < num_of_digits; i++) {
        char c = str[i];
        value <<= 4;  // shift left 4 bits (hex digit)

        if (c >= '0' && c <= '9') {
            value |= (c - '0');
        } else if (c >= 'A' && c <= 'F') {
            value |= (c - 'A' + 10);
        } else if (c >= 'a' && c <= 'f') {
            value |= (c - 'a' + 10);
        }
    }

    return value;
}

unsigned int utils_ascii_dec2dec(int num_of_digits, char *str)
{
    unsigned int value = 0;
    int i = 0;

    if (num_of_digits > 0)
    {
        while (i < num_of_digits) {
            char c = str[i];
            value = value * 10 + (c - '0');
            i++;
        }
    }
    else // get string mode
    {   
        while(str[i]!='\0')
        {
            char c = str[i];
            value = value * 10 + (c - '0');
            i++;
        }
    }
    

    return value;
}

/*
other part
*/
size_t  utils_align_up(size_t  value, size_t  alignment)
{
    unsigned long mask = alignment - 1;
    return (value + mask) & ~mask;
}