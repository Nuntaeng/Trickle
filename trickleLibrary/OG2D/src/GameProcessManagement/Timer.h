#pragma once
#include "Object\Object.h"
#include "OGSystem\Timer\glTimer.h"
#include <iostream>

//__________________________
//|                      //|
//|�����@2018/04/14 ���� //|
//|�����@2018/04/15 ���� //|
//|�����@2018/04/19 ���� //|
//|�����@2018/04/26 ���� //|
//|______________________//|

class Timer : public Time
{
public:
	/*
	�R���X�g���N�^
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	Timer();


	/*
	�f�X�g���N�^
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	~Timer();


	/*
	�^�C�}�[�̃[���N���A������
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	void Initialize();


	/*
	�^�C�}�[�̊֐����܂Ƃ߂ČĂяo��
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	void Update();


	/*
	�^�C�}�[�̎��Ԃ�1�t���[���Âv������
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	void Instrumentation();

	/*
	�w�肵���^�C�}�[�̎��Ԃ��R�}���h�v�����v�g�ɏo�͂���
	�������@Timer& �o�͂������^�C�}�[
	���߂�@�Ȃ�
	*/
	void Instrumentation_output(Timer&);

	/*
	�^�C�}�[�̎��Ԃ��t���[�����ԂɊi�[����
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	void Frame_Set();

	int Get_frame();
private:
	int frame_time;                                //Time�N���X���玞�Ԃ��󂯎��֐�
};