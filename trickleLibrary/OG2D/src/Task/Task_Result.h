#pragma once
#include "Object\Object.h"
#include "Win\WinMain.h"
#include "GameProcessManagement\Timer.h"


class Result
{
public:
	/*
	�R���X�g���N�^
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	Result();

	/*
	�f�X�g���N�^
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	~Result();

	/*
	���ɂȂ�
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	void Initialize();

	/*
	�^�X�N��J�ڂ��锻����Ƃ�
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	TaskFlag Update();

	/*
	���U���g��ʂ�`������܂�
	�������@�Ȃ�
	���߂�@�Q�[���̃^�X�N
	*/
	void Render();

	/*
	�g�p�����摜��������܂�
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	void Finalize();

	/*
	�A�h���X���������܂�
	�������@Timer �A�h���X�l���󂯌p��
	���߂�@�Ȃ�
	*/

	void Result_DataInput();

	enum Achievement
	{
		Flag1 = 1 << 0,		//�t���O1
		Flag2 = 1 << 1,		//�t���O2
		Flag3 = 1 << 2,		//�t���O3
		Flag4 = 1 << 3,		//�t���O4
	};
	void Flag_Input(Achievement);
	int Get_Flag();
	//�t���O�̃`�F�b�N
	bool Flag_Judge();
	bool Flag_Judge(Achievement, Achievement);
	bool Flag_Judge(Achievement, Achievement, Achievement);

	void Flag_Judge_Clear();
private:
	Texture image;


	const std::string _FilePath = "";

	int Flag;

	//���ʂ̍ۂɕK�v�ȃ|�C���^�@�܂��́@�t�@�C���̓ǂݍ���
	const char* TimeFilePath = "./data/Result/Result.dat";
};