#ifndef __TIMER_H
#define __TIMER_H	
#include "sys.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"

void TIM2_Int_Init(u16 arr, u16 psc);
void TIM3_Cap_Init(u16 arr,u16 psc);
#endif
