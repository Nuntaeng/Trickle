#include "Switch.h"
using namespace std;

void Switch::Initialize(Vec2 pos) 
{
	//���W�̐ݒ�
	position = pos;
	//�����蔻��̎���
	CreateObject(Cube, position, Vec2(64, 64), 0.0f);
	//�I�u�W�F�N�g�^�O�̒ǉ�
	objectTag = "Switch";
	//�X�C�b�`�̐؂�ւ��t���O��ON�ɂ���
	is_on = false;
}
void Switch::Update() 
{
	//�����Ȃ�
}
void Switch::Finalize() 
{
	targets.clear();
	image.Finalize();
}
void Switch::Render() 
{
	//csv������̂ŕ`��̋@�\�͂Ȃ�
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
void Switch::SetTarget(Object* t) 
{
	//���Ƃŉ��M��Ɛ��X�@�̃^�O���ǉ����邱��
	if (t->objectTag != "Fan") { return; }
	targets.push_back(t);
}