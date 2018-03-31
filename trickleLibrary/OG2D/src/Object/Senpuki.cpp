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
	Switch_Hitflag = false;                 //�ŏ��͏�̐�@�������Ă�����
	CheakHit();								//�����蔻����s��
	return true;
}
//��������//-----------------------------------------------------------------------------
void Senpuki::UpDate()
{
	if (Switch_Hitflag)                     //�X�C�b�`�Ƃ̓����蔻�肪����Ƃ��E�E�E
	{
		cout << "�X�C�b�`�ƐڐG��" << endl;
	}
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
		//cout << "�����_���̏������Ȃ�" << endl;                      //�o��
		if (o_.objectTag == "Water")                                 //Player�̓����蔻��i�{���͐��Ŕ�������j
		{
			this->Water_flag = true;                                 //flag��true�ɂ���
			//cout << "�������Ă��܂�" << endl;                        //�o��
			if (Water_flag)                                          //���ƐڐG���肵����E�E�E
			{
				if (((Water&)o_).GetState() == Water::State::GAS)    //�����C�̏�ԂȂ�΁E�E�E
				{
					//cout << "���������܂�" << endl;
				}
				if (((Water&)o_).GetState() == Water::State::LIQUID) //�t�̂̏�ԂȂ�΁E�E�E
				{
					
				}
			}
		}
		else
		{
			this->Water_flag = false;
		}

		//_____________________________________________________________________________________________|//
		//|                                                                                            |//
		//|��@��Switch�Ƃ̓����蔻�菈�����e�I�u�W�F�N�g�^�O���g�p���Ăł̓����蔻����̗p���܂����B|//
		//|����t���O�������Ȃ�ꍇ��int�^�ł�flag�𗘗p���ăr�b�g���Z�ōs���\��ł��B                 |//
		//|____________________________________________________________________________________________|//
		if (o_.objectTag == "Switch")              //objectTag��Switch��������E�E�E
		{
			this->Switch_Hitflag = true;           //true�ɂ��ĉ��̃{�^���ɐ؂�ւ���
		}
		else
		{
			this->Switch_Hitflag = false;          //�X�C�b�`�ł͂Ȃ��ꍇ��false��Ԃ�
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
Vec2 Senpuki::Switch_On_or_Off_pos(const Vec2 pos)                   //��@��؂�ւ���Ƃ��ɍ��W�l���؂�ւ���֐���
{
	return position = pos;
}


//|__________________________________________________________________________________|//
//|�������@                                                                          |//
//|�E�X�C�b�`�̏����󂯎���ăX�C�b�`�̐؂�ւ������Ɛ�@���؂�ւ�鏈�������s��|//
//|                                                                                  |//
//|__________________________________________________________________________________|//