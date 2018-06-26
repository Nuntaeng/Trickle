#include "Kanetuki.h"
using namespace std;

//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
#include "Water\water.h"
#include "Task\Task_Game.h"


Kanetuki::Kanetuki()
	:
	maxChangeTimeLiquid(7),
	maxChangeTimeSolid(120)
{
	cout << "���M��@����" << endl;
	//�T�E���h�t�@�C����	
	startsoundname = "fire1.wav";
	soundname = "fire2.wav";
	stopsoundname = "fire3.wav";
}
Kanetuki::~Kanetuki()
{
	this->Finalize();
	cout << "���M��@���" << endl;
}


bool Kanetuki::Initialize(Vec2& pos, Vec2 range, Angle ang, bool active) {
	this->taskName = "Kanetuki";	//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//Taskwaterect���̏������s��

	changeStateCnt = 0;
	CreateObject(Cube, pos, range, 0);
	this->active = active;

	//�T�E���h�Ɋւ�����
	startflag = false;
	nowplay = false;
	//�T�E���h�̐���
	sound.create(soundname, true);
	//�T�E���h�̐����@�@����
	soundstart.create(startsoundname, false);
	//�T�E���h�̐����@�@����
	soundstop.create(stopsoundname, false);

	this->SetTexture(rm->GetTextureData((std::string)"fireIce"));
	this->animCnt = 0;
	draw.clear();
	//this->hotNum = 0;
	this->angle = ang;
	//�{�̂̌����ɂ���ĉ��̌����ƕ`�搔��ύX
	switch (this->angle) {
	case UP:
		this->hotNum = this->Scale.x / 64;
		this->draw.resize(this->hotNum);
		for (int i = 0; i < this->hotNum; ++i) {
			draw[i] = Box2D(position.x + (64 * i), position.y, 64.f, Scale.y);
			draw[i].OffsetSize();
		}
		this->texRotaAng = 0.0f;
		break;
	case RIGHT:
		this->hotNum = this->Scale.y / 64;
		this->draw.resize(this->hotNum);
		for (int i = 0; i < this->hotNum; ++i) {
			draw[i] = Box2D(position.x, position.y + (64 * i), Scale.x, 64.f);
			draw[i].OffsetSize();
		}
		this->texRotaAng = 90.0f;
		break;
	case LEFT:
		//�����_�ő��݂��Ȃ��̂ŗ�
		break;
	case BOTTOM:
		this->hotNum = this->Scale.x / 64;
		this->draw.resize(this->hotNum);
		for (int i = 0; i < this->hotNum; ++i) {
			draw[i] = Box2D(position.x + (64 * i), position.y, 64.f, Scale.y);
			draw[i].OffsetSize();
		}
		this->texRotaAng = 180.0f;
		break;
	}

	cout << "���M��@������" << endl;

	return true;
}
void Kanetuki::UpDate() {
	if (active) {
		toSteam();
	}
	//�T�E���h�֌W
	//���̉����Đ�
	this->nowplay = sound.isplay();
	volControl.Play(&this->position, 700.0f, 1.0f, sound);
	if (active)
	{
		//if(�����ɉ��M��̕��������炤) {
		//this->hotNum = Scale.x / 64;
		//draw.resize(hotNum);
		//}
		if (startflag)
		{
			sound.play();
		}
	}
	//���΂̉����Đ�
	if (active)
	{
		if (startflag)
		{
			soundstart.play();
			startflag = false;
		}
	}
	if (!active)
	{
		if (nowplay)
		{
			sound.stop();
		}
		if(startflag == false)
		{
			soundstop.play();
		}
		startflag = true;
	}

}
void Kanetuki::Render2D() {
	
	if (active) {
		++animCnt;
		Box2D src = { 256 * (animCnt / 5 % 3), 0, 256, 256 };
		src.OffsetSize();

		this->hotImg->Rotate(this->texRotaAng);
		for (auto draw_ : draw) {
			this->hotImg->Draw(draw_, src);
		}
	}
	//�f�o�b�O�p
	if (active) this->LineDraw();
}
bool Kanetuki::Finalize() {
	//�摜���������œǂݍ��ނȂ�Texture��Finalize()���ĂԂ���
	return true;
}
void Kanetuki::toSteam() {
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		//���Ƃ̓����蔻��
		if ((*id)->hit(*this))
		{	//�@�́@�ˁ@�t��
			if ((*id)->GetState() == Water::State::SOLID && (*id)->GetSituation() == Water::Situation::Normal)
			{
				changeStateCnt++;
				cout << changeStateCnt++ << endl;
				//���̎��Ԃ��o������E�E�E
				if (changeStateCnt >= maxChangeTimeSolid)
				{
					//�t�̂ɂ���
					//auto water = Water::Create((*id)->position);
					//Texture watertex;
					//auto game = OGge->GetTask<Game>("game");
					//water->SetTexture(&game->getWaterTex());
					//(*id)->SetState(Water::State::LIQUID);
					//(*id)->SetSituation(Water::Situation::Newfrom);
					(*id)->SolidMelt();
					//					(*id)->Kill();
					changeStateCnt = 0;
				}
			}
			//�t�́@�ˁ@�����C
			if ((*id)->GetState() == Water::State::LIQUID)
			{
				changeStateCnt++;
				cout << changeStateCnt << endl;
				//���̎��Ԃ��o������E�E�E
				if (changeStateCnt >= maxChangeTimeLiquid)
				{
					//�����C�ɂ���
					if ((*id)->GetWaterVolume() < 0.5f)
					{
						(*id)->Kill();
					}
					else
					{
						(*id)->SetState(Water::State::GAS);
					}
					changeStateCnt = 0;
				}
			}
		}
	}
}
void Kanetuki::changeActive() {
	this->active = !this->active;
}
void Kanetuki::SetTexture(Texture* tex)
{
	this->hotImg = tex;
}
Kanetuki::SP Kanetuki::Create(Vec2& pos, Vec2 range, Angle ang, bool active, bool flag_) {
	Kanetuki::SP to = Kanetuki::SP(new Kanetuki());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos, range, ang, active))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}



