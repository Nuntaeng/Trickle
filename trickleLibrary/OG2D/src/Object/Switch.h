//______________________________//
//|�����M�~�b�N  �X�C�b�`      |//
//|�����F2018/03/26 ����	   |//
//|�@                          |//
//|____________________________|//
#pragma once
#include "Object.h"
//#include "Player\Player.h"
#include "Player\EnemyHitTest.h"

class EnemyHitTest;
//class Player;

class Switch : public Object
{
public:
	Switch(EnemyHitTest* e_pointa);
	~Switch();
	void Initlaize();
	void UpDate();
	void Finalize();
	void Render();
private:
	void CheakHit(Object* objhit);
	Texture image;
	std::string _filePath;
	//Player* player_pointa;
	//EnemyHitTest* enemy_pointa;

	//����̓r�b�g���Z�ōs��

	bool flag;//�����蔻��
	bool switchflag;//�X�C�b�`��ON��OFF��������
};