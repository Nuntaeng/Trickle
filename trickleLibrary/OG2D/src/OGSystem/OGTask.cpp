#include "OGSystem\OGTask.h"
#include "Task\Task_Title.h"
void OGTK::_myGameInitialize()
{
	//生成するWindow情報
	OGge->SetWindow(960, 540, "WindowName", false);	
	//OGge->SetWindow(1920, 1080, "Trickel");
	//OGge->SetWindowPos(Vec2(0, 0));
}

void OGTK::StartTaskObject()
{
	//タスクの初期化
	auto TopTask = Title::Create();
}