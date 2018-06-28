#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include <vector>
#include "Bucket\bucket.h"

class UImanager;

class UI :public GameObject,public TaskObject {
	Texture tex;
	Vec2 pos;		//���W
	int counter;	//���Ԃ͂���B
	int index;		//�`�悷��src
	int num;		//�摜������
	int life;		//����
	Box2D draw;
	std::vector<Box2D> srcTable;
	Vec2 maxWH;		//�ő�`��͈�
	Vec2 nowWH;		//���݂̕`��͈�
	Vec2 endPos;	//�ő�\�����̍���̍��W
	Easing easeW;
	Easing easeH;
	int id_;

public:	
	bool active;	//����
	int appeared;	//�����F-1�A��x�v���C���ƐڐG������0�A�o����1
	std::function<bool()> appear;
	std::function<bool()> vanish;

	struct UIinfo {
		Vec2 pos;
		Box2D hit;
		std::string path;
		int life;
		int picNum;
		std::function<bool()> appear;
		std::function<bool()> vanish;
	};

	UI();
	~UI();
	typedef std::shared_ptr<UI> SP;
	static SP Create(Vec2&, Box2D&, std::string&, int life, int num, int id, bool = true);
	static SP Create(UIinfo& info, int id, bool = true);

	bool Initialize(Vec2& p, Box2D& coll, std::string& path, int life, int id, std::function<bool()> appear, std::function<bool()> vanish, int num = 0);	//���W�A�t�@�C���p�X�A�����A�摜������
	void UpDate();
	void Move(Vec2 p);		//���W�𓮂����Ƃ��Ɏg��
	void Render2D();
	bool Finalize();
};

class UImanager :public GameObject, public TaskObject {
public:
	UImanager();
	~UImanager();

	bool Initialize(unsigned short& mapNum);
	void UpDate();

private:
	int maxNum;		//�\������UI�̐��AInitialize�Ŏw��AUI���₷���͂�����ς��Ȃ��Ⴂ���Ȃ��N�\�d�l
	std::vector<std::shared_ptr<UI>> UIlist_;
	std::vector<UI::UIinfo> uiInfo;

	int activeID;
};


//UI�̏o���A���ŏ����Ɏg���֐����`���Ă��������̃N���X
class UIfunc {
public:
	UIfunc() {};
	bool getBucket();
	bool getWater();
	bool Hit(GameObject& me);
	bool NoHit(GameObject& me);
	bool playerPos();
	bool spoilWater();
};
extern std::unique_ptr<UIfunc> uifunc;