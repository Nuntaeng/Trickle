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

	const std::array<std::string, 3> WALKABLE_CHIPS{
		"Floor",
		"Soil",
		"Net"
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

	/**
	 * @brief	�o�P�b�c�̂��߂ȃX�y�V�����ȏ���
	 * @note	�����蔻��݌v�~�X�ł��f�փy��
	 */
	void TakeBucket(Bucket*);

	void CustomCollision(std::vector<Object*>*);

private:
	const std::string fileName = "player.png";
	const float MOVE_SPEED = 10.f;								//�ړ��X�s�[�h
	const float JUMP_POWER = -20.f;								//�W�����v�p���[
	const float GRAVITY = 0.98f;								//�d�͉����x
	//const Input::Key BUCKET_SPOIL_KEY = Input::Key::B;			//�o�P�b�c���ڂ��L�[
	//const Input::Key BUCKET_TAKEDROP_KEY = Input::Key::F;		//�o�P�b�c�E���E�̂Ă�L�[

	Texture playerimg;
	Move move;
	Vec2 est;										//�ړ���
	Direction direction;							//�������i�[����ϐ�
	Bucket* bucket;

	// �����蔻��p
	Object footBase;
	Object headBase;
	Object leftBase;
	Object rightBase;

	bool InputLeft() {
		return gameEngine->in.on(Input::CL,0) /*|| gameEngine->gamepad[0].ButtonOn(GLFW_JOYSTICK_14)*/;
	}
	bool InputRight() {
		return gameEngine->in.on(Input::CR,0) /*|| gameEngine->gamepad[0].ButtonOn(GLFW_JOYSTICK_12)*/;
	}
};