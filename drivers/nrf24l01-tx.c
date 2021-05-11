#include <devices/nrf24l01.h>
#include <common/console.h>
#include "nrf24l01_config.h"

uint8_t tx_data[32] = {0xAA,0xAF,0x03,32-5,0x01,0x07,0x04,0x03,0x09,0x06,0x00,0x04,0x05,0x04};
// 配对密码，本地地址
const uint8_t TX_ADDRESS[]= {0x11,0x22,0x33,0x44,0x55};
// 接收地址RX_ADDR_P0 == RX_ADDR
const uint8_t RX_ADDRESS[]= {0x11,0x22,0x33,0x44,0x55};

/*
 * 该函数初始化NRF24L01到TX模式
 * 设置TX地址,写TX数据宽度,设置RX自动应答的地址,填充TX发送数据,
 * 选择RF频道,波特率和LNA HCURR PWR_UP,CRC使能
 * 当CE变高后,即进入RX模式,并可以接收数据了
 * CE为高大于10us,则启动发送.
 */
void set_tx_mode(void)
{
	nrf24l01_enable_chip();
	
	//写TX节点地址 
	nrf24l01_write_buf(SPI_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);
	//设置TX节点地址,主要为了使能ACK
	nrf24l01_write_buf(SPI_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);	
	//使能通道0的自动应答
	nrf24l01_write_reg(SPI_WRITE_REG+EN_AA,0x01);
	//使能通道0的接收地址
	nrf24l01_write_reg(SPI_WRITE_REG+EN_RXADDR,0x01);
	//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
	nrf24l01_write_reg(SPI_WRITE_REG+SETUP_RETR,0x1a);
	//设置RF通道为40
	nrf24l01_write_reg(SPI_WRITE_REG+RF_CH,45);
	//设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	nrf24l01_write_reg(SPI_WRITE_REG+RF_SETUP,0x27);  //0x27  250K   0x07 1M
	//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,PRIM_RX发送模式,开启所有中断
	nrf24l01_write_reg(SPI_WRITE_REG+NCONFIG,0x0e);
	
	nrf24l01_disable_chip();
}

u8 nrf24l01_send_packet(u8 *txbuf)
{
	u8 state;
	
	nrf24l01_enable_chip();
	
	nrf24l01_write_buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);  //写数据到TX BUF  32个字节
//	while(READ_NRF24L01_IRQ!=0);                           //等待发送完成
	state=nrf24l01_read_reg(STATUS);                       //读取状态寄存器的值
	nrf24l01_write_reg(SPI_WRITE_REG+STATUS,state);        //清除TX_DS或MAX_RT中断标志
	if(state & MAX_TX)                                     //达到最大重发次数
	{
		prints("Reach the MAX_TX!\n");
		nrf24l01_write_reg(FLUSH_TX,0xff);                 //清除TX FIFO寄存器 
		return MAX_TX; 
	}
	if(state & TX_OK)                                      //发送完成
	{
		return TX_OK;
	}
	
	nrf24l01_disable_chip();
	
	return 0xff;
}

void set_mode()
{
	prints("check nrf24l01 device.\n");
	while(nrf24l01_check());
	prints("set nrf24l01 tx_mode.\n");
	set_tx_mode();
}

void remote_control()
{
	nrf24l01_send_packet(tx_data);
}