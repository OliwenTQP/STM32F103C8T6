#include "commonhead.h"


extern unsigned char mode_show;  //模式为1蓝牙控制模式，模式为2为循迹模式，模式3为屏障碍模式
extern u8 blu_char;
float distant; //超声波的距离
//行进
#define W0100 L1==0&&ML==1&&MR==0&&R1==0   //0100=========左小弯
#define W0010 L1==0&&ML==0&&MR==1&&R1==0   //0010=========右小弯
#define W0110 L1==0&&ML==1&&MR==1&&R1==0   //0110=========前进

#define W0000 L1==0&&ML==0&&MR==0&&R1==0   //0100=========前进

#define W1000 L1==1&&ML==0&&MR==0&&R1==0   //1000=========左大弯
#define W0001 L1==0&&ML==0&&MR==0&&R1==1	 //0001=========右大弯
//#define W001 L1==0&&ML==0&&R1==1		//001
//#define W011 L1==0&&ML==1&&R1==1		//011
//#define W100 L1==1&&ML==0&&R1==0		//100
//#define W101 L1==1&&ML==0&&R1==1		//101
//#define W110 L1==1&&ML==1&&R1==0		//110

//停车
#define T111 L1==1&&ML==1&&R1==1




int main()
{
	SystemInit1();
	
	   //Go(800,800);	 
	 
	 while(1)
{			
//		Go(1000,1000);
//		delay_ms(5000);
//		Stop(0,0);	
//delay_ms(5000);	
//	TurnL1(500,250);
//	delay_ms(10000);
//	TurnL2(500,400);
//	delay_ms(10000);
//	TurnR1(250,500);
//	delay_ms(10000);
//	TurnR2(250,500);
//	delay_ms(10000);
//	char message[30];
////				distant = Hcsr04GetLength();
////				printf("%f\r\n",distant);
////				printf("%d\r\n",mode_show);
//		sprintf(message,"distant=%.1f",distant);
//		PrintChar(message);

	Go(400,400);
	if(mode_show == 1)
	{
			//Stop(0,0);	delay_ms(2000);
		if(blu_char!='\0')
		{			
			if(blu_char=='W')						{			Go(1000,1000);	}
			else if(blu_char=='S')			{			Back(1000,1000);}
			else if(blu_char=='A')			{			TurnL1(800,1000);	delay_ms(7000);		blu_char='\0';		}
			else if(blu_char=='D')			{			TurnR1(1000,800);	delay_ms(7000);		blu_char='\0';		}
			else if(blu_char=='C')			{			Stop(0,0);			}	
				
		}
		else if(blu_char=='\0')				{			Stop(0,0);			}
	}
	else if(mode_show == 2)
	{
					blu_char='\0';
																				if(W0000)//直行     111101111
																				{																				Go(800,800);					delay_ms(100);													}																								//																
//																				else if(W111)//   停车
//																				{																			  Stop(0,0);						delay_ms(2000);													}															
//																				else if(W000)//    全白
//																				{																			  Go(850,850);					delay_ms(2000);													}	
																				else if(W0001)//    右大转
																				{																				TurnR1(1000,250);		  delay_ms(500);													}																			
																				else if(W1000)//    左大转
																				{																				TurnL1(250,1000);			delay_ms(500);													}
	          														else if(W0010)//    右小转
																				{																				TurnR2(1000,800);			delay_ms(200);					  		      		}																					
																				else if(W0100)//    左小转
																				{																			  TurnL2(800,1000);			delay_ms(200);								  				}		

	}																				
																				
//		printf("L1 = %d,ML = %d,MR = %d,R1 = %d\r\n",L1,ML,MR,R1);
//	printf("%d",mode_show); 
	else if(mode_show == 3)
	{
				distant = Hcsr04GetLength();
				printf("%f\r\n",distant);
		TurnL1(900,900);delay_ms(100);
		if(distant < 23.0)	{	TurnL1(100,900); delay_ms(1000);}
	}
	

	distant = 1.0;
		//distant = Hcsr04GetLength();
		//printf("%f\r\n",distant);
	printf("helloworld\r\n");
	
//  while(1)
//	{
//		
////		 pwmzkb=250;
////			TIM_SetCompare1(TIM2,pwmzkb);	 // 修改占空比        
////			pwmzkb=250;
////			TIM_SetCompare3(TIM4,pwmzkb);
//		
////			Right_dianji_zhenzhuan(500);
////			Left_dianji_zhenzhuan(500);
////		pwmzkb--;
////		if(pwmzkb >500)
////		{
////			pwmzkb = 250;
////		}
////		printf("pwmzkb = %d\r\n",pwmzkb);

////		delay_ms(100);
////		LED_open();	
////		delay_ms(500);	
////		LED_close();		
////		delay_ms(500);
//	printf("L1 = %d,M = %d,R1 = %d\r\n",L1,M,R1);

			printf("helloworld\r\n");
////	PrintChar("helloworldusart3");
	}
}
 
