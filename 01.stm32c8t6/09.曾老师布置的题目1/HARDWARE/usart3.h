#ifndef __USART3_H
#define	__USART3_H

#include "stm32f10x.h"
#include <stdio.h>
#include "commonhead.h"
//���ڽ���DMA����
//#define UART_RX_LEN		128
#define UART4_REC_NUM  	200  	//�����������ֽ��� 200
extern uint8_t Uart3_Rx[UART4_REC_NUM];
//extern unsigned char mode_show;//ģʽΪ1��������ģʽ��ģʽΪ2Ϊѭ��ģʽ��ģʽ3Ϊ���ϰ�ģʽ
void USART3_Config(void);
void NVIC_Configurationusart3(void);
void PrintChar(char *s);
void UART3_Send_Char(char *s);


#endif /* __USART1_H */
