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
	Texture Image;		//�g�p�摜
	Vec2 move;			//�ړ��l
	const float MOVE_SPEED;								//�ړ��X�s�[�h
	const float JUMP_POWER;								//�W�����v�p���[
	const float MAX_FALL;								//�����ő呬�x
	const float GRAVITY;		//�d�͉����x
	const float FIN_SPEED;								//���C
	Direction direction;										//�������i�[����ϐ�
	std::string taskName;										//��
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
public:
	Chara(std::string&, Vec2&);	//�R���X�g���N�^
	virtual ~Chara();			//�f�X�g���N�^
	typedef std::shared_ptr<Chara> SP;
	static SP Create(std::string&, Vec2&, bool = true);
	void UpDate();		//�X�V����
	void Render2D();	//�`�揈��
	void Friction(Vec2&);	//�d�͏���
	void MoveCheck(Vec2);	//�ړ�����
	bool FootCheck();		//�����`�F�b�N
	bool Jump();			//�W�����v���s��
	void AutoMove();		//�I�[�g�ړ�
	void ManualMove(Vec2&);	//�蓮�ړ�
	void IsCollisionCheck();	//�����蔻��J�E���g�𑝂₷
	bool CollisionNumCheck(__int8);	//�����蔻��J�E���g�������Ɠ�������Ԃ�
	void MoveReset();				//�ړ��l��������������
	void SetDirection(const Direction&);	//�����������ύX������
	void SetAutoFlag(const bool);			//�I�[�g�ړ����s������ݒ�
	void SetAutoMode(const bool);			//�I�[�g������C�ӂ̂��̂���ݒ�
	Vec2 GetMove() const;					//�ړ��l��Ԃ�
	void Set(const Vec2&, const Vec2&);		//�J�n�ʒu�ƏI���ʒu��o�^����
	bool isAutoPlay() const;				//�I�[�g�ړ����s���Ă��邩��Ԃ�
	Direction nowDirection() const;			//���݂̌�����Ԃ�
};