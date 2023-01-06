#include "stm32f10x_gpio.h" 
#include "led.h" 
#include "delay.h" 
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "i2c.h"
void delay_nms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  //自己定义
      while(i--) ;    
   }
}
//extern float Pitch,Roll,Yaw;
float pitch,roll,yaw; 		//欧拉角
int main(void)
{
SystemInit();                   //=====系统初始化
	LED_Init(); //调用初始化LED函数，引用"led.h"后可使用
	delay_init(); //调用初始化延迟函数，引用"delay.h"后可使用
	USART1_Config();
	USART3_Config();

	i2cInit(); 	 
	MPU6050_Init();

	/*陀螺仪传感器初始化*/
  //InitMPU6050();
	//TIM2_Int_Init(9999,7199);  //arr:自动重装载值，psc:预分频系数

	while(1)
	{	
		MPU6050_Pose();						 //获取MPU6050角度状态
		printf("Pitch = %f\r\n",Pitch);
		printf("Roll = %f\r\n",Roll);
		printf("Yaw = %f\r\n",Yaw);
//		MPU6050_Pose();						 //获取MPU6050角度状态
//printf("helloworld\r\n");
//	  GPIO_SetBits(GPIOC, GPIO_Pin_13);    //GPIOA_PIN4输出高电平，LED灯熄灭，引用"stm32f10x_gpio.h"后可使用
//		//PAout(4)=1; //引用sys.h头文件后，可以直接使用该宏定义操作IO(GPIOA_PIN4)输出高电平
//		delay_ms(100);                     //延迟1秒，引用"delay.h"后可使用 
//		GPIO_ResetBits(GPIOC, GPIO_Pin_13);  //设置A4引脚为低电平，点亮，引用"stm32f10x.h"后可使用
//		//PAout(4)=0; //引用sys.h头文件后，可以直接使用该宏定义操作IO(GPIOA_PIN4)输出低电平
//		delay_ms(100);                     //延迟1秒，引用"delay.h"后可使用
//		//PrintChar("helloworld");
//		printf("Pitch = %f\r\n",Pitch);
//		printf("Roll = %f\r\n",Roll);
//		printf("Yaw = %f\r\n",Yaw);
//		PrintChar("helloworldusart3");
	}

	
	/***********************************************************************/
	
//	while(1)
//	{
//		static int temp;
//	temp=  GetData(GYRO_ZOUT_H);
//	    if(temp>32768)
//		{
//		  temp-=65536;
//		}

//		
//		printf("\r\n---------加速度X轴原始数据---------%d \r\n",GetData(ACCEL_XOUT_H));
//		printf("\r\n---------加速度Y轴原始数据---------%d \r\n",GetData(ACCEL_YOUT_H));	
//		printf("\r\n---------加速度Z轴原始数据---------%d \r\n",GetData(ACCEL_ZOUT_H));	
//		printf("\r\n---------陀螺仪X轴原始数据---------%d \r\n",GetData(GYRO_XOUT_H));	
//		printf("\r\n---------陀螺仪Y轴原始数据---------%d \r\n",GetData(GYRO_YOUT_H));	
//		printf("\r\n---------陀螺仪Z轴原始数据---------%d \r\n",temp);
//		delay_ms(100);
//	}		
}
 
