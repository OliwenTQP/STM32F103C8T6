#ifndef __HOARE_H
#define __HOARE_H	 


#define R1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) 
//#define R2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)	 
//#define R3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)
//#define R4 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)
#define MR GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define ML GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
//#define L3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
//#define L2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)
#define L1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)

void HOARE_Init(void);//IO≥ı ºªØ
					    
#endif
