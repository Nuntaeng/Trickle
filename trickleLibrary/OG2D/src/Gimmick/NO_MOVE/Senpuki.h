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

class Switch;

class Fan : public GameObject, public TaskObject
{
	//-------------------------------------------
	//�e���Ő��삷��Ƃ��Ɏg�p������̂͂����ɋL�q����
	//-------------------------------------------
public:

	enum Dir
	{
		LEFT,
		RIGHT,
	};
	void SetWindRange(Vec2&);
private:
	//------------------
	//�Œ艻����Ă��鏈��
	//------------------
	void SetSwitchFlag(std::shared_ptr<Switch>&);
	bool GetSwitchFlag();
	void GetFlag();
	void Motion();
public:
	std::shared_ptr<Switch> target;
	std::string taskName;
	bool switchflag;
	virtual ~Fan();
	typedef std::shared_ptr<Fan> SP;
	static Fan::SP Create(Vec2 pos, float r, Fan::Dir d, bool = true);
	static Fan::SP Create( Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Switch>& target,bool = true);
	//-------------
	//�ύX���Ȃ�����
	//-------------
	Fan();
	bool Initialize(Vec2 pos, float r, Dir d);
	bool Initialize(Vec2 pos, float r, Dir d,std::shared_ptr<Switch>&target);
	void UpDate();			//�X�V����
	void Render2D();		//�`�揈��
	bool Finalize();		//�������
private:
	Dir dir;
	Texture image;
	const Box2D Src = { 0,0,768 / 3,256 };
	float range;
	float movePos;
	int strength;
	struct Animetion
	{
		int animetionframe;
		int speed;
		void AnimetionMove(bool flag);				//�A�j���[�V�����t���[���𓮂���
		void AnimetionReset();						//�A�j���[�V�����̐��l�����Z�b�g����
		void AnimetionSrc(Box2D& src,bool flag);	//�A�j���[�V�����t���[����`��ɉe��������
	};
	Animetion animetion;
	GameObject WindHitBase;
};

