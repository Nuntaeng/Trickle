#pragma once

#include "OGSystem\OGSystem.h"

class Load : public TaskObject
{
	Texture image;	//�摜
	Box2D draw;		//����錾�����肱���ɏ����Ă�������������y���Ȃ�̂ł͂̌��؂����Ă��܂��B
	Box2D src;		//
	Texture tex;
public:
private:
	void UpDate();
	Color* color;
public:
	Load();
	virtual ~Load();
	typedef std::shared_ptr<Load> SP;
	static SP Create(bool = true);
	void Draw();		//�����`����s��
	void Render2D();
};