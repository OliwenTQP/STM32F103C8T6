//�˺���Ϊ���ú���������С����һЩ����
#include "common.h" 
#include "led.h"
#include "delay.h"
#include "LQ12864.h"
#include "adc.h"
#include "stdio.h"



//��ʾ��ص�ѹ����
void Show_Battary_Vol()
{
	float vol=0;
	char buff[20];
	vol = (Get_Adc(8)/4096.0)*11*3.3;
	sprintf(buff,"Vol:%.1f",vol);
	OLED_P6x8Str(2,20,(u8 *)buff);
}






