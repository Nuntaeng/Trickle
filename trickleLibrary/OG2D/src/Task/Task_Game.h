#pragma once
//______________________________//
//|�^�X�N�T���v��               |//
//|�����F2018/03/20���q��       |//
//|____________________________|//
#include "Win\WinMain.h"
#include "CollisionManager\CollisionManager.h"
#include "OGSystem\OGsystem.h"
#include "Player\Player.h"
#include "Back\Back.h"
#include "Map\Map.h"
#include "Water\water.h"
#include "Bucket\bucket.h"


class Game
{
public:
	void Initialize();
	TaskFlag UpDate();
	void Render2D();
	void Finalize();
	//��������//
	//�ǉ��ϐ�//
	//��������//
	Player player;
	Bucket bucket;
	Back back;
	Map map;
	std::vector<Water*> water;
	CollisionManager cm;
	int timecnt;
};