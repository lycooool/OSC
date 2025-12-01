#ifndef _SHELL_H
#define _SHELL_H

void shell();
void read_command(char *str);
void parse_command(char *str);
void help();
void hello();
void ls();
void  cat(char *filename);
void memAlloc(char* wanted_size);
#endif