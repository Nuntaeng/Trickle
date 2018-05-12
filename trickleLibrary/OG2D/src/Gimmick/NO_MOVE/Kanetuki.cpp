#include "Kanetuki.h"
using namespace std;

//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����

bool Kanetuki::Initialize()
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "Kanetuki";			//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	

	return true;
}
void Kanetuki::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------

	//���M���Motion�N��
	for (auto& w : *water)
	{
		if (hitBace.hit(*w))
		{
			toSteam(w);
		}
	}
}

void Kanetuki::Render2D()
{
	//--------------------
	//�`�掞�ɍs���������L�q
	//--------------------
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
	
}

bool Kanetuki::Finalize()
{
	//-----------------------------------------
	//���̃I�u�W�F�N�g�����ł���Ƃ��ɍs���������L�q
	//-----------------------------------------

	//���̃^�X�N����邩���A�v���P�[�V�������I���\�肩�ǂ���
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		//�����������ꍇ��Kill���g��
		this->Kill();
	}
	return true;
}
void Kanetuki::Create(Vec2 pos, Vec2 scale)
{
	Fire_movetime = 0;
	hitBace.CreateObject(Cube, pos, scale, 0);
}

void Kanetuki::SetWaterPool(std::vector<Water*>* w)
{
	water = w;
}
void Kanetuki::toSteam(Water* obj)
{
	if (obj->GetState() == Water::State::SOLID)
	{
		while (true)
		{
			bool flag = false;
			Fire_movetime++;
			if (Fire_movetime >= Fire_time_SOLID)
			{
				obj->SetState(Water::State::LIQUID);
				Fire_movetime = 0;
				flag = true;
			}
			if (flag)
			{
				break;
			}
		}
	}
	if (obj->GetState() == Water::State::LIQUID)
	{
		while (true)
		{
			bool flag = false;
			Fire_movetime++;
			if (Fire_movetime >= Fire_time_LIQUID)
			{
				obj->SetState(Water::State::GAS);
				Fire_movetime = 0;
				flag = true;
			}
			if (flag)
			{
				break;
			}
		}
	}
}
//----------------------------
//�������牺��class���̂ݕύX����
//�ق��͕ύX���Ȃ�����
//----------------------------
Kanetuki::Kanetuki()
{

}

Kanetuki::~Kanetuki()
{
	this->Finalize();
}

Kanetuki::SP Kanetuki::Create(bool flag_)
{
	Kanetuki::SP to = Kanetuki::SP(new Kanetuki());
	if (to)
	{
		to->me = to;
		if (flag_)
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