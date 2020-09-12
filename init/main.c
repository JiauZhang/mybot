#include <wilinker/led.h>
#include <wilinker/usart.h>
#include <wilinker/spi.h>
#include <stm32f10x.h>
#include <stdio.h>

void delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

int main(void)
{
	unsigned char count = 'a';
	
	led_init();
	usart_init();
	spi_init();

	while (1)
	{
		usart_puts("printf test");
		led_on();
		spi_write('s');
		delay(0xfffff);
		delay(0xfffff);
		led_off();
		
		if ('s' == spi_read())
			count++;
		if (count > 'z')
			count = 'a';
		
		usart_putc(count);
		delay(0xfffff);
		delay(0xfffff);
	}
}