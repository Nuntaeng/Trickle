#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include <vector>


class UI :public Object {
	Texture tex;
	Vec2 pos;		//���W
	int counter;	//���Ԃ͂���B
	int index;		//�`�悷��src
	//Box2D src;		//Draw()�̑�����
	int num;		//�摜������
	int life;		//����
	bool active;	//����
	bool visible;	//���s��
	std::vector<Box2D> srcTable;
	Object* player;

public:
	UI();
	~UI();

	
	void Initialize(Vec2 p, Box2D coll, std::string path, int life, int num = 0);	//���W�A�t�@�C���p�X�A�����A�摜������
	void Update();
	void Move(Vec2 p);		//���W�𓮂����Ƃ��Ɏg��
	void Render();
	void Finalize();

	void Appear();
	void Vanish();
	bool CheckHitPlayer();
	void SetPlayerPtr(Object* pl);
};