#include <common/shell.h>
#include <common/console.h>

char cmd_line[CMD_LINE_SIZE] = {'\0'};
const char FIBOT_PROMPT[] = "FiBot> ";

void show_prompt()
{
	prints(FIBOT_PROMPT);
}

void read_line()
{
	cmd_line[0] = '\0';
	
	unsigned char exec, count;
	exec = 1;
	count = 0;
	char c = getc();
	
	while (c != KEY_ENTER) {
		if (count < (CMD_LINE_SIZE - 1)) {
			printc(c);
			cmd_line[count] = c;
			count++;
		} else {
			prints("\n");
			prints("Your input is TOO long!\n");
			show_prompt();
			exec = 0;
			break;
		}
		
		c = getc();
	}
	
	if (exec) {
		cmd_line[count] = '\0';
		prints("\n");
		prints("running a cmdline: ");
		prints(cmd_line);
		prints("\n");
		show_prompt();
	}
}