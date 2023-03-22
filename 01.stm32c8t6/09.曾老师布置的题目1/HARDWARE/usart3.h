#ifndef __USART3_H
#define	__USART3_H

#include "stm32f10x.h"
#include <stdio.h>
#include "commonhead.h"
//串口接收DMA缓存
//#define UART_RX_LEN		128
#define UART4_REC_NUM  	200  	//定义最大接收字节数 200
extern uint8_t Uart3_Rx[UART4_REC_NUM];
//extern unsigned char mode_show;//模式为1蓝牙控制模式，模式为2为循迹模式，模式3为屏障碍模式
void USART3_Config(void);
void NVIC_Configurationusart3(void);
void PrintChar(char *s);
void UART3_Send_Char(char *s);


#endif /* __USART1_H */
