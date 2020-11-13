#include <common/console.h>
#include <devices/pwm.h>
#include <common/shell.h>
#include <common/project.h>

void start_project()
{
	prints("start pwm devices......\n");
	start_pwm();
	
	prints("FiBot> ");
	while (1) {
		read_line();
	}
}