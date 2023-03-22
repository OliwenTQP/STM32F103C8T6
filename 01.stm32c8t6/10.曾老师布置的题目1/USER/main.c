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

		while(1)
	{
	float AdcValue=0;
	delay_init();
	adc_Init();
	USART1_Config();
  while(1)
	{		
		AdcValue=3.3*Get_adc_Average(ADC_Channel_0,10)/0x0fff; //ADC值范围为从0-2^12=4095（111111111111）
		                                                       //一般情况下如本例程对应电压为0-3.3V
		delay_ms(300);
    printf("adc_Average=%.3fV\r\n", AdcValue); //保留3为小数发送
	}
}
 //		if(DHT11_Read_Data(&temp,&humi))     //&temp的地址对应*temp地址，所以数据一样
//			printf("\r\n temp: %d'C   ,humi: %d",temp,humi);  //'%'有实体意义，只能用字符表示
//	 else
//		 printf("\r\n EEROR! THE DHT11 HAS NO RESPOND...");//由于是库函数编程，不能准确把握函数的执行时间，
//																											//所以会经常出现这条警告信息

}

