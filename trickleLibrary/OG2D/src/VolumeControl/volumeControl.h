#pragma once
#include "OGSystem\OGsystem.h"


class VolumeControl :public Sound
{
	Vec2* playerPos;        //���g(�v���C���[�̈ʒu)
	Vec2 soundPos;          //�����̈ʒu
	float distance;         //�����ƃv���C���̒�������
	float maxdis;
	float maxvol;
public:
	VolumeControl();
	~VolumeControl();
	float GetDistance(Vec2 soundpos);      //�����ƃv���C���Ƃ̋��������߂�
	float VolSet();                        //���ʂ������ɂ���ĕύX������
	void GetPlPos();                       //�v���C���̈ʒu�����߂�
	void Play(Vec2 pos,float maxDis,float maxVol,Sound&sound);
};