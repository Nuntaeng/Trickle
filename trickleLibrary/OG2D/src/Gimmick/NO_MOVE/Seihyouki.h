#pragma once
#include "Object\Object.h"
#include "Water\water.h"

class Seihyouki : public Object
{
public:
	Seihyouki();
	~Seihyouki();
	bool Create(Vec2, Vec2);		//���W�l�@�����蔻��T�C�Y
	void CheckHit();				//�����蔻��
	void Set_pointa();				//���̓����蔻���o�^����
	Object hitBace;
private:
	bool Initital;					//1�x���������������Ă��邩�ǂ����E�E�E
	int movetime;					//�X�ɂ���܂ł̊i�[����t���[����
	const int movetime_ice = 20;	//�X�ɂ���܂ŁE�E�E
	std::vector<Water*> w_vec;		//�����i�[���邽�߂̂��
};