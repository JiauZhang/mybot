#include <devices/led.h>
#include <devices/console.h>
#include <devices/spi.h>
#include <devices/nrf24l01.h>

void delay(unsigned int count)
{
	for(; count != 0; count--);
}

void start_project()
{
	led_init();
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