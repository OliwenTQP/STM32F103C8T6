#include "commonhead.h"


unsigned char mode_show = 2;//模式为1蓝牙控制模式，模式为2为循迹模式，模式3为屏障碍模式

void SystemInit1(void)
{
	u32 pwmzkb = 250;
	LED_Init(); //调用初始化LED函数，引用"led.h"后可使用
	delay_init(); //调用初始化延迟函数，引用"delay.h"后可使用
	USART1_Config();
	USART3_Config();
	
	//TIM2_Int_Init(999,71);
	//TIM4_Int_Init(999,71);
	TIM2_PWM_Init(999,9);  //arr:自动重装载值，psc:预分频系数
	TIM4_PWM_Init(999,9);  //arr:自动重装载值，psc:预分频系数
	Go(1000,1000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	
	//============oled显示初始化=====================
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	OLED_DrawPoint(0,0);
	OLED_DrawLine(20,0,50,60);
	OLED_DrawCircle(64,32,20);
	delay_ms(1000);
	OLED_Clear();
	OLED_ShowChinese(36,20,0,16);//模
	OLED_ShowChinese(54,20,1,16);//式
	OLED_ShowNum(72,20,mode_show,1,16);
	OLED_Refresh();
	
//	Hcsr04Init();//超声波模块初始化
//	hcsr04_NVIC();
	
	//控制类模块初始化
	HOARE_Init();
	//pwmzkb=500;
  //TIM_SetCompare1(TIM2,pwmzkb);
	Right_dianji_Init();
	Left_dianji_Init();
}




