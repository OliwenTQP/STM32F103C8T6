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
������Ϊѭ��С����·������������
��д��Dinvent
@ħʯ�Ƽ�@
************************************/


 int main(void)
 {
	char buff[20];
	int date=0;
	delay_init();//��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ��
	uart_init(115200);//���ڳ�ʼ�� ������115200
	OLED_Init();//OLED��ʼ������
	Encoder_Init_TIM2();
	LED_Init();	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	Beep_Init(); //��������ʼ������		 
	Motor_Init();//�����ʼ������
	Servor_Init();//�����ʼ������			  
	Adc_Init();		//�ڲ�ADC��ʼ������	 
	Control_Init();	
	NRF24L01_Init();//24L01��ʼ��
	NRF24L01_TX_Mode();//���óɷ���ģʽ
	//OLED_P6x8Str(2,20,"Car System");
	Show_CH(30,0);//��ʾ���ı���
	//Show_Battary_Vol();//��ʾ��ص�ѹ����	 
	while(1)
	{	
		LED_test();
		GetParament();
		//date=GetTraceDate();
		//sprintf(buff,"%d",date);
		//printf(buff);
	}
 }

	

