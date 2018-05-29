//______________________________//
//|�����M�~�b�N  �X�C�b�`      |//
//|�����F2018/03/29 ����	   |//
//|�����F2018/03/31 �����@     |//
//|�����F2018/04/01 ����       |//
//|����: 2018/04/02 ����       |//
//|����: 2018/04/03 ����       |//
//|�����F2018/04/07 ����       |//
//|�����F2018/05/24 ����       |//
//|____________________________|//
#pragma once
//�K�v�ǂݍ��݃t�@�C��
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
class Switch : public GameObject, public TaskObject
{
	//-------------------------------------------
	//�e���Ő��삷��Ƃ��Ɏg�p������̂͂����ɋL�q����
	//-------------------------------------------
public:
	bool GetisON();
private:
	Texture image;
	const Box2D Src = { 0,0,256,256 };
	std::shared_ptr<Switch>targetswitch;

	std::string soundname;      //�T�E���h�̃t�@�C�����i�[

	bool is_on;
	//------------------
	//�Œ艻����Ă��鏈��
	//------------------
private:
	void UpDate();				//�X�V����
	void Render2D();			//�`�揈��
	bool Finalize();			//�������
public:
	std::string taskName;
	virtual ~Switch();
	typedef std::shared_ptr<Switch> SP;
	//�ʏ펞
	//����X�C�b�`�ƃt���O��؂�ւ���X�C�b�`�𐶐�����ꍇ
	static Switch::SP Create(Vec2& pos, bool = true);
	static Switch::SP Create(Vec2& pos, Switch::SP target,bool = true);
	Switch();
	//-------------
	//�ύX���Ȃ�����
	//-------------
	bool Initialize(Vec2& pos, Switch::SP target);
	bool Initialize(Vec2& pos);

	Sound sound;
	void ON_OFF();
private:	
	void TargetSwitchChenge();			//�^�[�Q�b�g�̃X�C�b�`�ƃt���O�����ւ���
	void SetTarget(Switch::SP target);
};