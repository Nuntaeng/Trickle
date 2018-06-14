#include "Task_Pause.h"
#include "Task_Title.h"
#include "Task\StageSelect.h"
#include "Task_Game.h"
Pause::Pause()
{
	__super::SetDrawOrder(1.0f);
}
//--------------------------------------------------------------------------------------
Pause::~Pause()
{
	this->Finalize();

}
//--------------------------------------------------------------------------------------
bool Pause::Initialize()
{
	//�摜�ǂݍ���
	texCursor.Create((std::string)"gear2.png");
	texRestart.Create((std::string)"restart.png");
	texReturn.Create((std::string)"return.png");
	texStageSelect.Create((std::string)"StageSelect.png");
	texTransparentBack.Create((std::string)"TransparentBack.png");
	select = Select::Return;

	__super::Init((std::string)"pause");
	__super::SetDrawOrder(1.f);		//�摜�\������
	std::cout << "�|�[�Y��ʏ�����" << std::endl;
	return true;
}
//--------------------------------------------------------------------------------------
void Pause::UpDate()
{
}
//--------------------------------------------------------------------------------------
void Pause::Render2D()
{
	//�|�[�Y�I�����̕\��
	Pause_draw();

}
//--------------------------------------------------------------------------------------
bool Pause::Finalize()
{
	std::cout << "Pause���" << std::endl;

	//�g�p�摜�̉��
	texCursor.Finalize();
	texRestart.Finalize();
	texReturn.Finalize();
	texTransparentBack.Finalize();
	texStageSelect.Finalize();

	OGge->SetPause(false);

	switch (select) {
	case Restart:
		{
			/*auto game = OGge->GetTask<Game>("game");
			if (game){
				game->Finalize();
				game->Initialize();
			}*/
		auto game = Game::Create();
		}
	break;
	case Stage:
		{
		/*	auto game = OGge->GetTasks<Game>("game");
			for (auto& g : (*game)) {
				g->Kill();
			}*/
		}
		StageSelect::Create();
		break;
	case Return:
		break;
	}
	return true;
}
//--------------------------------------------------------------------------------------
//�|�[�Y�I�����̕\��
void Pause::Pause_draw()
{
	if (OGge->GetPause()) {
		{
			//�w�i
			{
				Box2D draw(transparentbackPos.x, transparentbackPos.y, 1920.f, 1080.f);
				draw.OffsetSize();
				Box2D src(0, 0, 1280, 720);
				src.OffsetSize();
				texTransparentBack.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, 0.5f));
			}
			//�J�[�\���̕\��
			{
				Box2D draw(cursorPos.x, cursorPos.y, 64.0f, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 0, 200, 200);
				src.OffsetSize();
				texCursor.Draw(draw, src);
			}
			//Restart
			{
				Box2D draw(RestartPos.x, RestartPos.y, 64.f*7, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 64*8, 64*7, 64);
				src.OffsetSize();
				rm->GetTextureData((std::string)"fontui")->Draw(draw, src);
			}
			//Return
			{
				Box2D draw(ReturnPos.x, ReturnPos.y, 64.f*11, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 64*9, 64*11, 64);
				src.OffsetSize();
				rm->GetTextureData((std::string)"fontui")->Draw(draw, src);
			}
			//stageselect
			{
				Box2D draw(stageselectPos.x, stageselectPos.y, 64.f*18, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 64*7, 64*19, 64);
				src.OffsetSize();
				rm->GetTextureData((std::string)"fontui")->Draw(draw, src);
			}

		}
	}
}
//--------------------------------------------------------------------------------------
Pause::SP Pause::Create(bool flag_)
{
	auto to = Pause::SP(new Pause());
	if (to)
	{
		to->me = to;
		if (flag_) {
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize()) {
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
//--------------------------------------------------------------------------------------
void Pause::PauseUpDate()
{
	//�I�����̕\���̓J�����ɂ���Ĉʒu���ύX
	auto NowCameraPos = OGge->camera->GetPos();
	auto NowCameraSize = OGge->camera->GetSize();
	auto map = OGge->GetTask<Map>("map");
	float NewPos = NowCameraSize.x + NowCameraPos.x;
	transparentbackPos = OGge->camera->GetPos();

	//�I�����ʒu
	ReturnPos = Vec2(NewPos - 64 * 12, NowCameraPos.y + NowCameraSize.y - 300.f);
	RestartPos = Vec2(NewPos - 64 * 8, NowCameraPos.y + NowCameraSize.y - 200.f);
	stageselectPos = Vec2(NewPos - 64*19 + 50,NowCameraPos.y + NowCameraSize.y - 100.f);

	//���̈ړ�
	if (OGge->in->down(Input::CU) || OGge->in->down(In::LU)) {
		selectPos = (selectPos <= 0) ? selectPos : --selectPos;
	}
	if (OGge->in->down(Input::CD) || OGge->in->down(In::LD)) {
		selectPos = (selectPos >= 2) ? selectPos : ++selectPos;
	}
	Vec2 cPosTable[3] = { Vec2(ReturnPos.x - 80, ReturnPos.y)
							,Vec2(stageselectPos.x - 80,stageselectPos.y)
							,Vec2(RestartPos.x - 80,RestartPos.y) };
	cursorPos = cPosTable[selectPos];
	select = Select::Return;

	//�I����
	if (cursorPos.y == RestartPos.y){
		select = Restart;
	}
	if (cursorPos.y == stageselectPos.y){
		select = Stage;
	}
	if (cursorPos.y == ReturnPos.y){
		select = Return;
	}

	//�I�����̌��菈��
	if (OGge->in->down(In::B2)){
		OGge->SetPause(false);
		if (select != Return) {
			OGge->GetTask<Game>("game")->Kill();
		}
	}

	//�J�����ړ�����
	if (InputLeft()) {
		if (NowCameraPos.x > 0) {
			OGge->camera->MovePos(Vec2(-5.0f, 0.0f));
		}
	}
	if (InputRight()) {
		if (NowCameraPos.x + NowCameraSize.x<map->mapSize.x * map->DrawSize.x) {
			OGge->camera->MovePos(Vec2(+5.0f, 0.0f));
		}
	}
	if (InputUp()) {
		if (NowCameraPos.y > 0) {
			OGge->camera->MovePos(Vec2(0.0f, -5.0f));
		}
	}
	if (InputDown()) {
		if (NowCameraPos.y + NowCameraSize.y < map->mapSize.y * map->DrawSize.y) {
			OGge->camera->MovePos(Vec2(0.0f, 5.0f));
		}
	}
}