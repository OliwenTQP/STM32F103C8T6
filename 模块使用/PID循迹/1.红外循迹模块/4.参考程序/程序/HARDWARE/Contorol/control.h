#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "sys.h"

/***************外部变量声明***************/
extern long int Temp_POS;//定义小车目标位置变量
extern int ReadEncode;
extern u16 adc1,adc2,adc_m;
extern u8 END_FLAG;
/***************电机PID参数设置***************/



/***************舵机PID参数设置***************/




/***************外部函数声明***************/
extern int Position_PID (int Encoder,int Target);
extern void Control_Init(void);
extern void Control_Motor_PWM(void);
extern void Control_Motor_PWM_BACK(void);
extern void Set_Servor_Angle(void);
extern void Control_Servor_Angle(void);
extern void Control_Servor_Angle_Back(void);
extern void Check_END(void);
extern int myabs(int a);

#endif

