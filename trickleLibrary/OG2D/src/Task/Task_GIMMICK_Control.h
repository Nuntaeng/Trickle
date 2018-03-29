#pragma once
#include "Object\Object.h"
#include "Win\WinMain.h"
//�o�^����M�~�b�N�������ɋL�q����//
//#include "Player\EnemyHitTest.h"
//______________________________//
//|�����M�~�b�N  ����N���X    |//
//|�����F2018/03/29 ����	   |//
//|�@                          |//
//|  �N���X�̐錾�Ŏg�p�\____|//

#include "Object\Switch.h"
#include "Object\Kanetuki.h"
#include "Object\Senpuki.h"
#include "Object\Ladder.h"
#include <array>

//class Player;
//class EnemyHitTest;
class Kanetuki;
class Senpuki;
class Switch;
class Ladder;

class GIMMICK_Control : public Object
{
public:
	GIMMICK_Control();
	~GIMMICK_Control();
	void Initialize();
	TaskFlag UpDate();
	void Finalize();
	void Render2D();

	std::array<Object*, 4> GetGimmicks() const;

public:
	//Player* _p_pointa;
	//EnemyHitTest* _e_pointa;
	Kanetuki*     _ka_pointa;
	Senpuki*      _sen_pointa;
	Switch*		 _swi_pointa;
	Ladder*      _lad_pointa;
};