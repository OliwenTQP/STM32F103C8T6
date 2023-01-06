#include "commonhead.h"
#include "FFT.h"
#include "arm_math.h"
#include "fft.h"

float FFT_InputBuf[FFT_LENGTH*2];	//FFT输入数组
float FFT_OutputBuf[FFT_LENGTH];	//FFT输出数组
float input[2*FFT_LENGTH];

arm_cfft_radix2_instance_f32 scfft;



void Init_FFT(u16 FFT_Length)
{
	arm_cfft_radix2_init_f32(&scfft,FFT_Length,0,1);//初始化scfft结构体，设定FFT相关参数
}


void Generate_InputArray(float input[],u16 Length)
{
	for(u16 i=0;i<Length;i++)
	{
		FFT_InputBuf[2*i]=input[i];//实数部分
		FFT_InputBuf[2*i+1]=0;//虚数部分
	}
}


/*
@brief 输入数组的下标值必须是输出数组的两倍
*/

void FFT_GetValue(float input[],float output[], u16 Length)
{
	Init_FFT(Length);
	Generate_InputArray(input,Length);
	arm_cfft_radix2_f32(&scfft,FFT_InputBuf);	//FFT计算（基2）
	arm_cmplx_mag_f32(FFT_InputBuf,output,Length);	//把运算结果复数求模得幅值 
}


void test_fft()
{
	u16 i=0;
	

	for(i=0;i<FFT_LENGTH;i++)	//生成输入信号
	{
		input[i]=100+10*arm_sin_f32(2*PI*i/FFT_LENGTH)+30*arm_sin_f32(2*PI*i*4/FFT_LENGTH)+50*arm_cos_f32(2*PI*i*8/FFT_LENGTH);
	}
			FFT_GetValue(input,FFT_OutputBuf,FFT_LENGTH);
//	
//	    arm_cfft_radix4_init_f32(&scfft,FFT_LENGTH,0,1);
//			for(i=0;i<FFT_LENGTH;i++)//生成信号序列
//			{
//				 FFT_InputBuf[2*i]=100+10*arm_sin_f32(2*PI*i/FFT_LENGTH)+30*arm_sin_f32(2*PI*i*4/FFT_LENGTH)+50*arm_cos_f32(2*PI*i*8/FFT_LENGTH);	//生成输入信号实部
//				 FFT_InputBuf[2*i+1]=0;//虚部全部为0
//			}
//			arm_cfft_radix4_f32(&scfft,FFT_InputBuf);	//FFT计算（基4）
//			arm_cmplx_mag_f32(FFT_InputBuf,FFT_OutputBuf,FFT_LENGTH);	//把运算结果复数求模得幅值 
			for(i=0;i<FFT_LENGTH;i++)
			{
				printf("%f\r\n",FFT_OutputBuf[i]);
			}
}
