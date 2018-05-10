#include "Seihyouki.h"
using namespace std;

//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����

bool Seihyouki::Initialize()
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "";			//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��


	return true;
}
void Seihyouki::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------
	for (auto& w : *water)
	{
		/*if (w->hit(hitBace))
		{
			toIce(w);
		}*/
	}
}

void Seihyouki::Render2D()
{
	//--------------------
	//�`�掞�ɍs���������L�q
	//--------------------
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
	
}

bool Seihyouki::Finalize()
{
	//-----------------------------------------
	//���̃I�u�W�F�N�g�����ł���Ƃ��ɍs���������L�q
	//-----------------------------------------
	this->sampleImage.Finalize();
	//���̃^�X�N����邩���A�v���P�[�V�������I���\�肩�ǂ���
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		//�����������ꍇ��Kill���g��
		this->Kill();
	}
	return true;
}
void Seihyouki::toIce(Water* obj)
{
	if (obj->GetState() == Water::State::SOLID)
	{
		while (true)
		{
			movetime++;
			if (movetime >= movetime_ice)
			{
				obj->SetState(Water::State::LIQUID);
				movetime = 0;
				break;
			}
		}
	}
	if (obj->GetState() == Water::State::LIQUID)
	{
		while (true)
		{
			movetime++;
			if (movetime >= movetime_ice)
			{
				obj->SetState(Water::State::SOLID);
				movetime = 0;
				break;
			}
		}
	}
}
void Seihyouki::Create(Vec2 pos, Vec2 scale)
{
	movetime = 0;
	hitBace.CreateObject(Cube, pos, scale, 0);
}
void Seihyouki::SetWaterPool(std::vector<Water*>*w)
{
	water = w;
}
//----------------------------
//�������牺��class���̂ݕύX����
//�ق��͕ύX���Ȃ�����
//----------------------------
Seihyouki::Seihyouki()
{

}

Seihyouki::~Seihyouki()
{
	this->Finalize();
}

Seihyouki::SP Seihyouki::Create(bool flag_)
{
	Seihyouki::SP to = Seihyouki::SP(new Seihyouki());
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