#include "Seihyouki.h"
using namespace std;

//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
#include "Water\water.h"
bool Seihyouki::Initialize(Vec2& pos , Vec2& scale)
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "Seihyouki";			//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	HitGeneration(pos,scale);

	return true;
}
void Seihyouki::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------
	auto water = OGge->GetTask<Water>("Water");
	if (water->hit(hitBace))
	{
		toIce();
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
		
	}
	return true;
}
void Seihyouki::toIce()
{
	auto water = OGge->GetTask<Water>("Water");
	if (water->GetState() == Water::State::SOLID)
	{
		while (true)
		{
			movetime++;
			if (movetime >= movetime_ice)
			{
				water->SetState(Water::State::LIQUID);
				movetime = 0;
				break;
			}
		}
	}
	if (water->GetState() == Water::State::LIQUID)
	{
		while (true)
		{
			movetime++;
			if (movetime >= movetime_ice)
			{
				water->SetState(Water::State::SOLID);
				movetime = 0;
				break;
			}
		}
	}
}
void Seihyouki::HitGeneration(Vec2& pos, Vec2& scale)
{
	movetime = 0;
	hitBace.CreateObject(Cube, pos, scale, 0);
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

Seihyouki::SP Seihyouki::Create(Vec2& pos,Vec2& scale,bool flag_)
{
	Seihyouki::SP to = Seihyouki::SP(new Seihyouki());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos , scale))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}