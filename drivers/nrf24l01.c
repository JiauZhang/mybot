#include <devices/nrf24l01.h>
#include <devices/spi.h>
#include "nrf24l01_config.h"

void nrf24l01_deselect_chip()
{
	GPIOB->BSRR = GPIOB_PIN_CSN;
}

void nrf24l01_select_chip()
{
	GPIOB->BRR = GPIOB_PIN_CSN;
}

void nrf24l01_enable_chip()
{
	GPIOA->BRR = GPIOA_PIN_CE;
}

void nrf24l01_disable_chip()
{
	GPIOA->BSRR = GPIOA_PIN_CE;
}

void nrf24l01_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIOA_PIN_CE;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIOB_PIN_CSN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	nrf24l01_disable_chip();
	nrf24l01_deselect_chip();

	GPIO_InitStructure.GPIO_Pin = GPIOA_PIN_IRQ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIOA_PIN_IRQ);

	nrf24l01_enable_chip();
	
	set_mode();
}

u8 nrf24l01_check(void)
{
	u8 wbuf[5]={'W', 'i', 'L', 'i', 'n'};
	u8 rbuf[5];
	u8 i;

	nrf24l01_enable_chip();
	nrf24l01_write_buf(SPI_WRITE_REG+TX_ADDR, wbuf, 5);
	nrf24l01_read_buf(TX_ADDR, rbuf, 5);
	nrf24l01_disable_chip();

	for (i=0;i<5;i++)
		if (rbuf[i] != wbuf[i])
			return 1;

	return 0;
}

u8 nrf24l01_write_reg(u8 addr,u8 data)
{
	u8 status;
	
	nrf24l01_select_chip();
	
	spi_write(addr);
	status = spi_read();
	spi_write(data);
	(void)spi_read();
	
	nrf24l01_deselect_chip();

	return status;
}

u8 nrf24l01_read_reg(u8 addr)
{
	u8 res;
	
	nrf24l01_select_chip();
	
	spi_write(addr);
	(void)spi_read();
	spi_write(0xff);
	res = spi_read();
	
	nrf24l01_deselect_chip();
	
	return res;
}

u8 nrf24l01_read_buf(u8 addr,u8 *buf,u8 len)
{
	u8 status, i;
	
	nrf24l01_select_chip();
	
	spi_write(addr);
	status = spi_read();
	for(i=0; i<len; i++) {
		spi_write(0xff);
		buf[i] = spi_read();
	}
	
	nrf24l01_deselect_chip();
	
	return status;
}

u8 nrf24l01_write_buf(u8 addr, u8 *buf, u8 len)
{
	u8 status, i;
	
	nrf24l01_select_chip();
	
	spi_write(addr);
	status = spi_read();
	for(i=0; i<len; i++) {
		spi_write(*buf++);
		spi_read();
	}

	nrf24l01_deselect_chip();
	
	return status;
}