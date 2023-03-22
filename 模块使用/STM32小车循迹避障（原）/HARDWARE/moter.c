#include "moter.h"



void CarGo(void)
{
	TIM_SetCompare1(TIM3 , 400);  //数值越大速度越慢
	TIM_SetCompare2(TIM3 , 900);
	TIM_SetCompare3(TIM3 , 400);  
	TIM_SetCompare4(TIM3 , 900);	
}

void CarStop(void)
{
    TIM_SetCompare1(TIM3 , 900);
    TIM_SetCompare2(TIM3 , 900);
	TIM_SetCompare3(TIM3 , 900);	
	TIM_SetCompare4(TIM3 , 900);
}

void CarBack(void)
{
    TIM_SetCompare1(TIM3 , 900);
    TIM_SetCompare2(TIM3 , 300);
	TIM_SetCompare3(TIM3 , 900);	
	TIM_SetCompare4(TIM3 , 300);
}

void CarLeft(void)
{
    TIM_SetCompare1(TIM3 , 900);
	TIM_SetCompare2(TIM3 , 300);
	TIM_SetCompare3(TIM3 , 300);
	TIM_SetCompare4(TIM3 , 900);
}

void CarBigLeft(void)
{
    TIM_SetCompare1(TIM3 , 900);
	TIM_SetCompare2(TIM3 , 100);
	TIM_SetCompare3(TIM3 , 100);
	TIM_SetCompare4(TIM3 , 900);
}

void CarRight(void)
{
    TIM_SetCompare1(TIM3 , 300);
	TIM_SetCompare2(TIM3 , 900);
	TIM_SetCompare3(TIM3 , 900);
	TIM_SetCompare4(TIM3 , 300);
	
}

void CarBigRight(void)
{
    TIM_SetCompare1(TIM3 , 100);
	TIM_SetCompare2(TIM3 , 900);
	TIM_SetCompare3(TIM3 , 900);
	TIM_SetCompare4(TIM3 , 100);
	
}


void TIM3_PWM_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure; 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	
	
	TIM_TimeBaseStructure.TIM_Period = 899;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM3 , &TIM_TimeBaseStructure);
	
	//端口复用
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	
	GPIO_Init(GPIOA, &GPIO_InitStructure);   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	
	GPIO_Init(GPIOB, &GPIO_InitStructure);   
	
	//PWM通道1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 900;
	TIM_OC1Init(TIM3 , &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3 , TIM_OCPreload_Enable);
	
	//PWM通道2
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 900;
	TIM_OC2Init(TIM3 , &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3 , TIM_OCPreload_Enable);
	
	//PWM通道3
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 900;
	TIM_OC3Init(TIM3 , &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3 , TIM_OCPreload_Enable);
	
	//PWM通道4
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 900;
	TIM_OC4Init(TIM3 , &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3 , TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM3 , ENABLE);
}

