#include "commonhead.h"
#include "hcsr04.h"
//����������
u16 msHcCount = 0;

//��ʱ��3����
void hcsr04_NVIC()
{
NVIC_InitTypeDef NVIC_InitStructure;
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;    //open time3          
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;         
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;       
NVIC_Init(&NVIC_InitStructure);
}


//IO�ڳ�ʼ�� ��������ʼ��
void Hcsr04Init()
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
   
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5;      
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB,GPIO_Pin_5);
     
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;     
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);  
    GPIO_ResetBits(GPIOB,GPIO_Pin_9);    
     
          
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   
     
    TIM_DeInit(TIM3);  //I chamge the TIM2 to TIM4,I don't know what this means 
    TIM_TimeBaseStructure.TIM_Period = (1000-1);    //��1000����
    TIM_TimeBaseStructure.TIM_Prescaler =(72-1);   //72��Ƶ�����1MHZ
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;  //��Ƶ���ӣ�����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
    //��ʼ����ʱ��������ARR,PSC
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);          
   
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);  
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //�򿪶�ʱ�������ж�   
    hcsr04_NVIC();
    TIM_Cmd(TIM3,DISABLE);     
}


//�򿪶�ʱ��3
static void OpenTimerForHc()  
{
   TIM_SetCounter(TIM3,0);
   msHcCount = 0;
   TIM_Cmd(TIM3, ENABLE); 
}


//�رն�ʱ��3
static void CloseTimerForHc()    
{
   TIM_Cmd(TIM3, DISABLE); 
}


//��ʱ��3���ж�
void TIM3_IRQHandler(void)     //����ʱ����ʱ�䵽�ˣ���תִ����������
{
   if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)    //�����ж���ִ���ж��ڵĺ���
   {
       TIM_ClearITPendingBit(TIM3, TIM_IT_Update  ); 
       msHcCount++;
   }
}
 


//��ȡ��ʱ��3������ֵ
u32 GetEchoTimer(void)
{
   u32 t = 0;       
   t = msHcCount*1000;
   t += TIM_GetCounter(TIM3); //��ʱ����ȡʱ��
   TIM3->CNT = 0;  
   delay_ms(50);
   return t;
}
 
//ͨ����ʱ��3������ֵ�������
//float Hcsr04GetLength(void )
//{  
//	
//   u32 t = 0;
//   int i = 0;
//   float lengthTemp = 0;
//   float sum = 0;
//   while(i!=5)        //5��ѭ����⣬ȡƽ��ֵ����Ȩƽ���˲�
//   {
//      TRIG_Send = 1;  //����10us��������ֻҪ10us   
//      delay_us(10);  
//      TRIG_Send = 0;
//      while(ECHO_Reci == 0);      
//      OpenTimerForHc();    //�򿪶�ʱ��3����ʼ��ʱ    
//      i = i + 1;           
//      while(ECHO_Reci == 1); //���䲻�Ǹߵ�ƽ�ǣ�����ѭ������ִ�� 
//      CloseTimerForHc();    //�رն�ʱ��
//      t = GetEchoTimer();   //��ȡʱ�䣬     
//      lengthTemp = ((float)t/58.0);//cm
//      sum = lengthTemp + sum ;
//        
//    }   
//    lengthTemp = sum/5.0;
//    return lengthTemp;
//}



 //��λֵƽ���˲���
float Hcsr04GetLength(void )
{
	
    unsigned int count, i, j;
    u32 value_buf[N], temp;
    float  sum = 0;
	   
    for( count = 0; count < N; count++ )
    {
			//printf("helloworld\r\n");
			TRIG_Send = 1;  //����10us��������ֻҪ10us   
    delay_us(10);  
    TRIG_Send = 0;
    while(ECHO_Reci == 0);      
    OpenTimerForHc();    //�򿪶�ʱ��3����ʼ��ʱ 
		//while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) == 1) break; 
    while(ECHO_Reci == 1); //���䲻�Ǹ�`��ƽ�ǣ�����ѭ������ִ��
     CloseTimerForHc();    //�رն�ʱ�� 			
        value_buf[count] =  ((float)GetEchoTimer()/58.0);//cm
    }
    for( j = 0; j < N - 1; j++ )
    {
        for( i = 0; i < N - j - 1; i++ )
        {
            if( value_buf[i] > value_buf[i + 1] )
            {
                temp = value_buf[i];
                value_buf[i] = value_buf[i + 1];
                value_buf[i + 1] = temp;
            }
        }
    }
    for( count = 1; count < N - 1; count++ )
    {
        sum += value_buf[count];
    }
    return  (float)(sum / ( N - 2 )) ;
}




