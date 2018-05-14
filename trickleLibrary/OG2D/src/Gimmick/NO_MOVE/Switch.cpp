#include "Switch.h"
using namespace std;

#include "Senpuki.h"
//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
bool Switch::Initialize(Vec2& pos)
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "Switch";		//�������Ɏg�����߂̖���o�^����

	//�^�O���������m�\�ɂ���
	this->Init(taskName);			//TaskObject���̏������s��

									//���W�̐ݒ�
	//�����蔻��̎���
	CreateObject(Cube, pos, Vec2(64, 64), 0.0f);
	//�I�u�W�F�N�g�^�O�̒ǉ�
	objectTag = "Switch";
	//�X�C�b�`�̐؂�ւ��t���O��ON�ɂ���
	is_on = false;

	cout << "�X�C�b�`�@������" << endl;
	return true;
}
void Switch::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------
}

void Switch::Render2D()
{
	//--------------------
	//�`�掞�ɍs���������L�q
	//--------------------
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();

}

bool Switch::Finalize()
{
	//-----------------------------------------
	//���̃I�u�W�F�N�g�����ł���Ƃ��ɍs���������L�q
	//-----------------------------------------
	
	//���̃^�X�N����邩���A�v���P�[�V�������I���\�肩�ǂ���
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		image.Finalize();
	}
	return true;
}
bool Switch::isON()
{
	//�؂�ւ��t���O��Ԃ�
	return is_on;
}
void Switch::ON_OFF()
{
	//true��false�̐؂�ւ��t���O��؂�ւ���
	is_on = !is_on;
	//�X�C�b�`��ONOFF���؂�ւ�����������^�[�Q�b�g��ChangeState()���Ăяo��
	auto target = OGge->GetTasks<Fan>("Fan");
	for (int i = 0; i < (*target).size(); ++i)
	{
		(*target)[i]->ChangeState();
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

Switch::SP Switch::Create(Vec2& pos , bool flag_)
{
	Switch::SP to = Switch::SP(new Switch());
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