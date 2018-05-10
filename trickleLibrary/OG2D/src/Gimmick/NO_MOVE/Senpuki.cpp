#include "Senpuki.h"
using namespace std;

//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����

bool Fan::Initialize(Vec2 pos, float r, Fan::Dir d, bool activ)
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "";			//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	position = pos;
	objectTag = "Fan";
	range = r;
	dir = d;
	active = activ;
	if (dir == Fan::Dir::LEFT)
	{
		CreateObject(Cube, pos, Vec2(64.0f, 64.0f), 0.0f);
		strength = -3;
		this->WindHitBase.CreateObject(Cube, Vec2(pos.x - (64 * 8), pos.y), Vec2(64 * 8, 64), 0.0f);
	}
	else
	{
		CreateObject(Cube, pos, Vec2(64.0f, 64.0f), 0.0f);
		strength = 3;
		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * 16, 64), 0.0f);
		//this->WindHitBase.CreateObject(Cube, Vec2(0,0), Vec2(0,0), 0.0f);
	}


	return true;
}
void Fan::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------

	for (auto& w : water)
	{
		//�����蔻��
		//if (this->WindHitBase.hit(*w))
		//{//�X�C�b�`�̏��
		//	Motion(w);
		//}
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
		switches.clear();
		this->water.clear();
		//�����������ꍇ��Kill���g��
		this->Kill();
	}
	return true;
}
void Fan::SetTexture(Texture* tex)
{
	this->image = tex;
}
void Fan::SetWaterPool(Water* w)
{
	this->water.push_back(w);
}
bool Fan::DeleteWaterPool(Water* w)
{
	for (auto id = this->water.begin(); id != this->water.end(); ++id)
	{
		if ((*id) == w)
		{
			this->water.erase(id);
			return true;
		}
	}
	return false;
}
void Fan::SetWindRange(Vec2& b)
{
	this->WindHitBase.Scale = b;
}
void Fan::AddSwitch(Switch* swit)
{
	switches.push_back(swit);
}
void Fan::ChangeState()
{
	active = !active;
}
void Fan::Motion(Water* w)
{
	if (active)
	{
		if (w->GetState() == Water::State::GAS)
		{
			//w->position.x += strength; // Left -1 Right 1
			w->MovePos(Vec2(strength, 0));
		}
	}
}
//----------------------------
//�������牺��class���̂ݕύX����
//�ق��͕ύX���Ȃ�����
//----------------------------
Fan::Fan()
{

}

Fan::~Fan()
{
	this->Finalize();
}

Fan::SP Fan::Create(bool flag_, Vec2 pos, float r, Fan::Dir d, bool activ)
{
	Fan::SP to = Fan::SP(new Fan());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos,r,d,activ))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
