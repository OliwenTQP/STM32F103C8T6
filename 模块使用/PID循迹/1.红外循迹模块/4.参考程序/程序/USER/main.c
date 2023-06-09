#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "beep.h" 
#include "led.h"
#include "motor.h"
#include "servor.h"
#include "LQ12864.h"
#include "encoder.h"   
#include "timer.h"
#include "common.h"
#include "control.h"
#include "adc.h"
#include "track.h"
#include "24l01.h"


/***********************************
本程序为循迹小车电路板驱动函数库
编写：Dinvent
@魔石科技@
************************************/


 int main(void)
 {
	char buff[20];
	int date=0;
	delay_init();//延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级�
	uart_init(115200);//串口初始化 波特率115200
	OLED_Init();//OLED初始化函数
	Encoder_Init_TIM2();
	LED_Init();	 //初始化与LED连接的硬件接口
	Beep_Init(); //蜂鸣器初始化函数		 
	Motor_Init();//电机初始化函数
	Servor_Init();//舵机初始化函数			  
	Adc_Init();		//内部ADC初始化函数	 
	Control_Init();	
	NRF24L01_Init();//24L01初始化
	NRF24L01_TX_Mode();//配置成发送模式
	//OLED_P6x8Str(2,20,"Car System");
	Show_CH(30,0);//显示中文标题
	//Show_Battary_Vol();//显示电池电压函数	 
	while(1)
	{	
		LED_test();
		GetParament();
		//date=GetTraceDate();
		//sprintf(buff,"%d",date);
		//printf(buff);
	}
 }

	

