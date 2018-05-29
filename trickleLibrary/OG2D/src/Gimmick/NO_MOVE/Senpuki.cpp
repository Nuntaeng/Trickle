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

	range = r;
	dir = d;
	//��@�̕`����W
	position = pos;
	if (dir == Fan::Dir::LEFT)
	{
		strength = -3;
		this->WindHitBase.CreateObject(Cube, Vec2(position.x - (64.f * r), position.y), Vec2(64.f * r + pos.x - (pos.x - 64), 64.f), 0.0f);
	}
	else
	{
		strength = 3;
		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * r, 64.f), 0.0f);
	}
	animetion.AnimetionReset();

	this->GetFlag();
	std::string filePath = "fan.png";
	image.Create(filePath);
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

	//��@�̕`����W
	position = pos;
	dir = d;
	range = r;

	if (dir == Fan::Dir::LEFT)
	{
		strength = -3;
		this->WindHitBase.CreateObject(Cube, Vec2(position.x - (64.f * r), position.y), Vec2(64.f * r + pos.x, 64.f), 0.0f);
	}
	else
	{
		strength = 3;
		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * r, 64.f), 0.0f);
	}
	animetion.AnimetionReset();

	this->SetSwitchFlag(obj);
	std::string filePath = "fan.png";
	image.Create(filePath);
	std::cout << "��@�@������" << std::endl;
	return true;
}
void Fan::Animetion::AnimetionReset()
{
	this->animetionframe = 0;
	this->speed = 0;
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
void Fan::Animetion::AnimetionMove(bool flag)
{
	this->speed = 2;
	//��@���ғ����Ă���
	if (flag)
	{
		if (animetionframe <= 300)
		{
			animetionframe++;
		}
		else
		{
			animetionframe += speed;
		}
	}
	else
	{
		if (animetionframe >= 300)
		{
			animetionframe -= 10;
		}
		else if(animetionframe > 0)
		{
			animetionframe -= speed;
		}
		else
		{
			this->AnimetionReset();
		}
	}
}
void Fan::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------
	this->GetFlag();
	if (GetSwitchFlag())
	{
		animetion.AnimetionMove(GetSwitchFlag());
		Motion();
	}
	else
	{
		animetion.AnimetionMove(GetSwitchFlag());
		animetion.AnimetionReset();
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
			src.x += (animetionframe / 15 % 3)* src.w;
		}
		else if (animetionframe >= 120)
		{
			src.x += (animetionframe / 8 % 3)* src.w;
		}
		else
		{
			src.x += (animetionframe / 5 % 3)* src.w;
		}
	}
}
void Fan::Render2D()
{
	//--------------------
	//�`�掞�ɍs���������L�q
	//--------------------
	Box2D draw(position, Vec2(64, 64));
	draw.OffsetSize();
	Box2D src = this->Src;
	this->animetion.AnimetionSrc(src,GetSwitchFlag());
	src.OffsetSize();
	if (this->dir == Fan::Dir::LEFT)
	{
		int k = src.w;
		src.w = src.x;
		src.x = k;
	}
	
	this->image.Draw(draw, src);
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
void Fan::SetWindRange(Vec2& b)
{
	this->WindHitBase.Scale = b;
}
void Fan::Motion()
{
	auto water = OGge->GetTasks<Water>("water");
	if (water)
	{
		for (auto id = (*water).begin(); id != (*water).end(); ++id)
		{
			if ((*id)->hit(this->WindHitBase))
			{
				if ((*id)->GetState() == Water::State::GAS)
				{
					(*id)->MovePos(Vec2(this->strength, 0));
				}
			}
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
