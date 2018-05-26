#pragma once
//�K�v�ǂݍ��݃t�@�C��
#include "OGSystem\OGsystem.h"

class Result : public TaskObject
{
	//-------------------------------------------
	//�e���Ő��삷��Ƃ��Ɏg�p������̂͂����ɋL�q����
	//-------------------------------------------
public:
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
	int GetFrameTime();
	int GetDigitTime();
private:
	int Flag;
	int FrameTime;				//���ʃ^�C�����i�[����
	int outputdigit;			//�^�C��UI�ɏo�͂���������
	//���ʂ̍ۂɕK�v�ȃ|�C���^�@�܂��́@�t�@�C���̓ǂݍ���
	const char* TimeFilePath = "./data/Result/Result.dat";
	Texture image;
	const Box2D backSrc = { 0,0,1280,720 };
	Texture maptile;
	const Box2D maptileSrc = { 0,0,256,256 };
	//------------------
	//�Œ艻����Ă��鏈��
	//------------------
public:
	std::string taskName;
	virtual ~Result();
	typedef std::shared_ptr<Result> SP;
	static Result::SP Create(bool = true);
	Result();
	//-------------
	//�ύX���Ȃ�����
	//-------------
	bool Initialize();		//����������
	void UpDate();			//�X�V����
	void Render2D();		//�`�揈��
	bool Finalize();		//�������
};