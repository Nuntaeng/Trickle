#pragma once
//______________________________//
//|�w�i�^�X�N�@�@               |//
//|�����F2018/03/20���q��       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Back : public Object {
public:
	Texture backimg;
	std::string fileName = "back.png";

	void Initialize();
	void Update();
	void Render();
	void Finalize();
};