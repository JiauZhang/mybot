#ifndef __PWM_H__
#define __PWM_H__

void start_pwm();
void stop_pwm();

void set_pwm_period(unsigned int period);
unsigned int get_pwm_period();

void set_pwm_duty(unsigned int duty);
unsigned int get_pwm_duty();

#endif