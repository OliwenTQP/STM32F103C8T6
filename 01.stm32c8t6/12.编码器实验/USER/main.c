#include "stm32f10x_gpio.h" 
#include "led.h" 
#include "delay.h" 
#include "sys.h"
#include "usart.h"
#include "timer.h"
extern int circle_count;
extern int count;
int leftcount;
int rightcount;
int main(void)
{
	LED_Init(); //调用初始化LED函数，引用"led.h"后可使用
	delay_init(); //调用初始化延迟函数，引用"delay.h"后可使用
	USART1_Config();
	TIM4_Mode_Config();
	TIM3_Encoder_Init();
TIM2_Int_Init(9999,719);
//	Encoder_Init_TIM4(999,0);
  while(1)
	{		 
		delay_ms(200); //每隔200ms读取一次编码器计数，即速度。
//		               //可以使用定时中断实现更精准的速度计算，用户可自定义
//		int num=TIM4->CNT;
//		printf("helloworld\r\n");
//		printf("TIM3->CNT=%d\r\n", TIM3->CNT);
//		printf("TIM4->CNT=%d\r\n", TIM4->CNT);
//		printf("leftcount=%d\r\n", leftcount);
//		printf("rightcount=%d\r\n",rightcount);
		//printf("%d  ",(TIM4->CNT)/4);
		//printf("Encoder=%d\r\n", Read_Encoder_TIM4());
	}
}


