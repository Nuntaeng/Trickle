#include "Senpuki.h"
using namespace std;

//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
#include "Water\water.h"


Fan::Fan() {
	this->taskName = "Senpuki";
	this->soundname = "wind1.wav";
}
Fan::~Fan() {}
bool Fan::Initialize(Vec2 pos, float r, Dir d, /*std::shared_ptr<Switch>& swich,*/float effectdis, bool active) {
	this->taskName = "Senpuki";			//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);			//TaskObject���̏������s��
	SetDrawOrder(0.5f);

										//�A�j���[�V�����̃��Z�b�g������
	animetion.AnimetionReset();

	//�摜�֘A�̕`��p�X
	std::string filePath = "fan.png";      //��@�̉摜
	image.Create(filePath);
	//���̉摜
	std::string filePathWind = "wind1.png";
	windimage.Create(filePathWind);
	std::string filePathWind2 = "wind2.png";
	windimage2.Create(filePathWind2);
	std::string filePathWind3 = "wind3.png";
	windimage3.Create(filePathWind3);
	std::string filePathWind4 = "wind4.PNG";
	windimage4.Create(filePathWind4);
	std::string filePathWind5 = "wind5.PNG";
	windimage5.Create(filePathWind5);


	//�T�E���h�̐���
	this->startflag = true;
	sound.create(soundname, true);
	//�G�t�F�N�g�֘A���
	this->effectCnt = 0;
	this->endpos = effectdis;

	range = r;
	dir = d;
	//this->swich_ = swich;
	this->active_ = active;
	//��@�̕`����W
	position = pos;

	if (dir == Fan::Dir::LEFT)
	{
		strength = -5;
		this->WindHitBase.CreateObject(Cube, Vec2(position.x - (64.f * r), position.y), Vec2(64.f * r + 64, 64.f), 0.0f);
	}
	else
	{
		strength = 5;
		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * r, 64.f), 0.0f);
	}

	return true;
}
void Fan::SetWindRange(Vec2&) {

}
void Fan::UpDate() {
	if (active_) {
		SendWind();
		//���̃G�t�F�N�g����-----------------------------------------------------------------------------------------------
		this->effectCnt++;

		if (this->effectCnt % 15 == 0)
		{
			effectnum = rand() % 5 + 1;
			//��@���E�����̎�
			if (dir == RIGHT)
			{
				auto effect = Effect::Create(Vec2(this->position.x+32,this->position.y), Vec2(0, 64), Vec2(256, 64), 1, 200);
				effect->SetWind(Vec2(64 * 8, 64), effect->position, Vec2(effect->position.x + endpos, effect->position.y), Effect::Mode::WindR);
				switch (effectnum)
				{
				case 1:
					effect->SetTexture(&windimage);
					break;
				case 2:
					effect->SetTexture(&windimage2);
					break;
				case 3:
					effect->SetTexture(&windimage3);
					break;
				case 4:
					effect->SetTexture(&windimage4);
					break;
				case 5:
					effect->SetTexture(&windimage5);
					break;
				}
			}
			//��@���������̎�
			else
			{
				auto effect = Effect::Create(Vec2(this->position.x + 32, this->position.y), Vec2(0, 64), Vec2(256, 64), 1, 200, 5);
				effect->SetWind(Vec2(64 * 4, 64), effect->position, Vec2(effect->position.x - endpos, effect->position.y), Effect::Mode::WindL);
				switch (effectnum)
				{
				case 1:
					effect->SetTexture(&windimage);
					break;
				case 2:
					effect->SetTexture(&windimage2);
					break;
				case 3:
					effect->SetTexture(&windimage3);
					break;
				case 4:
					effect->SetTexture(&windimage4);
					break;
				case 5:
					effect->SetTexture(&windimage5);
					break;
				}
			}
		}
		if (this->effectCnt == 300)
		{
			this->effectCnt = 0;
		}
		//---------------------------------------------------------------------------------------------------------------
	}

	//�A�j���[�V�����𓮂�������
	animetion.AnimetionMove(this->active_);

	//�T�E���h�̍Đ��ɂ���
	if (active_)
	{
		volControl.Play(&this->position, 1000.0f, 0.6f, sound);
		if (startflag)
		{
			sound.play();
			startflag = false;
		}
	}
	if (!active_)	//�X�C�b�`���I�t
	{
		if (sound.isplay())
		{
			sound.stop();
		}
		startflag = true;
	}

}
void Fan::Render2D() {
	//��@�{�̂̕`��
	Box2D draw(position, Vec2(64, 64));
	draw.OffsetSize();
	Box2D src = this->Src;
	this->animetion.AnimetionSrc(src, this->active_);
	src.OffsetSize();
	if (this->dir == Fan::Dir::LEFT)
	{
		float k = src.w;
		src.w = src.x;
		src.x = k;
	}

	this->image.Draw(draw, src);

	//�f�o�b�O�p
	if (active_) WindHitBase.LineDraw();
}
bool Fan::Finalize() {
	return image.Finalize();
}
void Fan::SendWind() {
	auto water = OGge->GetTasks<Water>("water");
	if (water)
	{
		for (auto id = (*water).begin(); id != (*water).end(); ++id)
		{
			if ((*id)->CubeHit(this->WindHitBase))
			{
				if ((*id)->GetState() == Water::State::GAS)
				{
					(*id)->MovePos_x((float)this->strength);
				}
			}
		}
	}
}
void Fan::Animetion::AnimetionReset()
{
	this->animetionframe = 0;
	this->speed = 0;
}
void Fan::Animetion::AnimetionMove(bool flag)
{
	this->speed = 2;
	//��@���ғ����Ă���
	if (flag)
	{
		//��@�𓮂���(�A�j���[�V����)
		if (animetionframe <= 100)
		{
			animetionframe++;
		}
		else if (animetionframe <= 170)
		{
			animetionframe += speed;
		}
		else
		{
			animetionframe += speed;
			if (animetionframe >= 300)
			{
				animetionframe = 170;
			}
		}
	}
	else
	{
		//��@��x������i�A�j���[�V�����j
		if (animetionframe >= 100)
		{
			animetionframe -= 5;
		}
		else if (animetionframe > 0)
		{
			animetionframe -= speed;
		}
		else
		{
			this->AnimetionReset();
		}
	}
}
void Fan::Animetion::AnimetionSrc(Box2D& src, bool flag)
{
	if (flag)
	{
		//�A�j���[�V�����̌v�Z������
		if (animetionframe <= 120)
		{
			src.x += (animetionframe / 15 % 3)* src.w;
		}
		else if (animetionframe <= 160)
		{
			src.x += (animetionframe / 8 % 3)* src.w;
		}
		else
		{
			src.x += (animetionframe / 5 % 3)* src.w;
		}
	}
	else
	{
		//�A�j���[�V�����̌v�Z������
		if (animetionframe >= 160)
		{
			src.x += (animetionframe / 9 % 3)* src.w;
		}
		else if (animetionframe >= 120)
		{
			src.x += (animetionframe / 12 % 3)* src.w;
		}
		else
		{
			src.x += (animetionframe / 15 % 3)* src.w;
		}
	}
}

