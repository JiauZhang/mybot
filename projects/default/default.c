#include <common/console.h>
#include <common/project.h>
#include <common/shell.h>

void start_project(void)
{
	show_prompt();
	
	while (1) {
		read_line();
	}
}