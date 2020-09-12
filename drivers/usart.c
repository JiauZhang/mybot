#include <wilinker/usart.h>
#include <wilinker/serial.h>
#include <misc.h>
#include <stm32f10x.h>
#include <stdio.h>

static struct serial_device stm32_serial_drv = {
	.name   = "stm32_serial",
	.start  = usart_init,
	.stop   = NULL,
	.setbrg = NULL,
	.putc   = usart_putc,
	.puts   = usart_puts,
	.getc   = NULL,
};

int usart_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	
	return 0;
}

void usart_putc(const char c)
{
	USART_SendData(USART1, (uint8_t)c);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void usart_puts(const char *s)
{
	usart_putc('\n');
	usart_putc('\r');

	while (*s != '\0') {
		usart_putc(*s);
		s++;
	}
}

void stm32_serial_initialize(void)
{
	serial_register(&stm32_serial_drv);
}