#include "cpio.h"
#include "utils.h"

cpio_file_t cpio_files[MAX_CPIO_FILES];

int cpio_file_count = 0;

int parse_cpio (void *start)
{   

    cpio_newc_header_t *header = (cpio_newc_header_t *)start;
    cpio_file_t *cpio_files_head = cpio_files;
    
    const char expected[7] = "070701";
    const char end[11] = "TRAILER!!!";
    

    int count = 0;

    while(1)
    {
        // magic check;
        for (int i = 0; i < 6; i++) 
        {
            if (header->c_magic[i] != expected[i])  return -1;
        }
        // name seze
        unsigned int namesize;
        namesize = utils_ascii_hex2dec(8, header -> c_namesize);

        // file neme
        char *filename =(char *)(header + 1);

        if(utils_str_compare((char*)end, filename)) break; // the end of cpio file

        cpio_files_head -> filename = filename;

        // mode
        cpio_files_head -> mode = utils_ascii_hex2dec(8, header -> c_mode);

        // file size & data
        unsigned int filesize = utils_ascii_hex2dec(8, header -> c_filesize);
        cpio_files_head -> filesize =  filesize;
        
        // align data
        unsigned long name_end_ptr = (unsigned long)(filename + namesize);
        unsigned char *data = (unsigned char *)utils_align_up((unsigned long)name_end_ptr, 4); 
        cpio_files_head -> data = data;

        // align next header
        unsigned long file_end_ptr =  (unsigned long)(data + filesize);
        header = (cpio_newc_header_t *)utils_align_up((unsigned long)file_end_ptr,4);
        
        cpio_files_head ++;
        count++;
    }
    return count;
}