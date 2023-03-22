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

//�������þ��Ǽ�⴫�ݸ������Ĳ����Ƿ�����Ч�Ĳ���
#ifdef  USE_FULL_ASSERT
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))��
//��ʾ����exprΪfalse����ִ�к����assert_failed()������__FILE__, __LINE__�Ǳ�׼�⺯���еĺ궨�壬��ʾ�ļ������к�
void assert_failed(uint8_t* file, uint32_t line);//�����ú���
#else
#define assert_param(expr) ((void)0)
#endif

#endif
