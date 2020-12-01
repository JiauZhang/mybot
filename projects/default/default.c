#include <common/console.h>
#include <common/project.h>
#include <common/shell.h>
#include <common/command.h>

extern char cmd_line[CMD_LINE_SIZE];
extern char *argv[CMD_LINE_MAX_ARGS+1];

void start_project(void)
{
	int argc;
	cmd_t *cmd;
	
	prints("\nThis is the default project!\n");
	while (1) {
		show_prompt();
		read_line();
		argc = parse_line(cmd_line, argv);
		
		if (argc) {
			print_argv(argv);
			cmd = find_cmd_entry(argv[0]);
			
			if (cmd)
				run_cmd(cmd, argc, argv);
			else
				prints("Unknown command!\n");
		} else {
			cmd = (cmd_t *)0;
		}
	}
}