#ifndef _CPIO_H
#define _CPIO_H

#include <stdint.h>

#define MAX_CPIO_FILES 99

typedef struct __attribute__((packed)) cpio_newc_header {
   char    c_magic[6];
   char    c_ino[8];
   char    c_mode[8];
   char    c_uid[8];
   char    c_gid[8];
   char    c_nlink[8];
   char    c_mtime[8];
   char    c_filesize[8];
   char    c_devmajor[8];
   char    c_devminor[8];
   char    c_rdevmajor[8];
   char    c_rdevminor[8];
   char    c_namesize[8];
   char    c_check[8];
 }cpio_newc_header_t ;

typedef struct {
   const char *filename;   // 檔案名稱（指向 cpio 內部字串）
   unsigned int mode;    // 檔案型別 (regular / dir / symlink)
   unsigned int filesize;
   unsigned char *data;  // 檔案內容的位址
} cpio_file_t;

extern cpio_file_t cpio_files[MAX_CPIO_FILES];  
extern cpio_file_count;                  

int parse_cpio (void *start);

#endif