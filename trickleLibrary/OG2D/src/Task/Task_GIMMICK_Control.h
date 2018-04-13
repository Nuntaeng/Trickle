#pragma once
#include "Object\Object.h"
#include "Win\WinMain.h"
//�o�^����M�~�b�N�������ɋL�q����//
//#include "Player\EnemyHitTest.h"
//______________________________//
//|�����M�~�b�N  ����N���X    |//
//|�����F2018/03/27 ����	   |//
//|�@                          |//
//|  �N���X�̐錾�Ŏg�p�\____|//

#include "Gimmick\NO_MOVE\Kanetuki.h"
#include "Gimmick\NO_MOVE\Switch.h"
#include "Gimmick\NO_MOVE\Senpuki.h"

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
	//EnemyHitTest* _e_pointa;
	Kanetuki*     _ka_pointa;
	Senpuki*      _sen_pointa;
	Switch*		 _swi_pointa;
};