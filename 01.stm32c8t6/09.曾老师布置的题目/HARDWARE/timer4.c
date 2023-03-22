#include "commonhead.h"

	int b = 0;
//ͨ�ö�ʱ��2��ʼ��������arr:�Զ���װ��ֵ��psc:Ԥ��Ƶϵ����Ĭ�϶�ʱʱ��Ϊ72MHZʱ�����߹�ͬ������ʱ�ж�ʱ��
void TIM4_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue; //����һ����ʱ�жϵĽṹ��
	NVIC_InitTypeDef NVIC_InitStrue; //����һ���ж����ȼ���ʼ���Ľṹ��
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ��ͨ�ö�ʱ��4ʱ��
	
	TIM_TimeBaseInitStrue.TIM_Period=arr; //����ģʽΪ���ϼ���ʱ����ʱ����0��ʼ����������������arrʱ������ʱ�жϷ�����
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //Ԥ��Ƶϵ��������ÿһ��������ʱ��
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //����ģʽ�����ϼ���
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //һ�㲻ʹ�ã�Ĭ��TIM_CKD_DIV1
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStrue); //����TIM_TimeBaseInitStrue�Ĳ�����ʼ����ʱ��TIM4
	
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //ʹ��TIM4�жϣ��ж�ģʽΪ�����жϣ�TIM_IT_Update
	
	NVIC_InitStrue.NVIC_IRQChannel=TIM4_IRQn; //����TIM2�ж�
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE; //�ж�ʹ��
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�Ϊ1����ֵԽС���ȼ�Խ�ߣ�0�����ȼ����
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1; //��Ӧ���ȼ�Ϊ1����ֵԽС���ȼ�Խ�ߣ�0�����ȼ����
	NVIC_Init(&NVIC_InitStrue); //����NVIC_InitStrue�Ĳ�����ʼ��VIC�Ĵ���������TIM4�ж�
	
	TIM_Cmd(TIM4, ENABLE); //ʹ�ܶ�ʱ��TIM4
}

//void TIM4_IRQHandler()
//{
//		static int b = 0;
////	printf("helloworld");
//	//if(TIM_GetITStatus(TIM2, TIM_IT_Update)==1) //�������ж�ʱ״̬�Ĵ���(TIMx_SR)��bit0�ᱻӲ����1
//	
//  if(TIM_GetITStatus(TIM4, TIM_IT_Update)==1) //�������ж�ʱ״̬�Ĵ���(TIMx_SR)��bit0�ᱻӲ����1
//	{
//		b++;
//	  PCout(13)=!PCout(13); //LED��(A4����)״̬ȡ�����ú�����װ�ڿ⺯��"sys.h"��
//		if(b >= 10)
//		{
//			printf("helloworld");
//			b = 0;
//		}
//		TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //״̬�Ĵ���(TIMx_SR)��bit0��0
//	}
//}

void TIM4_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure; //����һ�����ų�ʼ���Ľṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue; //����һ����ʱ�жϵĽṹ��	
	TIM_OCInitTypeDef TIM_OCInitTypeStrue; //����һ��PWM����Ľṹ��
	NVIC_InitTypeDef NVIC_InitStrue; //����һ���ж����ȼ���ʼ���Ľṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��GPIOBʱ�ӣ���STM32��ʹ��IO��ǰ��Ҫʹ�ܶ�Ӧʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ��ͨ�ö�ʱ��2ʱ�ӣ�A0���Ŷ�ӦTIM4CHN3
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;//����8
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; //�����������ģʽ����ʱ������ΪA0���Ÿ��ù���
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //�������������ٶ�Ϊ50MHZ
  GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ������GPIOA0
	 
	TIM_TimeBaseInitStrue.TIM_Period=arr; //����ģʽΪ���ϼ���ʱ����ʱ����0��ʼ����������������arrʱ������ʱ�жϷ�����
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //Ԥ��Ƶϵ��������ÿһ��������ʱ��
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //����ģʽ�����ϼ���
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //һ�㲻ʹ�ã�Ĭ��TIM_CKD_DIV1
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStrue); //����TIM_TimeBaseInitStrue�Ĳ�����ʼ����ʱ��TIM2
	
	TIM_OCInitTypeStrue.TIM_OCMode=TIM_OCMode_PWM2; //PWMģʽ2������ʱ����������TIM_Pulseʱ����ʱ����ӦIO�����Ч��ƽ
	TIM_OCInitTypeStrue.TIM_OCPolarity=TIM_OCPolarity_Low; //�����Ч��ƽΪ�͵�ƽ    TIM_OCPolarity_High TIM_OCPolarity_Low
	TIM_OCInitTypeStrue.TIM_OutputState=TIM_OutputState_Enable; //ʹ��PWM���
	TIM_OCInitTypeStrue.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OC3Init(TIM4, &TIM_OCInitTypeStrue); //��TIM_OCInitTypeStrue������ʼ����ʱ��2ͨ��1

	NVIC_InitStrue.NVIC_IRQChannel=TIM4_IRQn; //����TIM2�ж�
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE; //�ж�ʹ��
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�Ϊ1����ֵԽС���ȼ�Խ�ߣ�0�����ȼ����
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1; //��Ӧ���ȼ�Ϊ1����ֵԽС���ȼ�Խ�ߣ�0�����ȼ����
	NVIC_Init(&NVIC_InitStrue); //����NVIC_InitStrue�Ĳ�����ʼ��VIC�Ĵ���������TIM2�ж�
//	TIM_OCInitTypeStrue.TIM_OCMode=TIM_OCMode_PWM2; //PWMģʽ2������ʱ����������TIM_Pulseʱ����ʱ����ӦIO�����Ч��ƽ
//	TIM_OCInitTypeStrue.TIM_OCPolarity=TIM_OCPolarity_Low; //�����Ч��ƽΪ�͵�ƽ
//	TIM_OCInitTypeStrue.TIM_OutputState=TIM_OutputState_Enable; //ʹ��PWM���
//	TIM_OCInitTypeStrue.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
//	TIM_OC1Init(TIM2, &TIM_OCInitTypeStrue); //��TIM_OCInitTypeStrue������ʼ����ʱ��2ͨ��1

//	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable); //CH1Ԥװ��ʹ��
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Disable); //CH2Ԥװ��ʹ��
	TIM_ARRPreloadConfig(TIM4, ENABLE); //CH2Ԥװ��ʹ��
	
	TIM_Cmd(TIM4, ENABLE); //ʹ�ܶ�ʱ��TIM2
}
