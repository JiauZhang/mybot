/*
 * https://github.com/JiauZhang/FiBot/common/command.c
 */

#include <common/command.h>
#include <common/console.h>
#include <common/string.h>

extern unsigned int _cmd_entry_start;
extern unsigned int _cmd_entry_end;

#define get_cmd_entry_start()                                         \
    ({                                                                \
        cmd_t *_start = (cmd_t *)&_cmd_entry_start;                   \
        _start;                                                       \
    })

#define get_cmd_entry_end()                                           \
    ({                                                                \
        cmd_t *_end = (cmd_t *)&_cmd_entry_end;                       \
        _end;                                                         \
    })

#define get_cmd_entry_next(start, end)                                \
    ({                                                                \
        cmd_t *_next = start + 1;                                     \
        if (_next > end)                                              \
            _next = end;                                              \
        _next;                                                        \
    })

cmd_t *find_cmd_entry(const char *name)
{
	cmd_t *cmd = 0;
	cmd_t *cmd_entry_start = get_cmd_entry_start();
	cmd_t *cmd_entry_end   = get_cmd_entry_end();
	
	while (cmd_entry_start != cmd_entry_end) {
		if (strcmp(name, cmd_entry_start->name) == 0) {
			cmd = cmd_entry_start;
			break;
		} else {
			cmd_entry_start = get_cmd_entry_next(cmd_entry_start, cmd_entry_end);
		}
	}
	
	return cmd;
}

int run_cmd(cmd_t *cmd, int argc, char * const argv[])
{
	return cmd->cmd(cmd, argc, argv);
}

int do_help(cmd_t *cmd, int argc, char *const argv[])
{
	char *name, *help;
	int status = 0;
	cmd_t *cmd_entry_start = get_cmd_entry_start();
	cmd_t *cmd_entry_end   = get_cmd_entry_end();
	
	if (argc == 1) {
		if (cmd_entry_start < cmd_entry_end) {
			prints("FiBot shell commands:\n");
			
			do {
				name = cmd_entry_start->name;
				help = cmd_entry_start->help;
				prints("%s   - %s\n", name, help);
				cmd_entry_start = get_cmd_entry_next(cmd_entry_start, cmd_entry_end);
			} while (cmd_entry_start != cmd_entry_end);
		} else {
			prints("No commands availble!\n");
		}
	} else if (argc == 2) {
		cmd_entry_start = find_cmd_entry(argv[1]);
		
		if (cmd_entry_start) {
			prints("%s\n", cmd_entry_start->usage);
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

int do_clear(cmd_t *cmd, int argc, char *const argv[])
{
	prints("\x1b[2J\x1b[H");
	return 0;
}
FIBOT_CMD(clear, do_clear, "clear", "clear screen");

int do_reboot(cmd_t *cmd, int argc, char *const argv[])
{
	extern void Reset_Handler(void);
	
	prints("System is rebooting from %d.\n", Reset_Handler);	
	Reset_Handler();
	
	return -1;
}
FIBOT_CMD(reboot, do_reboot, "reboot", "reboot the system");