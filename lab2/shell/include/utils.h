#ifndef _UTILS_H
#define _UTILS_H

// 去看 AArch64 呼叫慣例 (AArch64 PCS) 可知道傳入的參數在 asm 中會放在哪
extern void delay ( unsigned long);


/*
string part
*/
int utils_str_compare(char* a, char* b);
void utils_uint2str_hex(unsigned int num, char *str);
void utils_uint2str_dec(unsigned int num, char *str);
unsigned int utils_ascii_hex2dec(int num_of_digits, char *str);

#endif	/*_BOOT_H */ 