#pragma once

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Win\WinMain.h"

class Youki :public Object
{
public:
	Texture ContainerImg;
	std::string fileName = "Collision.png";

	float water;        //�����Ă鐅�̗�0.0f~1.0f
	float speed;        //�ړ����x
	bool hold;          //�v���C���������Ă��邩�ǂ����̔���
	bool hitCheck;

	void CreateNew(Box2D pos);      //�I�u�W�F�N�g�𐶐�

	void Initialize();
	void UpDate();
	void Render();
	void Finalize();
};

class Player :public Object
{
public:
	Texture PlImg;
	std::string fileName = "Collision.png";
	bool hitCheck;

	void Initialize();
	void UpDate();
	void Finalize();
	void Render();
};

class Container_ :public Object
{
public:
	void Initialize();
	TaskFlag UpDate();
	void Render();
	void Finalize();

	Player pl_;
	Youki youki_;
};

