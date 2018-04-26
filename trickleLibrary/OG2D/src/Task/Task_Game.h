#pragma once
//______________________________//
//|�^�X�N�T���v��               |//
//|�����F2018/03/20���q��       |//
//|�����F2018/04/17����N�@    |//
//|____________________________|//
#include "Win\WinMain.h"
#include "CollisionManager\CollisionManager.h"
#include "OGSystem\OGsystem.h"
#include "Player\Player.h"
#include "Back\Back.h"
#include "Map\Map.h"
#include "Water\water.h"
#include "Bucket\bucket.h"
#include "Goal\Goal.h"
#include "Block\block.h"
#include "Gimmick\NO_MOVE\Kanetuki.h"
#include "Gimmick\NO_MOVE\Seihyouki.h"
#include "Gimmick\NO_MOVE\Senpuki.h"
#include "Gimmick\NO_MOVE\Switch.h"

#include "GameProcessManagement\GameProcessManagement.h"


class Game
{
public:
	void Initialize();
	TaskFlag Update();
	void Render2D();
	void Finalize();
	//��������//
	//�ǉ��ϐ�//
	//��������//
	Player player;
	//std::vector<Bucket*> bucket;
	Block block;
	Bucket bucket;
	Back back;
	Map map;
	std::vector<Water*> water;
	CollisionManager cm;
	int timecnt;
	Goal goal;

private:
	//---------------------------------------------------------------------
	//�����o�[�֐�
	//---------------------------------------------------------------------
	//�J��������
	void Camera_move();
	//�W���X�e�B����
	/*Senpuki senpuki;
	Seihyouki seihyouki;
	Kanetuki kanetuki;
	Switch switch_;*/

	//���c����
	Switch swich[2];
	Fan fan[2];

	GameProcessManagement gameprocess;
	Texture waterTex;
	Texture playerTex;
};