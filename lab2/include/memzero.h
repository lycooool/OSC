#ifndef	_MEMZERO_H
#define	_MEMZERO_H

#define PAGE_SHIFT	 	12
#define TABLE_SHIFT 	9
#define SECTION_SHIFT	(PAGE_SHIFT + TABLE_SHIFT)

#define PAGE_SIZE   	(1 << PAGE_SHIFT)	
#define SECTION_SIZE	(1 << SECTION_SHIFT)	

#define LOW_MEMORY      (2 * SECTION_SIZE)

#ifndef __ASSEMBLER__ // Predefined Macro，if 正在編譯 asm 忽略此部分內容

void memzero(unsigned long src, unsigned long n); 

#endif

#endif  /*_MM_H */

