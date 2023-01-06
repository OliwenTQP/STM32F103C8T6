#include "stm32f10x_gpio.h" 
#include "led.h" 
#include "delay.h" 
#include "sys.h"
#include "usart.h"
#include "timer.h"
int main(void)
{
	u32 pwmzkb;
	LED_Init(); //调用初始化LED函数，引用"led.h"后可使用
	delay_init(); //调用初始化延迟函数，引用"delay.h"后可使用
	USART1_Config();
	USART3_Config();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	TIM2_PWM_Init(10000,710);  //arr:自动重装载值，psc:预分频系数
	
  pwmzkb=500;
  TIM_SetCompare2(TIM2,pwmzkb);
  while(1)
	{
		   pwmzkb=500;
			TIM_SetCompare2(TIM2,pwmzkb);	 // 修改占空比    pa1    
	}
}
 
