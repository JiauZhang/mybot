#include <devices/nrf24l01.h>
#include <devices/console.h>

uint8_t RC_rxData[32];
// 接收地址RX_ADDR_P0 == RX_ADDR
const uint8_t RX_ADDRESS[]= {0x11,0x22,0x33,0x44,0x55};

void print_rx()
{
	int i;
	for (i=0; i<32; i++) {
		printh(RC_rxData[i]);
		printc(' ');
	}
	
	prints("\n");
}

void set_rx_mode(void)
{
	nrf24l01_enable_chip();
	
	//写RX节点地址
	nrf24l01_write_buf(SPI_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);
	//使能通道0的自动应答
	nrf24l01_write_reg(SPI_WRITE_REG+EN_AA,0x01);
	//使能通道0的接收地址
	nrf24l01_write_reg(SPI_WRITE_REG+EN_RXADDR,0x01);
	//设置RF通信频率
	nrf24l01_write_reg(SPI_WRITE_REG+RF_CH,45);
	//选择通道0的有效数据宽度 	    
	nrf24l01_write_reg(SPI_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);
	//设置TX发射参数,0db增益,2Mbps,低噪声增益开启
	nrf24l01_write_reg(SPI_WRITE_REG+RF_SETUP,0x27);
	//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,PRIM_RX接收模式 
	nrf24l01_write_reg(SPI_WRITE_REG+NCONFIG, 0x0f);
	
	nrf24l01_disable_chip();
}

u8 nrf24l01_receive_packet(u8 *rxbuf)
{
	u8 status;
	
	nrf24l01_enable_chip();
	
	status = nrf24l01_read_reg(STATUS);                       //读取状态寄存器的值
	nrf24l01_write_reg(SPI_WRITE_REG+STATUS,status);          //清除TX_DS或MAX_RT中断标志
	if(status & RX_OK)                                        //接收到数据
	{
		nrf24l01_read_buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);  //读取数据
		nrf24l01_write_reg(FLUSH_RX,0xff);                    //清除RX FIFO寄存器 
		return 0;
	}
	
	nrf24l01_disable_chip();
	
	return 1;
}

void set_mode()
{
	prints("check nrf24l01 device.\n");
	while(nrf24l01_check());
	prints("set nrf24l01 rx_mode.\n");
	set_rx_mode();
}

void remote_control()
{
	prints("nrf24l01 read data!\n");
	if (nrf24l01_receive_packet(RC_rxData))
		prints("no wireless data\n");
	else
		print_rx();
}