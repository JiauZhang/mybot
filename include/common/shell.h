#ifndef __SHELL_H__
#define __SHELL_H__

#define CMD_LINE_SIZE        64
#define CMD_LINE_MAX_ARGS    6

#define KEY_ENTER       0x0d

extern void show_prompt(void);

extern int read_line(void);
extern int parse_line(char *cmdline, char *argv[]);
extern void print_argv(char *argv[]);

#endif