#include "stm32f10x_gpio.h" 
#include "led.h" 
#include "delay.h" 
#include "sys.h"
#include "usart.h"
#include "timer.h"
int main(void)
{
	u32 pwmzkb;
	LED_Init(); //���ó�ʼ��LED����������"led.h"���ʹ��
	delay_init(); //���ó�ʼ���ӳٺ���������"delay.h"���ʹ��
	USART1_Config();
	USART3_Config();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	TIM2_PWM_Init(10000,710);  //arr:�Զ���װ��ֵ��psc:Ԥ��Ƶϵ��
	
  pwmzkb=500;
  TIM_SetCompare2(TIM2,pwmzkb);
  while(1)
	{
		   pwmzkb=500;
			TIM_SetCompare2(TIM2,pwmzkb);	 // �޸�ռ�ձ�    pa1    
	}
}
 
