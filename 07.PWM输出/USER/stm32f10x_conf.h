#ifndef __STM32F10x_CONF_H
#define __STM32F10x_CONF_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#include "misc.h"
#include "sys.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_fsmc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_tim.h"

//它的作用就是检测传递给函数的参数是否是有效的参数
#ifdef  USE_FULL_ASSERT
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))　
//表示参数expr为false，则执行后面的assert_failed()函数，__FILE__, __LINE__是标准库函数中的宏定义，表示文件名和行号
void assert_failed(uint8_t* file, uint32_t line);//申明该函数
#else
#define assert_param(expr) ((void)0)
#endif

#endif
