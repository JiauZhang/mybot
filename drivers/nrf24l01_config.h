#ifndef __NRF24L01_CONFIG_H__
#define __NRF24L01_CONFIG_H__

#include <stm32f10x.h>

// nrf24l01 引脚连线
#define GPIOB_PIN_CSN GPIO_Pin_13
#define GPIOA_PIN_CE  GPIO_Pin_11
#define GPIOA_PIN_IRQ GPIO_Pin_12

//NRF24L01发送接收数据宽度定义
#define TX_ADR_WIDTH    5     //5字节的地址宽度
#define RX_ADR_WIDTH    5     //5字节的地址宽度
#define TX_PLOAD_WIDTH  32    //20字节的用户数据宽度
#define RX_PLOAD_WIDTH  32    //20字节的用户数据宽度

#endif