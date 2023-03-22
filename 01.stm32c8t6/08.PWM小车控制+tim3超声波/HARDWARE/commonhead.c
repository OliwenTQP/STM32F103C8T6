#include "commonhead.h"


unsigned char mode_show = 2;//ģʽΪ1��������ģʽ��ģʽΪ2Ϊѭ��ģʽ��ģʽ3Ϊ���ϰ�ģʽ

void SystemInit1(void)
{
	u32 pwmzkb = 250;
	LED_Init(); //���ó�ʼ��LED����������"led.h"���ʹ��
	delay_init(); //���ó�ʼ���ӳٺ���������"delay.h"���ʹ��
	USART1_Config();
	USART3_Config();
	
	//TIM2_Int_Init(999,71);
	//TIM4_Int_Init(999,71);
	TIM2_PWM_Init(999,9);  //arr:�Զ���װ��ֵ��psc:Ԥ��Ƶϵ��
	TIM4_PWM_Init(999,9);  //arr:�Զ���װ��ֵ��psc:Ԥ��Ƶϵ��
	Go(1000,1000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	
	//============oled��ʾ��ʼ��=====================
	OLED_Init();
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
	OLED_DrawPoint(0,0);
	OLED_DrawLine(20,0,50,60);
	OLED_DrawCircle(64,32,20);
	delay_ms(1000);
	OLED_Clear();
	OLED_ShowChinese(36,20,0,16);//ģ
	OLED_ShowChinese(54,20,1,16);//ʽ
	OLED_ShowNum(72,20,mode_show,1,16);
	OLED_Refresh();
	
//	Hcsr04Init();//������ģ���ʼ��
//	hcsr04_NVIC();
	
	//������ģ���ʼ��
	HOARE_Init();
	//pwmzkb=500;
  //TIM_SetCompare1(TIM2,pwmzkb);
	Right_dianji_Init();
	Left_dianji_Init();
}




