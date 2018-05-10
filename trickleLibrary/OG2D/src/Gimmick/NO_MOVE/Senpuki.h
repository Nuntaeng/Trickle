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

#include "Gimmick\NO_MOVE\Switch.h"
#include "Water\water.h"

class Switch;

class Fan : public GameObject, public TaskObject
{
	//-------------------------------------------
	//�e���Ő��삷��Ƃ��Ɏg�p������̂͂����ɋL�q����
	//-------------------------------------------
public:
	std::vector<Switch*> switches;		//���g�̉ғ��ɂ�������Ă���X�C�b�`�ꗗ

	enum Dir
	{
		LEFT,
		RIGHT,
	};
	Fan(Vec2);
	bool Initialize(Vec2 pos, float r, Dir d, bool activ);
	void AddSwitch(Switch* swit);
	void ChangeState();
	void SetTexture(Texture*);
	void SetWindRange(Vec2&);

	//Water��Vector���̃A�h���X�l���󂯎��
	void SetWaterPool(Water*);
	bool DeleteWaterPool(Water*);
	void Motion(Water*);
private:
	//------------------
	//�Œ艻����Ă��鏈��
	//------------------
public:
	std::string taskName;
	virtual ~Fan();
	typedef std::shared_ptr<Fan> SP;
	static Fan::SP Create(bool, Vec2 pos, float r, Fan::Dir d, bool activ);
	Fan();
	//-------------
	//�ύX���Ȃ�����
	//-------------
	bool Initialize();		//����������
	void UpDate();			//�X�V����
	void Render2D();		//�`�揈��
	bool Finalize();		//�������
private:
	Dir dir;
	Texture* image;
	float range;
	float movePos;
	bool active;
	int strength;
	std::vector<Water*>water;
	GameObject WindHitBase;
};

