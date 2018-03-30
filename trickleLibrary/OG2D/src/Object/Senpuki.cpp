#include "Senpuki.h"

using namespace std;

//11�Ԕz�u���W

const int IMAGE_SIZE_X = 64;			//�摜�T�C�Y
const int IMAGE_SIZE_Y = 64;			//�摜�T�C�Y

const int INITIALCOORDINATE_X = IMAGE_SIZE_X * 11;	//�������W
const int INITIALCOORDINATE_Y = IMAGE_SIZE_Y * 7;	//�������W

const float WIND = 1.5f;				//���́i���̋����j

//��������//-----------------------------------------------------------------------------
Senpuki::Senpuki()
{

}
Senpuki::Senpuki(Vec2 pos)
{
	position = pos;
}
//��������//-----------------------------------------------------------------------------
Senpuki::~Senpuki()
{

}
//��������//-----------------------------------------------------------------------------

//������������Ƃ���(Vec2 �������W)
bool Senpuki::Initialize(Vec2 pos)
{
	objectTag = "Senpuuki";

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
void Senpuki::CheakHit()
{
	Object::CollisionProcess = [&](const Object& o_)
	{
		cout << "�����_���̏������Ȃ�" << endl;
		if (parent->hit(*this))			//Player�̓����蔻��i�{���͐��Ŕ�������j
		{
			flag = true;				//Player�Ɛڂ��Ă���
			cout << "�������Ă��܂�" << endl;
			if (flag)
			{
				//flag = collisionCube.hitBox(objhit->collisionCube); //���@�Ƃ̓����蔻��
				if (((Water&)o_).GetState() == Water::State::GAS)//Player�������C�̏�ԂȂ�΁E�E�E
				{
					//���𑗂�x���W�ɑ��邱�Ƃŕ��������Ă���悤�Ɍ�����
					//o_.position.x -= WIND;
					cout << "���������܂�" << endl;
				}
			}
		}
		else
		{
			flag = false;
		}
	};
}
bool Senpuki::HasParent()const
{
	return parent != nullptr;
}
void Senpuki::SetParent(Object* obj) 
{
	parent = obj;
}