#ifndef __COMMAND_H__
#define __COMMAND_H__

struct cmd_tbl {
	char *name;
	int (*cmd)(struct cmd_tbl *cmd, int argc, char *const argv[]);
	char *usage;
	char *help;
};

#define FIBOT_CMD(__name, __usage, __help, __cmd)                \
    const struct cmd_tbl __fibot_cmd_##__name                    \
        __attribute__((unused, section(".fibot_cmd_tbl"))) = {   \
        #__name, __usage, __help, __cmd                          \
    }

#endif