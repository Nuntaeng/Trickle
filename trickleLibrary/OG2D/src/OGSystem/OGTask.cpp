#include "OGSystem\OGTask.h"
#include "Task\Task_Title.h"
#include "Task\Task_Game.h"
#include "Task\Task_TitleMovement.h"
#include "Task\StageSelect.h"
#include "Task\Task_Result.h"
#include "Task\Task_Credit.h"
#include "GameProcessManagement\GameProcessManagement.h"

void OGTK::_myGameInitialize()
{
	//��������Window���
	OGge->SetWindow(960, 540, "WindowName", false);	
//	OGge->SetWindow(1920, 1080, "Trickel", true);
	OGge->SetWindowPos(Vec2(0, 0));
	//�}�E�X�J�[�\���s��
	OGge->SetCursorOn(false);
}

void OGTK::StartTaskObject()
{
	//�g�p�t�H���g�̓ǂݍ���
	Texture* fontTex;
	fontTex = new Texture();
	fontTex->Create("fontui.png");
	rm->SetTextureData((std::string)"fontui", fontTex);

	//�^�X�N�̏�����
	//auto TopTask = Title::Create();
	*MapNum = 5;
	auto TopTask = Credit::Create();
	//GameManager::ResetData();
}

OGTK::~OGTK()
{
	if (rm->GetTextureData((std::string)"fontui"))
	{
		delete rm->GetTextureData((std::string)"fontui");
		rm->DeleteTexture((std::string)"fontui");
	}
}