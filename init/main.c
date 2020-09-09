#include <wilinker/led.h>
#include <wilinker/usart.h>
#include <stm32f10x.h>
#include <stdio.h>

void delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

int main(void)
{
	led_init();
	usart_init();

	while (1)
	{
		printf("printf test\n");
		led_on();
		delay(0xfffff);
		delay(0xfffff);
		delay(0xfffff);
		delay(0xfffff);
		led_off();
		delay(0xfffff);
		delay(0xfffff);
		delay(0xfffff);
		delay(0xfffff);
	}
}