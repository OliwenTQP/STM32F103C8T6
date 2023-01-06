#include "commonhead.h"
int count = 0;
//通用定时器1初始化函数，arr:自动重装载值，psc:预分频系数，默认定时时钟为72MHZ时，两者共同决定定时中断时间
void TIM1_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue; //定义一个定时中断的结构体
	NVIC_InitTypeDef NVIC_InitStrue; //定义一个中断优先级初始化的结构体
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //使能通用定时器1时钟
	
	TIM_TimeBaseInitStrue.TIM_Period=arr; //计数模式为向上计数时，定时器从0开始计数，计数超过到arr时触发定时中断服务函数
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //预分频系数，决定每一个计数的时长
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //计数模式：向上计数
	TIM_TimeBaseInitStrue.TIM_ClockDivision=1; //一般不使用，默认TIM_CKD_DIV1
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStrue); //根据TIM_TimeBaseInitStrue的参数初始化定时器TIM1
	
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //使能TIM3中断，中断模式为更新中断：TIM_IT_Update
	
	NVIC_InitStrue.NVIC_IRQChannel=TIM1_UP_IRQn; //属于TIM1中断
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE; //中断使能
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级为1级，值越小优先级越高，0级优先级最高
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=0; //响应优先级为1级，值越小优先级越高，0级优先级最高
	NVIC_Init(&NVIC_InitStrue); //根据NVIC_InitStrue的参数初始化VIC寄存器，设置TIM1中断
	
	TIM_Cmd(TIM1, ENABLE); //使能定时器TIM1
}

void TIM1_UP_IRQHandler()
{

  if(TIM_GetITStatus(TIM1, TIM_IT_Update)==1) //当发生中断时状态寄存器(TIMx_SR)的bit0会被硬件置1
	{
printf("helloworld111\r\n");
		//count++;
//		if(count > 10)
//		{
//			printf("helloworld111\r\n");
//			count=0;
//		}
		
//		a++;
//	  PCout(13)=!PCout(13); //LED灯(A4引脚)状态取反，该函数封装在库函数"sys.h"中
//		if(a >= 10)
//		{
//			printf("helloworld");
//			a = 0;
//		}
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update); //状态寄存器(TIMx_SR)的bit0置0
	}
}

