#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include <vector>


class UI :public GameObject,public TaskObject {
	Texture tex;
	Vec2 pos;		//���W
	int counter;	//���Ԃ͂���B
	int index;		//�`�悷��src
	//Box2D src;		//Draw()�̑�����
	int num;		//�摜������
	int life;		//����
	bool active;	//����
	//bool visible;	//���s��
	std::vector<Box2D> srcTable;
	int appeared;	//�����F-1�A��x�v���C���ƐڐG������0�A�o����1

public:
	UI();
	~UI();
	typedef std::shared_ptr<UI> SP;
	static SP Create(Vec2&, Box2D&, std::string&, int, int,bool = true);
	
	bool Initialize(Vec2& p, Box2D& coll, std::string& path, int life, int num = 0);	//���W�A�t�@�C���p�X�A�����A�摜������
	void UpDate();
	void Move(Vec2 p);		//���W�𓮂����Ƃ��Ɏg��
	void Render2D();
	bool Finalize();

	//void Appear();
	//void Vanish();
	//bool CheckHitPlayer();
};