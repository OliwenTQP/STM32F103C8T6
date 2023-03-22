#include "left_control.h" 
#include "stm32f10x_gpio.h" 

//LEDӲ����ʼ����������
void Left_dianji_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure; //����һ�����ų�ʼ���Ľṹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��GPIOAʱ�ӣ�GPIOA������APB2ʱ���£���STM32��ʹ��IO��ǰ��Ҫʹ�ܶ�Ӧʱ��
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6 | GPIO_Pin_7; //����4
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //�����������ģʽΪ�������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //��������ٶ�Ϊ50MHZ
	GPIO_Init(GPIOB, &GPIO_InitStructure); //�����������úõ�GPIO_InitStructure��������ʼ������GPIOA_PIN4
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_6); //��ʼ����������GPIOA4Ϊ�ߵ�ƽ
	GPIO_ResetBits(GPIOB, GPIO_Pin_7); //��ʼ����������GPIOA4Ϊ�ߵ�ƽ
}

void Left_dianji_zhenzhuan(u32 pwmzkb)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_6); //��ʼ����������GPIOA4Ϊ�ߵ�ƽ
	GPIO_ResetBits(GPIOB, GPIO_Pin_7); //��ʼ����������GPIOA4Ϊ�ߵ�ƽ
	TIM_SetCompare3(TIM4,pwmzkb);
}

void Left_dianji_fanzhuan(u32 pwmzkb)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_6); //��ʼ����������GPIOA4Ϊ�ߵ�ƽ
	GPIO_SetBits(GPIOB, GPIO_Pin_7); //��ʼ����������GPIOA4Ϊ�ߵ�ƽ
	TIM_SetCompare3(TIM4,pwmzkb);
}

