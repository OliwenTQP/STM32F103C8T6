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
USART1_Config();
USART3_Config();
delay_init(); 
LED_Init();
KEY_Init();
DHT11_Init();
Hcsr04Init();//������ģ���ʼ��
hcsr04_NVIC();
	TIM2_PWM_Init(arr,psc);  //arr:�Զ���װ��ֵ��psc:Ԥ��Ƶϵ�� //PA0
	TIM4_PWM_Init(999,9);  //arr:�Զ���װ��ֵ��psc:Ԥ��Ƶϵ��	//PB8
	TIM1_Int_Init(999,71);

			while(1)
	{
				//TIM_SetCompare3(TIM4,pwmzkb); //PB8
				//TIM_SetCompare1(TIM2,pwmzkb);	 //PA0 �޸�ռ�ձ�  
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
				//printf("\r\n temp: %d'C   ,humi: %d",temp,humi);  //'%'��ʵ�����壬ֻ�����ַ���ʾ
				distant = Hcsr04GetLength();
				//printf("%f\r\n",distant);
				delay_ms(500);
		sprintf(message,"temperature=%d,distant=%f",temp,distant);
		UART3_Send_Char(message);
			//printf("helloworld\r\n");
	}
}
 //		if(DHT11_Read_Data(&temp,&humi))     //&temp�ĵ�ַ��Ӧ*temp��ַ����������һ��
//			printf("\r\n temp: %d'C   ,humi: %d",temp,humi);  //'%'��ʵ�����壬ֻ�����ַ���ʾ
//	 else
//		 printf("\r\n EEROR! THE DHT11 HAS NO RESPOND...");//�����ǿ⺯����̣�����׼ȷ���պ�����ִ��ʱ�䣬
//																											//���Իᾭ����������������Ϣ



