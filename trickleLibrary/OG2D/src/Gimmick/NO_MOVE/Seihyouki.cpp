#include "Seihyouki.h"
using namespace std;

//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
#include "Water\water.h"
bool Seihyouki::Initialize(Vec2& pos)
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "Seihyouki";	//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	movetime = 0;
	hitBace.CreateObject(Cube, pos, Vec2(64, 64), 0);
	this->GetFlag();
	cout << "���X�@�@������" << endl;
	return true;
}
bool Seihyouki::Initialize(Vec2& pos ,std::shared_ptr<Switch> &target)
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "Seihyouki";	//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	movetime = 0;
	hitBace.CreateObject(Cube, pos, Vec2(64,64), 0);
	this->SetSwitchFlag(target);
	cout << "���X�@�@������" << endl;
	return true;
}
void Seihyouki::GetFlag()
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
void Seihyouki::SetSwitchFlag(std::shared_ptr<Switch>&obj)
{
	if (obj != nullptr)
	{
		target = obj;
	}
}
bool Seihyouki::GetSwitchFlag()
{
	return switchflag;
}
void Seihyouki::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------
	this->GetFlag();

	if (GetSwitchFlag())
	{
		toIce();
	}
}

void Seihyouki::Render2D()
{
	//--------------------
	//�`�掞�ɍs���������L�q
	//--------------------
}

bool Seihyouki::Finalize()
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
void Seihyouki::toIce()
{
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		if ((*id)->hit(hitBace))
		{
			if ((*id)->GetState() == Water::State::SOLID)
			{
				while (true)
				{
					movetime++;
					if (movetime >= movetime_ice)
					{
						(*id)->SetState(Water::State::LIQUID);
						movetime = 0;
						break;
					}
				}
			}
			if ((*id)->GetState() == Water::State::LIQUID)
			{
				while (true)
				{
					movetime++;
					if (movetime >= movetime_ice)
					{
						(*id)->SetState(Water::State::SOLID);
						movetime = 0;
						break;
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
Seihyouki::Seihyouki()
{
	cout << "���X�@�@����" << endl;
}

Seihyouki::~Seihyouki()
{
	this->Finalize();
	cout << "���X�@�@���" << endl;
}
Seihyouki::SP Seihyouki::Create(Vec2& pos,bool flag_)
{
	Seihyouki::SP to = Seihyouki::SP(new Seihyouki());
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
Seihyouki::SP Seihyouki::Create(Vec2& pos,std::shared_ptr<Switch>&target,bool flag_)
{
	Seihyouki::SP to = Seihyouki::SP(new Seihyouki());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos , target))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}