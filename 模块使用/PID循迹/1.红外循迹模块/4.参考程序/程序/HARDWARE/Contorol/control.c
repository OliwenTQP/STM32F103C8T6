#include "control.h"
#include "timer.h"
#include "common.h"
#include "encoder.h"
#include "Motor.h"
#include "led.h"
#include "adc.h"
#include "servor.h"
#include "usart.h"
#include "delay.h"
#include "OLED.h"
#include "beep.h"

#define Target_POS_CAR  50*Encoder_P//28.5  46
u16 adc1,adc2,adc_m;
long int Target_POS = Target_POS_CAR;//����С��Ŀ��λ�ñ���
long int Temp_POS = 0;						//����С������λ�ñ���
int ReadEncode = 0;
u8 END_FLAG=0;//���嵽�յ��߱�־λ��������յ�����=1������Ϊ0
u8 ANTI_FLAG=0;
int Encode_n;

float Forward_P=0,Forward_D=0;
float Back_P=0,Back_D=0;
int Forward_Speed=0,Back_Speed=0;
/**************************************************************************
�������ܣ�λ��ʽPID������
��ڲ���������������λ����Ϣ��Ŀ��λ��
����  ֵ�����PWM
����λ��ʽ��ɢPID��ʽ 
pwm=Kp*e(k)+Ki*��e(k)+Kd[e��k��-e(k-1)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  
��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;����kΪ1,2,,k;
pwm�������
**************************************************************************/
int Position_PID (int Encoder,int Target)
{ 	
	 float Position_KP=-1.2,Position_KI=0,Position_KD=-70;
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //����ƫ��
	 Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������
	 Last_Bias=Bias;                                       //������һ��ƫ�� 
	 return Pwm;                                           //�������
}

//���PID���ƺ���
int Position_PID_Servo(int Encoder,int Target)
{ 	
	float Position_KP=Forward_P,Position_KI=0,Position_KD=Forward_D;//0.33
	static float Bias,Pwm,Integral_bias,Last_Bias;
	Bias=Encoder-Target;                                  //����ƫ��
	Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������
	Last_Bias=Bias;                                       //������һ��ƫ�� 
	return Pwm;                                            //�������
}


/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}


//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ��
		ReadEncode=Read_Encoder(2);
		Temp_POS-=ReadEncode;//��ȡ����������
		if(Target_POS>0)
		{
			Control_Servor_Angle();
			Control_Motor_PWM();
		}		
	}
}


//���Ƴ�ʼ��
//��ʼ����ȡPID���غ�PWM����
void Control_Init(void)
{
	TIM3_Int_Init(7199,39);//�ж�ʱ�䳤��5ms
}

//����PID��������ֱ�����PWM
void Control_Motor_PWM(void)
{
	long int MotorPWM = 0;
	MotorPWM = Position_PID(Temp_POS,Target_POS);
	if(myabs(Temp_POS)<Encode_n*Encoder_P)
	{	
		if(Target_POS<=0)	MotorPWM=-7200;
		else MotorPWM=7200;
	}
	else
	{
		if(MotorPWM>Forward_Speed) MotorPWM=Forward_Speed;//�޷�
		else if(MotorPWM<-Forward_Speed)	MotorPWM=-Forward_Speed;
		if(myabs(Temp_POS-Target_POS)<26*Encoder_P)
		{
			if(MotorPWM>Forward_Speed) MotorPWM=3100;//�޷�
			else if(MotorPWM<-Forward_Speed)	MotorPWM=-3100;
		}
	}	
	Set_Motor_PWM(MotorPWM);
}


//�˻�ʱ���ƶ������
void Control_Servor_Angle(void)
{
	/*int Temp=0;//�����м���ʱ����
	int MID_AD=0;//����Ѱ�߲�ֵ����
	int SERVOR_V=0;//������ƶ���Ƕȱ���
	static int Last_SERVOR_V=0;
	adc_m=Get_Adc(5);
	if(adc_m>1500)
	{
		adc1=Get_Adc(6);
		adc2=Get_Adc(7);	
		MID_AD=(adc1-adc2+D_AD_BACK_VALUE);
		SERVOR_V=Position_PID_Servo(MID_AD,0);
		if(SERVOR_V>190)	SERVOR_V=190;
		else if(SERVOR_V<-190)	SERVOR_V=-190;	
	}
	else if(adc_m<1500)
	{
		adc1=Get_Adc(6);
		adc2=Get_Adc(7);	
		Temp=adc1-adc2+D_AD_BACK_VALUE;
		if(myabs(Temp)>300)
		{
			if(Temp>0)
			MID_AD=4800-Temp;
			else 
			{
				MID_AD=-4800-Temp;
			}
			SERVOR_V=Position_PID_Servo(MID_AD,0);
			if(SERVOR_V>190)	SERVOR_V=190;
			else if(SERVOR_V<-190)	SERVOR_V=-190;
			Last_SERVOR_V=SERVOR_V;
		}	
		else SERVOR_V=Last_SERVOR_V;
		if((myabs(Temp)<300)&&(adc_m<400))
		{
			SERVOR_V=Last_SERVOR_V;
		}
	}
	TIM_SetCompare4(TIM1,Servo_MID+SERVOR_V);*/
}



