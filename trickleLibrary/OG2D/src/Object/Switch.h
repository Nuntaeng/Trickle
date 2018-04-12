//______________________________//
//|�����M�~�b�N  �X�C�b�`      |//
//|�����F2018/03/27 ����	   |//
//|�@                          |//
//|____________________________|//
#pragma once
#include "Object.h"
#include "Object\Senpuki.h"
//#include "Player\Player.h"
//#include "Player\EnemyHitTest.h"

//class EnemyHitTest;
//class Player;

//class Switch : public Object
//{
//public:
//	Switch(/*EnemyHitTest* e_pointa*/);
//	~Switch();
//	void Initlaize();
//	void UpDate();
//	void Finalize();
//	void Render();
//
//	void CheakHit(Object* objhit);
//private:
//	Texture image;
//	std::string _filePath;
//	//Player* player_pointa;
//	//EnemyHitTest* enemy_pointa;
//
//	//����̓r�b�g���Z�ōs��
//
//	bool flag;//�����蔻��
//	bool switchflag;//�X�C�b�`��ON��OFF��������
//};




//���ӁI�I�I�I
//�v���C������ȏ�̃X�C�b�`�ɓ����ɐڐG����ƃG���[�f���܂�
//�K���X�C�b�`�𕡐��u���Ƃ��͂P�}�X�ȏ㗣���Ĕz�u
class Switch :public Object {
public:	
	void Initialize(Vec2 pos);
	void Update();
	void Finalize();
	void Render();
	bool isON();
	void ON_OFF();
	void SetTarget(Object* t);
private:
	std::vector<Object*> targets;
	Texture image;
	std::string path;
	bool is_on;

};