#ifndef __MOTER_H
#define	__MOTER_H


#include "stm32f10x.h"

#define IN1_up GPIO_SetBits(GPIOA, GPIO_Pin_1)
#define IN1_down  GPIO_ResetBits(GPIOA,GPIO_Pin_1)

#define IN2_up GPIO_SetBits(GPIOA, GPIO_Pin_2)
#define IN2_down  GPIO_ResetBits(GPIOA,GPIO_Pin_2)

#define IN3_up GPIO_SetBits(GPIOA, GPIO_Pin_3)
#define IN3_down  GPIO_ResetBits(GPIOA,GPIO_Pin_3)

#define IN4_up GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define IN4_down  GPIO_ResetBits(GPIOA,GPIO_Pin_4)

void TIM3_PWM_Init(void);
void CarGo(void);
void CarStop(void);
void CarBack(void);
void CarLeft(void);
void CarBigLeft(void);  //大右转
void CarRight(void);
void CarBigRight(void);   //大左转

#endif
