#ifndef __SG90_H
#define	__SG90_H

#include "stm32f10x.h"
#include "delay.h"
   
#define   SG90_Right_90     TIM_SetCompare2(TIM2, 195)		
#define   SG90_Right_45		TIM_SetCompare2(TIM2, 190)		
#define   SG90_Front		TIM_SetCompare2(TIM2, 185)		
#define   SG90_Left_45		TIM_SetCompare2(TIM2, 180)		
#define   SG90_Left_90		TIM_SetCompare2(TIM2, 175)
		
void SG90_scan(void); //舵机左右摆头
void SG90_pwm_init(void);  //舵机pwm初始化

#endif
