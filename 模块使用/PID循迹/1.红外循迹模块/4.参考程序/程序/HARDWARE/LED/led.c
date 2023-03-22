#include "led.h"
#include "delay.h"	   
	    
//LED IO初始化
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能PORTB时钟
	

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOBA	
	GPIO_SetBits(GPIOC,GPIO_Pin_13);				 //PA4 输出高
}

//LED灯测试
void LED_test(void)
{
	LED=0;
	delay_ms(500);
	LED=1;
	delay_ms(500);
}
