#include "OGSystem\OGTask.h"
#include "Task\Task_Title.h"
void OGTK::_myGameInitialize()
{
	//��������Window���
	OGge->SetWindow(960, 540, "WindowName", false);	
}

void OGTK::StartTaskObject()
{
	//�^�X�N�̏�����
	auto topTask = Title::Create();
}