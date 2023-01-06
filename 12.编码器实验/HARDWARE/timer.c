#include "timer.h"
#include "usart.h"
#include "stm32f10x.h"
#include "stm32f10x_exti.h"

extern int leftcount;
extern int rightcount;

//这个想用的话需要重装载值和码盘转一圈计得数一样，因为这个是计完中断一次。
int circle_count=0;//圈数
int GET_ENCODER_STATE(void)
{
	int16_t value;
	value = TIM3->CNT - 32768;
	TIM3->CNT = 32768;
	
	return -value;
}

void TIM3_IRQHandler(void)
{ 		   
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{       
		if((TIM3->CR1>>4 & 0x01)==0) //DIR==0
			leftcount++;
		else if((TIM3->CR1>>4 & 0x01)==1)//DIR==1
			leftcount--;		
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  
}

void TIM4_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)
    {       
				TIM4->CNT = 64215;
        if((TIM4->CR1>>4 & 0x01)==0) //DIR==0
            rightcount++;
        else if((TIM4->CR1>>4 & 0x01)==1)//DIR==1
            rightcount--;
    }
    TIM_ClearITPendingBit(TIM4,TIM_IT_Update); 
}

void TIM4_Mode_Config(void)
{
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
/* Encoder unit connected to TIM3, 4X mode */    
  GPIO_InitTypeDef GPIO_InitStructure;
  //NVIC_InitTypeDef NVIC_InitStructure;
  
  /* TIM3 clock source enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  /* Enable GPIOA, clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PA.06,07 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* Enable the TIM3 Update Interrupt */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //优先级组别
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
   
  /* Timer configuration in Encoder mode */
  TIM_DeInit(TIM4);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0;  // No prescaling 
  TIM_TimeBaseStructure.TIM_Period = 0xffff;  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式 
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
 
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge); //TIM_ICPolarity_Rising上升沿捕获
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6; //无滤波器
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  
 // Clear all pending interrupts
 
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);	  //使能中断
  
  //Reset counter
  //TIM4->CNT = 0;
  TIM4->CNT = 64215;
//  ENC_Clear_Speed_Buffer();
TIM_Cmd(TIM4, ENABLE);  	   //使能定时器4
}


void TIM3_Encoder_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Encoder unit connected to TIM3, 4X mode */    
  GPIO_InitTypeDef GPIO_InitStructure;
  //NVIC_InitTypeDef NVIC_InitStructure;
  
  /* TIM3 clock source enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  /* Enable GPIOA, clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PA.06,07 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Enable the TIM3 Update Interrupt */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //优先级组别
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Timer configuration in Encoder mode */
  TIM_DeInit(TIM3);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式 
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
 
  //TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling); //TIM_ICPolarity_Rising上升沿捕获
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge); //TIM_ICPolarity_Rising上升沿捕获
  //TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); //TIM_ICPolarity_Rising上升沿捕获
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6; //无滤波器
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  
 // Clear all pending interrupts
 
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);	  //使能中断

  //Reset counter
  TIM3->CNT = 32768;
  
//  ENC_Clear_Speed_Buffer();
  
  TIM_Cmd(TIM3, ENABLE);  	   //使能定时器3
}


void TIM2_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue; //定义一个定时中断的结构体
	NVIC_InitTypeDef NVIC_InitStrue; //定义一个中断优先级初始化的结构体
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //使能通用定时器2时钟
	
	TIM_TimeBaseInitStrue.TIM_Period=arr; //计数模式为向上计数时，定时器从0开始计数，计数超过到arr时触发定时中断服务函数
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //预分频系数，决定每一个计数的时长
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //计数模式：向上计数
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //一般不使用，默认TIM_CKD_DIV1
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStrue); //根据TIM_TimeBaseInitStrue的参数初始化定时器TIM2
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //使能TIM2中断，中断模式为更新中断：TIM_IT_Update
	
	NVIC_InitStrue.NVIC_IRQChannel=TIM2_IRQn; //属于TIM2中断
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE; //中断使能
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级为1级，值越小优先级越高，0级优先级最高
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1; //响应优先级为1级，值越小优先级越高，0级优先级最高
	NVIC_Init(&NVIC_InitStrue); //根据NVIC_InitStrue的参数初始化VIC寄存器，设置TIM2中断
	
	TIM_Cmd(TIM2, ENABLE); //使能定时器TIM2
}

void TIM2_IRQHandler()
{
	static double V= 0;
  if(TIM_GetITStatus(TIM2, TIM_IT_Update)==1) //当发生中断时状态寄存器(TIMx_SR)的bit0会被硬件置1
	{
	  //PCout(13)=!PCout(13); //LED灯(A4引脚)状态取反，该函数封装在库函数"sys.h"中
		//printf("helloworld");
		V = GET_ENCODER_STATE()*210.4867/1320;  //半径为6.7 周长为21.04867042 //0.1s扫一次
		
		printf("%lf\r\n",V);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //状态寄存器(TIMx_SR)的bit0置0
	}
}










