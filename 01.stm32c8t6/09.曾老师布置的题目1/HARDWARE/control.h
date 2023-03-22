#ifndef __CONTROL_H //与 #endif 一起使用，避免重复引用头文件，提高编译效率
#define __CONTROL_H //如果没有引用过头文件，则进入以下定义

#include "commonhead.h"
void Go(int speed1,int speed2);
void TurnL1(int speed1,int speed2);
void TurnR1(int speed1,int speed2);
void TurnL2(int speed1,int speed2);
void TurnR2(int speed1,int speed2);
void TurnL3(int speed1,int speed2);
void TurnR3(int speed1,int speed2);
void TurnL4(int speed1,int speed2);
void TurnR4(int speed1,int speed2);
void Stop(int speed1,int speed2);
void Slow(int speed1,int speed2);
void TurnW4(int speed1,int speed2);
void Back(int speed1,int speed2);
#endif //定义完毕，或者引用过头文件到达这一步
