#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "sys.h"

#define PWMA1   TIM4->CCR1  
#define PWMA2   TIM4->CCR2 

#define PWMB1   TIM4->CCR3  
#define PWMB2   TIM4->CCR4




/***************外部函数声明****************/
extern void Motor_Gpio_init(void);
extern void Set_Pwm_Motor1(int motor_a);
extern void Set_Pwm_Motor2(int motor_b);
extern void Motor_Init(void);
extern void Set_Motor_PWM(int PWM);
#endif
