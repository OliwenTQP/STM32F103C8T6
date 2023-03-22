#include "timer.h"
#include "usart.h"
int a = 0;
//ͨ�ö�ʱ��2��ʼ��������arr:�Զ���װ��ֵ��psc:Ԥ��Ƶϵ����Ĭ�϶�ʱʱ��Ϊ72MHZʱ�����߹�ͬ������ʱ�ж�ʱ��
void TIM2_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue; //����һ����ʱ�жϵĽṹ��
	NVIC_InitTypeDef NVIC_InitStrue; //����һ���ж����ȼ���ʼ���Ľṹ��
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʹ��ͨ�ö�ʱ��2ʱ��
	
	TIM_TimeBaseInitStrue.TIM_Period=arr; //����ģʽΪ���ϼ���ʱ����ʱ����0��ʼ����������������arrʱ������ʱ�жϷ�����
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //Ԥ��Ƶϵ��������ÿһ��������ʱ��
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //����ģʽ�����ϼ���
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //һ�㲻ʹ�ã�Ĭ��TIM_CKD_DIV1
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStrue); //����TIM_TimeBaseInitStrue�Ĳ�����ʼ����ʱ��TIM2
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //ʹ��TIM2�жϣ��ж�ģʽΪ�����жϣ�TIM_IT_Update
	
	NVIC_InitStrue.NVIC_IRQChannel=TIM2_IRQn; //����TIM2�ж�
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE; //�ж�ʹ��
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�Ϊ1����ֵԽС���ȼ�Խ�ߣ�0�����ȼ����
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1; //��Ӧ���ȼ�Ϊ1����ֵԽС���ȼ�Խ�ߣ�0�����ȼ����
	NVIC_Init(&NVIC_InitStrue); //����NVIC_InitStrue�Ĳ�����ʼ��VIC�Ĵ���������TIM2�ж�
	
	TIM_Cmd(TIM2, ENABLE); //ʹ�ܶ�ʱ��TIM2
}

void TIM2_IRQHandler()
{
	
  if(TIM_GetITStatus(TIM2, TIM_IT_Update)==1) //�������ж�ʱ״̬�Ĵ���(TIMx_SR)��bit0�ᱻӲ����1
	{
			printf("helloworld\r\n");
//		a++;
//	  PCout(13)=!PCout(13); //LED��(A4����)״̬ȡ�����ú�����װ�ڿ⺯��"sys.h"��
//		if(a >= 10)
//		{
//			printf("helloworld\r\n");
//			a = 0;
//		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //״̬�Ĵ���(TIMx_SR)��bit0��0
	}
}


//��ʱ��3ͨ��3���벶�����ó�ʼ������
void TIM3_Cap_Init(u16 arr,u16 psc)
{	 
	//������ؽṹ��
	GPIO_InitTypeDef GPIO_InitStructure; //����һ��GPIO��ʼ���Ľṹ��
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; //����һ����ʱ����ʼ���Ľṹ��
	TIM_ICInitTypeDef  TIM3_ICInitStructure; //����һ����ʱ�����������ʼ���Ľṹ��
 	NVIC_InitTypeDef NVIC_InitStructure; //����һ���ж����ȼ���ʼ���Ľṹ��

	//ʹ�����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ��TIM3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOBʱ��
	
	//��ʼ��GPIOB0
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;  //PA7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //�������룬Ĭ�ϵ͵�ƽ�����Ա��ⲿ��ѹ����Ϊ�ߵ�ƽ
	GPIO_Init(GPIOA, &GPIO_InitStructure); //����GPIO_InitStructure�Ĳ�����ʼ��GPIOB0
	GPIO_ResetBits(GPIOA,GPIO_Pin_7); //��ʼ��PA7Ϊ�͵�ƽ
	
	//��ʼ����ʱ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct�Ĳ�����ʼ����ʱ��TIM3
  
	//��ʼ��TIM3���벶�����
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_2; //���벶��ͨ��2
  TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI3��
	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������ƵΪ����Ƶ����Ƶ�������������¼������жϷ�����
	TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲���Ϊ���˲�
	TIM_ICInit(TIM3, &TIM3_ICInitStructure); //��TIM3_ICInitStructure������ʼ����ʱ��TIM3���벶��
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //��ռ���ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //�ж�ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,ENABLE);//����TIM3�����ж�|����TIM3ͨ��3�����ж�	
  TIM_Cmd(TIM3, ENABLE ); 	//ʹ�ܶ�ʱ��2
}

u8 falling_flag=0; //�½��ز����־   				
u16	TIM3CH3_CAPTURE_VAL; //���벶�����ֵ

//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void)
{ 
	printf("helloworld\r\n");
	if(TIM_GetITStatus(TIM3, TIM_IT_CC3)&&falling_flag==0) //���������¼�&&�����¼�Ϊ�����أ��������£�B0��ͨ�ߵ�ƽ��
		{			
			TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Falling); //����Ϊ�½��ز���
			falling_flag=1; //���±�־
			TIM_SetCounter(TIM3,0); //�������	
			//TIM3->CNT=0; //�������
		}	
  else if(TIM_GetITStatus(TIM3, TIM_IT_CC3)&&falling_flag==1) //���������¼�&&�����¼�Ϊ�½���
  	{		
	    TIM3CH3_CAPTURE_VAL=TIM_GetCapture3(TIM3)/10; //ͳ���������¼���ĸߵ�ƽ����ʱ�䣨��������ʱ�䣩,
			                                              //������Ƶ��p=��Ƶʱ��(72M)/Ԥ��Ƶϵ��(psc)=72*10^6/7200=10Khz����0.0001s=0.1msһ�μ���
			                                              //����ֵ����arr(����������Ϊ65535)�����¼���
			printf("TIM3CH3_CAPTURE_VAL:%d ms\r\n",TIM3CH3_CAPTURE_VAL); //�򴮿ڵ������ַ���ͳ��ʱ�䣬ע��ʱ������Ϊ6.5535�룬����6.5535������¼���
      TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Rising); //����Ϊ�����ز���
			falling_flag=0; //���±�־
      TIM_SetCounter(TIM3,0);	//�������	
			//TIM3->CNT=0; //�������	
	  }
  TIM_ClearITPendingBit(TIM3, TIM_IT_CC2|TIM_IT_Update);//ÿ�ν����ж϶�Ҫ����жϱ�־���������������޷�����ִ��
}
