#ifndef __COMMAND_H__
#define __COMMAND_H__

struct cmd_tbl {
	char *name;
	char *desc;
	char *usage;
	
	int (*cmd)(struct cmd_tbl *cmd, int argc, char *const argv[]);
};

#define FIBOT_CMD {}

#endif