/**********************************************************************************
 * 文件名  ：usart1.c
 * 描述    ：将printf函数重定向到USART1。这样就可以用printf函数将单片机的数据
 *           打印到PC上的超级终端或串口调试助手。         
 * 实验平台亚博智能开发板
 * 硬件连接：------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
**********************************************************************************/
#include "usart3.h"
#include <stdarg.h>
#include "misc.h"
#include "commonhead.h"

//串口接收DMA缓存
uint8_t Uart3_Rx[UART4_REC_NUM] = {0};
u8 uart_byte_count=0;
u8 blu_char;
extern unsigned char mode_show;  //模式为1蓝牙控制模式，模式为2为循迹模式，模式3为屏障碍模式

/*
 * 函数名：USART3_Config
 * 描述  ：USART3 GPIO 配置,工作模式配置。115200 8-N-1
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void USART3_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;	//定义串口初始化结构体
	
	/* config USART3 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);
		/* config GPIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB	, ENABLE);
	/* USART3 GPIO config */
	/* Configure USART3 Tx (PB.10) as alternate function push-pull 推拉输出模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);    
	/* Configure USART3 Rx (PB.11) as input floating 浮点输入模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
  	
	
	NVIC_Configurationusart3(); 
	/* USART3 mode config */
	//USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_BaudRate = 9600;//波特率9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8位数据
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ;//无校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//禁用RTSCTS硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//使能发送接收
  

	USART_Init(USART3, &USART_InitStructure); 
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//使能接收中断
	
	USART_Cmd(USART3, ENABLE);
	
}




void NVIC_Configurationusart3(void)
{
   NVIC_InitTypeDef NVIC_InitStructure;
/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


/*串口3发送函数*/
void USART3_Send_Byte(unsigned char byte)   //串口发送一个字节
{
        USART_SendData(USART3, byte);        //通过库函数  发送数据
        while( USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);  
        //等待发送完成。   检测 USART_FLAG_TC 是否置1；    //见库函数 P359 介绍
        
}
void UART3_Send_Char(char *s)
{
	char *p;
	p=s;
	while(*p != '\0')
	{
		USART3_Send_Byte(*p);
		p++;
	}	
}

//输出字符串
void PrintChar(char *s)
{
	char *p;
	p=s;
	while(*p != '\0')
	{
		USART3_Send_Byte(*p);
		p++;
	}
}

//串口3中断服务程序
//extern unsigned char mode_show;  //模式为1蓝牙控制模式，模式为2为循迹模式，模式3为屏障碍模式
void USART3_IRQHandler(void)
{  
u8 rec_data;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断 
		{
				rec_data =(u8)USART_ReceiveData(USART3);         //(USART1->DR) 读取接收到的数据
			if(mode_show == 1)
			{
				if(rec_data=='W')		  	                         //如果是S，表示是命令信息的起始位
				{	
						blu_char = 'W';
						Go(300,300);
				}
				else if(rec_data=='S')
				{
						blu_char = 'S';
						Back(300,300);
				}
				else if(rec_data=='A')
				{
						blu_char = 'A';
						TurnL1(150,400);
				}
				else if(rec_data=='D')
				{
						blu_char = 'D';
						TurnR1(400,150);
				}
				else if(rec_data=='C')
				{
						blu_char = 'C';
						//TurnR1(400,150);
				}
			}
			
			if(rec_data=='#')		  	                         //如果是S，表示是命令信息的起始位
			{
				uart_byte_count=0x01; 
			}
			else if(rec_data=='E')		                         //如果E，表示是命令信息传送的结束位
			{
				if(strcmp("mode1",(char *)Uart3_Rx)==0)   	mode_show = 1;
				else if(strcmp("mode2",(char *)Uart3_Rx)==0)    mode_show = 2;
				else if(strcmp("mode3",(char *)Uart3_Rx)==0)    mode_show =3;
				
				for(uart_byte_count=0;uart_byte_count<32;uart_byte_count++)
					{
						Uart3_Rx[uart_byte_count]=0x00;
					}
					uart_byte_count=0;
					OLED_Clear();OLED_ShowChinese(36,20,0,16);OLED_ShowChinese(54,20,1,16);OLED_ShowNum(72,20,mode_show,1,16);OLED_Refresh();
			}		  
			else if((uart_byte_count>0)&&(uart_byte_count<=UART4_REC_NUM))
			{
				   Uart3_Rx[uart_byte_count-1]=rec_data;
				   uart_byte_count++;
			}   
			
//        if(rec_data=='1')			  	                         //如果是S，表示是命令信息的起始位
//				{
//					mode_show = 1;
//					//printf("%d",mode_show); 
//				}
//				else if(rec_data=='2')		
//				{
//					mode_show = 2;
//					//printf("helloworld2"); 
//				}
//				else if(rec_data=='3')		
//				{
//					mode_show = 3;
//					//printf("helloworld2"); 
//				}
		}
}		

