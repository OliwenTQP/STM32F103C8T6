#ifndef __TIMER_H
#define __TIMER_H	
#include "sys.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"

void Encoder_Init_TIM4(u16 arr,u16 psc);
int Read_Encoder_TIM4(void);
void TIM4_Mode_Config(void);
void TIM3_Encoder_Init(void);
int GET_ENCODER_STATE(void);
void TIM2_Int_Init(u16 arr, u16 psc);
#endif
