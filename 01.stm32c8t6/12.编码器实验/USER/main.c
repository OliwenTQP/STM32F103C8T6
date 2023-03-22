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
	LED_Init(); //���ó�ʼ��LED����������"led.h"���ʹ��
	delay_init(); //���ó�ʼ���ӳٺ���������"delay.h"���ʹ��
	USART1_Config();
	TIM4_Mode_Config();
	TIM3_Encoder_Init();
TIM2_Int_Init(9999,719);
//	Encoder_Init_TIM4(999,0);
  while(1)
	{		 
		delay_ms(200); //ÿ��200ms��ȡһ�α��������������ٶȡ�
//		               //����ʹ�ö�ʱ�ж�ʵ�ָ���׼���ٶȼ��㣬�û����Զ���
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


