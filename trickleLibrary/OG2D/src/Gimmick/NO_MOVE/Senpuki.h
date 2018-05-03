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
#include "Object\Object.h"
#include "Win\WinMain.h"
#include "Gimmick\NO_MOVE\Switch.h"
#include "Water\water.h"

class Switch;

class Fan :public Object 
{
	std::vector<Switch*> switches;		//���g�̉ғ��ɂ�������Ă���X�C�b�`�ꗗ
public:
	enum Dir 
	{
		LEFT,
		RIGHT,
	};
	explicit Fan();
	explicit Fan(Vec2);
	virtual ~Fan();
	void Initialize(Vec2 pos, float r, Dir d, bool activ);
	void AddSwitch(Switch* swit);
	void ChangeState();
	void Finalize();
	void Render();
private:
	Dir dir;
	Texture image;
	float range;
	float movePos;
	bool active;
};

