#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Chara : public GameObject, public TaskObject
{
public:
	enum Direction						//�������Ǘ�
	{
		LEFT,
		RIGHT,
	};
private:
	Texture Image;
	Vec2 move;
	const float MOVE_SPEED;								//�ړ��X�s�[�h
	const float JUMP_POWER;								//�W�����v�p���[
	const float MAX_FALL;								//�����ő呬�x
	const float GRAVITY;		//�d�͉����x
	const float FIN_SPEED;								//���C
	Direction direction;										//�������i�[����ϐ�
	std::string taskName;										//��
<<<<<<< HEAD
	int AnimCnt;
	bool isAuto;
	bool isCollision;
	int MoveCnt;
	__int8 isCollisionNow;
	bool isAutoOff;
=======
	int AnimCnt;			//�A�j���[�V�����J�E���g
	bool isAuto;			//�I�[�g��ԗL��
	bool isCollision;		//�����蔻��L��
	int MoveCnt;			//�ړ��J�E���g
	__int8 isCollisionNow;	//�����蔻���ԃJ�E���g
	bool isAutoOff;			//�I�[�g���[�h�ڍs�L��
	bool isAutoMode;		//�I�[�g���[�h�ł̈ړ��w��L��
	Vec2 startPos;			//�I�[�g���[�h���̊J�n�n�_
	Vec2 EndPos;			//�I�[�g���[�h���̏I���n�_
	Easing easing_x;		//�C�[�W���O�ړ��l
>>>>>>> develop
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
	void SetDirection(const Direction&);
	void SetAutoFlag(const bool);
<<<<<<< HEAD
	Vec2 GetMove() const;
=======
	void SetAutoMode(const bool);
	Vec2 GetMove() const;
	void Set(const Vec2&, const Vec2&);
	bool isAutoPlay() const;
	Direction nowDirection() const;
>>>>>>> develop
};