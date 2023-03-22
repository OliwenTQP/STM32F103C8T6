//头文件
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



//循迹检测到黑线后返回高电平


 int main(void)
{	
//	char str[20];          //用来存放浮点数字符
	
	float  length_res[5];  //用来存放测距结果

	
	SystemInit();	// 配置系统时钟为72M 
    delay_init();    //延时初始化		
	xunji_config();   //循迹初始化
	TIM3_PWM_Init();	//电机pwm   TIM3
	SG90_pwm_init();  //舵机pwm	    TIM2
	CH_SR04_Init();  //超声波定时器    TIM4
	OLED_Init();    //oled显示初始化

	
//避障循环	
	
 	while(1)
	{	
		
		SG90_Front;   //舵机摆正
		delay_ms(100);
        length_res[0] =Senor_Using();  //测前方距离放在数组里
		delay_ms(100);
		
		if(length_res[0]>30.00)       //如果前方距离大于30cm  前进
			{
			CarGo();
			}	
				
		if(length_res[0]<30.00)     //如果前方距离小于30厘米  停车测左右距离
			{
			CarStop();  
			SG90_Left_45;      //舵机左转45度测距
			delay_ms(700);		
			length_res[1] =Senor_Using();    //把测量结果放进数组
			
            SG90_Right_45;     //舵机右转45度测距
			delay_ms(700);	
            length_res[4] =Senor_Using();     //把测量结果放进数组				
				
			SG90_Front;           //舵机摆正
			delay_ms(100); 
			if(length_res[1]>length_res[4])    //如果左边的距离大于右边的距离
				{
					do                        //舵机摆正
					{
					SG90_Front;
					delay_ms(10);
					length_res[0] =Senor_Using();	//重复测前方的距离同时左转
					delay_ms(10);						
					CarLeft();
					}
					while(length_res[0]<30.00);		//一直转到前方距离大于30cm		
				}
		   if(length_res[1]<length_res[4])    //如果右边的距离大于左边的距离
				{
					do
					{
					SG90_Front;
					delay_ms(10);
					length_res[0] =Senor_Using();  //重复测前方的距离同时右转
					delay_ms(10);						
					CarRight();
					}
					while(length_res[0]<30.00);		//一直转到前方距离大于30cm
				}
				
			}		
	
	}	


	
/*
//循迹循环函数	
  while(1)
  {	
     Read_xunji_Date(); //读循迹线值
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





