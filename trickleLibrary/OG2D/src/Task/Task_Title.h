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
class ObjectSample :public Object{
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
};
class Title
{
public:
	void Initialize();
	TaskFlag UpDate();
	void Render2D();
	void Finalize();
	//��������//
	//�ǉ��ϐ�//
	//��������//
	CollisionManager cm;
	ObjectSample objsmp;
	ObjectSample2 objsmp2;
	Map map;
	Sound sound;
};