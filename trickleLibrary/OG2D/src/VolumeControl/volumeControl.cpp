#include "VolumeControl\volumeControl.h"
#include "Player\Player.h"
#include <math.h>

VolumeControl::VolumeControl()
{
	this->distance = 0.0f;
	this->playerPos = nullptr;
	this->soundPos = Vec2(0, 0);
	//std::cout << "�{�����[�����߃N���X����" << std::endl;
}
VolumeControl::~VolumeControl()
{
	//std::cout << "�{�����[�����߃N���X���" << std::endl;
	if (this->playerPos)
	{
		delete this->playerPos;
	}
}


//���������߂�
float VolumeControl::GetDistance(Vec2* soundpos)
{
	Vec2 hypotenuse;      //���������߂�ׂ̐��l���i�[�@hypotenuse�͎Εӂ̈�
	soundPos = *soundpos;       //�f�o�b�N�Œl�����₷�������������B�s�v�Ȃ�폜�\��
	if (this->playerPos)       //�v���C�������݂��Ă�����
	{
		//x��
		if (playerPos->x >= soundPos.x)
		{
			hypotenuse.x = playerPos->x - soundPos.x;
		}
		else
		{
			hypotenuse.x = soundPos.x - playerPos->x;
		}
		//y��
		if (playerPos->y >= soundPos.y)
		{
			hypotenuse.y = playerPos->y - soundPos.y;
		}
		else
		{
			hypotenuse.y = soundPos.y - playerPos->y;
		}
	}
	else                      //�v���C�������݂��Ă��Ȃ�������
	{
		hypotenuse = soundPos;
	}
	//�f�o�b�N�p
	//std::cout << sqrt(hypotenuse.x*hypotenuse.x + hypotenuse.y*hypotenuse.y) << std::endl;

	distance = sqrt(hypotenuse.x*hypotenuse.x + hypotenuse.y*hypotenuse.y);        //�������������߂�
	return distance;
}

//�����ɉ������{�����[����ݒ肷�邽�߂̐��l(0~1)���擾
float VolumeControl::VolSet()
{
	float changeVolDis;
	changeVolDis = this->maxdis / 10.0f;    //���ʂ��\�i�K�؂�ւ�
											//�����������قǉ��ʂ�������
	if (distance < changeVolDis*2.0f)
	{
		return 1.0f*maxvol;     //�ő剹��	
	}
	else if (distance < changeVolDis*3.0f)
	{
		return 0.9f*maxvol;
	}
	else if (distance < changeVolDis*4.0f)
	{
		return 0.8f*maxvol;
	}
	else if (distance < changeVolDis*5.0f)
	{
		return 0.7f*maxvol;
	}
	else if (distance < changeVolDis*6.0f)
	{
		return 0.6f*maxvol;
	}
	else if (distance < changeVolDis*7.0f)
	{
		return 0.5f*maxvol;
	}
	else if (distance < changeVolDis*8.0f)
	{
		return 0.4f*maxvol;
	}
	else if (distance < changeVolDis*9.0f)
	{
		return 0.3f*maxvol;
	}
	else if (distance < maxdis)
	{
		return 0.1f*maxvol;
	}
	//else if (distance < 1000)
	//{
	//	return 0.1f;
	//}
	else
	{
		return 0.0f;
	}
}

void VolumeControl::GetPlPos()
{
	auto player = OGge->GetTask<Player>("Player");
	if (playerPos)
	{
		delete this->playerPos;
	}
	if (player)         //�v���C�������݂��Ă�����	
	{
		this->playerPos = new Vec2(player->position);
	}
	//�v���C�������݂��Ă��Ȃ������珉���l�œ��ꂽnullptr���Ԃ�
}


void VolumeControl::Play(Vec2* pos, float maxDis, float maxVol, Sound& sound)    //�ő剹�ʂ��w��
{
	maxdis = maxDis;
	maxvol = maxVol;
	//�����ɂ���ĉ��ʂ�ς���
	this->GetPlPos();
	this->GetDistance(pos);
	sound.volume(this->VolSet());
}