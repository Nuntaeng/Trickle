#include "Senpuki.h"
using namespace std;


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
	//�������W�̐ݒu
	position = pos;
	//�I�u�W�F�N�g�^�O�̐ݒ�
	objectTag = "Fan";
	//�͈͂̐ݒ�
	range = r;
	//�����̎w��
	dir = d;
	//0 true 1 false
	active = activ;

	//�����ɂ���Ĕ͈͂̐ݒ��ω�������
	if (dir == Fan::Dir::LEFT) 
	{
		//���ꂾ��������Ȃ�
		CreateObject(Cube, Vec2(position.x - 64.0f*range, position.y), Vec2(64.0f * range, 64.0f), 0.0f);
		//�ړ�Move�̐ݒ�
		movePos = -1;
	}
	else 
	{
		CreateObject(Cube, Vec2(position.x + 64.0f*range, position.y), Vec2(64.0f*range, 64.0f), 0.0f);
		movePos = 1;
	}

	//�����_�������蔻��
	Object::CollisionProcess = [&](const Object& o_) 
	{
		//true�ɂȂ��Ă���Ȃ�E�E�E
		if (active) 
		{//���ƐڐG��������E�E�E
			if (o_.objectTag == "Water") 
			{//�����C�̂Ȃ�E�E�E
				if (((Water&)o_).GetSituation() == Water::Situation::Normal && ((Water&)o_).GetState() == Water::State::GAS) 
				{//�ړ�Move�ɂ����X���W��ω�������
					const_cast<Object&>(o_).position.x += movePos;
				}
			}
		}
	};
}
void Fan::AddSwitch(Switch* swit) 
{
	//
	switches.push_back(swit);
}
void Fan::ChangeState()
{
	//�����_�ł̃t���O���t�]������
	active = !active;
}
void Fan::Finalize() 
{
	switches.clear();
	image.Finalize();
}
void Fan::Render(){}