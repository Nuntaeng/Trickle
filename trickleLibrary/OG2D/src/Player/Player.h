#pragma once
//______________________________//
//|�v���C��                    |//
//|�����F2018/03/23���c	       |//
//|�����F2018/03/26����N�@    |//
//|�����F2018/03/29����N�@    |//
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
	Vec2 est;
	//�W�����v��Ԕ���
	bool jumpFlag;
	//�ړ��X�s�[�h
	const float MOVE_SPEED = 10.f;
	//�W�����v�p���[
	const float JUMP_POWER = -20.f;
	//�d�͉����x
	const float GRAVITY = 0.98f;
	//�v���C���[�̌�����\�����O���
	enum Direction
	{
		LEFT,
		RIGHT,
	};
	//�������i�[����ϐ�
	Direction direction;
	//��������p
	Object footBase;
	//�����蔻��p
	Object headBase;

	struct Move {
		Vec2 est;
		float angle;
	};
	Move move;

	//��������//-----------------------------------------------------------------------------
	//�N���X�̃����o�֐�
	//��������//-----------------------------------------------------------------------------
	//�W�����v�̃v���g�^�C�v�錾
	void JumpMove();
	//�����ڐG����̃v���g�^�C�v�錾
	void CheckFoot();
	//���ڐG����̃v���g�^�C�v�錾
	void CheckHead();
};


