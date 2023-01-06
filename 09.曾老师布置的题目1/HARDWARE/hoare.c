#include "stm32f10x.h"
#include "hoare.h"
void HOARE_Init(void)

{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
	
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //A15 B3 B4
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;	
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3 | GPIO_Pin_4 ;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//红外模块探测数据浮空输入
	//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//红外模块探测数据浮空输入
	//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

}
