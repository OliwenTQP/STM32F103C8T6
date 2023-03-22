#ifndef __TIMER4_H
#define __TIMER4_H	
#include "sys.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"

void TIM4_Int_Init(u16 arr, u16 psc);
void TIM4_PWM_Init(u16 arr, u16 psc);
#endif
