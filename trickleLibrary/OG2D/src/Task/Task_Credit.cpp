#include <fstream>
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
	this->frame[0].tex.Create((std::string)"credit1.png");
	this->frame[1].tex.Create((std::string)"credit2.png");
	this->frame[2].tex.Create((std::string)"credit3.png");
	this->frame[3].tex.Create((std::string)"credit4.png");
	this->frame[4].tex.Create((std::string)"credit5.png");
	this->frame[5].tex.Create((std::string)"credit6.png");
	this->frame[6].tex.Create((std::string)"credit7.png");
	this->frame[7].tex.Create((std::string)"credit8.png");
	this->nameTex.Create((std::string)"name.png");
	//�w�i����
	auto backImage = Back::Create(std::string("back.png"), 1920, 1080);
	//�}�b�v����
	Map::Create((std::string) "credit.csv");
	this->LadderTex.Create("mapchip2.png");
	//�`�����^�X�N����
	auto npc = Chara::Create((std::string)"player.png", Vec2(-120, 64 * 8));
	npc->SetDirection(Chara::Direction::RIGHT); 
	npc->Set(Vec2(-120, 64 * 8), Vec2(64 * 2, 64 * 8), 15.f);
	OGge->camera->SetSize(Vec2(1280, 720));

	this->nowMode = 0;
	this->jumpTimeCnt = 0;
	this->timeCnt = 0;
	this->WAITTIME = 200;
	if (LoadSize())
	{
		SetSize();
	}
	
	
	
	return true;
}

void Credit::UpDate()
{
	OGge->camera->SetSize(Vec2(1280, 720));
	auto npc = OGge->GetTask<Chara>("Chara");
	npc->creditFlag = true;
	if (OGge->in->key.down(In::T))
	{
		npc->AutoJump();
	}
	if (nowMode == NON) {
		npc->AutoMoveX();
		if (!npc->isAutoPlayX()) {
			this->nowMode = MODE1;
		}
	}

	if (nowMode == MODE1) {
		++timeCnt;
		if (timeCnt >= WAITTIME) {
			npc->SetX(npc->position.x, 1700, 30.f);
			this->camera_anim.Set(OGge->camera->GetPos(), Vec2(1500.f, 0.f));
			Next();
		}
	}

	if (nowMode == MODE2) {
		npc->AutoMoveX();
		OGge->camera->SetPos(this->camera_anim.Move(30.f));
		if (!npc->isAutoPlayX()) {
			++timeCnt;
			if (timeCnt >= WAITTIME) {
				npc->SetX(npc->position.x, 2800, 20.f);
				this->camera_anim.Set(OGge->camera->GetPos(), Vec2(2700.f, 750.f));
				Next();
			}
		}
	}
	if (nowMode == MODE3) {
		++jumpTimeCnt;
		CreditJump(120, 6);
		npc->AutoMoveX();
		OGge->camera->SetPos(this->camera_anim.Move(20.f));

		if (!npc->isAutoPlayX()) {
			++timeCnt;
			if (timeCnt >= WAITTIME) {
				npc->SetX(npc->position.x, 3800, 20.f);
				this->camera_anim.Set(OGge->camera->GetPos(), Vec2(3500.f, 750.f));
				Next();
			}
		}
	}

	if (nowMode == MODE4) {
		++jumpTimeCnt;
		CreditJump(50, 10);
		CreditJump(85, 10);
		CreditJump(130, 10);
		npc->AutoMoveX();
		OGge->camera->SetPos(this->camera_anim.Move(20.f));

		if (!npc->isAutoPlayX()) {
			npc->Set(npc->position, Vec2(npc->position.x, 190.f), 20.f);
			this->camera_anim.Set(OGge->camera->GetPos(), Vec2(3500.f, 0.f));
			Next();
		}
	}

	if (nowMode == MODE5) {
		npc->AutoMove();
		OGge->camera->SetPos(this->camera_anim.Move(20.f));
		if (npc->isAutoPlay()) {
			npc->SetCollisionNow(0);
		}
		else {
			++jumpTimeCnt;
			++timeCnt;
			CreditJump(0, 10);
			npc->SetCollisionNow(1);
			if (timeCnt > 10) {
				npc->SetX(npc->position.x, 4500, 20.f);
				this->camera_anim.Set(OGge->camera->GetPos(), Vec2(4000.f, 0.f));
				Next();
			}
		}

	}

	if (nowMode == MODE6) {
		npc->AutoMoveX();
		OGge->camera->SetPos(this->camera_anim.Move(20.f));
		if (!npc->isAutoPlayX()) {
			++timeCnt;
			if (timeCnt >= WAITTIME) {
				npc->SetX(npc->position.x, 5800, 20.f);
				this->camera_anim.Set(OGge->camera->GetPos(), Vec2(5700.f, 550.f));
				Next();
			}
		}
	}

	if (nowMode == MODE7) {
		++jumpTimeCnt;
		CreditJump(70, 10);
		npc->AutoMoveX();
		OGge->camera->SetPos(this->camera_anim.Move(20.f));
		if (!npc->isAutoPlayX()) {
			npc->SetX(npc->position.x, 7500, 40.f);
			this->camera_anim.Set(OGge->camera->GetPos(), Vec2(7400.f, 550.f));
			Next();
		}
	}

	if (nowMode == MODE8) {
		npc->AutoMoveX();
		OGge->camera->SetPos(this->camera_anim.Move(40.f));
		if (!npc->isAutoPlayX()) {
			npc->Happy(7);
		}

		if (npc->happyCnt >= 7) {
			++timeCnt;
			if (timeCnt > WAITTIME) {
				npc->SetX(npc->position.x, 9000, 20.f);
				Next();
			}
		}
	}

	if (nowMode == MODE9) {
		npc->AutoMoveX();
		if (!npc->isAutoPlayX()) {
			this->Kill();
		}
	}

}

