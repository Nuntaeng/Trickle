#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Chara : public GameObject, public TaskObject
{
	enum Direction						//�������Ǘ�
	{
		LEFT,
		RIGHT,
	};
	Texture Image;
	Vec2 move;
	const float MOVE_SPEED;								//�ړ��X�s�[�h
	const float JUMP_POWER;								//�W�����v�p���[
	const float MAX_FALL;								//�����ő呬�x
	const float GRAVITY;		//�d�͉����x
	const float FIN_SPEED;								//���C
	Direction direction;										//�������i�[����ϐ�
	std::string taskName;										//��
	int AnimCnt;
	bool isAuto;
	bool isCollision;
	int MoveCnt;
	__int8 isCollisionNow;
public:
	Chara(std::string&, Vec2&);
	virtual ~Chara();
	typedef std::shared_ptr<Chara> SP;
	static SP Create(std::string&, Vec2&, bool = true);
	void UpDate();
	void Render2D();
	void Friction(Vec2&);
	void MoveCheck(Vec2);
	bool FootCheck();
	bool Jump();
	void AutoMove();
	void ManualMove(Vec2&);
	void IsCollisionCheck();
	bool CollisionNumCheck(__int8);
	void MoveReset();
};