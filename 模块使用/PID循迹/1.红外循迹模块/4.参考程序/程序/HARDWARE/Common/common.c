//此函数为公用函数，设置小车的一些参数
#include "common.h" 
#include "led.h"
#include "delay.h"
#include "LQ12864.h"
#include "adc.h"
#include "stdio.h"



//显示电池电压函数
void Show_Battary_Vol()
{
	float vol=0;
	char buff[20];
	vol = (Get_Adc(8)/4096.0)*11*3.3;
	sprintf(buff,"Vol:%.1f",vol);
	OLED_P6x8Str(2,20,(u8 *)buff);
}






