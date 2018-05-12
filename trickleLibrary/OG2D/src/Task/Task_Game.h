#pragma once
//______________________________//
//|�^�X�N�T���v��               |//
//|�����F2018/03/20���q��       |//
//|�����F2018/04/17����N�@    |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "Player\Player.h"
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

class Game : public TaskObject
{
public:
	typedef std::shared_ptr<Game> SP;
	static SP Create(bool = true);
	Game();
	virtual ~Game();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();
	//��������//
	//�ǉ��ϐ�//
	//��������//
	Player player;
	//std::vector<Bucket*> bucket;
	std::vector<Block*> block;
	std::vector<Bucket*> bucket;
	Map map;
	std::vector<Water*> water;
	int timecnt;
	std::vector<Goal*> goal;
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
	Kanetuki kanetuki;
	Vec2 _waterpos;

	Texture waterTex;
	Texture playerTex;
	Texture fanTex;

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