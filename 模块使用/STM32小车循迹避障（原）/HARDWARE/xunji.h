#ifndef __XUNJI_H
#define	__XUNJI_H

#include "stm32f10x.h"

#define xunji_1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
#define xunji_2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define xunji_3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define xunji_4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)

void xunji_config(void);
void Read_xunji_Date(void);  //读循迹模块返回的值

#endif
