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

	void Timer_Input();
private:
	Texture image;
	

	const std::string _FilePath = "";

	int Flag;

	enum Achievement
	{
		Goal  = 1,		//�S�[�����Ă���
		Color = 2,		//�J���[
	};

	//���ʂ̍ۂɕK�v�ȃ|�C���^�@�܂��́@�t�@�C���̓ǂݍ���
	FILE* file;			//�t�@�C����ǂݍ��ݗp
	const char* TimeFilePath = "./data/Result.dat";
};