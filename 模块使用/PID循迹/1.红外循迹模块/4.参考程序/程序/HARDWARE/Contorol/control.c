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
long int Target_POS = Target_POS_CAR;//定义小车目标位置变量
long int Temp_POS = 0;						//定义小车现在位置变量
int ReadEncode = 0;
u8 END_FLAG=0;//定义到终点线标志位，如果到终点线则=1，否则为0
u8 ANTI_FLAG=0;
int Encode_n;

float Forward_P=0,Forward_D=0;
float Back_P=0,Back_D=0;
int Forward_Speed=0,Back_Speed=0;
/**************************************************************************
函数功能：位置式PID控制器
入口参数：编码器测量位置信息，目标位置
返回  值：电机PWM
根据位置式离散PID公式 
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
**************************************************************************/
int Position_PID (int Encoder,int Target)
{ 	
	 float Position_KP=-1.2,Position_KI=0,Position_KD=-70;
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
}

//舵机PID控制函数
int Position_PID_Servo(int Encoder,int Target)
{ 	
	float Position_KP=Forward_P,Position_KI=0,Position_KD=Forward_D;//0.33
	static float Bias,Pwm,Integral_bias,Last_Bias;
	Bias=Encoder-Target;                                  //计算偏差
	Integral_bias+=Bias;	                                 //求出偏差的积分
	Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	Last_Bias=Bias;                                       //保存上一次偏差 
	return Pwm;                                            //增量输出
}


/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}


//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标�
		ReadEncode=Read_Encoder(2);
		Temp_POS-=ReadEncode;//读取编码器数据
		if(Target_POS>0)
		{
			Control_Servor_Angle();
			Control_Motor_PWM();
		}		
	}
}


//控制初始化
//初始化获取PID调控后PWM参数
void Control_Init(void)
{
	TIM3_Int_Init(7199,39);//中断时间长度5ms
}

//根据PID参数设置直流电机PWM
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
		if(MotorPWM>Forward_Speed) MotorPWM=Forward_Speed;//限幅
		else if(MotorPWM<-Forward_Speed)	MotorPWM=-Forward_Speed;
		if(myabs(Temp_POS-Target_POS)<26*Encoder_P)
		{
			if(MotorPWM>Forward_Speed) MotorPWM=3100;//限幅
			else if(MotorPWM<-Forward_Speed)	MotorPWM=-3100;
		}
	}	
	Set_Motor_PWM(MotorPWM);
}


//退回时控制舵机函数
void Control_Servor_Angle(void)
{
	/*int Temp=0;//定义中间临时变量
	int MID_AD=0;//定义寻线差值变量
	int SERVOR_V=0;//定义控制舵机角度变量
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



