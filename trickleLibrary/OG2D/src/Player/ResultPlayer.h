#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
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
	};

	Texture image;
	std::string filePath;
	Vec2 moveVec;
	Animetion animetion;
	void Move();
	void Think();
	void Motion();
	const Box2D Src = { Vec2(0, 575), Vec2(586, 575) };


	//���U���g��ʂւ̃t���O�֐�
	bool walkstop;
	void ResetWalkStop();
	
	

public:
	typedef std::shared_ptr<ResultPlayer> SP;
	ResultPlayer();
	virtual ~ResultPlayer();
	std::string taskName;

	bool Initialize(Vec2& pos,Vec2& speed);
	void UpDate();
	void Render2D();
	bool Finalize();
	static ResultPlayer::SP Create(Vec2 pos,Vec2 speed = Vec2(1,0) ,bool = true);

	//���U���g��ʂɊ֘A����t���O�֐�
	bool GetResetWalkStop();
};