//bool Kanetuki::Initialize(Vec2& pos)
//{
//	//-----------------------------
//	//�������ɏ������鏉�����������L�q
//	//-----------------------------
//	this->taskName = "Kanetuki";	//�������Ɏg�����߂̖���o�^����
//	__super::Init(taskName);		//Taskwaterect���̏������s��
//
//	Fire_MovetimeReset();
//	CreateObject(Cube, pos, Vec2(64, 64), 0);
//	this->GetFlag();
//
//	//�T�E���h�Ɋւ�����
//	startflag = false;
//	nowplay = false;
//	//�T�E���h�̐���
//	sound.create(soundname, true);
//	//�T�E���h�̐����@�@����
//	soundstart.create(startsoundname, false);
//
//	cout << "���M��@������" << endl;
//	return true;
//}
//bool Kanetuki::Initialize(Vec2& pos, std::shared_ptr<Switch>& target)
//{
//	//-----------------------------
//	//�������ɏ������鏉�����������L�q
//	//-----------------------------
//	this->taskName = "Kanetuki";	//�������Ɏg�����߂̖���o�^����
//	__super::Init(taskName);		//Taskwaterect���̏������s��
//
//	Fire_MovetimeReset();
//	CreateObject(Cube, pos, Vec2(64, 64), 0);
//	this->SetSwitchFlag(target);
//
//	cout << "���M��@������" << endl;
//	//�T�E���h�Ɋւ�����
//	startflag = false;
//	nowplay = false;
//	//�T�E���h�̐���
//	sound.create(soundname, true);
//	//�T�E���h�̐����@�@����
//	soundstart.create(startsoundname, false);
//
//	return true;
//}
//void Kanetuki::Fire_MovetimeReset()
//{
//	Fire_movetime = 0;
//}
//void Kanetuki::GetFlag()
//{
//	if (target != nullptr)
//	{
//		switchflag = target->isON();
//	}
//	else
//	{
//		switchflag = true;
//	}
//}
//void Kanetuki::UpDate()
//{
//	//--------------------
//	//�X�V���ɍs���������L�q
//	//--------------------
//	this->GetFlag();
//	if (this->GetSwitchFlag())
//	{
//		this->toSteam();
//	}
//
//	//�T�E���h�֌W
//	//���̉����Đ�
//	this->nowplay = sound.isplay();
//	if (switchflag)
//	{
//		if (startflag)
//		{
//			sound.play();
//		}
//	}
//	//���΂̉����Đ�
//	if (switchflag)
//	{
//		if (startflag)
//		{
//			soundstart.play();
//			startflag = false;
//		}
//	}
//	if (switchflag == false)
//	{
//		if (nowplay)
//		{
//			sound.stop();
//		}
//		startflag = true;
//	}
//}
//
//void Kanetuki::Render2D()
//{
//	//--------------------
//	//�`�掞�ɍs���������L�q
//	//--------------------
//	this->LineDraw();
//}
//bool Kanetuki::Finalize()
//{
//	//-----------------------------------------
//	//���̃I�u�W�F�N�g�����ł���Ƃ��ɍs���������L�q
//	//-----------------------------------------
//
//	//���̃^�X�N����邩���A�v���P�[�V�������I���\�肩�ǂ���
//	if (this->GetNextTask() && !OGge->GetDeleteEngine())
//	{
//
//	}
//	return true;
//}
//void Kanetuki::SetSwitchFlag(std::shared_ptr<Switch>& obj)
//{
//	if (obj != nullptr)
//	{
//		target = obj;
//	}
//}
//bool Kanetuki::GetSwitchFlag()
//{
//	return switchflag;
//}
//void Kanetuki::toSteam()
//{
//	auto waters = OGge->GetTasks<Water>("water");
//	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
//	{
//		//���Ƃ̓����蔻��
//		if ((*id)->hit(*this))
//		{	//�@�́@�ˁ@�t��
//			if ((*id)->GetState() == Water::State::SOLID)
//			{
//				Fire_movetime++;
//				//���̎��Ԃ��o������E�E�E
//				if (Fire_movetime >= Fire_time_SOLID)
//				{
//					//�t�̂ɂ���
//					(*id)->SetState(Water::State::LIQUID);
//					Fire_MovetimeReset();
//				}
//			}
//			//�t�́@�ˁ@�����C
//			if ((*id)->GetState() == Water::State::LIQUID)
//			{
//				Fire_movetime++;
//				//���̎��Ԃ��o������E�E�E
//				if (Fire_movetime >= Fire_time_LIQUID)
//				{
//					//�����C�ɂ���
//					(*id)->SetState(Water::State::GAS);
//					Fire_MovetimeReset();
//				}
//			}
//		}
//		//else {
//		//	Fire_movetime = 0;
//		//}
//	}
//}
////----------------------------
////�������牺��class���̂ݕύX����
////�ق��͕ύX���Ȃ�����
////----------------------------
//Kanetuki::Kanetuki()
//{
//	cout << "���M��@����" << endl;
//	//�T�E���h�t�@�C����	
//	startsoundname = "fire1.wav";
//	soundname = "fire2.wav";
//}
//
//Kanetuki::~Kanetuki()
//{
//	this->Finalize();
//	cout << "���M��@���" << endl;
//}
//
//Kanetuki::SP Kanetuki::Create(Vec2& pos, bool flag_)
//{
//	Kanetuki::SP to = Kanetuki::SP(new Kanetuki());
//	if (to)
//	{
//		to->me = to;
//		if (flag_)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}
//
//Kanetuki::SP Kanetuki::Create(Vec2& pos, std::shared_ptr<Switch>& target, bool flag_)
//{
//	Kanetuki::SP to = Kanetuki::SP(new Kanetuki());
//	if (to)
//	{
//		to->me = to;
//		if (flag_)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos, target))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}