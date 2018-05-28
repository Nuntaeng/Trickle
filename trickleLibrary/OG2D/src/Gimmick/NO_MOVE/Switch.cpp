#include "Switch.h"
using namespace std;

//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
bool Switch::Initialize(Vec2& pos , Player::SP target,bool is_on)
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "Switch";		//�������Ɏg�����߂̖���o�^����

	if (target)
	{
		std::cout << "Player�����m" << std::endl;
	}
	else
	{
		std::cout << "Player������s" << std::endl;
	}

	//�^�O���������m�\�ɂ���
	this->Init(taskName);			//TaskObject���̏������s��
	//�����蔻��̎���
	CreateObject(Cube, pos, Vec2(64, 64), 0.0f);
	//�X�C�b�`�̐؂�ւ��t���O��ON�ɂ���
	this->is_on = is_on;
	//�X�C�b�`�ɑΉ�����
	SetTarget(target);

	image.Create((std::string)"switch.png");
	cout << "�X�C�b�`�@������" << endl;
	return true;
}
bool Switch::Initialize(Vec2& pos, Switch::SP target)
{
	if (target)
	{
		cout << "�X�C�b�`�����m" << endl;
	}
	else
	{
		cout << "�X�C�b�`������s" << endl;
	}

	//�^�O���������m�\�ɂ���
	this->Init(taskName);			//TaskObject���̏������s��
	//�����蔻��̎���
	CreateObject(Cube, pos, Vec2(64, 64), 0.0f);
	//�^�[�Q�b�g��������
	SetTarget(target);
	image.Create((std::string)"switch.png");
	cout << "�^�[�Q�b�g�X�C�b�`�@������" << endl;
	return true;
}
void Switch::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------
	if (this->CheckHit())
	{
		if (OGge->in->key.down(Input::KeyBoard::S))
		{
			this->ON_OFF();
		}
	}
	//���̃X�C�b�`�̃t���O�ƑΏۂɔ��]������
	if (targetswitch != nullptr)
	{
		this->TargetSwitchChenge();
	}
}
bool Switch::CheckHit()
{
	if (this->target != nullptr)
	{
		if (this->target->hit(*this))
		{
			return true;
		}
	}
	return false;
}
void Switch::Render2D()
{
	//--------------------
	//�`�掞�ɍs���������L�q
	//--------------------
	Box2D draw(position, Scale);
	draw.OffsetSize();
	Box2D src = this->Src;
	src.OffsetSize();
	if (this->GetisON())
	{
		int temp = src.x;
		src.x = src.w;
		src.w = temp;
	}
	image.Draw(draw, src);
}

bool Switch::Finalize()
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
bool Switch::GetisON()
{
	//�؂�ւ��t���O��Ԃ�
	return is_on;
}
void Switch::ON_OFF()
{
	//true��false�̐؂�ւ��t���O��؂�ւ���
	is_on = !is_on;
}
void Switch::SetTarget(Player::SP target)
{
	if (target != nullptr)
	{
		this->target = target;
	}
}
void Switch::SetTarget(Switch::SP target)
{
	if (target != nullptr)
	{
		this->targetswitch = target;
		this->is_on = !this->targetswitch->GetisON();
	}
}
void Switch::TargetSwitchChenge()
{
	if (targetswitch != nullptr)
	{
		this->is_on = !this->targetswitch->GetisON();
	}		
}
Switch::Switch()
{
	cout << "�X�C�b�`�@����" << endl;
}

Switch::~Switch()
{
	this->Finalize();
	cout << "�X�C�b�`�@���" << endl;
}
Switch::SP Switch::Create(Vec2& pos, Player::SP target ,bool is_on ,bool flag_)
{
	Switch::SP to = Switch::SP(new Switch());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos,target,is_on))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
Switch::SP Switch::Create(Vec2& pos, Switch::SP target,bool flag)
{
	Switch::SP to = Switch::SP(new Switch());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos, target))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}