#include "Seihyouki.h"

const int Map_Size = 64;    //�����蔻���`�̃T�C�Y
const int COLDMAX = 30;     //�X�ɂȂ�܂ł̎���
const int COLDSPPED = 2;    //���X�@�̃p���[

//��������//---------------------------------------------------------
Seihyouki::Seihyouki()
{

}
//��������//---------------------------------------------------------
Seihyouki::Seihyouki(Vec2 pos)
{
	Pos.push_back(pos);              //vector�ɍ��W�l��ǉ�����
}
//��������//---------------------------------------------------------
Seihyouki::~Seihyouki()
{

}
//��������//---------------------------------------------------------
void Seihyouki::Initialize()
{
	coldCount = 0;                    //���X�@�J�E���^��0�N���A����
	hitBace.CreateObject(Objform::Cube, Pos[0], Vec2(Map_Size, Map_Size), 0);                         //�����蔻���`�𐶐�����
	hitBace.objectTag = "Seihyouki";
	CheakHit();                       //�����蔻�菈��������
}
//�ǉ��֐�//---------------------------------------------------------
void Seihyouki::CheakHit()
{
	hitBace.CollisionProcess = [&](const Object& o_)
	{
		if (o_.objectTag == "Water")           //���̃I�u�W�F�N�g�͐��ł��邩�H
		{
			if (((Water&)o_).GetState() == Water::State::LIQUID)
			{
				coldCount += COLDSPPED;        //���X�ɉt�̂𓀂点�Ă���
				if (coldCount >= COLDMAX)      //�t�̂��X�ɂȂ�����
				{
					((Water&)o_).SetState(Water::State::SOLID);         //state��ύX
					coldCount = 0;                                      //�J�E���^�����ɖ߂�
				}
			}
		}
	};
}
//�ǉ��֐�//---------------------------------------------------------
void Seihyouki::Input_Pos(Vec2 pos)
{
	Pos.push_back(pos);                //vector�Ɉ����̍��W�l��ǉ�����
}