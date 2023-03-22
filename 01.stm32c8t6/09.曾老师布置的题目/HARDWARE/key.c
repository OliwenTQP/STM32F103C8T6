#include "key.h" 
#include "commonhead.h" 

extern u32 pwmzkb1;
//LEDӲ����ʼ����������PA7
//void KEY_Init(void)
//{
//	
//	GPIO_InitTypeDef GPIO_InitStructure; //����һ�����ų�ʼ���Ľṹ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��GPIOAʱ�ӣ�GPIOA������APB2ʱ���£���STM32��ʹ��IO��ǰ��Ҫʹ�ܶ�Ӧʱ��
//	
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7; //����7
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU; //�����������ģʽΪ�������ģʽ
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //��������ٶ�Ϊ50MHZ
//	GPIO_Init(GPIOA, &GPIO_InitStructure); //�����������úõ�GPIO_InitStructure��������ʼ������GPIOA_PIN4
//	
//	GPIO_SetBits(GPIOA, GPIO_Pin_7); //��ʼ����������GPIOA7Ϊ�ߵ�ƽ
//}

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
	//????
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //????
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_7); //��ʼ����������GPIOA7Ϊ�ߵ�ƽ
	GPIO_SetBits(GPIOA, GPIO_Pin_6); //��ʼ����������GPIOA6Ϊ�ߵ�ƽ
}	


void Scan_KAY(void)
{
			//GPIO_SetBits(GPIOA, GPIO_Pin_7);
		//Scan_value = 1;
		//printf("%d",Scan_value);
		if(PAin(7)==0)
		{
			//delay_ms(10);
			while(PAin(7)==0)printf("PA7 = %d,PA6 = %d\r\n",PAin(7),PAin(6));;
			if(pwmzkb1 <= 900)
			{ pwmzkb1+=100; TIM_SetCompare1(TIM2,pwmzkb1);	LED_close();} //PA0 �޸�ռ�ձ� }
		}
		else if(PAin(6)==0)
		{
			//delay_ms(10);
			while(PAin(6)==0)printf("PA7 = %d,PA6 = %d\r\n",PAin(7),PAin(6));;
			if(pwmzkb1 >= 100)
			{pwmzkb1-=100;	TIM_SetCompare1(TIM2,pwmzkb1);	LED_open();} //PA0 �޸�ռ�ձ� }
		}
			//LED_open();
}

