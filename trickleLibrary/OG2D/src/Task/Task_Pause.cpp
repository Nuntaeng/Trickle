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
	texTitle.Create((std::string)"titleTx.png");
	texRuselt.Create((std::string)"Ruselt.png");
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
	texTitle.Finalize();
	texRuselt.Finalize();
	texTransparentBack.Finalize();
	texStageSelect.Finalize();

	OGge->SetPause(false);

	switch (select) {
	case ToTitle:
		{
			auto game = OGge->GetTask<Game>("game");
			game->Finalize();
			game->Initialize();
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
	case Ruselt:
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
			//Title
			{
				Box2D draw(titlePos.x, titlePos.y, 256.0f, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 0, 256, 64);
				src.OffsetSize();
				texTitle.Draw(draw, src);
			}
			//ruselt
			{
				Box2D draw(ruseltPos.x, ruseltPos.y, 256.0f, 64.0f);
				draw.OffsetSize();
				Box2D src(0, 0, 256, 64);
				src.OffsetSize();
				texRuselt.Draw(draw, src);
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

	titlePos = Vec2(NewPos + 600.0f, NowCameraPos.y + 50.0f);
	ruseltPos = Vec2(NewPos + 600.0f, NowCameraPos.y + 250.0f);
	stageselectPos = Vec2(NewPos + 600.0f, NowCameraPos.y + 150.0f);

	//���̈ړ�
	if (OGge->in->key.down(In::UP)) {
		selectPos = (selectPos <= 0) ? selectPos : --selectPos;
	}
	if (OGge->in->key.down(In::DOWN)) {
		selectPos = (selectPos >= 2) ? selectPos : ++selectPos;
	}
	cursorPos = Vec2(NewPos + 500.0f, NowCameraPos.y + 50.0f + (100.f * selectPos));
	select = Select::Ruselt;
	//�I����
	if (cursorPos.y == titlePos.y)
	{
		select = ToTitle;
	}
	if (cursorPos.y == stageselectPos.y)
	{
		select = Stage;
	}
	if (cursorPos.y == ruseltPos.y)
	{
		select = Ruselt;
	}
	//�I�����̌��菈��
	if (OGge->in->down(In::B2))
	{
		OGge->SetPause(false);
		if (select != Ruselt) {
			this->Kill();
		}
	}

	//��ʊO����
	if (NowCameraPos.x < 0) {
		NowCameraPos.x = 0;
	}
	if (NowCameraPos.x + NowCameraSize.x > map->mapSize.x * map->DrawSize.x) {
		NowCameraPos.x = (map->mapSize.x * map->DrawSize.x) - NowCameraSize.x;
	}
	if (NowCameraPos.y < 0) {
		NowCameraPos.y = 0;
	}
	if (NowCameraPos.y + NowCameraSize.y > map->mapSize.y * map->DrawSize.y) {
		NowCameraPos.y = (map->mapSize.y * map->DrawSize.y) - NowCameraSize.y;
	}

	//�J�����ړ�����(������)
		if (OGge->in->key.on(In::A)){
			OGge->camera->MovePos(Vec2(-5.0f, 0.0f));
		}
		if (OGge->in->key.on(In::D)){
			OGge->camera->MovePos(Vec2(+5.0f, 0.0f));
		}
		if (OGge->in->key.on(In::W)) {
			OGge->camera->MovePos(Vec2(0.0f,-5.0f));
		}
		if (OGge->in->key.on(In::S)) {
			OGge->camera->MovePos(Vec2(0.0f, 5.0f));
		}


}