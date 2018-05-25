#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include <vector>


class UImanager;

class UI :public GameObject,public TaskObject {
	Texture tex;
	Vec2 pos;		//���W
	int counter;	//���Ԃ͂���B
	int index;		//�`�悷��src
	//Box2D src;		//Draw()�̑�����
	int num;		//�摜������
	int life;		//����
	//bool visible;	//���s��
	std::vector<Box2D> srcTable;
	int appeared;	//�����F-1�A��x�v���C���ƐڐG������0�A�o����1

	int id_;

public:	
	bool active;	//����

	struct UIinfo {
		Vec2 pos;
		Box2D hit;
		std::string path;
		int life;
		int picNum;
	};

	UI();
	~UI();
	typedef std::shared_ptr<UI> SP;
	static SP Create(Vec2&, Box2D&, std::string&, int life, int num, int id, UImanager* manager, bool = true);
	static SP Create(UIinfo& info, int id, UImanager* manager, bool = true);

	bool Initialize(Vec2& p, Box2D& coll, std::string& path, int life, int id, UImanager* manager, int num = 0);	//���W�A�t�@�C���p�X�A�����A�摜������
	void UpDate();
	void Move(Vec2 p);		//���W�𓮂����Ƃ��Ɏg��
	void Render2D();
	bool Finalize();
	bool CreateNext(UI::UIinfo& info);


	//void Appear();
	//void Vanish();
	//bool CheckHitPlayer();
};

class UImanager :public GameObject, public TaskObject {
public:
	UImanager();
	~UImanager();

	bool Initialize(unsigned short& mapNum);
	void UpDate();
	bool AddUI(UI* next);
	bool Finalize();

private:
	int maxNum;		//�\������UI�̐��AInitialize�Ŏw��AUI���₷���͂�����ς��Ȃ��Ⴂ���Ȃ��N�\�d�l
	std::vector<std::shared_ptr<UI>> UIlist_;
	std::vector<UI::UIinfo> uiInfo;

	int activeID;
};