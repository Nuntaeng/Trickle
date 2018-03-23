#pragma once
//______________________________//
//|�v���C��                     |//
//|�����F2018/03/23���c	       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Player :public Object
{
public:
	Texture playerimg;
	std::string fileName = "player.png";
	bool hitcheck;

	void Initialize();
	void UpDate();
	void Render();
	void Finalize();

	float speed;
};


