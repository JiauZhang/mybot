#include <common/console.h>
#include <common/project.h>
#include <common/shell.h>
#include <common/command.h>

int do_test(struct cmd_tbl *cmd, int argc, char *const argv[])
{
	prints("do_test\n");
	return 0;
}

FIBOT_CMD(test, do_test, "test", "test");

void start_project(void)
{
	show_prompt();
	
	do_help(0, 0, 0);
	
	while (1) {
		__fibot_cmd_test.cmd(0, 0, 0);
		read_line();
	}
}