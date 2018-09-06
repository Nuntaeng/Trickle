#include "Seihyouki.h"
using namespace std;

//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
#include "Water\water.h"


Seihyouki::Seihyouki()
	:
	maxChangeTime(5),maxCnt(30)
{}


bool Seihyouki::Initialize(Vec2& pos, Vec2 range, Angle ang, bool active) {
	this->taskName = "Seihyouki";	//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��
	SetDrawOrder(0.5f);

	changeStateCnt = 0;
	CreateObject(Cube, pos, range, 0);
	this->active = active;
	this->SetTexture(rm->GetTextureData((std::string)"fireIce"));

	this->animCnt = 0;
	this->coldNum = 0;
	this->timeCnt = 0;
	draw.clear();
	draw.resize(1);

	this->angle = ang;

	return true;
}
void Seihyouki::UpDate() {
	this->animCnt++;
	if (this->animCnt > 150)
	{
		this->animCnt = 0;
	}
	if (active) {
		//toIce();
	}
	if (this->active)
	{
		if (this->timeCnt < this->maxCnt)
		{
			++this->timeCnt;
		}
	}
	else
	{
		if (this->timeCnt > 0)
		{
			--this->timeCnt;
		}
	}
}

void Seihyouki::Render2D() {
	//�f�o�b�O�p
	//if (active) 
	{
		LineDraw();
		//Box2D drawRL,srcR;
		if (angle == RIGHT)
		{
			coldNum = 1;
			float angle = 90.0f;
			for (int i = 0; i < coldNum; ++i) {
				draw[i] = Box2D(position.x + 15 + (64 * i), position.y - 32.0f, 64.f, Scale.y*2.0f);
				Vec2 origin = Vec2(draw[i].w, draw[i].h);
				draw[i].w *= ((float)this->timeCnt / (float)this->maxCnt);
				draw[i].h *= ((float)this->timeCnt / (float)this->maxCnt);
				draw[i].y += (origin.y - draw[i].h) / 2.f;
				draw[i].x -= (origin.x - draw[i].w) / 2.f;
				draw[i].OffsetSize();
			}
			Box2D src = { 256 * (animCnt / 5 % 3), 256, 256, 256 };
			src.OffsetSize();

			coldImg->Rotate(angle);
			for (auto draw_ : draw) {
				this->coldImg->Draw(draw_, src);
			}
		}
		else if (angle==LEFT)
		{
			coldNum = 1;
			float angle = 270.0f;
			for (int i = 0; i < coldNum; ++i) {
				draw[i] = Box2D(position.x+32.0f + (64 * i), position.y-32.0f, 64.f, Scale.y*2.0f);
				Vec2 origin = Vec2(draw[i].w, draw[i].h);
				draw[i].w *= ((float)this->timeCnt / (float)this->maxCnt);
				draw[i].h *= ((float)this->timeCnt / (float)this->maxCnt);
				draw[i].y += (origin.y - draw[i].h) / 2.f;
				draw[i].x += (origin.x - draw[i].w) * 1.5f;
				draw[i].OffsetSize();
			}
			Box2D src = { 256 * (animCnt / 5 % 3), 256, 256, 256 };
			src.OffsetSize();

			coldImg->Rotate(angle);
			for (auto draw_ : draw) {
				this->coldImg->Draw(draw_, src);
			}
		}
		//������̐��X�@�g���Ă��Ȃ�
		//else if (angle == UP)
		//{
		//			for (int i = 0; i < coldNum; ++i) {
		//				draw[i] = Box2D(position.x + (64 * i), position.y, 64.f, Scale.y);
		//				draw[i].OffsetSize();
		//			}
		//			src = { 256 * (animCnt / 5 % 3), 256, 256, 256 };
		//			src.OffsetSize();

		//			for (auto draw_ : draw) {
		//				this->coldImg->Draw(draw_, src);
		//			}
		//}
	}
}
bool Seihyouki::Finalize() {
	//�摜���������œǂݍ��ނȂ�Texture��Finalize()���ĂԂ���
	return true;
}
void Seihyouki::toIce() {
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		if ((*id)->GetState() == Water::State::LIQUID)
		{
			if ((*id)->hit(*this))
			{
				//changeStateCnt++;
				(*id)->SetIceCnt((*id)->GetIceCnt() + 1);
				if ((*id)->GetIceCnt() >= maxChangeTime)
				{
					(*id)->SetState(Water::State::SOLID);
					(*id)->SetIceCnt(0);
					break;
				}
			}
		}
	}
}
void Seihyouki::changeActive() {
	this->active = !this->active;
}
void Seihyouki::SetTexture(Texture* tex)
{
	this->coldImg = tex;
}
Seihyouki::SP Seihyouki::Create(Vec2& pos, Vec2 range, Seihyouki::Angle ang, bool active, bool flag_) {
	Seihyouki::SP to = Seihyouki::SP(new Seihyouki());
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
unsigned int Seihyouki::GetChengeSolid() const
{
	return this->maxChangeTime;
}
bool Seihyouki::GetActive() const
{
	return this->active;
}

//bool Seihyouki::Initialize(Vec2& pos)
//{
//	//-----------------------------
//	//�������ɏ������鏉�����������L�q
//	//-----------------------------
//	this->taskName = "Seihyouki";	//�������Ɏg�����߂̖���o�^����
//	__super::Init(taskName);		//TaskObject���̏������s��
//
//	movetime = 0;
//	hitBace.CreateObject(Cube, pos, Vec2(64, 64), 0);
//	this->GetFlag();
//	cout << "���X�@�@������" << endl;
//	return true;
//}
//bool Seihyouki::Initialize(Vec2& pos ,std::shared_ptr<Switch> &target)
//{
//	//-----------------------------
//	//�������ɏ������鏉�����������L�q
//	//-----------------------------
//	this->taskName = "Seihyouki";	//�������Ɏg�����߂̖���o�^����
//	__super::Init(taskName);		//TaskObject���̏������s��
//
//	movetime = 0;
//	hitBace.CreateObject(Cube, pos, Vec2(64,64), 0);
//	this->SetSwitchFlag(target);
//	cout << "���X�@�@������" << endl;
//	return true;
//}
//void Seihyouki::GetFlag()
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
//void Seihyouki::SetSwitchFlag(std::shared_ptr<Switch>&obj)
//{
//	if (obj != nullptr)
//	{
//		target = obj;
//	}
//}
//bool Seihyouki::GetSwitchFlag()
//{
//	return switchflag;
//}
//void Seihyouki::UpDate()
//{
//	//--------------------
//	//�X�V���ɍs���������L�q
//	//--------------------
//	this->GetFlag();
//
//	if (GetSwitchFlag())
//	{
//		toIce();
//	}
//}
//
//void Seihyouki::Render2D()
//{
//	//--------------------
//	//�`�掞�ɍs���������L�q
//	//--------------------
//}
//
//bool Seihyouki::Finalize()
//{
//	//-----------------------------------------
//	//���̃I�u�W�F�N�g�����ł���Ƃ��ɍs���������L�q
//	//-----------------------------------------
//	//���̃^�X�N����邩���A�v���P�[�V�������I���\�肩�ǂ���
//	if (this->GetNextTask() && !OGge->GetDeleteEngine())
//	{
//		
//	}
//	return true;
//}
//void Seihyouki::toIce()
//{
//	auto waters = OGge->GetTasks<Water>("water");
//	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
//	{
//		if ((*id)->hit(hitBace))
//		{
//			if ((*id)->GetState() == Water::State::SOLID)
//			{
//				while (true)
//				{
//					movetime++;
//					if (movetime >= movetime_ice)
//					{
//						(*id)->SetState(Water::State::LIQUID);
//						movetime = 0;
//						break;
//					}
//				}
//			}
//			if ((*id)->GetState() == Water::State::LIQUID)
//			{
//				while (true)
//				{
//					movetime++;
//					if (movetime >= movetime_ice)
//					{
//						(*id)->SetState(Water::State::SOLID);
//						movetime = 0;
//						break;
//					}
//				}
//			}
//		}
//	}
//}
////----------------------------
////�������牺��class���̂ݕύX����
////�ق��͕ύX���Ȃ�����
////----------------------------
//Seihyouki::Seihyouki()
//{
//	cout << "���X�@�@����" << endl;
//}
//
//Seihyouki::~Seihyouki()
//{
//	this->Finalize();
//	cout << "���X�@�@���" << endl;
//}
//Seihyouki::SP Seihyouki::Create(Vec2& pos,bool flag_)
//{
//	Seihyouki::SP to = Seihyouki::SP(new Seihyouki());
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
//Seihyouki::SP Seihyouki::Create(Vec2& pos,std::shared_ptr<Switch>&target,bool flag_)
//{
//	Seihyouki::SP to = Seihyouki::SP(new Seihyouki());
//	if (to)
//	{
//		to->me = to;
//		if (flag_)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos , target))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}