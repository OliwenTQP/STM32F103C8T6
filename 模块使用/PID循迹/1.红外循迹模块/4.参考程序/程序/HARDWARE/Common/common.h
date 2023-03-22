#ifndef __COMMON_H_
#define	__COMMON_H_

#include "sys.h"

#define INQ1 PBin(12)// PA5
#define INQ2 PBin(13)// PA5



/***************关于舵机的设置****************/
#define Servo_MID 165 			//定义舵机中间位置参数


/***************关于车子的参数****************/
#define Wheel_G 21		//定义小车轮子周长,单位厘米

#define Encoder_P 507	//编码器转一圈数值

/***************关于赛道的参数****************/
#define Rode_L 1000		//定义轨道长度，单位厘米
#define Rode_Cilcle 47  //定义小车走完一趟所用的圈数



//一档PID参数
#define Forward_P_DATE1 0.005
#define Forward_D_DATE1 0.3
#define Back_P_DATE1 0.0025
#define Back_D_DATE1 0.4
#define Forward_Speed_DATE1 3200
#define Back_Speed_DATE1 2200
#define Encode_n_DATE1 1


/***************外部变量声明****************/
extern long int Target_POS;
extern long int Temp_POS;	
extern float Forward_P,Forward_D;
extern int Forward_Speed,Back_Speed;
extern int Encode_n;


/*****************函数声明*****************/
extern void Show_Battary_Vol(void);
extern void Speed_PIN_Config(void);
extern void Change_Speed(void);
#endif



