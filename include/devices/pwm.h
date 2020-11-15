#ifndef __PWM_H__
#define __PWM_H__

void start_pwm();
void stop_pwm();

void set_pwm_period(unsigned short period);
unsigned short get_pwm_period();

void set_pwm1_duty(unsigned short duty);
void set_pwm2_duty(unsigned short duty);
void set_pwm3_duty(unsigned short duty);
void set_pwm4_duty(unsigned short duty);

unsigned short get_pwm1_duty();
unsigned short get_pwm2_duty();
unsigned short get_pwm3_duty();
unsigned short get_pwm4_duty();

#endif