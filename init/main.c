#include <wilinker/led.h>
#include <wilinker/console.h>
#include <wilinker/spi.h>
#include <wilinker/nrf24l01.h>
#include <stm32f10x.h>

void delay(uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}



int main(void)
{
	led_init();
	stdio_init();
	prints("console is avaiable.\n");
	spi_init();
	prints("SPI1 has initialized.\n");
	nrf24l01_init();
	prints("nrf24l01 has initialized!\n");

	while (1)
	{
		led_on();
		delay(0xfffff);
		delay(0xfffff);
		
		remote_control();
		
		led_off();
		delay(0xfffff);
		delay(0xfffff);
	}
}