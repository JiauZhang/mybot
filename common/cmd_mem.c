/*
 * https://github.com/JiauZhang/FiBot/common/console.c
 */

#include <common/command.h>
#include <common/console.h>

int do_mem_read(cmd_t *cmd, int argc, char *const argv[])
{
	int status = 0;

	if (argc == 1 || argc > 3) {
		prints("%s\n", cmd->usage);
		status = -1;
	} else if (argc == 2) {
		
	} else {
		
	}
	
	return status;
}
FIBOT_CMD(mr, do_mem_read, "mr addr [size]", "read memory values");