#include "Switch.h"
using namespace std;
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
bool Switch::Initlaize(Vec2 pos)           //�����������@�����蔻��E��`�̐����E�t���O�̏�����
{
	CreateObject(Objform::Cube, pos, Vec2(IMAGE_SIZE_X, IMAGE_SIZE_Y), 0);                                    //�����蔻���`�𐶐�����
	CheakHit();                            //�����蔻��֐����Ăяo��
	return true;                           //�֐����������ɏI���������Ƃ�true�ŕԂ�
}
//��������//-----------------------------------------------------------------------------
void Switch::UpDate()                      //�X�V����                      
{
	CheakHit();                            //�����蔻��̏������܂Ƃ߂��֐�
}
//��������//-----------------------------------------------------------------------------
void Switch::Finalize()                    //�������
{
	
}
//��������//-----------------------------------------------------------------------------
void Switch::Render()                      //�`�揈��
{
	
}
//�ǉ��ϐ�//-----------------------------------------------------------------------------
void Switch::CheakHit()                                 //�����蔻��̏������܂Ƃ߂��֐�
{	
	Object::CollisionProcess = [&](const Object& o_)                                                          //�����蔻�菈��                
	{
		cout << "�����_��" << endl;
		if (player_pointa->hit(*this))                       //Player�Ƃ̐ڐG���肪��������E�E�E                                                               
		{
			cout << "�ڐG����" << endl;                      //�o�͂���
			Hitflag = true;                                  //�����蔻��t���O��true
		}
		else                                                 //Player�ł͂Ȃ������ꍇ�E�E�E
		{
			cout << "�ڐG�Ȃ��@�X�C�b�`" << endl;            //�o��
			Hitflag = false;                                 //�����蔻��t���O��false
		}
		if (Hitflag)                                         //�����蔻��t���O��true�Ȃ�E�E�E
		{
			if (Input::KeyInputDown(Input::S))                    //���L�[�{�[�h����wS�x�����ꂽ��E�E�E
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
