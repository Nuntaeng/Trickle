#include "OGSystem\OGTask.h"
#include "Task\Task_Title.h"
#include "Task\Task_Game.h"
#include "Task\Task_TitleMovement.h"
#include "Task\Task_Game.h"
void OGTK::_myGameInitialize()
{
	//��������Window���
	OGge->SetWindow(960, 540, "WindowName", false);	
	//OGge->SetWindow(1920, 1080, "Trickel", true);
	//OGge->SetWindowPos(Vec2(0, 0));
	//�}�E�X�J�[�\���s��
	OGge->SetCursorOn(false);
}

void OGTK::StartTaskObject()
{
	//�^�X�N�̏�����
	//auto TopTask = Title::Create();
	*MapNum = 1;
	OGge->camera->SetSize(Vec2(1920, 1080));
	auto ga = Game::Create();
	
}

OGTK::~OGTK()
{
	if (rm->GetTextureData((std::string)"fontui"))
	{
		delete rm->GetTextureData((std::string)"fontui");
		rm->DeleteTexture((std::string)"fontui");
	}
}