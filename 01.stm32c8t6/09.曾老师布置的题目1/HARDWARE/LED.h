#ifndef __LED_H //�� #endif һ��ʹ�ã������ظ�����ͷ�ļ�����߱���Ч��
#define __LED_H //���û�����ù�ͷ�ļ�����������¶���

#define LED_open() GPIO_ResetBits(GPIOC, GPIO_Pin_13); //��ʼ����������GPIOA4Ϊ�ߵ�ƽ
#define LED_close() GPIO_SetBits(GPIOC, GPIO_Pin_13); //��ʼ����������GPIOA4Ϊ�ߵ�ƽ
void LED_Init(void); //���庯��ԭ��(��������)��һ��ͷ�ļ�(.h�ļ�)�ڶ��Ǻ���ԭ�ͣ�
                     //.c�ļ��ڶ��Ǻ�������
										 //�ú���ΪLEDӲ����ʼ������

#endif //������ϣ��������ù�ͷ�ļ�������һ��
