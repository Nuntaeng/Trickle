#pragma once
//______________________________//
//|�v���C��                    |//
//|�����F2018/03/23���c	       |//
//|�����F2018/03/26����N�@    |//
//|�����F2018/03/29����N�@    |//
//|�����F2018/03/30�ؖ��@    |//
//|____________________________|//
#include "CollisionManager\CollisionManager.h"
#include "Bucket\bucket.h"
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Player :public Object {

	struct Move {
		Vec2 est;
		float angle;
	};

	enum Direction
	{
		LEFT,
		RIGHT,
	};

	const std::array<std::string, 2> WALKABLE_CHIPS{
		"Floor",
		"Soil"
	};

private:
	void JumpMove();
	void CheckFoot();
	void CheckHead();
	void CheckLeft();
	void CheckRight();
	bool isWalkable(std::string);

public:
	void Initialize();
	void UpDate();
	void Render();
	void Finalize();

	/**
	 * @brief	�����蔻��ɓo�^����
	 * @param	�����蔻��Ǘ��҂̃A�h���X�l
	 */
	void Register(CollisionManager*);

private:
	const std::string fileName = "player.png";
	const float MOVE_SPEED = 10.f;					//�ړ��X�s�[�h
	const float JUMP_POWER = -20.f;					//�W�����v�p���[
	const float GRAVITY = 0.98f;					//�d�͉����x

	Texture playerimg;
	Move move;
	Vec2 est;										//�ړ���
	Direction direction;							//�������i�[����ϐ�

	// ����Ɏg���Ă�A�[��e���V�����Ȃ�ł���ǂ�
	Object footBase;
	Object headBase;
	Object leftBase;
	Object rightBase;
};