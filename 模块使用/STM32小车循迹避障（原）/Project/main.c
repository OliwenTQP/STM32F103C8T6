//ͷ�ļ�
#include "stm32f10x.h"
#include "led.h"
#include "moter.h"
#include "xunji.h"  
#include "sg90.h"
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "cs.h"



//ѭ����⵽���ߺ󷵻ظߵ�ƽ


 int main(void)
{	
//	char str[20];          //������Ÿ������ַ�
	
	float  length_res[5];  //������Ų����

	
	SystemInit();	// ����ϵͳʱ��Ϊ72M 
    delay_init();    //��ʱ��ʼ��		
	xunji_config();   //ѭ����ʼ��
	TIM3_PWM_Init();	//���pwm   TIM3
	SG90_pwm_init();  //���pwm	    TIM2
	CH_SR04_Init();  //��������ʱ��    TIM4
	OLED_Init();    //oled��ʾ��ʼ��

	
//����ѭ��	
	
 	while(1)
	{	
		
		SG90_Front;   //�������
		delay_ms(100);
        length_res[0] =Senor_Using();  //��ǰ���������������
		delay_ms(100);
		
		if(length_res[0]>30.00)       //���ǰ���������30cm  ǰ��
			{
			CarGo();
			}	
				
		if(length_res[0]<30.00)     //���ǰ������С��30����  ͣ�������Ҿ���
			{
			CarStop();  
			SG90_Left_45;      //�����ת45�Ȳ��
			delay_ms(700);		
			length_res[1] =Senor_Using();    //�Ѳ�������Ž�����
			
            SG90_Right_45;     //�����ת45�Ȳ��
			delay_ms(700);	
            length_res[4] =Senor_Using();     //�Ѳ�������Ž�����				
				
			SG90_Front;           //�������
			delay_ms(100); 
			if(length_res[1]>length_res[4])    //�����ߵľ�������ұߵľ���
				{
					do                        //�������
					{
					SG90_Front;
					delay_ms(10);
					length_res[0] =Senor_Using();	//�ظ���ǰ���ľ���ͬʱ��ת
					delay_ms(10);						
					CarLeft();
					}
					while(length_res[0]<30.00);		//һֱת��ǰ���������30cm		
				}
		   if(length_res[1]<length_res[4])    //����ұߵľ��������ߵľ���
				{
					do
					{
					SG90_Front;
					delay_ms(10);
					length_res[0] =Senor_Using();  //�ظ���ǰ���ľ���ͬʱ��ת
					delay_ms(10);						
					CarRight();
					}
					while(length_res[0]<30.00);		//һֱת��ǰ���������30cm
				}
				
			}		
	
	}	


	
/*
//ѭ��ѭ������	
  while(1)
  {	
     Read_xunji_Date(); //��ѭ����ֵ
   CarGo();
	 if(xunji_1==0&&xunji_2==0&&xunji_3==0&&xunji_4==0)//0000
	  {
	  CarGo();		  
	  delay_ms(10);
	  }
	 if(xunji_1==0&&xunji_2==1&&xunji_3==1&&xunji_4==0)//0110
	  {
	  CarGo();
	  delay_ms(10);
	  }	  
	 if(xunji_1==0&&xunji_2==1&&xunji_3==0&&xunji_4==0)//0100
	  {
	  CarBigLeft();
	  delay_ms(10);
	  }
 	 if(xunji_1==0&&xunji_2==0&&xunji_3==1&&xunji_4==0)//0010
	  {
	  CarBigRight();
	  delay_ms(10); 
	  }
	  if(xunji_1==1&&xunji_2==0&&xunji_3==0&&xunji_4==0)//1000
	  {
	  CarBigLeft();
	  delay_ms(10);
	  }
	  if(xunji_1==0&&xunji_2==0&&xunji_3==0&&xunji_4==1)//0001
	  {
	  CarBigRight();
	  delay_ms(10); 
	  }
  
  }	
*/

}





