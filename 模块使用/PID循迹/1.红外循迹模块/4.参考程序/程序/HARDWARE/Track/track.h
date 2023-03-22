#ifndef _TRACK_H__
#define _TRACK_H__


#define D_AD_VALUE -400 		//确定左右传感器差值
#define LEFT_MAX 2927   	//左传感器峰值
#define RIGHT_MAX 2868  	//右传感器峰值
#define LEFT_THERSH 954	//左传感器阈值
#define RIGHT_THERSH 1258	//右传感器阈值
#define LEFT_SPAN 3763		//传感器向左移动跳跃差值   //790
#define RIGHT_SPAN -2831		//传感器向右移动跳跃差值   //1023





/****************函数声明********************/
extern int GetTraceDate(void);
extern void GetParament(void);


#endif

