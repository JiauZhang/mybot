#include <wilinker/nrf24l01.h>
#include <wilinker/console.h>

uint8_t RC_rxData[32];
const uint8_t RX_ADDRESS[]= {0x11,0x22,0x33,0x44,0x55};	//接收地址RX_ADDR_P0 == RX_ADDR

void print_rx()
{
	int i;
	for (i=0; i<32; i++) {
		printh(RC_rxData[i]);
		printc(' ');
	}
	
	prints("\n");
}

//该函数初始化NRF24L01到RX模式
//设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR
//当CE变高后,即进入RX模式,并可以接收数据了
void RX_Mode(void)
{
	Clr_NRF24L01_CE;
    //写RX节点地址
  	NRF24L01_Write_Buf(SPI_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);

    //使能通道0的自动应答    
  	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_AA,0x01);
    //使能通道0的接收地址  	 
  	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_RXADDR,0x01);
    //设置RF通信频率
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_CH,45);	   //(要改单机控制，就把45改成跟遥控器单独一样的。就可以单机控制了)
    //选择通道0的有效数据宽度 	    
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);
    //设置TX发射参数,0db增益,2Mbps,低噪声增益开启
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_SETUP,0x27);//0x0f
    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,PRIM_RX接收模式 
  	NRF24L01_Write_Reg(SPI_WRITE_REG+NCONFIG, 0x0f);
    //CE为高,进入接收模式
  	Set_NRF24L01_CE;
}

//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:0，接收完成；其他，错误代码
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 state;
	state=NRF24L01_Read_Reg(STATUS);                //读取状态寄存器的值
	NRF24L01_Write_Reg(SPI_WRITE_REG+STATUS,state); //清除TX_DS或MAX_RT中断标志
	if(state&RX_OK)                                 //接收到数据
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//读取数据
		NRF24L01_Write_Reg(FLUSH_RX,0xff);          //清除RX FIFO寄存器 
		return 0; 
	}	   
	return 1;                                      //没收到任何数据
}

void set_mode()
{
	prints("check nrf24l01 device.\n");
	while(NRF24L01_Check());
	prints("set nrf24l01 rx_mode.\n");
	RX_Mode();
}

void remote_control()
{
	prints("nrf24l01 read data!\n");
	if (NRF24L01_RxPacket(RC_rxData))
		prints("no wireless data\n");
	else
		print_rx();
}