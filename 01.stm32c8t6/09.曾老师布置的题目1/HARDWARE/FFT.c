#include "commonhead.h"
#include "FFT.h"
#include "arm_math.h"
#include "fft.h"

float FFT_InputBuf[FFT_LENGTH*2];	//FFT��������
float FFT_OutputBuf[FFT_LENGTH];	//FFT�������
float input[2*FFT_LENGTH];

arm_cfft_radix2_instance_f32 scfft;



void Init_FFT(u16 FFT_Length)
{
	arm_cfft_radix2_init_f32(&scfft,FFT_Length,0,1);//��ʼ��scfft�ṹ�壬�趨FFT��ز���
}


void Generate_InputArray(float input[],u16 Length)
{
	for(u16 i=0;i<Length;i++)
	{
		FFT_InputBuf[2*i]=input[i];//ʵ������
		FFT_InputBuf[2*i+1]=0;//��������
	}
}


/*
@brief ����������±�ֵ������������������
*/

void FFT_GetValue(float input[],float output[], u16 Length)
{
	Init_FFT(Length);
	Generate_InputArray(input,Length);
	arm_cfft_radix2_f32(&scfft,FFT_InputBuf);	//FFT���㣨��2��
	arm_cmplx_mag_f32(FFT_InputBuf,output,Length);	//��������������ģ�÷�ֵ 
}


void test_fft()
{
	u16 i=0;
	

	for(i=0;i<FFT_LENGTH;i++)	//���������ź�
	{
		input[i]=100+10*arm_sin_f32(2*PI*i/FFT_LENGTH)+30*arm_sin_f32(2*PI*i*4/FFT_LENGTH)+50*arm_cos_f32(2*PI*i*8/FFT_LENGTH);
	}
			FFT_GetValue(input,FFT_OutputBuf,FFT_LENGTH);
//	
//	    arm_cfft_radix4_init_f32(&scfft,FFT_LENGTH,0,1);
//			for(i=0;i<FFT_LENGTH;i++)//�����ź�����
//			{
//				 FFT_InputBuf[2*i]=100+10*arm_sin_f32(2*PI*i/FFT_LENGTH)+30*arm_sin_f32(2*PI*i*4/FFT_LENGTH)+50*arm_cos_f32(2*PI*i*8/FFT_LENGTH);	//���������ź�ʵ��
//				 FFT_InputBuf[2*i+1]=0;//�鲿ȫ��Ϊ0
//			}
//			arm_cfft_radix4_f32(&scfft,FFT_InputBuf);	//FFT���㣨��4��
//			arm_cmplx_mag_f32(FFT_InputBuf,FFT_OutputBuf,FFT_LENGTH);	//��������������ģ�÷�ֵ 
			for(i=0;i<FFT_LENGTH;i++)
			{
				printf("%f\r\n",FFT_OutputBuf[i]);
			}
}
