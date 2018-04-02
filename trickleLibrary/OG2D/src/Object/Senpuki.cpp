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
	position = pos;                                                //����ꂽ���W�l���@�̍��W�f�[�^�ɑ��������
	Pos.push_back(pos);                                            //����ꂽ���W�l��ۑ�����i�X�C�b�`�̐؂�ւ����ɕK�v������j
}
//��������//-----------------------------------------------------------------------------
Senpuki::~Senpuki()                                                //�f�X�g���N�^�@�����݂͉�������܂���
{

}
//��������//-----------------------------------------------------------------------------

bool Senpuki::Initialize(Vec2 pos)
{
	objectTag = "Senpuuki";                 //�I�u�W�F�N�g�^�O���𐶐�����

	//�����蔻��̋�`��p�ӂ���
	CreateObject(Objform::Cube, pos, Vec2(IMAGE_SIZE_X, IMAGE_SIZE_Y), 0);								//�����蔻���`�𐶐�����
	cout << "������W(" << position.x + IMAGE_SIZE_X << "," << position.y + IMAGE_SIZE_Y << endl;		//�f�o�b�O�@�\�ł̓����蔻��̕\��
	//
	Water_flag = false;						//�����蔻�菉���t���O�̐ݒ�
	CheakHit();								//�����蔻����s��
	Switch_Swap();                          //�X�C�b�`�̐؂�ւ��t���O�ɂ���č��W�l�̍Đݒ�����܂��B
	return true;
}
//��������//-----------------------------------------------------------------------------
void Senpuki::UpDate()
{

}
//��������//-----------------------------------------------------------------------------
void Senpuki::Finalize()
{
	parent = nullptr;
	switch_pointa = nullptr;
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
		if (o_.objectTag == "Water")                                 //Player�̓����蔻��i�{���͐��Ŕ�������j
		{
			this->Water_flag = true;                                 //flag��true�ɂ���

			if (Water_flag)                                          //���ƐڐG���肵����E�E�E
			{
				if (((Water&)o_).GetState() == Water::State::GAS)      //�����C�̏�ԂȂ�΁E�E�E
				{
					const_cast<Object&>(o_).position = Water_Move((Water&)o_);      //const���O����Vec2�̓�����n��
				}
			}
		}
		else
		{
			this->Water_flag = false;
		}
	};
}
bool Senpuki::HasParent()const                                       //nullptr�ł͂Ȃ����m�F����֐�
{
	return parent != nullptr;
}
void Senpuki::SetParent(Switch* obj)                                 //�����蔻��ɕK�v�ȃI�u�W�F�N�g��(Switch*)�ɑ������
{
	switch_pointa = obj;
}
void Senpuki::SetParent(Object* obj)                                 //�����蔻��ɕK�v�ȃI�u�W�F�N�g�̃A�h���X�l���i�[����
{
	parent = obj;
}
Vec2 Senpuki::Switch_On_or_Off_pos(const Vec2 pos)                   //��@��؂�ւ���Ƃ��ɍ��W�l���؂�ւ���֐�
{
	return position = pos;
}
void Senpuki::Set_Pos(const Vec2 pos)
{
	Pos.push_back(pos);
}
void Senpuki::Switch_Swap()
{
	//_____________________________________________________________________________________________|//
	//|                                                                                            |//
	//|�X�C�b�`�̐؂�ւ��t���O�ɂ���č��W�l�����ւ��鏈���ł��B                                |//
	//|���W�l�ɂ��Ă�vector�ŕۑ������z��ɂ���Ēl�����Ă��܂��B                              |//
	//|�Ȃ̂ŁA���݂ł�Task_Game�̂Ƃ���ō��W�l��vector�ɓ��������ɂȂ�܂��B                   |//
	//|____________________________________________________________________________________________|//

	if (!switch_pointa->switch_ON_OFF)                                 //�X�C�b�`�̐؂�ւ��t���O��true�̎�
	{
		Switch_On_or_Off_pos(Pos[0]);                                  //�����蔻��̍��W�l��ύX���� ��̍��W�l
	}
	else
	{
		Switch_On_or_Off_pos(Pos[1]);                                  //�����蔻��̍��W�l��ύX���� ���̍��W�l
	}
	cout << this->position.x << " , " << this->position.y << endl;     //�ύX�������W�l�̏o�͂���
}
Vec2 Senpuki::Water_Move(Water& o_)
{
	if (Water_flag)                               //���֌W�̓����蔻��t���O��ture�Ȃ�E�E�E
	{
		if (o_.GetState() == Water::State::GAS)       //�����C�Ȃ�΁E�E�E
		{
			o_.position.x++;                          //x���W�̈ړ�������
		}
	}
	return o_.position;
}
template<typename T>
T& Senpuki::const_off(T& obj)
{
	return const_cast<T&>(obj);
}
//|__________________________________________________________________________________|//
//|�������@                                                                          |//
//|                                                                                  |//
//|�E�X�C�b�`�𕡐������蔻��Ώۂɂ��邱��                                          |//
//|�E���̈ړ��i�A�N�Z�X������@�ɋ��)                                               |//
//|�E���𔭐������i�ǂ܂ŕ��𑗂�j                                                |//
//|__________________________________________________________________________________|//