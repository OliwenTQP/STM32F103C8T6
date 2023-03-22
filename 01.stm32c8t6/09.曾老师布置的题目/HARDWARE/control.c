#include "control.h"

void Left_dianji_zhenzhuan(u32 pwmzkb);
//void Left_dianji_fanzhuan(u32 pwmzkb);
void Right_dianji_zhenzhuan(u32 pwmzkb);
//void Right_dianji_fanzhuan(u32 pwmzkb);

void Go(int speed1,int speed2)
{
	Left_dianji_zhenzhuan(speed1);
	Right_dianji_zhenzhuan(speed2);
}

void TurnL1(int speed1,int speed2)
{
	Left_dianji_zhenzhuan(speed1);
	Right_dianji_zhenzhuan(speed2);
}

void TurnR1(int speed1,int speed2)
{
	Left_dianji_zhenzhuan(speed1);
	Right_dianji_zhenzhuan(speed2);
}

void TurnL2(int speed1,int speed2)
{
	Left_dianji_zhenzhuan(speed1);
	Right_dianji_zhenzhuan(speed2);
}

void TurnR2(int speed1,int speed2)
{
	Left_dianji_zhenzhuan(speed1);
	Right_dianji_zhenzhuan(speed2);
}
	void TurnL3(int speed1,int speed2)
{
	Left_dianji_zhenzhuan(speed1);
	Right_dianji_zhenzhuan(speed2);
}

void TurnR3(int speed1,int speed2)
{
	Left_dianji_zhenzhuan(speed1);
	Right_dianji_zhenzhuan(speed2);
}
void TurnL4(int speed1,int speed2)
{
	Left_dianji_zhenzhuan(speed1);
	Right_dianji_zhenzhuan(speed2);
}

void TurnR4(int speed1,int speed2)
{
	Left_dianji_zhenzhuan(speed1);
	Right_dianji_zhenzhuan(speed2);
	}	

void Stop(int speed1,int speed2)
{
	Left_dianji_zhenzhuan(speed1);
	Right_dianji_zhenzhuan(speed2);
	Left_dianji_fanzhuan(speed1);
	Right_dianji_fanzhuan(speed2);
	GPIO_ResetBits(GPIOB, GPIO_Pin_6); //初始化设置引脚GPIOA4为高电平
	GPIO_ResetBits(GPIOB, GPIO_Pin_7); //初始化设置引脚GPIOA4为高电平
}
	void Slow(int speed1,int speed2)
{
	Left_dianji_zhenzhuan(speed1);
	Right_dianji_zhenzhuan(speed2);
}
 void TurnW4(int speed1,int speed2)
{
	Left_dianji_zhenzhuan(speed1);
	Right_dianji_zhenzhuan(speed2);
}

void Back(int speed1,int speed2)
{
	Left_dianji_fanzhuan(speed1);
	Right_dianji_fanzhuan(speed2);
}
