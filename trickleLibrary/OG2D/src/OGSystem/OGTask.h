#pragma once
//______________________________//
//|�^�X�N�V�X�e��               |//
//|�����F2018/03/20���q��       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "Win\WinMain.h"
//������������������//
//�ǉ��^�X�N       //
//������������������//
#include "Task\Task_Game.h"
#include "Task\Task_Title.h"
#include "Task\Task_Option.h"
#include "Task\Task_Result.h"
#include "Task\StageSelect.h"

class _OGTK
{
public:
	//������������������//
	//�^�X�Nclass�̐錾//
	//������������������//
	//�^�X�Nclass�̒ǉ��͂�����
	//cpp�ɂ����l�ɋL�q
	Game game;
	Title title;
	Option option;
	Result result;
	StageSelect select;

	////////////////////////////
	//�������牺�͕ύX���Ȃ�����//
	///////////////////////////
	//�^�X�N�ϐ�
	TaskFlag nowTask, nextTask;
	//�����E�B���h�E
	//Window _window;
	//�^�X�N�V�X�e���֐�
	void _myGameInitialize();
	void _myGameUpdate();
	void _myGameRender2D();
	void _myGameRender3D();
	void _myGameFinalize();
};