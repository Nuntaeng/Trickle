#pragma once
#include "Object\Object.h"
#include "Water\water.h"

class Water;

class Kanetuki : public Object
{
public:
	Kanetuki();
	~Kanetuki();
	bool Create(Vec2, Vec2);	//���W�l�@�����蔻��T�C�Y
	void CheckHit();			//�����蔻��݂̂���
	void Set_pointa();			//�}�l�[�W���[����Water������S�Ĕ����Ƃ�
	Object hitBace;
private:
	bool Initital;						//������������1�x�������Ȃ����߂ɁE�E�E
	const int Fire_time_LIQUID = 60;	//���M���鎞�� �t��
	const int Fire_time_SOLID = 30;	    //���M���鎞�� ��
	int Fire_movetime;					//�R�₷���Ԃ��i�[����
	std::vector <Water*>w_vec;

	
};

//cm �ɃA�h���X��n��
//Create()������
//Initialize()������