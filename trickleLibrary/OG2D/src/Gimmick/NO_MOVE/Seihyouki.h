#pragma once
#include "Object\Object.h"
#include "Water\water.h"

class Seihyouki : public Object
{
public:
	Seihyouki();
	~Seihyouki();
	void Create(Vec2, Vec2);		//���W�l�@�����蔻��T�C�Y
	void CheckHit();
	void Motion();

	Object hitBace;
private:
	int movetime;
	const int movetime_ice = 20;	//�X�ɂ���܂ŁE�E�E
};