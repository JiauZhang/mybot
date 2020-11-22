#ifndef __SHELL_H__
#define __SHELL_H__

#define CMD_LINE_SIZE        64
#define CMD_LINE_MAX_ARGS    6

#define KEY_ENTER       0x0d

void show_prompt();

int read_line();
int parse_line(char *cmdline, char *argv[]);
void print_argv(char *argv[]);

#endif