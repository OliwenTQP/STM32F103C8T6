#include "delay.h"
#include "led.h"
#include "key.h" 
#include "exti.h"

//�ⲿ�жϳ�ʼ������
void EXTI5_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure; //����һ���ⲿ�жϳ�ʼ���Ľṹ��
 	  NVIC_InitTypeDef NVIC_InitStructure; //����һ���ж����ȼ���ʼ���Ľṹ��

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�ж���Ҫʹ��AFIOʱ��

	  KEY_Init();//��ʼ������IO

  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6 | GPIO_PinSource7); //�ú�����GPIO�˿����ж���ӳ������

  	EXTI_InitStructure.EXTI_Line=GPIO_PinSource6 | GPIO_PinSource7; //�ⲿ�ж���5
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//�ⲿ�ж���0-15Ϊ�����ж�
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE; //ʹ��
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			  //�����ⲿ�ж�5-9
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;				//��Ӧ���ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//�ж�ʹ��
  	NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStrue�Ĳ�����ʼ��VIC�Ĵ���
  
}

void EXTI9_6_IRQHandler(void)
{
  delay_ms(10);    //����
	if(KEY==0)       //����
	{	  
		PAout(4)=!PAout(4); //LED��ȡ��
	}
	EXTI_ClearITPendingBit(EXTI_Line5);  //���EXTI5��·�жϱ�־
}
