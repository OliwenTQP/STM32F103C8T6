#include "commonhead.h"
#include "hcsr04.h"
//超声波计数
u16 msHcCount = 0;

//定时器3设置
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


//IO口初始化 及其他初始化
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
    TIM_TimeBaseStructure.TIM_Period = (1000-1);    //计1000个数
    TIM_TimeBaseStructure.TIM_Prescaler =(72-1);   //72分频，变成1MHZ
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;  //分频因子，不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
    //初始化定时器，配置ARR,PSC
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);          
   
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);  
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //打开定时器更新中断   
    hcsr04_NVIC();
    TIM_Cmd(TIM3,DISABLE);     
}


//打开定时器3
static void OpenTimerForHc()  
{
   TIM_SetCounter(TIM3,0);
   msHcCount = 0;
   TIM_Cmd(TIM3, ENABLE); 
}


//关闭定时器3
static void CloseTimerForHc()    
{
   TIM_Cmd(TIM3, DISABLE); 
}


//定时器3终中断
void TIM3_IRQHandler(void)     //当定时器的时间到了，跳转执行其中内容
{
   if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)    //进入中断了执行中断内的函数
   {
       TIM_ClearITPendingBit(TIM3, TIM_IT_Update  ); 
       msHcCount++;
   }
}
 


//获取定时器3计数器值
u32 GetEchoTimer(void)
{
   u32 t = 0;       
   t = msHcCount*1000;
   t += TIM_GetCounter(TIM3); //定时器获取时间
   TIM3->CNT = 0;  
   delay_ms(50);
   return t;
}
 
//通过定时器3计数器值推算距离
//float Hcsr04GetLength(void )
//{  
//	
//   u32 t = 0;
//   int i = 0;
//   float lengthTemp = 0;
//   float sum = 0;
//   while(i!=5)        //5次循环检测，取平均值，加权平均滤波
//   {
//      TRIG_Send = 1;  //上拉10us，理论上只要10us   
//      delay_us(10);  
//      TRIG_Send = 0;
//      while(ECHO_Reci == 0);      
//      OpenTimerForHc();    //打开定时器3，开始计时    
//      i = i + 1;           
//      while(ECHO_Reci == 1); //当其不是高电平是，跳出循环往下执行 
//      CloseTimerForHc();    //关闭定时器
//      t = GetEchoTimer();   //获取时间，     
//      lengthTemp = ((float)t/58.0);//cm
//      sum = lengthTemp + sum ;
//        
//    }   
//    lengthTemp = sum/5.0;
//    return lengthTemp;
//}



 //中位值平均滤波法
float Hcsr04GetLength(void )
{
	
    unsigned int count, i, j;
    u32 value_buf[N], temp;
    float  sum = 0;
	   
    for( count = 0; count < N; count++ )
    {
			//printf("helloworld\r\n");
			TRIG_Send = 1;  //上拉10us，理论上只要10us   
    delay_us(10);  
    TRIG_Send = 0;
    while(ECHO_Reci == 0);      
    OpenTimerForHc();    //打开定时器3，开始计时 
		//while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) == 1) break; 
    while(ECHO_Reci == 1); //当其不是高`电平是，跳出循环往下执行
     CloseTimerForHc();    //关闭定时器 			
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




