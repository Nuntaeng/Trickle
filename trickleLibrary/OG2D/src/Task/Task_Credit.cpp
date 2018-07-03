#include "Task_Credit.h"
#include "Chara/Chara.h"
#include "Task/Task_Title.h"
#include "Map/Map.h"

Credit::Credit()
{
	//�^�X�N�̌������ɓo�^������������g�p����
	this->taskName = "Credit";	//�^�X�N������
	__super::Init(this->taskName);	//�^�X�N�����I�u�W�F�N�g�ɂ����f
	//�`�揇�̓o�^
	__super::SetDrawOrder(1.0f);
	//����������
}

Credit::~Credit()
{
	//�������
	this->Finalize();
}

bool Credit::Initialize()
{
	//�摜����
	this->backTex.Create((std::string)"back.png");
	this->frameTex.Create((std::string)"selectframe2.png");
	this->nameTex.Create((std::string)"name.png");
	//�}�b�v����
	Map::Create((std::string) "credit.csv");
	//�`�����^�X�N����
	auto npc = Chara::Create((std::string)"player.png", Vec2(-120, 64 * 8));
	npc->SetDirection(Chara::Direction::RIGHT);
	npc->Set(Vec2(-120, 64 * 8), Vec2(1280, 64 * 8), 50.f);

	this->nowMode = Non;
	return true;
}

void Credit::UpDate()
{
	OGge->camera->SetSize(Vec2(1280, 720));
	auto npc = OGge->GetTask<Chara>("Chara");
	switch (nowMode) {
	case Non:
	{
		npc->AutoMove();
		if (!npc->isAutoPlay()) {
			this->nowMode = Mode1;
		}
		break;
	}
	case Mode1:
	{
		break;
	}
	}
}

void Credit::Render2D()
{
	//�w�i
	{
//		backTex.Draw(Box2D(0, 0, 1280, 720), Box2D(0, 0, 1280, 720));
	}
}

void Credit::Finalize()
{
	//�������
	this->backTex.Finalize();
	this->frameTex.Finalize();
	this->nameTex.Finalize();
	auto map = OGge->GetTask<Map>("map");
	if (map) { map->Kill(); }
}

Credit::SP Credit::Create(bool flag)
{
	auto to = Credit::SP(new Credit());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize())
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}