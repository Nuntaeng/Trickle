#pragma once
#include "Object\Object.h"
#include "Water\water.h"

class Seihyouki : public Object
{
public:
	Seihyouki();
	~Seihyouki();
	void Create(Vec2, Vec2);		//���W�l�@�����蔻��T�C�Y
	Object hitBace;
	void UpDate();
	void toIce(Water*);				//�X�ɂ���
	void SetWaterPool(std::vector<Water*>*);			//�f�[�^��n���֐�
private:
	int movetime;					//�X�ɂ���܂ł̊i�[����t���[����
	const int movetime_ice = 20;	//�X�ɂ���܂ŁE�E�E
	std::vector<Water*> *water;		//Vector�|�C���^
};