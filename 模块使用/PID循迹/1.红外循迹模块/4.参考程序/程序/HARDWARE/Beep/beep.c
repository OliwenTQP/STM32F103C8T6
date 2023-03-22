#include "beep.h"
#include "delay.h"


void Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA8	
	GPIO_SetBits(GPIOA,GPIO_Pin_5);				 //PA8 输出高

}
 
void N_Beep(char n)
{
	u32 i=0,j=0;
	for(i=n;i>0;i--)
	{
		for(j=500;j>0;j--)
		{
		  Beep=~Beep;      
		  delay_us(300);      
		}
	}
	for(i=n;i>0;i--)
	{
		for(j=500;j>0;j--)
		{     
		  delay_us(300);      
		}
	}
}


