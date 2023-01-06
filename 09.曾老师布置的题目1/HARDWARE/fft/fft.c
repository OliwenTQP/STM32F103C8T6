#include "fft.h"

#include "math.h"
#define NPT 1024
#define PI2 6.28318530717959
#define Fs 44800

long lBufInArray[NPT];
long lBufOutArray[NPT/2];
long lBufMagArray[NPT/2];

void InitBufInArray()
{
    unsigned short i;
    float fx,fs;
     fs = (float)Fs;
     for(i=0; i<NPT;i++)
     {
         fx = 1000 + 1500 * sin(PI2 * i * 350.0 / fs) +
              2500 * sin(PI2 * i * 8400.0 / fs) +
              4000 * sin(PI2 * i * 18725.0 / fs);
         lBufInArray[i] = ((signed short)fx) << 16 ;
     }
}

void GetPowerMag()
{
    signed short lX,lY;
    float X,Y,Mag;
    unsigned short i;

    for(i=0; i<NPT;i++)
    {
         lX  = (lBufOutArray[i] << 16) >> 16;
         lY  = (lBufOutArray[i] >> 16);
         X = NPT * ((float)lX) / 32768;
         Y = NPT * ((float)lY) / 32768;
         Mag = sqrt(X * X + Y * Y) * 1.0 / NPT;
         if(i == 0)
             lBufMagArray[i] = (unsigned long)(Mag * 32768);
         else
             lBufMagArray[i] = (unsigned long)(Mag * 65536);
    }
}

