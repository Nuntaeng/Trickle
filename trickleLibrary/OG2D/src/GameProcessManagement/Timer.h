#pragma once
#include "Object\Object.h"
#include <iostream>

//__________________________
//|                      //|
//|�����@2018/04/14 ���� //|
//|�����@2018/04/15 ���� //|
//|______________________//|

class Timer : public Object
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

private:
	int frame_time;                                //�t���[�����Ԃ��i�[����
	int frame_time_hours;                          //�Z����
	int frame_time_min;                            //�Z��
	int frame_time_sec;                            //�Z�b

	//�~���b�͖������@1�b�@=�@1000�~���b  4��23�b17�݂��������ɂ�����������E�E�E�������܂�
private:
	/*
	�^�C�}�[�̎��Ԃ��R�}���h�v�����v�g�ɏo�͂���
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	void Instrumentation_output();
};