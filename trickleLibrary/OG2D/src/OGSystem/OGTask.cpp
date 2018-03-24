#include "OGSystem\OGTask.h"
void _OGTK::_myGameInitialize()
{
	//生成するWindow情報
	//_window.createWindow(960, 540, "trickle", false);
	_window.createWindow(1920, 1080, "trickle", true);
	//タスクの初期化
	nowTask = NON;
	nextTask = Task_Title;
}

void _OGTK::_myGameUpDate()
{
	if (nowTask != nextTask)
	{
		switch (nowTask)
		{
		case Task_Sample:
			s.Finalize();
			break;
		case Task_Sample2:
			s2.Finalize();
			break;
		case Task_Title:
			title.Finalize();
			break;
		case Task_Game:
			game.Finalize();
			break;
		}
		nowTask = nextTask;
		switch (nowTask)
		{
		case Task_Sample:
			s.Initialize();
			break;
		case Task_Sample2:
			s2.Initialize();
			break;
		case Task_Title:
			title.Initialize();
			break;
		case Task_Game:
			game.Initialize();
			break;
		}
	}
	switch (nowTask)
	{
	case Task_Sample:
		nextTask = s.UpDate();
		break;
	case Task_Sample2:
		nextTask = s2.UpDate();
		break;
	case Task_Title:
		nextTask = title.UpDate();
		break;
	case Task_Game:
		nextTask = game.UpDate();
		break;
	}
}

void _OGTK::_myGameRender2D()
{
	switch (nowTask)
	{
	case Task_Sample:
		s.Render2D();
		break;
	case Task_Sample2:
		s2.Render2D();
		break;
	case Task_Title:
		title.Render2D();
		break;
	case Task_Game:
		game.Render2D();
		break;
	}
}

void _OGTK::_myGameRender3D()
{

}

void _OGTK::_myGameFinalize()
{
	switch (nowTask)
	{
	case Task_Sample:
		s.Finalize();
		break;
	case Task_Sample2:
		s2.Finalize();
		break;
	case Task_Title:
		title.Finalize();
		break;
	case Task_Game:
		game.Finalize();
		break;
	}
}