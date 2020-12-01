#ifndef __COMMAND_H__
#define __COMMAND_H__

struct cmd_entry {
	char *name;
	int (*cmd)(struct cmd_entry *cmd, int argc, char *const argv[]);
	char *usage;
	char *help;
};

#define FIBOT_CMD(__name, __usage, __help, __cmd)                \
    const struct cmd_entry __fibot_cmd_##__name                    \
        __attribute__((unused, section(".fibot_cmd_tbl"))) = {   \
        #__name, __usage, __help, __cmd                          \
    }

typedef struct cmd_entry cmd_t;

cmd_t *find_cmd_entry(const char *name);
int run_cmd(cmd_t *cmd, int argc, char * const argv[]);

#endif