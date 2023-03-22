#include "key.h" 
#include "commonhead.h" 

extern u32 pwmzkb1;
//LED硬件初始化函数定义PA7
//void KEY_Init(void)
//{
//	
//	GPIO_InitTypeDef GPIO_InitStructure; //定义一个引脚初始化的结构体
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能GPIOA时钟，GPIOA挂载在APB2时钟下，在STM32中使用IO口前都要使能对应时钟
//	
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7; //引脚7
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU; //引脚输入输出模式为推挽输出模式
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //引脚输出速度为50MHZ
//	GPIO_Init(GPIOA, &GPIO_InitStructure); //根据上面设置好的GPIO_InitStructure参数，初始化引脚GPIOA_PIN4
//	
//	GPIO_SetBits(GPIOA, GPIO_Pin_7); //初始化设置引脚GPIOA7为高电平
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
	GPIO_SetBits(GPIOA, GPIO_Pin_7); //初始化设置引脚GPIOA7为高电平
	GPIO_SetBits(GPIOA, GPIO_Pin_6); //初始化设置引脚GPIOA6为高电平
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
			{ pwmzkb1+=100; TIM_SetCompare1(TIM2,pwmzkb1);	LED_close();} //PA0 修改占空比 }
		}
		else if(PAin(6)==0)
		{
			//delay_ms(10);
			while(PAin(6)==0)printf("PA7 = %d,PA6 = %d\r\n",PAin(7),PAin(6));;
			if(pwmzkb1 >= 100)
			{pwmzkb1-=100;	TIM_SetCompare1(TIM2,pwmzkb1);	LED_open();} //PA0 修改占空比 }
		}
			//LED_open();
}

