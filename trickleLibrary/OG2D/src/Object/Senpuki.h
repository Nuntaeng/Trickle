//______________________________//
//|�����M�~�b�N  ��@        |//
//|�����F2018/03/27 ����	   |//
//|�@                          |//
//|____________________________|//
#pragma once
#include "Object\Object.h"
#include "Win\WinMain.h"
#include "Player\EnemyHitTest.h"
#include "Water\water.h"

//#include "Player\Player.h"
//
////class Player;
//class EnemyHitTest;
//
//class Senpuki : public Object
//{
//public:
//	void Initialize();
//	void UpDate();
//	void Finalize();
//	void Render();
//	Senpuki(/*EnemyHitTest* e_pointa*/);
//	//Senpuki(Player* p_pointa);
//	~Senpuki();
//private:
//	//Player* player_pointa;
//
//	//EnemyHitTest* enemy_pointa;
//	bool flag;							//�����蔻��i�[�ϐ�
//	Texture senimg;						//�摜�C���[�W
//	Texture collbox;					//�摜�C���[�W
//	std::string _filePath;				//�t�@�C���p�X
//	std::string _hitbox;				//�t�@�C���p�X
//	CollisionBox range;				    //����͈�
//public:
//	void CheckHit(Object* objhit , int value);
//};


class Fan :public Object {
	std::vector<Switch*> switches;		//���g�̉ғ��ɂ�������Ă���X�C�b�`�ꗗ
public:
	enum Dir {
		LEFT,
		RIGHT,
	};

	void Initialize(Vec2 pos, float r, Dir d, bool activ);
	void AddSwitch(Switch* swit);
	void ChangeState();
	void Finalize();
	void Render();
private:
	Dir dir;
	Texture image;
	float range;
	float strength;
	bool active;


};