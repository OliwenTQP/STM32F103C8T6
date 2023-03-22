#include "xunji.h"

	
	
void xunji_config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;	
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); // 使能PC端口时钟
	
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5  | GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_10;	//选择对应的引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//配置GPIO模式,输入上拉       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PC端口
}

void Read_xunji_Date(void)
{
 xunji_1;
 xunji_2;
 xunji_3;
 xunji_4;
}

