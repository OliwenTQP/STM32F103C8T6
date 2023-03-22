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
long int Target_POS = Target_POS_CAR;//¶¨ÒåĞ¡³µÄ¿±êÎ»ÖÃ±äÁ¿
long int Temp_POS = 0;						//¶¨ÒåĞ¡³µÏÖÔÚÎ»ÖÃ±äÁ¿
int ReadEncode = 0;
u8 END_FLAG=0;//¶¨Òåµ½ÖÕµãÏß±êÖ¾Î»£¬Èç¹ûµ½ÖÕµãÏßÔò=1£¬·ñÔòÎª0
u8 ANTI_FLAG=0;
int Encode_n;

float Forward_P=0,Forward_D=0;
float Back_P=0,Back_D=0;
int Forward_Speed=0,Back_Speed=0;
/**************************************************************************
º¯Êı¹¦ÄÜ£ºÎ»ÖÃÊ½PID¿ØÖÆÆ÷
Èë¿Ú²ÎÊı£º±àÂëÆ÷²âÁ¿Î»ÖÃĞÅÏ¢£¬Ä¿±êÎ»ÖÃ
·µ»Ø  Öµ£ºµç»úPWM
¸ù¾İÎ»ÖÃÊ½ÀëÉ¢PID¹«Ê½ 
pwm=Kp*e(k)+Ki*¡Æe(k)+Kd[e£¨k£©-e(k-1)]
e(k)´ú±í±¾´ÎÆ«²î 
e(k-1)´ú±íÉÏÒ»´ÎµÄÆ«²î  
¡Æe(k)´ú±íe(k)ÒÔ¼°Ö®Ç°µÄÆ«²îµÄÀÛ»ıºÍ;ÆäÖĞkÎª1,2,,k;
pwm´ú±íÊä³ö
**************************************************************************/
int Position_PID (int Encoder,int Target)
{ 	
	 float Position_KP=-1.2,Position_KI=0,Position_KD=-70;
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //¼ÆËãÆ«²î
	 Integral_bias+=Bias;	                                 //Çó³öÆ«²îµÄ»ı·Ö
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //Î»ÖÃÊ½PID¿ØÖÆÆ÷
	 Last_Bias=Bias;                                       //±£´æÉÏÒ»´ÎÆ«²î 
	 return Pwm;                                           //ÔöÁ¿Êä³ö
}

//¶æ»úPID¿ØÖÆº¯Êı
int Position_PID_Servo(int Encoder,int Target)
{ 	
	float Position_KP=Forward_P,Position_KI=0,Position_KD=Forward_D;//0.33
	static float Bias,Pwm,Integral_bias,Last_Bias;
	Bias=Encoder-Target;                                  //¼ÆËãÆ«²î
	Integral_bias+=Bias;	                                 //Çó³öÆ«²îµÄ»ı·Ö
	Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //Î»ÖÃÊ½PID¿ØÖÆÆ÷
	Last_Bias=Bias;                                       //±£´æÉÏÒ»´ÎÆ«²î 
	return Pwm;                                            //ÔöÁ¿Êä³ö
}


/**************************************************************************
º¯Êı¹¦ÄÜ£º¾ø¶ÔÖµº¯Êı
Èë¿Ú²ÎÊı£ºint
·µ»Ø  Öµ£ºunsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}


//¶¨Ê±Æ÷3ÖĞ¶Ï·şÎñ³ÌĞò
void TIM3_IRQHandler(void)   //TIM3ÖĞ¶Ï
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //¼ì²éTIM3¸üĞÂÖĞ¶Ï·¢ÉúÓë·ñ
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //Çå³ıTIMx¸üĞÂÖĞ¶Ï±êÖ
		ReadEncode=Read_Encoder(2);
		Temp_POS-=ReadEncode;//¶ÁÈ¡±àÂëÆ÷Êı¾İ
		if(Target_POS>0)
		{
			Control_Servor_Angle();
			Control_Motor_PWM();
		}		
	}
}


//¿ØÖÆ³õÊ¼»¯
//³õÊ¼»¯»ñÈ¡PIDµ÷¿ØºóPWM²ÎÊı
void Control_Init(void)
{
	TIM3_Int_Init(7199,39);//ÖĞ¶ÏÊ±¼ä³¤¶È5ms
}

//¸ù¾İPID²ÎÊıÉèÖÃÖ±Á÷µç»úPWM
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
		if(MotorPWM>Forward_Speed) MotorPWM=Forward_Speed;//ÏŞ·ù
		else if(MotorPWM<-Forward_Speed)	MotorPWM=-Forward_Speed;
		if(myabs(Temp_POS-Target_POS)<26*Encoder_P)
		{
			if(MotorPWM>Forward_Speed) MotorPWM=3100;//ÏŞ·ù
			else if(MotorPWM<-Forward_Speed)	MotorPWM=-3100;
		}
	}	
	Set_Motor_PWM(MotorPWM);
}


//ÍË»ØÊ±¿ØÖÆ¶æ»úº¯Êı
void Control_Servor_Angle(void)
{
	/*int Temp=0;//¶¨ÒåÖĞ¼äÁÙÊ±±äÁ¿
	int MID_AD=0;//¶¨ÒåÑ°Ïß²îÖµ±äÁ¿
	int SERVOR_V=0;//¶¨Òå¿ØÖÆ¶æ»ú½Ç¶È±äÁ¿
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



