#ifndef __COMMON_H_
#define	__COMMON_H_

#include "sys.h"

#define INQ1 PBin(12)// PA5
#define INQ2 PBin(13)// PA5



/***************���ڶ��������****************/
#define Servo_MID 165 			//�������м�λ�ò���


/***************���ڳ��ӵĲ���****************/
#define Wheel_G 21		//����С�������ܳ�,��λ����

#define Encoder_P 507	//������תһȦ��ֵ

/***************���������Ĳ���****************/
#define Rode_L 1000		//���������ȣ���λ����
#define Rode_Cilcle 47  //����С������һ�����õ�Ȧ��



//һ��PID����
#define Forward_P_DATE1 0.005
#define Forward_D_DATE1 0.3
#define Back_P_DATE1 0.0025
#define Back_D_DATE1 0.4
#define Forward_Speed_DATE1 3200
#define Back_Speed_DATE1 2200
#define Encode_n_DATE1 1


/***************�ⲿ��������****************/
extern long int Target_POS;
extern long int Temp_POS;	
extern float Forward_P,Forward_D;
extern int Forward_Speed,Back_Speed;
extern int Encode_n;


/*****************��������*****************/
extern void Show_Battary_Vol(void);
extern void Speed_PIN_Config(void);
extern void Change_Speed(void);
#endif



