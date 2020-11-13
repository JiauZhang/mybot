#include <devices/pwm.h>
#include <common/console.h>
#include <stm32f10x.h>

void start_pwm()
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(
		RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,
		ENABLE
	);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	set_pwm_period(665);
	
	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 600;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);
}

void stop_pwm()
{
	prints("stop_pwm() is Not implemented!\n");
}

void set_pwm_period(unsigned int period)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	uint16_t prescale;
	
	prescale = (uint16_t) (SystemCoreClock / 24000000) - 1;
	TIM_TimeBaseStructure.TIM_Period = period;
	TIM_TimeBaseStructure.TIM_Prescaler = prescale;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
}

unsigned int get_pwm_period()
{
	prints("get_pwm_period() is Not implemented!\n");
	
	return -1;
}

void set_pwm_duty(unsigned int duty)
{
	prints("set_pwm_duty() is Not implemented!\n");
}

unsigned int get_pwm_duty()
{
	prints("get_pwm_duty() is Not implemented!\n");
	
	return -1;
}