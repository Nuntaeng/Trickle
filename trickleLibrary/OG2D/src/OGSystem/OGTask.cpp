#include "OGSystem\OGTask.h"
#include "Task\Task_Title.h"
void OGTK::_myGameInitialize()
{
	//��������Window���
	//OGge->SetWindow(960, 540, "WindowName", false);	
	OGge->SetWindow(1920, 1080, "Trickel");
}

void OGTK::StartTaskObject()
{
	//�^�X�N�̏�����
	auto topTask = Title::Create();
}