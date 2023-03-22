#ifndef __HC_SR04_H
#define __HC_SR04_H
#include "commonhead.h"
void hcsr04_NVIC(void);

#define HCSR04_PORT     GPIOB
#define HCSR04_CLK      RCC_APB2Periph_GPIOB
#define HCSR04_TRIG     GPIO_Pin_5
#define HCSR04_ECHO     GPIO_Pin_9
#define N 10  //ÂË²¨ÊýÁ¿

#define TRIG_Send  PBout(5) 
#define ECHO_Reci  PBin(9)
void   Hcsr04Init(void);
float  Hcsr04GetLength(void);



#endif

