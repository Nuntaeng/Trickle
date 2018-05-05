#pragma once
#include "OGSystem\OGsystem.h"
#include <vector>


class UI {
	Texture tex;
	Vec2 pos;		//���W
	int counter;	//���Ԃ͂���B
	int index;		//�`�悷��src
	//Box2D src;		//Draw()�̑�����
	int num;		//�摜������
	int life;		//����
	bool active;	//����
	std::vector<Box2D> srcTable;

public:
	UI();
	~UI();

	
	void Initialize(Vec2 p, std::string path, int life, int num = 0);	//���W�A�t�@�C���p�X�A�����A�摜������
	void Update();
	void Move(Vec2 p);		//���W�𓮂����Ƃ��Ɏg��
	void Render();
	void Finalize();

};