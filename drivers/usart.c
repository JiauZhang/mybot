#include <common/serial.h>
#include <misc.h>
#include <stm32f10x.h>

int usart_init(void);
void usart_putc(const char c);
// void usart_puts(const char *s);
char usart_getc();

static struct serial_device stm32_serial_drv = {
	.name   = "stm32_serial",
	.start  = usart_init,
	.stop   = 0,
	.setbrg = 0,
	.putc   = usart_putc,
	.getc   = usart_getc,
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

/*
void usart_puts(const char *s)
{
	const char *c = s;
	
	while (*s != '\0') {
		usart_putc(*s);
		s++;
	}
	
	if (s > c && *(s-1) == '\n') {
		usart_putc('\r');
	}
}
*/

char usart_getc()
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	return (char)USART_ReceiveData(USART1);
}

void stm32_serial_initialize(void)
{
	serial_register(&stm32_serial_drv);
}