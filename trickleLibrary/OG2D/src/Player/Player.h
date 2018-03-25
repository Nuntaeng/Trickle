#pragma once
//______________________________//
//|�v���C��                     |//
//|�����F2018/03/23���c	       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Player :public Object
{
public:
	Texture playerimg;
	std::string fileName = "player.png";
	bool hitcheck;

	void Initialize();
	void UpDate();
	void Render();
	void Finalize();
	//��������//-----------------------------------------------------------------------------
	//�ǉ��ϐ�//-----------------------------------------------------------------------------
	//��������//-----------------------------------------------------------------------------


	bool jumpFlag = false;
	Vec2 est;

	const float MOVE_SPEED = 10.f;
	const float JUMP_POWER = -30.f;
	const float GRAVITY = 0.98f;

	//��������//-----------------------------------------------------------------------------
	//�N���X�̃����o�֐�
	//��������//-----------------------------------------------------------------------------
	//�W�����v�̃v���g�^�C�v�錾
	void JumpMove();
};


