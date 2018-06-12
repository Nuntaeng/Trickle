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

	enum Achievement
	{
		Flag1 = 1 << 0,		//�t���O1
		Flag2 = 1 << 1,		//�t���O2
		Flag3 = 1 << 2,		//�t���O3
		Flag4 = 1 << 3,		//�t���O4
		Master = 0x0F,		//�S�Ẵt���O
	};
	enum CreateFlag
	{
		NON = 0,			//�S�Ă𐶐�����
		Timeui =  1 << 0,	//�^�C��UI�̕\��
		Starui =  1 << 1,	//���̕\��
		Effect =  1 << 2,	//����Effect
		Clearui = 1 << 3,	//�N���AUI�̕\��
	};

	//�t���O�֘A
	void Flag_Input(Achievement);
	int  Get_Flag();
	void Flag_Judge();
	bool Flag_Judge(Achievement, Achievement);
	bool Flag_Judge(Achievement, Achievement, Achievement);
	void Flag_Judge_Clear();

	//�S�[���̃^�C���֘A
	int  GetFrameTime();
	void Result_DataInput();

	//UI�̏o���ɂ���
	void UI_Think();
	void UI_Create();					//�t���O�ɂ���Đ���������


private:
	struct CreateTask
	{
		int createflag;						//���������t���O
		int nextflag;						//���ɐ�������t���O
		void SetCreateFlag(CreateFlag);
		void SetNextFlag(CreateFlag);
		void ResetCreateFlag();
		void ResetNextFlag();
	};
	CreateTask createtask;
	int Flag;
	int FrameTime;				//���ʃ^�C�����i�[����

	//���ʂ̍ۂɕK�v�ȃ|�C���^�@�܂��́@�t�@�C���̓ǂݍ���


	//�t�@�C���̏o��
	const char* TimeFilePath = "./data/Result/Result.dat";

	//�摜�֘A
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