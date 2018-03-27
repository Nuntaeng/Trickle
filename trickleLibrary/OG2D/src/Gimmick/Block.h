#pragma once

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Win\WinMain.h"

//�{�b�N�X�{�̂̃N���X--------------------------------------------------------------------------------
class GimmickB :public Object
{
public:
	Texture BlockImg;
	std::string fileName = "Collision.png";
	Box2D HitR;
	Box2D HitL;
	bool hitRight;     //�E�������蔻��p
	bool hitLeft;      //���������蔻��p
	bool hitbottom;    //�n�ʓ����蔻��p
	float speed;       //�������Ƃ��̈ړ����x

	//bool MapHit(Box2D map, Box2D block);

	void Initialize();
	TaskFlag UpDate();
	void Render();
	void Finalize();
};


