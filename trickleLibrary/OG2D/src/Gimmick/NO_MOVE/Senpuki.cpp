#include "Senpuki.h"
using namespace std;

//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
#include "Gimmick\NO_MOVE\Switch.h"
#include "Water\water.h"
bool Fan::Initialize(Vec2 pos, float r, Fan::Dir d)
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "Senpuki";			//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	position = pos;
	objectTag = "Fan";
	range = r;
	dir = d;
	if (dir == Fan::Dir::LEFT)
	{
		strength = -3;
		this->WindHitBase.CreateObject(Cube, Vec2(pos.x - (64 * r), pos.y), Vec2(64 * r, 64.f), 0.0f);
	}
	else
	{
		strength = 3;
		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * r, 64.f), 0.0f);
	}
	this->GetFlag();
	std::cout << "��@�@������" << std::endl;
	return true;
}
bool Fan::Initialize(Vec2 pos, float r, Fan::Dir d,std::shared_ptr<Switch>&obj)
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "Senpuki";			//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	position = pos;
	objectTag = "Fan";
	range = r;
	dir = d;
	if (dir == Fan::Dir::LEFT)
	{
		strength = -3;
		this->WindHitBase.CreateObject(Cube, Vec2(pos.x - (64 * r), pos.y), Vec2(64 * r, 64.f), 0.0f);
	}
	else
	{
		strength = 3;
		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * r, 64.f), 0.0f);
	}
	this->SetSwitchFlag(obj);
	std::cout << "��@�@������" << std::endl;
	return true;
}
void Fan::GetFlag()
{
	if (target != nullptr)
	{
		switchflag = target->GetisON();
	}
	else
	{
		switchflag = true;
	}
}
void Fan::SetSwitchFlag(std::shared_ptr<Switch>&obj)
{
	if (obj != nullptr)
	{
		this->target = obj;
	}
}
bool Fan::GetSwitchFlag()
{
	return switchflag;
}
void Fan::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------
	this->GetFlag();
	if (GetSwitchFlag())
	{
		auto waters = OGge->GetTasks<Water>("water");
		if (waters)
		{
			for (int i = 0; i < (*waters).size(); ++i)
			{
				(*waters)[i]->hit(this->WindHitBase);
			}
		}
	}
}

void Fan::Render2D()
{
	//--------------------
	//�`�掞�ɍs���������L�q
	//--------------------
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
	Box2D src(0, 0, 256, 256);
	if (this->dir == Fan::Dir::LEFT)
	{
		int k = src.w;
		src.w = src.x;
		src.x = k;
	}
	this->image->Draw(draw, src);
}

bool Fan::Finalize()
{
	//-----------------------------------------
	//���̃I�u�W�F�N�g�����ł���Ƃ��ɍs���������L�q
	//-----------------------------------------

	//���̃^�X�N����邩���A�v���P�[�V�������I���\�肩�ǂ���
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		
	}
	return true;
}
void Fan::SetTexture(Texture* tex)
{
	this->image = tex;
}
void Fan::SetWindRange(Vec2& b)
{
	this->WindHitBase.Scale = b;
}
void Fan::Motion()
{
	auto water = OGge->GetTask<Water>("water");
	if (water)
	{
		if (water->GetState() == Water::State::GAS)
		{
			water->MovePos(Vec2(strength, 0));
		}
	}
}
//----------------------------
//�������牺��class���̂ݕύX����
//�ق��͕ύX���Ȃ�����
//----------------------------
Fan::Fan()
{
	std::cout << "��@�@����" << std::endl;
}
Fan::~Fan()
{
	this->Finalize();
	std::cout << "��@�@���" << std::endl;
}
Fan::SP Fan::Create(Vec2 pos, float r, Fan::Dir d, bool flag_)
{
	Fan::SP to = Fan::SP(new Fan());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos, r, d))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

Fan::SP Fan::Create(Vec2 pos, float r, Fan::Dir d,std::shared_ptr<Switch>&target, bool flag_)
{
	Fan::SP to = Fan::SP(new Fan());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos,r,d,target))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
