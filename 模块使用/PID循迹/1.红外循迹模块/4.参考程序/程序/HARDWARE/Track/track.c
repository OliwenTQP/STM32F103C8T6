#include "track.h"
#include "adc.h"
#include "stdio.h"
#include "stdlib.h"


/********************************
循迹功能函数

@魔石科技@
*********************************/


int PosFlagValue=(int)((LEFT_MAX+RIGHT_MAX-LEFT_THERSH-RIGHT_THERSH)/3.0f);



//获取循迹传感器输出函数
//返回值：int类型，范围循迹传感器数据，根据此值来调节小车舵机角度
int GetTraceDate(void)
{
	int Data_Out;//定义数据输出变量
	int Left_AD,Right_AD,Mid_AD;//定义左右中传感器AD值变量
	static char PosFlag=0;//定义传感器位置标志位，0认为传感器在黑线偏左位置，1认为小车在传感器偏右位置
	
	Left_AD=Get_Adc(2);
 	Mid_AD=Get_Adc(3);
	Right_AD=Get_Adc(4);
	
	Data_Out=(Left_AD-Right_AD+D_AD_VALUE);
	if(Data_Out>PosFlagValue)
	{
		PosFlag=1;
	}
	else if(Data_Out<-PosFlagValue)
	{
		PosFlag=0;
	}
	if(Mid_AD<LEFT_THERSH)
	{	
		if(Data_Out>PosFlagValue)
		{
			Data_Out=(2*LEFT_MAX-Left_AD)*2-LEFT_SPAN;
		}
		else if((Data_Out<PosFlagValue)&&(PosFlag==1))
		{
			Data_Out=abs((2*LEFT_MAX-Left_AD)*2-LEFT_SPAN);
		}
		
	} 
	
	if(Mid_AD<RIGHT_THERSH)
	{	
		if(Data_Out<-PosFlagValue)
		{
			Data_Out=(Right_AD-2*RIGHT_MAX)*2-RIGHT_SPAN;
		}
		else if((Data_Out>-PosFlagValue)&&(PosFlag==0))
		{
			Data_Out=-abs((Right_AD-2*RIGHT_MAX)*2-RIGHT_SPAN);
		}
	}
	
	return Data_Out;
}



//此函数为循迹传感器校准函数
void GetParament(void)
{
	int DValue=0;
	int Left_AD,Right_AD,Mid_AD;//定义左右中传感器AD值变量
	
	static int LeftMax=0;
	static int RightMax=0;
	static int Left_Thersh=0;
	static int Right_Thersh=0;
	static int Left_Span=0;
	static int Right_Span=0;
	
	
	Right_AD=Get_Adc(4); 	//右传感器获取的AD值
	Mid_AD=Get_Adc(3);	//中间传感器获取的AD值
	Left_AD=Get_Adc(2);		//左传感器获取的AD值
		
	
	if(Left_AD>LeftMax)	
	{
		LeftMax=Left_AD;
		Left_Thersh=Mid_AD;
		Left_Span=(2*LeftMax-Left_AD)*2-(Left_AD-Right_AD+D_AD_VALUE);
		
	}
	if(Right_AD>RightMax)
	{
		RightMax=Right_AD;
		Right_Thersh=Mid_AD;
		Right_Span=(Right_AD-2*RightMax)*2-(Left_AD-Right_AD+D_AD_VALUE);	
	}		
	
	
	DValue=Right_AD-Left_AD;//差值，右传感器减左传感器
	
	
	printf("Right_AD:%d Mid_AD:%d Left_AD:%d\r\n",Right_AD,Mid_AD,Left_AD);
	printf("D_AD_VALUE:%d LeftMax:%d RightMax:%d Left_Thersh:%d Right_Thersh:%d Left_Span:%d Right_Span:%d\r\n",DValue,LeftMax,RightMax,Left_Thersh,Right_Thersh,Left_Span,Right_Span);
}




