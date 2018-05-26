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

#include "Player\Player.h"
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
	std::shared_ptr<Player>target;
	bool is_on;
	//------------------
	//�Œ艻����Ă��鏈��
	//------------------
private:
	bool CheckHit();
	void ON_OFF();
	void SetTarget(Player::SP target);
public:
	std::string taskName;
	virtual ~Switch();
	typedef std::shared_ptr<Switch> SP;
	static Switch::SP Create(Vec2& pos,Player::SP target,bool is_on,bool = true);
	Switch();
	//-------------
	//�ύX���Ȃ�����
	//-------------
	bool Initialize(Vec2& pos, Player::SP target,bool is_on);	//����������
	void UpDate();				//�X�V����
	void Render2D();			//�`�揈��
	bool Finalize();			//�������
};