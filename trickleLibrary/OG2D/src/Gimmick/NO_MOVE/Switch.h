//______________________________//
//|�����M�~�b�N  �X�C�b�`      |//
//|�����F2018/03/29 ����	   |//
//|�����F2018/03/31 �����@     |//
//|�����F2018/04/01 ����       |//
//|����: 2018/04/02 ����       |//
//|����: 2018/04/03 ����       |//
//|�����F2018/04/07 ����       |//
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
	
	bool isON();
	void ON_OFF();
	//void SetTarget(GameObject* t);
private:
	Texture image;
	std::string path;
	bool is_on;
	//------------------
	//�Œ艻����Ă��鏈��
	//------------------
public:
	std::string taskName;
	virtual ~Switch();
	typedef std::shared_ptr<Switch> SP;
	static Switch::SP Create(Vec2& pos,bool = true);
	Switch();
	//-------------
	//�ύX���Ȃ�����
	//-------------
	bool Initialize(Vec2& pos);	//����������
	void UpDate();				//�X�V����
	void Render2D();			//�`�揈��
	bool Finalize();			//�������
};