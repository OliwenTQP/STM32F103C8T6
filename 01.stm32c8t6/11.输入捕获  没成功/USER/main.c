#include "stm32f10x_gpio.h" 
#include "led.h" 
#include "delay.h" 
#include "sys.h"
#include "usart.h"
#include "timer.h"
int main(void)
{
	LED_Init(); //���ó�ʼ��LED����������"led.h"���ʹ��
	delay_init(); //���ó�ʼ���ӳٺ���������"delay.h"���ʹ��
	USART1_Config();
	USART3_Config();
	//TIM2_Int_Init(9999,7199);  //arr:�Զ���װ��ֵ��psc:Ԥ��Ƶϵ��
	TIM3_Cap_Init(1,7199);
  //TIM2_Int_Init(499,71);  //arr:�Զ���װ��ֵ��psc:Ԥ��Ƶϵ��
	while(1)
	{

	  GPIO_SetBits(GPIOC, GPIO_Pin_13);    //GPIOA_PIN4����ߵ�ƽ��LED��Ϩ������"stm32f10x_gpio.h"���ʹ��
		//PAout(4)=1; //����sys.hͷ�ļ��󣬿���ֱ��ʹ�øú궨�����IO(GPIOA_PIN4)����ߵ�ƽ
		delay_ms(100);                     //�ӳ�1�룬����"delay.h"���ʹ�� 
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);  //����A4����Ϊ�͵�ƽ������������"stm32f10x.h"���ʹ��
		//PAout(4)=0; //����sys.hͷ�ļ��󣬿���ֱ��ʹ�øú궨�����IO(GPIOA_PIN4)����͵�ƽ
		delay_ms(100);                     //�ӳ�1�룬����"delay.h"���ʹ��
		//PrintChar("helloworld");
		//printf("helloworld\r\n");
//		PrintChar("helloworldusart3");
	}
}
 
