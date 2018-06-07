//|�����M�~�b�N  ��@        |//
//|�����F2018/03/29 ����       |//
//|�����F2018/03/30 �����@     |//
//|�����F2018/03/31 ����       |//
//|�����F2018/04/01 ����       |//
//|����: 2018/04/02 ����       |//
//|����: 2018/04/03 ����       |//
//|�����F2018/04/06 ����       |//
//|�����F2018/04/07 ����       |//
//|�����F2018/05/03 ����       |//
//|____________________________|//

#pragma once
//�K�v�ǂݍ��݃t�@�C��
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Switch.h"
#include "VolumeControl\volumeControl.h"

class Switch;

class Fan : public GameObject, public TaskObject {
public:
	enum Dir {
		LEFT,
		RIGHT,
	};
	void SetWindRange(Vec2&);
	//�T�E���h����̏��
	bool startflag;
	Sound sound;
	VolumeControl volControl;

	typedef std::shared_ptr<Fan> SP;
	//���W�A���͈̔�(�}�X��)�A�����A�X�C�b�`���I�t(�������)�ŉғ����Ă���Ȃ�true
	static Fan::SP Create(Vec2 pos, float r, Fan::Dir d, /*std::shared_ptr<Switch>& swich,*/ bool active, bool flag = true);

	void changeActive();				//���g�̉ғ���Ԃ𔽓]������
	~Fan();

private:
	Fan();
	bool Initialize(Vec2 pos, float r, Dir d, /*std::shared_ptr<Switch>& swich,*/ bool active);
	void UpDate();			//�X�V����
	void Render2D();		//�`�揈��
	bool Finalize();		//�������
	void SendWind();		//���Ő����C�𓮂���

	//std::shared_ptr<Switch> swich_;		//�I���I�t�ɑΉ�����X�C�b�`
	bool active_;						//�������ғ����Ă���Ȃ�true(���F�X�C�b�`��bool�Ɠ����ł͂Ȃ�)

	Dir dir;		//����
	Texture image;
	const Box2D Src = { 0,0,768 / 3,256 };
	float range;
	float movePos;
	int strength;
	std::string soundname;      //�T�E���h�̃t�@�C�����i�[
	std::string taskName;		//�����p

	struct Animetion
	{
		int animetionframe;
		int speed;
		void AnimetionMove(bool flag);				//�A�j���[�V�����t���[���𓮂���
		void AnimetionReset();						//�A�j���[�V�����̐��l�����Z�b�g����
		void AnimetionSrc(Box2D& src, bool flag);	//�A�j���[�V�����t���[����`��ɉe��������
	};
	Animetion animetion;
	GameObject WindHitBase;

};




//class Fan : public GameObject, public TaskObject
//{
//	//-------------------------------------------
//	//�e���Ő��삷��Ƃ��Ɏg�p������̂͂����ɋL�q����
//	//-------------------------------------------
//public:
//
//	enum Dir
//	{
//		LEFT,
//		RIGHT,
//	};
//	void SetWindRange(Vec2&);
//	//�T�E���h����̏��
//	bool startflag;
//	Sound sound;
//private:
//	//------------------
//	//�Œ艻����Ă��鏈��
//	//------------------
//	void SetSwitchTarget(std::shared_ptr<Switch>&);
//	void SetFanTarget(std::shared_ptr<Fan>&);
//	void SetFlag();
//	void Motion();
//	void DataInput();
//public:
//	std::shared_ptr<Switch> target;
//	std::shared_ptr<Fan> fantarget;
//	std::string taskName;
//	bool switchflag;
//	bool fanflag;
//	typedef std::shared_ptr<Fan> SP;
//	//�펞������@�̐���
//	static Fan::SP Create(Vec2 pos, float r, Fan::Dir d, bool = true);
//	//�X�C�b�`����̐�@�̐���
//	static Fan::SP Create(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Switch>& target, bool = true);
//	///��@A ���� B �����Ȃ� �̂悤�ȃt���O�̓���ւ��ɂ���ăM�~�b�N���ғ�������ꍇ
//	static Fan::SP Create(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Fan>& target, bool = true);
//	///��@A ���� B �����Ȃ� �̂悤�ȃt���O�̓���ւ��ɂ���ăM�~�b�N���ғ�������ꍇ(�X�C�b�`����)
//	static Fan::SP Create(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Fan>& fanTarget, std::shared_ptr<Switch>& switchTarget, bool = true);
//	//-------------
//	//�ύX���Ȃ�����
//	//-------------
//	Fan();
//	virtual ~Fan();
//	//������������������������������������������������������������������������������������
//
//	//��@�𐶐�����ꍇ�E�E�E
//
//	//Vec2 pos = ���W�@float r = ��@�̕��𑗂�͈́@Dir d = ��@�̌���
//	//SP�@Fan�@= this �ғ����Ȃ� �^�[�Q�b�g�X�C�b�`  �ғ����@�ɂȂ�܂�
//	//SP  Switch = �X�C�b�`�̃t���O�ɂ���ĉғ����Ă��邩���Ă��Ȃ��������܂�܂�
//
//	//������������������������������������������������������������������������������������
//
//
//	bool Initialize(Vec2 pos, float r, Dir d);
//	bool Initialize(Vec2 pos, float r, Dir d, std::shared_ptr<Fan> target);
//	bool Initialize(Vec2 pos, float r, Dir d, std::shared_ptr<Switch>&target);
//	bool Initialize(Vec2 pos, float r, Dir d, std::shared_ptr<Fan> fantarget, std::shared_ptr<Switch>&switchtarget);
//	void UpDate();			//�X�V����
//	void Render2D();		//�`�揈��
//	bool Finalize();		//�������
//
//	bool GetSwitchFlag();
//private:
//	Dir dir;
//	Texture image;
//	const Box2D Src = { 0,0,768 / 3,256 };
//	float range;
//	float movePos;
//	int strength;
//	std::string soundname;      //�T�E���h�̃t�@�C�����i�[
//	struct Animetion
//	{
//		int animetionframe;
//		int speed;
//		void AnimetionMove(bool flag);				//�A�j���[�V�����t���[���𓮂���
//		void AnimetionReset();						//�A�j���[�V�����̐��l�����Z�b�g����
//		void AnimetionSrc(Box2D& src, bool flag);	//�A�j���[�V�����t���[����`��ɉe��������
//	};
//	Animetion animetion;
//	GameObject WindHitBase;
//};
//
