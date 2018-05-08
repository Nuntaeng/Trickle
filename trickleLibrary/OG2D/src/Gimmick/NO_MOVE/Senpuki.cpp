#include "Senpuki.h"
using namespace std;

//���c����
Fan::Fan()
{

}
Fan::Fan(Vec2 pos)
{
	position = pos;
}
Fan::~Fan()
{

}
void Fan::Initialize(Vec2 pos, float r, Fan::Dir d, bool activ) 
{
	position = pos;
	objectTag = "Fan";
	range = r;
	dir = d;
	active = activ;
	if (dir == Fan::Dir::LEFT) 
	{
		CreateObject(Cube, Vec2(position.x - 64.0f*range, position.y), Vec2(64.0f * range, 64.0f), 0.0f);
		strength = -1;
	}
	else 
	{
		CreateObject(Cube, Vec2(position.x + 64.0f, position.y), Vec2(64.0f*range, 64.0f), 0.0f);
		strength = 1;
	}
}
void Fan::SetWaterPool(std::vector<Water*> *w)
{
	water = w;
}
void Fan::UpDate()
{
	for (auto& w : *water)
	{
		//�����蔻��
		if (hit(*w))
		{//�X�C�b�`�̏��
			Motion(w);
		}
	}
}
void Fan::Motion(Water* w)
{
	if (active)
	{//�����C�Ȃ�
		if (w->GetState() == Water::State::GAS)
		{
			w->position.x += strength;
		}
	}
}
void Fan::AddSwitch(Switch* swit) 
{
	switches.push_back(swit);
}
void Fan::ChangeState()
{
	active = !active;
}
void Fan::Finalize() 
{
	switches.clear();
	image.Finalize();
}
void Fan::Render(){}