/*
 * https://github.com/JiauZhang/FiBot/common/command.c
 */

#include <common/command.h>
#include <common/console.h>
#include <common/string.h>

extern unsigned int _cmd_tbl_start;
extern unsigned int _cmd_tbl_end;

#define get_cmd_tbl_start()                                           \
    ({                                                                \
        struct cmd_tbl *_start = (struct cmd_tbl *)&_cmd_tbl_start;   \
        _start;                                                       \
    })

#define get_cmd_tbl_end()                                             \
    ({                                                                \
        struct cmd_tbl *_end = (struct cmd_tbl *)&_cmd_tbl_end;       \
        _end;                                                         \
    })

#define get_cmd_tbl_next(start, end)                                  \
    ({                                                                \
        struct cmd_tbl *_next = start + 1;                            \
        if (_next > end)                                              \
            _next = end;                                              \
        _next;                                                        \
    })

struct cmd_tbl *find_cmd_tbl(const char *name)
{
	struct cmd_tbl *cmd = 0;
	struct cmd_tbl *cmd_tbl_start = get_cmd_tbl_start();
	struct cmd_tbl *cmd_tbl_end   = get_cmd_tbl_end();
	
	while (cmd_tbl_start != cmd_tbl_end) {
		if (strcmp(name, cmd_tbl_start->name) == 0) {
			cmd = cmd_tbl_start;
			break;
		} else {
			cmd_tbl_start = get_cmd_tbl_next(cmd_tbl_start, cmd_tbl_end);
		}
	}
	
	return cmd;
}

int run_cmd(struct cmd_tbl *cmd, int argc, char * const argv[])
{
	return cmd->cmd(cmd, argc, argv);
}

int do_help(struct cmd_tbl *cmd, int argc, char *const argv[])
{
	char *name, *help;
	int status = 0;
	struct cmd_tbl *cmd_tbl_start = get_cmd_tbl_start();
	struct cmd_tbl *cmd_tbl_end   = get_cmd_tbl_end();
	
	if (argc == 1) {
		if (cmd_tbl_start < cmd_tbl_end) {
			prints("FiBot shell commands:\n");
			
			do {
				name = cmd_tbl_start->name;
				help = cmd_tbl_start->help;
				prints("%s   - %s\n", name, help);
				cmd_tbl_start = get_cmd_tbl_next(cmd_tbl_start, cmd_tbl_end);
			} while (cmd_tbl_start != cmd_tbl_end);
		} else {
			prints("No commands availble!\n");
		}
	} else if (argc == 2) {
		cmd_tbl_start = find_cmd_tbl(argv[1]);
		
		if (cmd_tbl_start) {
			prints("%s\n", cmd_tbl_start->usage);
		} else {
			prints("No command match \'%s\'.\n", argv[1]);
			status = -1;
		}
	} else {
		prints("Try \'help help\' for more info.\n");
		status = -2;
	}
	
	return status;
}
FIBOT_CMD(help, do_help, "help [command]", "show command\'s help info");

int do_clear(struct cmd_tbl *cmd, int argc, char *const argv[])
{
	prints("\x1b[2J\x1b[H");
	return 0;
}
FIBOT_CMD(clear, do_clear, "clear", "clear screen");

int do_reboot(struct cmd_tbl *cmd, int argc, char *const argv[])
{
	extern void Reset_Handler(void);
	
	prints("System is rebooting from %d.\n", Reset_Handler);	
	Reset_Handler();
	
	return -1;
}
FIBOT_CMD(reboot, do_reboot, "reboot", "reboot the system");