#include "Task_Credit.h"
#include "Chara/Chara.h"
#include "Task/Task_Title.h"
#include "Map/Map.h"
#include "Back/Back.h"

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
	this->frameTex.Create((std::string)"selectframe2.png");
	this->nameTex.Create((std::string)"name.png");
	//�w�i����
	auto backImage = Back::Create(std::string("back.png"), 1920, 1080);
	//�}�b�v����
	Map::Create((std::string) "credit.csv");
	//�`�����^�X�N����
	auto npc = Chara::Create((std::string)"player.png", Vec2(-120, 64 * 8));
	npc->SetDirection(Chara::Direction::RIGHT); 
	npc->Set(Vec2(-120, 64 * 8), Vec2(64 * 2, 64 * 8), 15.f);
	OGge->camera->SetSize(Vec2(1280, 720));

	this->nowMode = 0;
	this->timeCnt = 0;
	this->alpha = 0.f;
	return true;
}

void Credit::UpDate()
{
	if (nowMode != Non) {
		++this->timeCnt;
	}

	OGge->camera->SetSize(Vec2(1280, 720));
	auto npc = OGge->GetTask<Chara>("Chara");
	
	if (nowMode == NON) {
		OGge->camera->SetPos(this->camera_anim.Move(10.f));
		npc->AutoMove();
		if (!npc->isAutoPlay()) {
			nowMode = MODE1;
		}
	}

	if (nowMode == MODE1) {
		Fade();
	}

	if (nowMode == MODE2) {
		Fade();
	}
	if (nowMode == MODE3) {
		Fade();
	}

	if (nowMode == MODE4) {
		npc->Jump();
		Fade();
	}

	if (nowMode == MODE5) {
		Fade();
	}

	if (nowMode == MODE6) {
		Fade();
	}

	if (nowMode == MODE7) {
		Fade();
		npc->Set(npc->position, Vec2(1500.f, npc->position.y), 30.f);
	}

	if (nowMode == MODE8) {
		npc->AutoMove();
		if (npc->position.x >= 1450) {
			this->Kill();
		}
	}

}

void Credit::Render2D()
{
	//�t���[��
	{
		Box2D draw(200, 50, 1000, 585);
		draw.OffsetSize();
		Box2D src = Box2D(0, 0, 1000, 585);
		src.OffsetSize();
		frameTex.Draw(draw, src);
	}
	//���O
	{
		Box2D draw(500, 300, 256, 256);
		draw.OffsetSize();
		Box2D src = Box2D(256 * (nowMode - 1), 0, 256, 256);
		src.OffsetSize();
		Color color(1.f, 1.f, 1.f, alpha);
		nameTex.Draw(draw, src, color);
	}
}

void Credit::Finalize()
{
	//�������
	this->frameTex.Finalize();
	this->nameTex.Finalize();
	auto map = OGge->GetTask<Map>("map");
	auto back = OGge->GetTask<Back>("back");
	if (back)
	{
		back->Kill();
	}
	if (map) { map->Kill(); }
}

void Credit::Fade()
{
	//�t�F�[�h�C��
	if (this->timeCnt < 20) {
		this->alpha += 0.05f;
	}
	//�t�F�[�h�A�E�g
	if (this->timeCnt > 60) {
		this->alpha -= 0.05f;
	}
	//���̃��[�h�ɍs��
	if (this->timeCnt > 80) {
		this->alpha = 0;
		this->timeCnt = 0;
		++this->nowMode;
	}

}

Credit::Animation::Animation()
{

}

Vec2 Credit::Animation::Move()
{
	return Vec2(this->easing_x.sine.In(this->easing_x.Time(10), this->StartPos.x, this->EndPos.x, 10), this->easing_y.sine.In(this->easing_y.Time(10), this->StartPos.y, this->EndPos.y, 10));
}

Vec2 Credit::Animation::Move(const float time)
{
	return Vec2(this->easing_x.sine.Out(this->easing_x.Time(time), this->StartPos.x, this->EndPos.x, 10), this->easing_y.linear.In(this->easing_y.Time(time), this->StartPos.y, this->EndPos.y, time));
}

Vec2 Credit::Animation::Move(const Easing::Name name, const Easing::Mode mode, const float time)
{
	switch (name)
	{
	case Easing::Name::Back:
		break;
	case Easing::Name::Bounce:
		break;
	case Easing::Name::Circ:
		break;
	case Easing::Name::Cubic:
		break;
	case Easing::Name::Elastic:
		break;
	case Easing::Name::Expo:
		break;
	case Easing::Name::Quad:
		break;
	case Easing::Name::Quart:
		break;
	case Easing::Name::Quint:
		break;
	case Easing::Name::Sine:
		break;
	default:
		break;
	}
	return Vec2(this->easing_x.sine.In(this->easing_x.Time(time), this->StartPos.x, this->EndPos.x, 10), this->easing_y.sine.In(this->easing_y.Time(time), this->StartPos.y, this->EndPos.y, time));
}

bool Credit::Animation::isPlay() const
{
	return this->easing_x.isplay() || this->easing_y.isplay() ? true : false;
}

bool Credit::CheckTime(int t)
{
	return this->timeCnt > t ? true : false;
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
