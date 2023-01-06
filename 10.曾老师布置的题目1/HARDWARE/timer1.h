#ifndef __TIMER3_H
#define __TIMER3_H	
#include "sys.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"

void TIM1_Int_Init(u16 arr, u16 psc);
void TIM1_PWM_Init(u16 arr, u16 psc);
#endif
