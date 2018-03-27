#pragma once

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Win\WinMain.h"

class GimmickC :public Object
{
public:
	Texture ContainerImg;
	std::string fileName = "Collision.png";
	float water;        //�����Ă鐅�̗�
	float speed;        //�ړ����x
	bool hold;          //player���e��������Ă��邩
	bool hitRight;
	bool hitLeft;
	bool hitBottom;

	void Initialize();
	TaskFlag UpDate();
	void Render();
	void Finalize();
};

