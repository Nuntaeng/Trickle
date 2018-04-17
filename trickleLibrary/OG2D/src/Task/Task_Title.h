#pragma once
//______________________________//
//|�^�C�g���^�X�N               |//
//|�����F2018/03/20���q��       |//
//|____________________________|//
#include "Win\WinMain.h"
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Map\Map.h"
#include "CollisionManager\CollisionManager.h"
/*class ObjectSample :public Object{
public:
//Object object;
Texture sampleimg;
std::string fileName = "Collision.png";
Object footHit;
Object toolHit;
bool hitcheck;
void Initialize();
void UpDate();
void Render();
void Finalize();
};
class ObjectSample2 :public Object {
public:
//Object object;
Texture sampleimg;
std::string fileName = "Collision.png";
bool hitcheck;
void Initialize();
void UpDate();
void Render();
void Finalize();
};*/
class Title
{
	Texture texCursor;
	Texture texStart;
	Texture texClose;
	Texture texPause;

	Vec2 startPos;
	Vec2 pausePos;
	Vec2 closePos;
	Vec2 cursorPos;

public:
	void Initialize();
	TaskFlag Update();
	void Render2D();
	void Finalize();

	void CursorMove();
	//��������//
	//�ǉ��ϐ�//
	//��������//
	CollisionManager cm;
	Map map;
	Sound sound;

	enum State
	{
		Start,        //�Q�[���X�^�[�g
		Pause,         //�ݒ�
		Close        //�Q�[�������
	};
	State state;
};