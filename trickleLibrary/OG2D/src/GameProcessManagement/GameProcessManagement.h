#pragma once
//__________________________
//|                      //|
//|�����@2018/04/14 ���� //|
//|�����@2018/04/19 ���� //|
//|______________________//|
#include "Object\Object.h"
#include <vector>
#include <iostream>
//�֘A����v���W�F�N�g//
#include "Goal\Goal.h"
#include "Timer.h"
#include "Win\WinMain.h" //�^�X�N�̑J�ڂɕK�v

class Goal;

class GameProcessManagement : public  Object
{
public:
	/*
	�R���X�g���N�^���Ăяo��
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	explicit GameProcessManagement();


	/*
	�f�X�g���N�^���Ăяo��
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	virtual ~GameProcessManagement();


	/*
	�t���O�̏������E�Q�[���p�̃^�C��������������
	������  �Ȃ�
	���߂�@�Ȃ�
	*/
	void Initialize();


	/*
	1�t���[�����ƂɊ֐����Ăяo���֐�
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	void Update();    


	/*
	�S�[���I�u�W�F�N�g�̒ǉ������܂�
	�������@Object*�@�ǉ��������S�[���I�u�W�F�N�g
	���߂�@�Ȃ�
	*/
	void Set_Goal(Object*);


	/*
	�S�[���̔�����s���܂�
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	void Goal_Check();


	/*
	�Q�[���̃t���O�ɂ���ĕω�����C�x���g�Ǘ��֐�
	�������@�Ȃ�
	���߂�@�Q�[���t���O��Ԃ�
	*/
	TaskFlag Goal_Event();

private:

	bool gameclear_flag;               //�l�X�ȃt���O���i�[����
	std::vector<Object*>goals;         //�S�[����������Vector
	Timer timer;                       //�^�C�}�[�̃Z�b�g������
};