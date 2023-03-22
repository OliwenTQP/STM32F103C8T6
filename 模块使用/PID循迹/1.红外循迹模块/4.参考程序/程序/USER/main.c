#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "beep.h" 
#include "led.h"
#include "motor.h"
#include "servor.h"
#include "LQ12864.h"
#include "encoder.h"   
#include "timer.h"
#include "common.h"
#include "control.h"
#include "adc.h"
#include "track.h"
#include "24l01.h"


/***********************************
±¾³ÌĞòÎªÑ­¼£Ğ¡³µµçÂ·°åÇı¶¯º¯Êı¿â
±àĞ´£ºDinvent
@Ä§Ê¯¿Æ¼¼@
************************************/


 int main(void)
 {
	char buff[20];
	int date=0;
	delay_init();//ÑÓÊ±º¯Êı³õÊ¼»¯
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ÉèÖÃÖĞ¶ÏÓÅÏÈ¼¶·Ö×éÎª×é2£º2Î»ÇÀÕ¼ÓÅÏÈ¼¶£¬2Î»ÏìÓ¦ÓÅÏÈ¼¶¯
	uart_init(115200);//´®¿Ú³õÊ¼»¯ ²¨ÌØÂÊ115200
	OLED_Init();//OLED³õÊ¼»¯º¯Êı
	Encoder_Init_TIM2();
	LED_Init();	 //³õÊ¼»¯ÓëLEDÁ¬½ÓµÄÓ²¼ş½Ó¿Ú
	Beep_Init(); //·äÃùÆ÷³õÊ¼»¯º¯Êı		 
	Motor_Init();//µç»ú³õÊ¼»¯º¯Êı
	Servor_Init();//¶æ»ú³õÊ¼»¯º¯Êı			  
	Adc_Init();		//ÄÚ²¿ADC³õÊ¼»¯º¯Êı	 
	Control_Init();	
	NRF24L01_Init();//24L01³õÊ¼»¯
	NRF24L01_TX_Mode();//ÅäÖÃ³É·¢ËÍÄ£Ê½
	//OLED_P6x8Str(2,20,"Car System");
	Show_CH(30,0);//ÏÔÊ¾ÖĞÎÄ±êÌâ
	//Show_Battary_Vol();//ÏÔÊ¾µç³ØµçÑ¹º¯Êı	 
	while(1)
	{	
		LED_test();
		GetParament();
		//date=GetTraceDate();
		//sprintf(buff,"%d",date);
		//printf(buff);
	}
 }

	

