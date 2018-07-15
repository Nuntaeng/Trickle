#pragma once
#include "OGSystem\OGsystem.h"


class VolumeControl :public Sound
{
	Vec2* playerPos;        //���g(�v���C���[�̈ʒu)
	Vec2 soundPos;          //�����̈ʒu
	float distance;         //�����ƃv���C���̒�������
	float maxdis;
	float maxvol;
	//�t�F�[�h�C���֘A�Ɏg�p����
	int timer;
	float fadeinBGM;
	float fadeoutBGM;
public:
	VolumeControl();
	~VolumeControl();
	float GetDistance(Vec2* soundpos);      //�����ƃv���C���Ƃ̋��������߂�
	float VolSet();                        //���ʂ������ɂ���ĕύX������
	void GetPlPos();                       //�v���C���̈ʒu�����߂�
	void Play(Vec2* pos, float maxDis, float maxVol, Sound&sound);
	float FadeIn(bool canControl);         //BGM�̃t�F�[�h�C��
	float FadeOut(bool canControl);        //BGM�̃t�F�[�h�A�E�g
};