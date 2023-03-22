#ifndef __SERVOR_H
#define	__SERVOR_H

#include "sys.h"


#define LED0 PAout(11)

void Servo1(void);
void Servor_GPIO_Config(void);	
void Servor_Init(void);
void TIM1_PWM_Init(u16 arr,u16 psc);
void Servor_Test(void);
#endif 