void Credit::Render2D()
{
	//�t���[��
	for (int i = 0; i < FRAME_NUM + 1; ++i)
	{
		frame[i].tex.Draw(frame[i].draw, frame[i].src);
	}
	//��q
	for (int i = 2; i < 10; ++i)
	{
		Box2D draw(3800.f, i*128.f, 128.f, 128.f);
		draw.OffsetSize();
		Box2D src(256*3, 256, 256, 256);
		src.OffsetSize();
		this->LadderTex.Draw(draw, src);
	}
	{
		Box2D draw(3800.f, 1*128.f, 128.f, 128.f);
		draw.OffsetSize();
		Box2D src(256*2, 256, 256, 256);
		src.OffsetSize();
		this->LadderTex.Draw(draw, src);
	}
}

void Credit::Finalize()
{
	//�������
	this->frameTex.Finalize();
	this->nameTex.Finalize();
	auto map = OGge->GetTask<Map>("map");
	auto back = OGge->GetTask<Back>("back");
	this->LadderTex.Finalize();
	if (back)
	{
		back->Kill();
	}
	if (map) { map->Kill(); }
}

void Credit::Next()
{
	//���̃��[�h�ɍs��
	this->timeCnt = 0;
	this->jumpTimeCnt = 0;
	++this->nowMode;
}

Credit::Animation::Animation()
{

}

void Credit::Animation::Set(Vec2& start_, Vec2& end_)
{
	this->StartPos = start_;
	this->EndPos = end_ - start_;
	this->easing_x.ResetTime();
	this->easing_y.ResetTime();
}

Vec2 Credit::Animation::Move()
{
	return Vec2(this->easing_x.quad.InOut(this->easing_x.Time(10), this->StartPos.x, this->EndPos.x, 10), this->easing_y.quad.InOut(this->easing_y.Time(10), this->StartPos.y, this->EndPos.y, 10));
}

Vec2 Credit::Animation::Move(const float time)
{
	return Vec2(this->easing_x.quad.InOut(this->easing_x.Time(time), this->StartPos.x, this->EndPos.x, time), this->easing_y.quad.InOut(this->easing_y.Time(time), this->StartPos.y, this->EndPos.y, time));
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


bool Credit::LoadSize()
{
	std::ifstream ifs("./data/Credit.txt");

	if (!ifs)
	{
		std::cout << "�ǂݍ��݃G���[" << std::endl;
		return false;
	}
	//�ǂݍ��񂾃f�[�^�����Ă����ϐ�
	std::string line;
	//���s���I���n�_�܂ł̕����̕������line�ɂ����
	std::getline(ifs, line);
	//������𑀍삷�邽�߂̓���class�A���ڃA�N�Z�X�ł���
	std::istringstream _is(line);
	//�ꎚ�������ݕϐ�
	std::string text;
	//_is�ɓ����Ă��镶���񂩂�','�܂ł̕�����text�ɂ����
	std::getline(_is, text, '\t');

	for (int i = 0; i < FRAME_NUM+1; ++i) {
		std::string lineText;
		std::getline(ifs, lineText);
		std::istringstream  ss_lt(lineText);
		for (int j = 0; j < 4; ++j)
		{
			std::string  text;
			std::getline(ss_lt, text, '\t');
			if (text == "\r")
			{
				continue;
			}
			(std::stringstream)text >> frame[i].imageSize[j];

		}
	}

	ifs.close();
	return true;
}
void Credit::SetSize()
{
	for (int i = 0; i < FRAME_NUM + 1; ++i) {
		frame[i].draw.x = (float)frame[i].imageSize[frame->DRAW_X];
		frame[i].draw.y = (float)frame[i].imageSize[frame->DRAW_Y];
		frame[i].draw.w = (float)frame[i].imageSize[frame->DRAW_W];
		frame[i].draw.h = (float)frame[i].imageSize[frame->DRAW_H];
		frame[i].draw.OffsetSize();

		frame[i].src.x = 0;
		frame[i].src.y = 0;
		frame[i].src.w = (float)frame[i].imageSize[frame->DRAW_W];
		frame[i].src.h = (float)frame[i].imageSize[frame->DRAW_H];
		frame[i].src.OffsetSize();
	}

}

void Credit::CreditJump(int start, int time)
{
	auto npc = OGge->GetTask<Chara>("Chara");
	//�W�����v���n�܂�t���[���ƏI���t���[�����w��
	if (jumpTimeCnt > start && jumpTimeCnt < start+time) {
		npc->AutoJump();
	}
}