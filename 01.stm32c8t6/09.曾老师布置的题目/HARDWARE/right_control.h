#ifndef __RIGHT_H //�� #endif һ��ʹ�ã������ظ�����ͷ�ļ�����߱���Ч��
#define __RIGHT_H //���û�����ù�ͷ�ļ�����������¶���

#include "timer2.h"
#include "timer4.h"
void Right_dianji_Init(void); //���庯��ԭ��(��������)��һ��ͷ�ļ�(.h�ļ�)�ڶ��Ǻ���ԭ�ͣ�
                     //.c�ļ��ڶ��Ǻ�������
										 //�ú���ΪLEDӲ����ʼ������
void Right_dianji_zhenzhuan(u32 pwmzkb);
void Right_dianji_fanzhuan(u32 pwmzkb);

#endif //������ϣ��������ù�ͷ�ļ�������һ��
