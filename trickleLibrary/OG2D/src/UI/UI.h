#pragma once
#include "OGSystem\OGsystem.h"


class UI {
	Texture tex;
	Vec2 pos;		//���W
	int counter;	//���Ԃ͂���B
	Box2D src;		//Draw()�̑�����
	int num;		//�摜������
	int life;		//����
	bool active;	//����

public:
	UI();
	~UI();


	void Initialize(Vec2 p, std::string path, int num, int life);	//���W�A�t�@�C���p�X�A�摜������
	void Update();
	void Move(Vec2 p);		//���W�𓮂����Ƃ��Ɏg��
	void Render();
	void Finalize();
};