#pragma once
#include "Object\Object.h"
#include "Water\water.h"

class Kanetuki : public Object
{
public:
	Kanetuki();
	~Kanetuki();
	void Create(Vec2,Vec2);		//���W�l�@�����蔻��T�C�Y
	void CheckHit();			//�����蔻��݂̂���
	void Motion();				//�N������
	Object hitBace;
private:
	const int Fire_time_LIQUID = 30;	//���M���鎞�� �t��
	const int Fire_time_SOLID = 60;	    //���M���鎞�� ��
	int Fire_movetime;			//�R�₷���Ԃ��i�[����
};

//cm �ɃA�h���X��n��
//Create()������
//Initialize()������