#pragma once
#include "Object\Object.h"
#include "Win\WinMain.h"
//�o�^����M�~�b�N�������ɋL�q����//

//#include "Player\Player.h"
//#include "Player\EnemyHitTest.h"
#include "Object\Kanetuki.h"
#include "Object\Senpuki.h"
//______________________________//
//|�����M�~�b�N  ����N���X    |//
//|�����F2018/03/26 ����	   |//
//|�@                          |//
//|  �N���X�̐錾�Ŏg�p�\____|//
#include "Object\Switch.h"

//class Player;
//class EnemyHitTest;
class Kanetuki;
class Senpuki;
class Switch;

class GIMMICK_Control
{
public:
	GIMMICK_Control();
	~GIMMICK_Control();
	void Initialize();
	TaskFlag UpDate();
	void Finalize();
	void Render2D();
public:
	//Player* _p_pointa;
	EnemyHitTest* _e_pointa;
	Kanetuki*     _ka_pointa;
	Senpuki*      _sen_pointa;
	Switch*		  _swi_pointa;
};

