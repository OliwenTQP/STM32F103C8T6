#include "commonhead.h"

u32 pwmzkb1 = 250;
u32 pwmzkb2 = 0;
u8 temp=0,humi=0;
u8 temp_max = 30,temp_min = 25;
u32 arr=999,psc = 9;
float distant = 0;
u8 distant_max = 10,distant_min = 200;//��λcm
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
		AdcValue=3.3*Get_adc_Average(ADC_Channel_0,10)/0x0fff; //ADCֵ��ΧΪ��0-2^12=4095��111111111111��
		                                                       //һ��������籾���̶�Ӧ��ѹΪ0-3.3V
		delay_ms(300);
    printf("adc_Average=%.3fV\r\n", AdcValue); //����3ΪС������
	}
}
 //		if(DHT11_Read_Data(&temp,&humi))     //&temp�ĵ�ַ��Ӧ*temp��ַ����������һ��
//			printf("\r\n temp: %d'C   ,humi: %d",temp,humi);  //'%'��ʵ�����壬ֻ�����ַ���ʾ
//	 else
//		 printf("\r\n EEROR! THE DHT11 HAS NO RESPOND...");//�����ǿ⺯����̣�����׼ȷ���պ�����ִ��ʱ�䣬
//																											//���Իᾭ����������������Ϣ

}

