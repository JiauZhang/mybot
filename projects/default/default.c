#include <devices/console.h>
#include <common/project.h>

void start_project(void)
{
	prints("FiBot default empty project!\n");
	prints("echo>");
	
	char echo;
	while (1) {
		printc('+');
		echo = getc();
		printc(echo);
		printc('+');
	}
}