#include "Senpuki.h"

using namespace std;

//11�Ԕz�u���W(����̂͏�)

const int IMAGE_SIZE_X = 64;                                       //�摜�T�C�Y_X
const int IMAGE_SIZE_Y = 64;                                       //�摜�T�C�Y_Y

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
	Wall_flag = false;                      //�ǂƂ̓����蔻��t���O�̐ݒ�
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
	parent_Wall = nullptr;
	for (int i = 0; i < 2; ++i)              //Switch�̐��ɂ���ă��[�v�񐔂�ω�������
	{
		switch_pointa[i] = nullptr;          //���݂���Switch�̕���nullptr�Ƃ��ĕԂ�
	}
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
		if (o_.objectTag == "Water")                                 //��@�̓����蔻��i�{���͐��Ŕ�������j
		{
			this->Water_flag = true;                                 //flag��true�ɂ���

			if (Water_flag)                                          //���ƐڐG���肵����E�E�E
			{
				cout << "�쓮" << endl;
				if (((Water&)o_).GetState() == Water::State::GAS)      //�����C�̏�ԂȂ�΁E�E�E
				{
					const_cast<Object&>(o_).position = Water_Move((Water&)o_);      //const���O����Vec2�̓�����n��
				}
			}
		}
		else
		{
			this->Water_flag = false;                               //���̃I�u�W�F�N�g�ł͐��Ƃ̓����蔻��t���O��false�ɂ���
		}
	};
}
bool Senpuki::HasParent()const                                      //nullptr�ł͂Ȃ����m�F����֐�
{
	return parent_Wall != nullptr;
}
void Senpuki::SetParent(Switch* obj, int value)                     //�����蔻��ɕK�v�ȃI�u�W�F�N�g��(Switch*)�ɑ������
{
	switch_pointa[value] = obj;
}
void Senpuki::SetParent(Object* obj)                                 //�����蔻��ɕK�v�ȃI�u�W�F�N�g�̃A�h���X�l���i�[����
{

}
void Senpuki::SetParent(Map* obj)
{
	parent_Wall = obj;                                               //�����蔻��ɕK�v�ȃI�u�W�F�N�g�̃A�h���X�l���i�[����
}
Vec2 Senpuki::Switch_On_or_Off_pos(const Vec2 pos)                   //��@��؂�ւ���Ƃ��ɍ��W�l���؂�ւ���֐�
{
	return position = pos;                                           //�؂�ւ��鎞��Vec2�Ŗ߂�l��n��
}
void Senpuki::Set_Pos(const Vec2 pos)
{
	Pos.push_back(pos);                                              //���W�l��Vector�ɓn��
}
void Senpuki::Switch_Swap(Switch& s_)
{
	//_____________________________________________________________________________________________|//
	//|                                                                                            |//
	//|�X�C�b�`�̐؂�ւ��t���O�ɂ���č��W�l�����ւ��鏈���ł��B                                |//
	//|���W�l�ɂ��Ă�vector�ŕۑ������z��ɂ���Ēl�����Ă��܂��B                              |//
	//|�Ȃ̂ŁA���݂ł�Task_Game�̂Ƃ���ō��W�l��vector�ɓ��������ɂȂ�܂��B                   |//
	//|____________________________________________________________________________________________|//
	if (!s_.switch_ON_OFF)                              //�X�C�b�`�̐؂�ւ��t���O��true�̎�
	{
		Switch_On_or_Off_pos(Pos[0]);                                  //�����蔻��̍��W�l��ύX���� ��̍��W�l
	}
	else
	{
		Switch_On_or_Off_pos(Pos[1]);                                  //�����蔻��̍��W�l��ύX���� ���̍��W�l
	}
}
Vec2 Senpuki::Water_Move(Object& o_)
{
	if (Water_flag)                               //���֌W�̓����蔻��t���O��ture�Ȃ�E�E�E
	{
		if (((Water&)o_).GetState() == Water::State::GAS)       //�����C�Ȃ�΁E�E�E
		{
			while (Wall_flag == false)                           //�ǂƂ̓����蔻��t���O��true�ɂȂ�܂�
			{
				o_.position.x++;                                 //x���W�̈ړ�������
				for (int y = 0; y < parent_Wall->mapSize.y; ++y) //�}�b�v��y�l�̒l�܂Ń��[�v�ϐ�y�𑝉�
				{
					for (int x = 0; x < parent_Wall->mapSize.x; ++x) //�}�b�v��x�l�܂Ń��[�v�ϐ�x�𑝉�
					{
						if (parent_Wall->hitBase[y][x].objectTag == "Floor") //�}�b�v�̃I�u�W�F�N�g�^�O�����Ȃ�΁E�E�E
						{
							if (parent_Wall->MapHitCheck(o_))        //�}�b�v�Ɛ��̓����蔻��֐����Ăяo��
							{
								Wall_flag = true;                    //�ڐG��������true��Ԃ�
								cout << "�ڐG����" << endl;          //�������m�F������o��
								break;                               //for���𔲂��o��
							}
						}
					}
					break;              //for���𔲂��o��
				}
				break;        //while���𔲂��o��
			}
		}
		Wall_flag = false;    //�����C�ȊO�͂��ׂ�false�ɂ���
	}
	return o_.position;       //�ύX�����x�N�g����Ԃ�
}
