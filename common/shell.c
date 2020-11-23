#include <common/shell.h>
#include <common/console.h>

char cmd_line[CMD_LINE_SIZE] = {'\0'};
char *argv[CMD_LINE_MAX_ARGS+1] = {0};

const char FIBOT_PROMPT[] = "FiBot> ";

void show_prompt()
{
	prints(FIBOT_PROMPT);
}

int read_line()
{
	cmd_line[0] = '\0';
	
	unsigned int count = 0;
	char c = getc();
	
	while (c != KEY_ENTER) {
		if (count < (CMD_LINE_SIZE - 1)) {
			printc(c);
			cmd_line[count] = c;
			count++;
		} else {
			prints("\nYour input is TOO long!\n");
			show_prompt();
			break;
		}
		
		c = getc();
	}
	
	prints("\n");
	cmd_line[count] = '\0';
	
	return count;
}

int parse_line(char *cmdline, char *argv[])
{
	int argc = 0;
	
	while (argc < CMD_LINE_MAX_ARGS) {
		while (*cmdline == ' ')
			cmdline++;
		
		if (*cmdline == '\0') {
			argv[argc] = 0;
			return argc;
		}
		
		argv[argc++] = cmdline;
		
		while ((*cmdline != '\0') && (*cmdline != ' '))
			cmdline++;
		
		if (*cmdline == '\0') {
			argv[argc] = 0;
			return argc;
		}
		
		*(cmdline++) = '\0';
	}
	
	return argc;
}

void print_argv(char *argv[])
{
	int argc = 0;
	
	while (*argv != 0)
		prints("argv[%d]: %s\n", argc++, *(argv++));
}