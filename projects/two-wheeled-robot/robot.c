#include <common/console.h>
#include <devices/pwm.h>
#include <common/shell.h>
#include <common/project.h>

void start_project()
{
	int duty = 50;
	
	prints("start pwm devices......\n");
	start_pwm();
	
	prints("FiBot> ");
	while (1) {
		read_line();
		set_pwm1_duty(duty);
		duty += 100;
		
		if (duty >= 650)
			duty = 50;
	}
}