/**********************************************************************************
 * �ļ���  ��usart1.c
 * ����    ����printf�����ض���USART1�������Ϳ�����printf��������Ƭ��������
 *           ��ӡ��PC�ϵĳ����ն˻򴮿ڵ������֡�         
 * ʵ��ƽ̨�y�ǲ����ܿ�����
 * Ӳ�����ӣ�------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
**********************************************************************************/
#include "usart3.h"
#include <stdarg.h>
#include "misc.h"
#include "commonhead.h"

//���ڽ���DMA����
uint8_t Uart3_Rx[UART4_REC_NUM] = {0};
u8 uart_byte_count=0;
u8 blu_char;
extern unsigned char mode_show;  //ģʽΪ1��������ģʽ��ģʽΪ2Ϊѭ��ģʽ��ģʽ3Ϊ���ϰ�ģʽ

/*
 * ��������USART3_Config
 * ����  ��USART3 GPIO ����,����ģʽ���á�115200 8-N-1
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void USART3_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;	//���崮�ڳ�ʼ���ṹ��
	
	/* config USART3 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);
		/* config GPIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB	, ENABLE);
	/* USART3 GPIO config */
	/* Configure USART3 Tx (PB.10) as alternate function push-pull �������ģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);    
	/* Configure USART3 Rx (PB.11) as input floating ��������ģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
  	
	
	NVIC_Configurationusart3(); 
	/* USART3 mode config */
	//USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_BaudRate = 9600;//������9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ����
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;//��У��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//����RTSCTSӲ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//ʹ�ܷ��ͽ���
  

	USART_Init(USART3, &USART_InitStructure); 
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�
	
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


/*����3���ͺ���*/
void USART3_Send_Byte(unsigned char byte)   //���ڷ���һ���ֽ�
{
        USART_SendData(USART3, byte);        //ͨ���⺯��  ��������
        while( USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);  
        //�ȴ�������ɡ�   ��� USART_FLAG_TC �Ƿ���1��    //���⺯�� P359 ����
        
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

//����ַ���
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

//����3�жϷ������
//extern unsigned char mode_show;  //ģʽΪ1��������ģʽ��ģʽΪ2Ϊѭ��ģʽ��ģʽ3Ϊ���ϰ�ģʽ
void USART3_IRQHandler(void)
{  
u8 rec_data;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж� 
		{
				rec_data =(u8)USART_ReceiveData(USART3);         //(USART1->DR) ��ȡ���յ�������
			if(mode_show == 1)
			{
				if(rec_data=='W')		  	                         //�����S����ʾ��������Ϣ����ʼλ
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
			
			if(rec_data=='#')		  	                         //�����S����ʾ��������Ϣ����ʼλ
			{
				uart_byte_count=0x01; 
			}
			else if(rec_data=='E')		                         //���E����ʾ��������Ϣ���͵Ľ���λ
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
			
//        if(rec_data=='1')			  	                         //�����S����ʾ��������Ϣ����ʼλ
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

