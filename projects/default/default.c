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

extern char cmd_line[CMD_LINE_SIZE];
extern char *argv[CMD_LINE_MAX_ARGS+1];

void start_project(void)
{
	unsigned int loop = 0;
	prints("This is the default project!\n");
	while (1) {
		prints("loop: %d\n", loop++);
		show_prompt();
		read_line();
		parse_line(cmd_line, argv);
		print_argv(argv);
	}
}