void Fan::changeActive() {
	this->active_ = !this->active_;
}

Fan::SP Fan::Create(Vec2 pos, float r, Fan::Dir d, /*std::shared_ptr<Switch>& swich,*/ float effectdis, bool active, bool flag) {
	Fan::SP to = Fan::SP(new Fan());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos, r, d, /*swich,*/effectdis, active))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;

}

//void Fan::DataInput()
//{
//	this->taskName = "Senpuki";			//�������Ɏg�����߂̖���o�^����
//	__super::Init(taskName);			//TaskObject���̏������s��
//
//										//�A�j���[�V�����̃��Z�b�g������
//	animetion.AnimetionReset();
//
//	//�摜�֘A�̕`��p�X
//	std::string filePath = "fan.png";
//	image.Create(filePath);
//
//	//�T�E���h�̐���
//	this->startflag = false;
//	sound.create(soundname, true);
//	sound.volume(0.8f);
//}
////�펞�ғ��@��@
//bool Fan::Initialize(Vec2 pos, float r, Fan::Dir d)
//{
//	//-----------------------------
//	//�������ɏ������鏉�����������L�q
//	//-----------------------------
//	range = r;
//	dir = d;
//	//��@�̕`����W
//	position = pos;
//
//	if (dir == Fan::Dir::LEFT)
//	{
//		strength = -5;
//		this->WindHitBase.CreateObject(Cube, Vec2(position.x - (64.f * r), position.y), Vec2(64.f * r + pos.x - (pos.x - 64), 64.f), 0.0f);
//	}
//	else
//	{
//		strength = 5;
//		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * r, 64.f), 0.0f);
//	}
//	this->DataInput();
//
//
//	std::cout << "�펞�N����@�@������" << std::endl;
//	return true;
//}
////���]�t���O����@��@
//bool Fan::Initialize(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Fan> target)
//{
//	//-----------------------------
//	//�������ɏ������鏉�����������L�q
//	//-----------------------------
//	range = r;
//	dir = d;
//	//��@�̕`����W
//	position = pos;
//
//	if (dir == Fan::Dir::LEFT)
//	{
//		strength = -5;
//		this->WindHitBase.CreateObject(Cube, Vec2(position.x - (64.f * r), position.y), Vec2(64.f * r + pos.x - (pos.x - 64), 64.f), 0.0f);
//	}
//	else
//	{
//		strength = 5;
//		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * r + 16.f, 64.f), 0.0f);
//	}
//	this->DataInput();
//
//
//	this->SetFanTarget(target);
//	std::cout << "���]�t���O��@�@������" << std::endl;
//	return true;
//}
////�X�C�b�`����@��@
//bool Fan::Initialize(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Switch>&obj)
//{
//	//-----------------------------
//	//�������ɏ������鏉�����������L�q
//	//-----------------------------
//	range = r;
//	dir = d;
//	//��@�̕`����W
//	position = pos;
//
//	if (dir == Fan::Dir::LEFT)
//	{
//		strength = -5;
//		this->WindHitBase.CreateObject(Cube, Vec2(position.x - (64.f * r), position.y), Vec2(64.f * r + pos.x - (pos.x - 64), 64.f), 0.0f);
//	}
//	else
//	{
//		strength = 5;
//		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * r, 64.f), 0.0f);
//	}
//	this->DataInput();
//
//	this->SetSwitchTarget(obj);
//	std::cout << "�X�C�b�`�����@�@������" << std::endl;
//	return true;
//}
////�X�C�b�`����@���]�t���O����
//bool Fan::Initialize(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Fan> fantarget, std::shared_ptr<Switch>& switchtarget)
//{
//	//-----------------------------
//	//�������ɏ������鏉�����������L�q
//	//-----------------------------
//	range = r;
//	dir = d;
//	//��@�̕`����W
//	position = pos;
//
//	if (dir == Fan::Dir::LEFT)
//	{
//		strength = -5;
//		this->WindHitBase.CreateObject(Cube, Vec2(position.x - (64.f * r), position.y), Vec2(64.f * r + pos.x - (pos.x - 64), 64.f), 0.0f);
//	}
//	else
//	{
//		strength = 5;
//		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * r, 64.f), 0.0f);
//	}
//	this->DataInput();
//
//	this->SetFanTarget(fantarget);
//	this->SetSwitchTarget(switchtarget);
//
//	std::cout << "�X�C�b�`�����@�@������" << std::endl;
//	return true;
//}
//void Fan::Animetion::AnimetionReset()
//{
//	this->animetionframe = 0;
//	this->speed = 0;
//}
//void Fan::SetFlag()
//{
//	//���݂��̃t���O���Ǘ����Ă���ꍇ
//	if (target != nullptr && fantarget != nullptr)
//	{
//		//�X�C�b�`�̃t���O���i�[����
//		switchflag = !target->GetisON();
//		//�^�[�Q�b�g�̃X�C�b�`����t���O���i�[����
//		fanflag = !fantarget->GetSwitchFlag();
//	}
//	//�X�C�b�`����t���O�����o��
//	else if (target != nullptr)
//	{
//		//�X�C�b�`�̃t���O��������
//		switchflag = target->GetisON();
//	}
//	//�����@����t���O�����o���i���]�j
//	else if (fantarget != nullptr)
//	{
//		switchflag = !fantarget->GetSwitchFlag();
//	}
//	else
//	{
//		//�X�C�b�`���Ȃ��ꍇ�͏펞�ғ�����
//		switchflag = true;
//	}
//}
//void Fan::SetSwitchTarget(std::shared_ptr<Switch>&obj)
//{
//	if (obj != nullptr)
//	{
//		this->target = obj;
//	}
//}
//void Fan::SetFanTarget(std::shared_ptr<Fan> &obj)
//{
//	if (obj != nullptr)
//	{
//		this->fantarget = obj;
//	}
//}
//bool Fan::GetSwitchFlag()
//{
//	return switchflag;
//}
//void Fan::Animetion::AnimetionMove(bool flag)
//{
//	this->speed = 2;
//	//��@���ғ����Ă���
//	if (flag)
//	{
//		//��@�𓮂���(�A�j���[�V����)
//		if (animetionframe <= 300)
//		{
//			animetionframe++;
//		}
//		else
//		{
//			animetionframe += speed;
//		}
//	}
//	else
//	{
//		//��@��x������i�A�j���[�V�����j
//		if (animetionframe >= 300)
//		{
//			animetionframe -= 5;
//		}
//		else if (animetionframe > 0)
//		{
//			animetionframe -= speed;
//		}
//		else
//		{
//			this->AnimetionReset();
//		}
//	}
//}
//void Fan::UpDate()
//{
//	//--------------------
//	//�X�V���ɍs���������L�q
//	//--------------------
//	this->SetFlag();
//	//�A�j���[�V�����𓮂�������
//	animetion.AnimetionMove(GetSwitchFlag());
//	//���݂��̃t���O�������Ă���ꍇ
//	if (target != nullptr && this->fantarget != nullptr)
//	{
//		//���݂���true�̂Ƃ��̂݋N��������
//		if (GetSwitchFlag() && this->fanflag)
//		{
//			Motion();
//		}
//	}
//	//true�Ȃ��@���N������
//	else if (GetSwitchFlag())
//	{
//		Motion();
//	}
//	else
//	{
//		//�l�����Z�b�g����
//		animetion.AnimetionReset();
//	}
//
//	//�T�E���h�̍Đ��ɂ���
//	if (switchflag)
//	{
//		if (startflag)
//		{
//			sound.play();
//			startflag = false;
//		}
//	}
//	if (switchflag == false)
//	{
//		if (sound.isplay() == true)
//		{
//			sound.stop();
//		}
//		startflag = true;
//	}
//}
//void Fan::Animetion::AnimetionSrc(Box2D& src, bool flag)
//{
//	if (flag)
//	{
//		//�A�j���[�V�����̌v�Z������
//		if (animetionframe <= 120)
//		{
//			src.x += (animetionframe / 15 % 3)* src.w;
//		}
//		else if (animetionframe <= 160)
//		{
//			src.x += (animetionframe / 8 % 3)* src.w;
//		}
//		else
//		{
//			src.x += (animetionframe / 5 % 3)* src.w;
//		}
//	}
//	else
//	{
//		//�A�j���[�V�����̌v�Z������
//		if (animetionframe >= 160)
//		{
//			src.x += (animetionframe / 15 % 3)* src.w;
//		}
//		else if (animetionframe >= 120)
//		{
//			src.x += (animetionframe / 8 % 3)* src.w;
//		}
//		else
//		{
//			src.x += (animetionframe / 5 % 3)* src.w;
//		}
//	}
//}
//void Fan::Render2D()
//{
//	//--------------------
//	//�`�掞�ɍs���������L�q
//	//--------------------
//	Box2D draw(position, Vec2(64, 64));
//	draw.OffsetSize();
//	Box2D src = this->Src;
//	this->animetion.AnimetionSrc(src, GetSwitchFlag());
//	src.OffsetSize();
//	if (this->dir == Fan::Dir::LEFT)
//	{
//		int k = src.w;
//		src.w = src.x;
//		src.x = k;
//	}
//
//	this->image.Draw(draw, src);
//}
//
//bool Fan::Finalize()
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
//void Fan::SetWindRange(Vec2& b)
//{
//	this->WindHitBase.Scale = b;
//}
//void Fan::Motion()
//{
//	auto water = OGge->GetTasks<Water>("water");
//	if (water)
//	{
//		for (auto id = (*water).begin(); id != (*water).end(); ++id)
//		{
//			if ((*id)->hit(this->WindHitBase))
//			{
//				if ((*id)->GetState() == Water::State::GAS)
//				{
//					(*id)->MovePos_x(this->strength);
//				}
//			}
//		}
//	}
//}
////----------------------------
////�������牺��class���̂ݕύX����
////�ق��͕ύX���Ȃ�����
////----------------------------
//Fan::Fan()
//{
//	std::cout << "��@�@����" << std::endl;
//	soundname = "wind1.wav";
//}
//Fan::~Fan()
//{
//	this->Finalize();
//	std::cout << "��@�@���" << std::endl;
//}
////�펞�ғ�
//Fan::SP Fan::Create(Vec2 pos, float r, Fan::Dir d, bool flag_)
//{
//	Fan::SP to = Fan::SP(new Fan());
//	if (to)
//	{
//		to->me = to;
//		if (flag_)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos, r, d))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}
////�X�C�b�`����
//Fan::SP Fan::Create(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Switch>&target, bool flag_)
//{
//	Fan::SP to = Fan::SP(new Fan());
//	if (to)
//	{
//		to->me = to;
//		if (flag_)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos, r, d, target))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}
////��@�̔��]�t���O����
//Fan::SP Fan::Create(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Fan>& target, bool flag_)
//{
//	Fan::SP to = Fan::SP(new Fan());
//	if (to)
//	{
//		to->me = to;
//		if (flag_)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos, r, d, target))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}
////�X�C�b�`����@��@�̔��]�t���O����
//Fan::SP Fan::Create(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Fan>& fantarget, std::shared_ptr<Switch>& switchtarget, bool flag_)
//{
//	Fan::SP to = Fan::SP(new Fan());
//	if (to)
//	{
//		to->me = to;
//		if (flag_)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos, r, d, fantarget, switchtarget))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}