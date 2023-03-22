#ifndef _FFT_H
#define _FFT_H

#define FFT_LENGTH		512		//FFT���ȣ�Ĭ����1024��FFT

extern float FFT_InputBuf[FFT_LENGTH*2];	//FFT��������
extern float FFT_OutputBuf[FFT_LENGTH];	//FFT�������
extern float input[2*FFT_LENGTH];

void Init_FFT(u16 FFT_Length);
void Generate_InputArray(float input[],u16 Length);
void FFT_GetValue(float input[],float output[], u16 Length);
void test_fft(void);
#endif
