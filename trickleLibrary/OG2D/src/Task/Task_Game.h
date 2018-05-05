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
#include "UI\UI.h"

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
	
	//�M�~�b�N�̒ǉ�
	Switch swich[2];
	Fan fan[2];

	GameProcessManagement gameprocess;
	Seihyouki seihyouki[2];

	Texture waterTex;
	Texture playerTex;

	//UI----------------------------------------
	//tutorial_1
	UI walkui;
	UI jumpui;
	UI getbucketui;
	UI getwaterui;
	UI spillwaterui;
	//tutorial_2	
	//tutorial_3
	UI switchui;
	UI evaporationui;
	//tutorial_4
	//stage1
	//stage2
};