//______________________________//
//|�����M�~�b�N  ��@        |//
//|�����F2018/03/29 ����	   |//
//|�@                          |//
//|____________________________|//
#pragma once
#include "Object\Object.h"
#include "Win\WinMain.h"
#include "Player\EnemyHitTest.h"

//#include "Player\Player.h"

//class Player;
class EnemyHitTest;

class Senpuki : public Object
{
public:
	void Initialize();
	void UpDate();
	void Finalize();
	void Render();
	Senpuki(/*EnemyHitTest* e_pointa*/);
	//Senpuki(Player* p_pointa);
	~Senpuki();
private:
	//Player* player_pointa;

	//EnemyHitTest* enemy_pointa;
	bool flag;							//�����蔻��i�[�ϐ�
	Texture senimg;						//�摜�C���[�W
	Texture collbox;					//�摜�C���[�W
	std::string _filePath;				//�t�@�C���p�X
	std::string _hitbox;				//�t�@�C���p�X
	CollisionBox range;				    //����͈�
public:
	void CheckHit(int);
};