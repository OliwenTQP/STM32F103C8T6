#ifndef _LQ12864_H_
#define _LQ12864_H_

#include "sys.h"
#include "delay.h"


/**************************************************************/
#define high 1
#define low 0

#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	64

/***********************引脚定义******************************/
#define SCL PBout(3)// PB3
#define SDA PBout(4)// PB4
/**********************函数声明*******************************/
void OLED_Fill(u8 bmp_dat);
void OLED_CLS(void);
void OLED_Init(void);
void OLED_P6x8Str(u8 x,u8 y,u8 ch[]);
void OLED_P8x16Str(u8 x,u8 y,u8 ch[]);
void OLED_P16x16Ch(u8 x,u8 y,u8 N);
void Draw_BMP(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);
void OLED_Pin_Init(void);
void Show_CH(u8 x,u8 y);
#endif
