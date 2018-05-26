#pragma once
//______________________________//
//|�^�X�N�T���v��               |//
//|�����F2018/03/20���q��       |//
//|�����F2018/04/17����N�@    |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "UI\UI.h"

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
private:
	//---------------------------------------------------------------------
	//�����o�[�֐�
	//---------------------------------------------------------------------
	//�J��������
	void Camera_move();
	
	//�M�~�b�N�̒ǉ�
	Vec2 _waterpos;

	Texture waterTex;
	Texture playerTex;
	Texture fanTex;

	//UI----------------------------------------
	//std::vector<UI::SP> ui;
	//std::vector<UI::UIinfo> uiInfo;
	std::shared_ptr<UImanager> UImng_;
};