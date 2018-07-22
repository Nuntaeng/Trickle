#pragma once
//______________________________//
//|�^�X�N�T���v��               |//
//|�����F2018/03/20���q��       |//
//|�����F2018/04/17����N�@    |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "UI\UI.h"
#include "VolumeControl/volumeControl.h"

class UI;

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
	int timecnt;

	//�T�E���h�֘A
	Sound sound;
	VolumeControl volControl;
	bool canvolControl;
private:
	//---------------------------------------------------------------------
	//�����o�[�֐�
	//---------------------------------------------------------------------
	//�J��������
	void Camera_move();
	
	//�M�~�b�N�̒ǉ�
	Vec2 _waterpos;

	Texture waterTex;
	Texture waterRed;
	Texture waterBlue;
	Texture waterPurple;
	Texture playerTex;
	Texture fanTex;
	Texture fireice;
	Texture PaintTex;
	Texture EffectTest;
	Texture Effectsond;
	Texture texSteam;
	Texture goalTex;
	Texture goalDirectionTex;
	Texture arrowflower;
	Texture doorTex;
	Texture WswitchTex;
	std::string gamesoundname;
	std::string tutorialsoundname;

	//UI----------------------------------------
	std::shared_ptr<UImanager> UImng_;
};