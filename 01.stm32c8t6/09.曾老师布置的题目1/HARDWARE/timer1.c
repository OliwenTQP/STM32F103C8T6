#include "commonhead.h"
int count = 0;
//ͨ�ö�ʱ��1��ʼ��������arr:�Զ���װ��ֵ��psc:Ԥ��Ƶϵ����Ĭ�϶�ʱʱ��Ϊ72MHZʱ�����߹�ͬ������ʱ�ж�ʱ��
void TIM1_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue; //����һ����ʱ�жϵĽṹ��
	NVIC_InitTypeDef NVIC_InitStrue; //����һ���ж����ȼ���ʼ���Ľṹ��
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʹ��ͨ�ö�ʱ��1ʱ��
	
	TIM_TimeBaseInitStrue.TIM_Period=arr; //����ģʽΪ���ϼ���ʱ����ʱ����0��ʼ����������������arrʱ������ʱ�жϷ�����
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //Ԥ��Ƶϵ��������ÿһ��������ʱ��
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //����ģʽ�����ϼ���
	TIM_TimeBaseInitStrue.TIM_ClockDivision=1; //һ�㲻ʹ�ã�Ĭ��TIM_CKD_DIV1
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStrue); //����TIM_TimeBaseInitStrue�Ĳ�����ʼ����ʱ��TIM1
	
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //ʹ��TIM3�жϣ��ж�ģʽΪ�����жϣ�TIM_IT_Update
	
	NVIC_InitStrue.NVIC_IRQChannel=TIM1_UP_IRQn; //����TIM1�ж�
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE; //�ж�ʹ��
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�Ϊ1����ֵԽС���ȼ�Խ�ߣ�0�����ȼ����
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=0; //��Ӧ���ȼ�Ϊ1����ֵԽС���ȼ�Խ�ߣ�0�����ȼ����
	NVIC_Init(&NVIC_InitStrue); //����NVIC_InitStrue�Ĳ�����ʼ��VIC�Ĵ���������TIM1�ж�
	
	TIM_Cmd(TIM1, ENABLE); //ʹ�ܶ�ʱ��TIM1
}

void TIM1_UP_IRQHandler()
{

  if(TIM_GetITStatus(TIM1, TIM_IT_Update)==1) //�������ж�ʱ״̬�Ĵ���(TIMx_SR)��bit0�ᱻӲ����1
	{
printf("helloworld111\r\n");
		//count++;
//		if(count > 10)
//		{
//			printf("helloworld111\r\n");
//			count=0;
//		}
		
//		a++;
//	  PCout(13)=!PCout(13); //LED��(A4����)״̬ȡ�����ú�����װ�ڿ⺯��"sys.h"��
//		if(a >= 10)
//		{
//			printf("helloworld");
//			a = 0;
//		}
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update); //״̬�Ĵ���(TIMx_SR)��bit0��0
	}
}

