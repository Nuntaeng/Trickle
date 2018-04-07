#include "Switch.h"
using namespace std;
typedef Input::KeyBoard It;                     //�N���X�̖��O��Ԃ̏ȗ�

const int IMAGE_SIZE_X = 64;                    //�摜�T�C�Y_X
const int IMAGE_SIZE_Y = 64;                    //�摜�T�C�Y_Y

const int POS_X = IMAGE_SIZE_X * 19;            //�������W�l�i���ݎg�p�͂��Ă��܂���j
const int POS_Y = IMAGE_SIZE_Y * 8;             //�������W�l�i���ݎg�p�͂��Ă܂���j

//��������//-----------------------------------------------------------------------------
Switch::Switch()                                //�R���X�g���N�^�i�����Ȃ��j                      
{

}
//��������//-----------------------------------------------------------------------------
Switch::Switch(Vec2 pos)                        //�R���X�g���N�^�iVec2�@�������W�l�j           
{
	position = pos;                             //�������W�l��Swicth�̍��W�l�ɑ������
	Pos.push_back(pos);                         //�����Ŏ󂯎�������W�l��vector�ɕۑ�����
}
//��������//-----------------------------------------------------------------------------
Switch::~Switch()                               //�f�X�g���N�^�@���݂͓��ɂȂ�
{
	
}
//��������//-----------------------------------------------------------------------------
bool Switch::Initlaize(Vec2 pos,Switch* s_)
{
	switch_pointa = s_;                           //switch_pointa�ɓ����蔻���`�𐶐����� 
	CreateObject(Objform::Cube, pos, Vec2(IMAGE_SIZE_X, IMAGE_SIZE_Y), 0);         //�����蔻���`�𐶐�����
	objectTag = "Switch";
	CheakHit(*switch_pointa);              //�����蔻��֐����Ăяo��
	return true;                           //�֐����������ɏI���������Ƃ�true�ŕԂ�
}
//��������//-----------------------------------------------------------------------------
void Switch::UpDate()                      //�X�V����                      
{

}
//��������//-----------------------------------------------------------------------------
void Switch::Finalize()                    //�������
{
	player_pointa = nullptr;
	senpuki_pointa = nullptr;
}
//��������//-----------------------------------------------------------------------------
void Switch::Render()                      //�`�揈��
{
	
}
//�ǉ��ϐ�//-----------------------------------------------------------------------------
void Switch::CheakHit(Switch& s_)                                 //�����蔻��̏������܂Ƃ߂��֐�
{	
	Object::CollisionProcess = [&](const Object& o_)                                                          //�����蔻�菈��                
	{
		if (player_pointa->hit(s_))                          //Player�Ƃ̐ڐG���肪��������E�E�E  //�G���[�ӏ�                                                             
		{
			Hitflag = true;                                  //�����蔻��t���O��true
		}
		else                                                 //Player�ł͂Ȃ������ꍇ�E�E�E
		{
			Hitflag = false;                                 //�����蔻��t���O��false
		}
		if (Hitflag)                                         //�����蔻��t���O��true�Ȃ�E�E�E
		{
			if (gameEngine->input.keyboard.down(It::Q))          //���L�[�{�[�h����wQ�x�����ꂽ��E�E�E
			{
				if (switch_ON_OFF)                                   //���̎��ɃX�C�b�`�̐؂�ւ��t���O��true�Ȃ�E�E�E
				{
					switch_ON_OFF = false;                               //�X�C�b�`�̐؂�ւ��t���O��false�ɂ���
					cout << "�X�C�b�`off" << endl;                       //�o��
				}
				else                                                 //false��������E�E�E
				{
					switch_ON_OFF = true;                                //�X�C�b�`�̐؂�ւ��t���O��true�ɂ���
					cout << "�X�C�b�`on" << endl;                        //�o��
				}
			}
			senpuki_pointa->Switch_Swap(*this);              //Switch�̏������ĎQ�Ƃ���
		}
	};
}

bool Switch::HasParent()const
{
	return player_pointa != nullptr;                    //Player*��nullptr�ɂȂ��Ă��Ȃ����H 
}

void Switch::SetParent(Player* player)
{
	player_pointa = player;                             //��������Player*�ɑ������
}

void Switch::SetParent(Senpuki* sen)
{
	senpuki_pointa = sen;                               //�����Ŏ󂯎�����A�h���X�l��senpuki_pointa�ɑ������
}

void Switch::Set_Pos(const Vec2 pos)
{
	Pos.push_back(pos);                                 //�����̍��W�l��ǉ�����
}
