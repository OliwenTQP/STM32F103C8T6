#include "commonhead.h"

u32 pwmzkb1 = 250;
u32 pwmzkb2 = 0;
u8 temp=0,humi=0;
u8 temp_max = 30,temp_min = 25;
u32 arr=999,psc = 9;
float distant = 0;
u8 distant_max = 10,distant_min = 200;//单位cm
char message[50];
int main()
{
	//SystemInit1();
USART1_Config();
USART3_Config();
delay_init(); 
LED_Init();
KEY_Init();
DHT11_Init();
Hcsr04Init();//超声波模块初始化
hcsr04_NVIC();
	TIM2_PWM_Init(arr,psc);  //arr:自动重装载值，psc:预分频系数 //PA0
	TIM4_PWM_Init(999,9);  //arr:自动重装载值，psc:预分频系数	//PB8
	TIM1_Int_Init(999,71);

			while(1)
	{
				//TIM_SetCompare3(TIM4,pwmzkb); //PB8
				//TIM_SetCompare1(TIM2,pwmzkb);	 //PA0 修改占空比  
				Scan_KAY();

				DHT11_Read_Data(&temp,&humi);
//temp = 40;
				if(temp > temp_min && temp < temp_max)
				{
						pwmzkb2 = 0;
				}
				else if(temp >= temp_max)
				{
						pwmzkb2 = 500+(temp-temp_max)*100;
				}
				else if(temp <= temp_min)
				{
						pwmzkb2 = 500+(temp_min-temp)*100;
				}	 
				TIM_SetCompare3(TIM4,pwmzkb2);
				//printf("\r\n temp: %d'C   ,humi: %d",temp,humi);  //'%'有实体意义，只能用字符表示
				distant = Hcsr04GetLength();
				//printf("%f\r\n",distant);
				delay_ms(500);
		sprintf(message,"temperature=%d,distant=%f",temp,distant);
		UART3_Send_Char(message);
			//printf("helloworld\r\n");
	}
}
 //		if(DHT11_Read_Data(&temp,&humi))     //&temp的地址对应*temp地址，所以数据一样
//			printf("\r\n temp: %d'C   ,humi: %d",temp,humi);  //'%'有实体意义，只能用字符表示
//	 else
//		 printf("\r\n EEROR! THE DHT11 HAS NO RESPOND...");//由于是库函数编程，不能准确把握函数的执行时间，
//																											//所以会经常出现这条警告信息



