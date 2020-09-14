#include <wilinker/led.h>
// #include <wilinker/serial.h>
#include <wilinker/console.h>
#include <wilinker/spi.h>
#include <stm32f10x.h>

void delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

int main(void)
{
	unsigned char count = 'a';
	
	led_init();
	stdio_init();
	spi_init();

	while (1)
	{
		puts("stdio puts: ");
		led_on();
		spi_write('s');
		delay(0xfffff);
		delay(0xfffff);
		led_off();
		
		if ('s' == spi_read())
			count++;
		if (count > 'z')
			count = 'a';
		
		putc(count);
		delay(0xfffff);
		delay(0xfffff);
	}
}