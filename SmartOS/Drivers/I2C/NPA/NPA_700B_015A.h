#ifndef _NPA_H
#define _NPA_H

#include "I2C.h"
//ѹ�������� NPA-700B-015A
class NPA_700B_015A
{
public:
	SoftI2C* IIC;

	NPA_700B_015A();
	int Read();
	float ReadP();//��ȡ����ѹֵ
	void Init();
private:	
	byte Address; //�豸��ַ
};
#endif
