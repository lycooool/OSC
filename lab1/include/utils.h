#ifndef _UTILS_H
#define _UTILS_H

// 去看 AArch64 呼叫慣例 (AArch64 PCS) 可知道傳入的參數在 asm 中會放在哪
extern void delay ( unsigned long);


/*
string part
*/
int utils_str_compare(char* a, char* b);

#endif	/*_BOOT_H */ 