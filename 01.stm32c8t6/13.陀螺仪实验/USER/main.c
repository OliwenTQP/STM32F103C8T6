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
      i=12000;  //�Լ�����
      while(i--) ;    
   }
}
//extern float Pitch,Roll,Yaw;
float pitch,roll,yaw; 		//ŷ����
int main(void)
{
SystemInit();                   //=====ϵͳ��ʼ��
	LED_Init(); //���ó�ʼ��LED����������"led.h"���ʹ��
	delay_init(); //���ó�ʼ���ӳٺ���������"delay.h"���ʹ��
	USART1_Config();
	USART3_Config();

	i2cInit(); 	 
	MPU6050_Init();

	/*�����Ǵ�������ʼ��*/
  //InitMPU6050();
	//TIM2_Int_Init(9999,7199);  //arr:�Զ���װ��ֵ��psc:Ԥ��Ƶϵ��

	while(1)
	{	
		MPU6050_Pose();						 //��ȡMPU6050�Ƕ�״̬
		printf("Pitch = %f\r\n",Pitch);
		printf("Roll = %f\r\n",Roll);
		printf("Yaw = %f\r\n",Yaw);
//		MPU6050_Pose();						 //��ȡMPU6050�Ƕ�״̬
//printf("helloworld\r\n");
//	  GPIO_SetBits(GPIOC, GPIO_Pin_13);    //GPIOA_PIN4����ߵ�ƽ��LED��Ϩ������"stm32f10x_gpio.h"���ʹ��
//		//PAout(4)=1; //����sys.hͷ�ļ��󣬿���ֱ��ʹ�øú궨�����IO(GPIOA_PIN4)����ߵ�ƽ
//		delay_ms(100);                     //�ӳ�1�룬����"delay.h"���ʹ�� 
//		GPIO_ResetBits(GPIOC, GPIO_Pin_13);  //����A4����Ϊ�͵�ƽ������������"stm32f10x.h"���ʹ��
//		//PAout(4)=0; //����sys.hͷ�ļ��󣬿���ֱ��ʹ�øú궨�����IO(GPIOA_PIN4)����͵�ƽ
//		delay_ms(100);                     //�ӳ�1�룬����"delay.h"���ʹ��
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
//		printf("\r\n---------���ٶ�X��ԭʼ����---------%d \r\n",GetData(ACCEL_XOUT_H));
//		printf("\r\n---------���ٶ�Y��ԭʼ����---------%d \r\n",GetData(ACCEL_YOUT_H));	
//		printf("\r\n---------���ٶ�Z��ԭʼ����---------%d \r\n",GetData(ACCEL_ZOUT_H));	
//		printf("\r\n---------������X��ԭʼ����---------%d \r\n",GetData(GYRO_XOUT_H));	
//		printf("\r\n---------������Y��ԭʼ����---------%d \r\n",GetData(GYRO_YOUT_H));	
//		printf("\r\n---------������Z��ԭʼ����---------%d \r\n",temp);
//		delay_ms(100);
//	}		
}
 
