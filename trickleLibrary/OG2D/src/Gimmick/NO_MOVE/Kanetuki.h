#pragma once
#include "Object\Object.h"
#include "Water\water.h"

class Water;

class Kanetuki : public Object
{
public:
	Kanetuki();
	~Kanetuki();
	void Create(Vec2, Vec2);	//���W�l�@�����蔻��T�C�Y
	void SetWaterPool(std::vector<Water*> *);
	void Update();
	Object hitBace;
private:
	const int Fire_time_LIQUID = 70;	//���M���鎞�� �t��
	const int Fire_time_SOLID = 40;	    //���M���鎞�� ��
	int Fire_movetime;					//�R�₷���Ԃ��i�[����
	
	//typedef std::vecor<Water*> WaterPool;
	std::vector<Water*> *water;		

	//��ԑJ��
	void toSteam(Water*);		//�����琅���C�ɂ���
};