#include "Task_Pause.h"
#include "Task_Title.h"
#include "Task\StageSelect.h"
#include "Task_Game.h"
Pause::Pause()
{
	__super::SetDrawOrder(1.f);
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
	texCursor.Create((std::string)"Collision.png");
	texRestart.Create((std::string)"restart.png");
	texReturn.Create((std::string)"return.png");
	texStageSelect.Create((std::string)"StageSelect.png");
	texTransparentBack.Create((std::string)"TransparentBack.png");

	this->nextTaskCheck = 0;
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
			auto game = OGge->GetTask<Game>("game");
			if (game)
			{
				game->Finalize();
				game->Initialize();
			}
		}
	break;
	case Stage:
		{
			auto game = OGge->GetTasks<Game>("game");
			for (auto& g : (*game)) {
				g->Kill();
			}
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
				Box2D draw(transparentbackPos.x, transparentbackPos.y, 1280.0f*2.0f, 720.0f*2.0f);
				draw.OffsetSize();
				Box2D src(0, 0, 1280, 720);
				src.OffsetSize();
				texTransparentBack.Draw(draw, src);
			}
			//�J�[�\���̕\��
			{
				//�Q�[���X�^�[�g
				Box2D draw(cursorPos.x, cursorPos.y, 64.0f, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 0, 128, 128);
				src.OffsetSize();
				texCursor.Draw(draw, src);
			}
			//restart
			{
				Box2D draw(RestartPos.x, RestartPos.y, 256.0f, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 0, 256, 64);
				src.OffsetSize();
				texRestart.Draw(draw, src);
			}
			//Return
			{
				Box2D draw(ReturnPos.x, ReturnPos.y, 256.0f, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 0, 256, 64);
				src.OffsetSize();
				texReturn.Draw(draw, src);
			}
			//stageselect
			{
				Box2D draw(stageselectPos.x, stageselectPos.y, 256.0f, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 0, 256, 64);
				src.OffsetSize();
				texStageSelect.Draw(draw, src);
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
	float keisan = NowCameraSize.x / 2;
	float NewPos = keisan + NowCameraPos.x;
	transparentbackPos = Vec2(0, 0);

	//�I�����ʒu
	RestartPos = Vec2(NewPos + 600.0f, NowCameraPos.y + 50.0f);
	ReturnPos = Vec2(NewPos + 600.0f, NowCameraPos.y + 250.0f);
	stageselectPos = Vec2(NewPos + 600.0f, NowCameraPos.y + 150.0f);

	//���̈ړ�
	if (OGge->in->key.down(In::UP)) {
		selectPos = (selectPos <= 0) ? selectPos : --selectPos;
	}
	if (OGge->in->key.down(In::DOWN)) {
		selectPos = (selectPos >= 2) ? selectPos : ++selectPos;
	}
	cursorPos = Vec2(NewPos + 500.0f, NowCameraPos.y + 50.0f + (100.f * selectPos));
	select = Select::Return;
	//�I����
	if (cursorPos.y == RestartPos.y)
	{
		select = Restart;
	}
	if (cursorPos.y == stageselectPos.y)
	{
		select = Stage;
	}
	if (cursorPos.y == ReturnPos.y)
	{
		select = Return;
	}
	//�I�����̌��菈��
	if (OGge->in->down(In::B2)){
		OGge->SetPause(false);
		if (select != Return) {
			this->Kill();
		}
	}

	//�J�����ړ�����
		if (OGge->in->key.on(In::A)){
			if (NowCameraPos.x > 0) {
				OGge->camera->MovePos(Vec2(-5.0f, 0.0f));
			}
		}
		if (OGge->in->key.on(In::D)){
			if (NowCameraPos.x + NowCameraSize.x<map->mapSize.x * map->DrawSize.x) {
				OGge->camera->MovePos(Vec2(+5.0f, 0.0f));
			}
		}
		if (OGge->in->key.on(In::W)) {
			if (NowCameraPos.y > 0) {
				OGge->camera->MovePos(Vec2(0.0f, -5.0f));
			}
		}
		if (OGge->in->key.on(In::S)) {
			if (NowCameraPos.y + NowCameraSize.y < map->mapSize.y * map->DrawSize.y) {
				OGge->camera->MovePos(Vec2(0.0f, 5.0f));
			}
		}
}