#include "Switch.h"
using namespace std;

//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����

bool Switch::Initialize(Vec2 pos)
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "Switch";			//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

									//���W�̐ݒ�
	position = pos;
	//�����蔻��̎���
	CreateObject(Cube, position, Vec2(64, 64), 0.0f);
	//�I�u�W�F�N�g�^�O�̒ǉ�
	objectTag = "Switch";
	//�X�C�b�`�̐؂�ւ��t���O��ON�ɂ���
	is_on = false;

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
		targets.clear();
		image.Finalize();
		//�����������ꍇ��Kill���g��
		this->Kill();
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
	for (auto t : targets)
	{
		if (t->objectTag == "Fan")
		{
			//�X�C�b�`�������ƁE�E�E
			((Fan*)t)->ChangeState();
		}
	}
}
void Switch::SetTarget(GameObject* t)
{
	//���Ƃŉ��M��Ɛ��X�@�̃^�O���ǉ����邱��
	if (t->objectTag != "Fan") { return; }
	targets.push_back(t);
}
//----------------------------
//�������牺��class���̂ݕύX����
//�ق��͕ύX���Ȃ�����
//----------------------------
Switch::Switch()
{

}

Switch::~Switch()
{
	this->Finalize();
}

Switch::SP Switch::Create(bool flag_, Vec2 pos)
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