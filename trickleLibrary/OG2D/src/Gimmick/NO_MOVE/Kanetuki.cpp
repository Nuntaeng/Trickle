#include "Kanetuki.h"
using namespace std;

//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
#include "Water\water.h"

bool Kanetuki::Initialize(Vec2& pos)
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "Kanetuki";	//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//Taskwaterect���̏������s��

	Fire_movetime = 0;
	hitBace.CreateObject(Cube, pos, Vec2(64, 64), 0);
	this->GetFlag();
	cout << "���M��@������" << endl;
	return true;
}
bool Kanetuki::Initialize(Vec2& pos,std::shared_ptr<Switch>& target)
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "Kanetuki";	//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//Taskwaterect���̏������s��

	Fire_movetime = 0;
	hitBace.CreateObject(Cube, pos,Vec2(64,64), 0);
	this->SetSwitchFlag(target);

	cout << "���M��@������" << endl;
	return true;
}
void Kanetuki::GetFlag()
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
void Kanetuki::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------
	this->GetFlag();
	if (this->GetSwitchFlag())
	{
		this->toSteam();
	}
}

void Kanetuki::Render2D()
{
	//--------------------
	//�`�掞�ɍs���������L�q
	//--------------------
}
bool Kanetuki::Finalize()
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
void Kanetuki::SetSwitchFlag(std::shared_ptr<Switch>& obj)
{
	if (obj != nullptr)
	{
		target = obj;
	}
}
bool Kanetuki::GetSwitchFlag()
{
	return switchflag;
}
void Kanetuki::toSteam()
{
	auto water = OGge->GetTasks<Water>("water");
	if (water != nullptr)
	{
		for (int i = 0; i < (*water).size(); ++i)
		{
			if ((*water)[i]->hit(hitBace))
			{
				if ((*water)[i]->GetState() == Water::State::SOLID)
				{
					while (true)
					{
						bool flag = false;
						Fire_movetime++;
						if (Fire_movetime >= Fire_time_SOLID)
						{
							(*water)[i]->SetState(Water::State::LIQUID);
							Fire_movetime = 0;
							flag = true;
						}
						if (flag)
						{
							break;
						}
					}
				}
				if ((*water)[i]->GetState() == Water::State::LIQUID)
				{
					while (true)
					{
						bool flag = false;
						Fire_movetime++;
						if (Fire_movetime >= Fire_time_LIQUID)
						{
							(*water)[i]->SetState(Water::State::GAS);
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
		}
	}
}
//----------------------------
//�������牺��class���̂ݕύX����
//�ق��͕ύX���Ȃ�����
//----------------------------
Kanetuki::Kanetuki()
{
	cout << "���M��@����" << endl;
}

Kanetuki::~Kanetuki()
{
	this->Finalize();
	cout << "���M��@���" << endl;
}

Kanetuki::SP Kanetuki::Create(Vec2& pos, bool flag_)
{
	Kanetuki::SP to = Kanetuki::SP(new Kanetuki());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

Kanetuki::SP Kanetuki::Create(Vec2& pos,std::shared_ptr<Switch>& target,bool flag_)
{
	Kanetuki::SP to = Kanetuki::SP(new Kanetuki());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos,target))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}