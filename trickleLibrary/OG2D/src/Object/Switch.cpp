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
void Switch::Initlaize()
{
	for (int i = 0; i < 2; ++i)                //�X�C�b�`�̐ݒu�����[�v������
	{
		switch_ON_OFF[i] = false;
		hitBace[i].CreateObject(Objform::Cube, Pos[i], Vec2(IMAGE_SIZE_X, IMAGE_SIZE_Y), 0);         //�����蔻���`�𐶐�����
	}
	CheakHit();
}
//��������//-----------------------------------------------------------------------------
void Switch::UpDate()                      //�X�V����                      
{

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
	hitBace[0].CollisionProcess = [&](const Object& o_)                                                          //�����蔻�菈��                
	{
		if (o_.objectTag == "PlayerFoot" || o_.objectTag == "PlayerLeft" || o_.objectTag == "PlayerRight")
		{
			if (gameEngine->in.down(Input::KeyBoard::Q))
			{
				if (switch_ON_OFF[0])
				{
					cout << "OFF" << endl;
					switch_ON_OFF[0] = false;
				}
				else
				{
					cout << "ON" << endl;
					switch_ON_OFF[0] = true;
				}
				((Senpuki&)o_).Switch_Swap(this, 0);
			}
		}
	};

	hitBace[1].CollisionProcess = [&](const Object& o_)                                                          //�����蔻�菈��                
	{
		if (o_.objectTag == "PlayerFoot" || o_.objectTag == "PlayerLeft" || o_.objectTag == "PlayerRight")
		{
			if (gameEngine->in.down(Input::KeyBoard::Q))
			{
				if (switch_ON_OFF[1])
				{
					cout << "OFF" << endl;
					switch_ON_OFF[1] = false;
				}
				else
				{
					cout << "ON" << endl;
					switch_ON_OFF[1] = true;
				}
				((Senpuki&)o_).Switch_Swap(this, 1);
			}
		}
	};
}
void Switch::Set_Pos(const Vec2 pos)
{
	Pos.push_back(pos);                                 //�����̍��W�l��ǉ�����
}
