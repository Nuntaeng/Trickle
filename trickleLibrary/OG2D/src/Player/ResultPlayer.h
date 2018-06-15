<<<<<<< HEAD
//#pragma once
//#include "OGSystem\OGsystem.h"
//#include "Object\Object.h"
//class ResultPlayer : public GameObject , public TaskObject 
//{
//public:
//	enum State
//	{
//		Normal,	//�������Ȃ�
//		Walk,	//�������[�V����
//		Smail,	//��ԃ��[�V����
//		Stop,	//�X�g�b�v��
//	};
//private:
//
//	//�A�j���[�V�����֘A
//	struct Animetion
//	{
//		int animetionCnt;				//�A�j���[�V�����J�E���^
//
//		Box2D ReturnSrc(Box2D, State);	//�A�j���[�V������Src��Ԃ�
//		void Reset();					//�A�j���[�V�����̃��Z�b�g
//		void ResetAnimetionCnt();		//�A�j���[�V�����J�E���g�����Z�b�g
//		void MotionChenge(State);		//�A�j���[�V������ύX����
//		void AnimetionMove();			//�A�j���[�V�����J�E���g���J�E���g���܂�
//		State motion;					//���[�V����
//
//		//���[�V�����Ɋւ���ϐ�
//		const int toSmailCnt = 200;				//��ԃ��[�V�����ɂ���܂ł̎��Ԃ��i�[����
//
//		//��ԃ��[�V�������I���������Ԃ�
//		bool  SmailMotionIsPlay();
//
//		//Src�̊�у��[�V���������Z�b�g
//		void  ResetSrc(Box2D&);
//	};
//	Animetion animetion;
//	
//	//�ړ��֘A
//	Vec2 moveVec;
//	void Move();
//	
//	//Player�̏�Ԋ֘A
//	void Think();
//	void Motion();
//	
//
//	//�摜�֘A
//	Texture image;
//	std::string filePath;
//	const Box2D Src = { Vec2(0, 575), Vec2(586, 575) };
//
//	//���U���g��ʂւ̃t���O�֐�
//	bool walkstop;
//	bool keyflag;
//	void ResetWalkStop();
//	
//	//�^�X�N�֘A
//	std::string taskName;
//	void UpDate();
//	void Render2D();
//	bool Finalize();
//
//public:
//	typedef std::shared_ptr<ResultPlayer> SP;
//	ResultPlayer();
//	virtual ~ResultPlayer();
//
//	bool Initialize(Vec2& pos,Vec2& speed);
//	static ResultPlayer::SP Create(Vec2 pos,Vec2 speed = Vec2(1,0) ,bool = true);
//
//	//���U���g��ʂɊ֘A����t���O�֐�
//	bool GetResetWalkStop();
//};
=======
#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Player.h"
class ResultPlayer : public GameObject , public TaskObject
{
public:
	enum State
	{
		Normal,	//�������Ȃ�
		Walk,	//�������[�V����
		Smail,	//��ԃ��[�V����
		Stop,	//�X�g�b�v��
	};
private:

	//�A�j���[�V�����֘A
	struct Animetion
	{
		int animetionCnt;				//�A�j���[�V�����J�E���^

		Box2D ReturnSrc(Box2D, State);	//�A�j���[�V������Src��Ԃ�
		void Reset();					//�A�j���[�V�����̃��Z�b�g
		void ResetAnimetionCnt();		//�A�j���[�V�����J�E���g�����Z�b�g
		void MotionChenge(State);		//�A�j���[�V������ύX����
		void AnimetionMove();			//�A�j���[�V�����J�E���g���J�E���g���܂�
		State motion;					//���[�V����

		//���[�V�����Ɋւ���ϐ�
		const int toSmailCnt = 200;				//��ԃ��[�V�����ɂ���܂ł̎��Ԃ��i�[����

		//��ԃ��[�V�������I���������Ԃ�
		bool  SmailMotionIsPlay();

		//Src�̊�у��[�V���������Z�b�g
		void  ResetSrc(Box2D&);
	};
	Animetion animetion;
	
	//�ړ��֘A
	Vec2 moveVec;
	void Move();
	void Jump();
	
	//Player�̏�Ԋ֘A
	void Think();
	void Motion();
	

	//�摜�֘A
	Texture image;
	Texture smail;
	std::string filePath;
	const Box2D Src[2] =
	{
		Box2D(Vec2(0, 575), Vec2(586, 575)),
		Box2D(Vec2(0,0),Vec2(1923 / 3 , 1068 / 2))
	};

	//���U���g��ʂւ̃t���O�֐�
	bool walkstop;
	bool keyflag;
	void ResetWalkStop();
	
	//�^�X�N�֘A
	std::string taskName;
	void UpDate();
	void Render2D();
	bool Finalize();

public:
	typedef std::shared_ptr<ResultPlayer> SP;
	ResultPlayer();
	virtual ~ResultPlayer();

	bool Initialize(Vec2& pos,Vec2& speed);
	static ResultPlayer::SP Create(Vec2 pos,Vec2 speed = Vec2(1,0) ,bool = true);

	//���U���g��ʂɊ֘A����t���O�֐�
	bool GetResetWalkStop();
};
>>>>>>> develop
