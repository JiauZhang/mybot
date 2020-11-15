#include <devices/pwm.h>
#include <common/console.h>
#include <stm32f10x.h>

void start_pwm()
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	unsigned short prescale;
	
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
	
	TIM_TimeBaseStructure.TIM_Period = 665;
	prescale = (SystemCoreClock / 24000000) - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = prescale;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_Cmd(TIM3, ENABLE);
}

inline void stop_pwm()
{
	TIM_CtrlPWMOutputs(TIM3, DISABLE);
}

inline void set_pwm1_duty(unsigned short period)
{
	TIM_SetCompare1(TIM3, period);
}

inline void set_pwm2_duty(unsigned short period)
{
	TIM_SetCompare2(TIM3, period);
}

inline void set_pwm3_duty(unsigned short period)
{
	TIM_SetCompare3(TIM3, period);
}

inline void set_pwm4_duty(unsigned short period)
{
	TIM_SetCompare4(TIM3, period);
}

inline unsigned short get_pwm1_duty()
{
	return TIM_GetCapture1(TIM3);
}

inline unsigned short get_pwm2_duty()
{
	return TIM_GetCapture2(TIM3);
}

inline unsigned short get_pwm3_duty()
{
	return TIM_GetCapture3(TIM3);
}

inline unsigned short get_pwm4_duty()
{
	return TIM_GetCapture4(TIM3);
}

inline void set_pwm_period(unsigned short period)
{
	TIM_SetAutoreload(TIM3, period);
}

inline unsigned short get_pwm_period()
{
	prints("get_pwm_period() is Not implemented!\n");
	
	return -1;
}