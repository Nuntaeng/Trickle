#include "Senpuki.h"

using namespace std;

//11�Ԕz�u���W(����̂͏�)

const int IMAGE_SIZE_X = 64;                                       //�摜�T�C�Y_X
const int IMAGE_SIZE_Y = 64;                                       //�摜�T�C�Y_Y

const int INITIALCOORDINATE_X = IMAGE_SIZE_X * 11;	               //�������W_X
const int INITIALCOORDINATE_Y = IMAGE_SIZE_Y * 7;	               //�������W_Y

const float WIND = 1.5f;				                           //���́i���̋����j

//��������//-----------------------------------------------------------------------------
Senpuki::Senpuki()                                                 //�R���X�g���N�^�i�Ȃ��j
{
	
}
Senpuki::Senpuki(Vec2 pos)                                         //�R���X�g���N�^�iVec2�@�������W�j
{
	position = pos;
}
//��������//-----------------------------------------------------------------------------
Senpuki::~Senpuki()                                                //�f�X�g���N�^�@�����݂͉�������܂���
{

}
//��������//-----------------------------------------------------------------------------

//������������Ƃ���(Vec2 �������W)
bool Senpuki::Initialize(Vec2 pos)
{
	objectTag = "Senpuuki";                 //�I�u�W�F�N�g�^�O���𐶐�����

	//�����蔻��̋�`��p�ӂ���
	CreateObject(Objform::Cube, pos, Vec2(IMAGE_SIZE_X, IMAGE_SIZE_Y), 0);								//�����蔻���`�𐶐�����
	cout << "������W(" << position.x + IMAGE_SIZE_X << "," << position.y + IMAGE_SIZE_Y << endl;		//�f�o�b�O�@�\�ł̓����蔻��̕\��
	//
	flag = false;							//�����蔻�菉���t���O�̐ݒ�
	CheakHit();								//�����蔻����s��
	return true;
}
//��������//-----------------------------------------------------------------------------
void Senpuki::UpDate()
{
	
}
//��������//-----------------------------------------------------------------------------
void Senpuki::Finalize()
{
	delete parent;
}
//��������//-----------------------------------------------------------------------------
void Senpuki::Render()
{

}
//��������//-----------------------------------------------------------------------------
//  �֐�  //-----------------------------------------------------------------------------
//��������//-----------------------------------------------------------------------------
void Senpuki::CheakHit()                                             //�����蔻��̏���
{
	Object::CollisionProcess = [&](const Object& o_)                 //�S�Ẵ��[�J���ł̃N���X���Q�Ƃ���H
	{
		cout << "�����_���̏������Ȃ�" << endl;                      //�o��
		if (o_.objectTag == "Water")                                 //Player�̓����蔻��i�{���͐��Ŕ�������j
		{
			flag = true;                                             //flag��true�ɂ���
			cout << "�������Ă��܂�" << endl;                        //�o��
			if (flag)                                                //���ƐڐG���肵����E�E�E
			{
				if (((Water&)o_).GetState() == Water::State::GAS)    //�����C�̏�ԂȂ�΁E�E�E
				{
					cout << "���������܂�" << endl;
				}
				if (((Water&)o_).GetState() == Water::State::LIQUID) //�t�̂̏�ԂȂ�΁E�E�E
				{
					cout << "�t�̂̏��" << endl;
				}
			}
		}
		else
		{
			flag = false;
		}
	};
}
bool Senpuki::HasParent()const                                       //nullptr�ł͂Ȃ����m�F����֐�
{
	return parent != nullptr;
}
void Senpuki::SetParent(Object* obj)                                 //�����蔻��ɕK�v�ȃI�u�W�F�N�g��Object* parent �ɑ������
{
	parent = obj;
}