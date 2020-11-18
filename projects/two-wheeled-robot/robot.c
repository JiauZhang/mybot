#include <common/console.h>
#include <devices/pwm.h>
#include <common/shell.h>
#include <common/project.h>
#include <common/command.h>

void start_project()
{
	int duty = 1;
	
	prints("start pwm devices......\n");
	start_pwm();
	
	prints("FiBot> ");
	while (1) {
		read_line();
		if (duty) {
			set_pwm1_duty(1000);
			set_pwm2_duty(0);
		} else {
			set_pwm1_duty(0);
			set_pwm2_duty(1000);
		}
		
		duty = !duty;
	}
}