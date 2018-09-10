#pragma once
//�K�v�ǂݍ��݃t�@�C��
#include "OGSystem\OGsystem.h"
#include "GameProcessManagement/Timer.h"
#include "../OGSystem/Easing/easing.hpp"

class Result :public TaskObject {
public:
	std::string taskName;
	typedef std::shared_ptr<Result> SP;
	static Result::SP Create(bool flag = true);
	Result();
	~Result();

	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();

	//�T�E���h�̐���
	Sound sound;
	Sound soundstar;
	Sound sounddrum;

	//�G�t�F�N�g�̃J�E���g
	int effCounter;

private:
	enum Mode {
		Non,
		Mode1,		//�v���C���AResultUI�o�������~�܂�
		Mode2,		//TIME�A���̘g�o�������~�܂�
		Mode3,		//�h�������[������N���A�^�C���̕\���܂�
		Mode4,		//���o������͂܂�܂�
		Mode5,		//�v���C����сACLEARUI�o�������~�܂�
		Mode6,		//�v���C���ޏ�A�I��
		Mode7,		//�ޏ��ł����Ǝ��ԕ\�����Ƃǂ܂点�Ă���
	};
	Mode nowMode;

	Texture backTex;
	//Texture resultTex;
	Texture frameTex;
	//Texture timeTex;
	//Texture starFrameTex;
	Texture starTex;
	Texture clearTex;
	Texture fontui;			//���A�{�Ԃŏ���
	Texture numberui;
	Texture stareffectTex;
	//�Ԃт�̃G�t�F�N�g
	Texture petalTex1;
	Texture petalTex2;
	Texture petalTex3;
	Texture petalTex4;
	Texture petalTex5;

	//�T�E���h�̃t�@�C�����i�[
	std::string soundname;
	std::string starsoundname;
	std::string drumsoundname;

	struct resultUI {
		Vec2 pos;
		Vec2 nowWH;
		Vec2 preWH;
		Easing easeX;
		Easing easeY;
		Easing easeW;
		Easing easeH;
		float bezcnt;
		int angle;
	};
	resultUI frame;
	resultUI result;
	resultUI time;
	resultUI number[4];
	resultUI starFrame[3];
	resultUI star[3];
	resultUI clear;


	int cnt;
	int num[4];
	bool starFlag[3];
	bool starturn[3];
	bool effectStarFlag[3];			//���G�t�F�N�g���o�͂������ǂ����̃t���O
	float starAngle;

	int petalRate;

	unsigned timer[4];
	int test1, test2;
	__int8 maxTrueNumber;
	void RoadData();
};

//class Result : public TaskObject
//{
//	//-------------------------------------------
//	//�e���Ő��삷��Ƃ��Ɏg�p������̂͂����ɋL�q����
//	//-------------------------------------------
//public:
//	/*
//	�A�h���X���������܂�
//	�������@Timer �A�h���X�l���󂯌p��
//	���߂�@�Ȃ�
//	*/
//	enum CreateFlag
//	{
//		NON = 0,			//�S�Ă𐶐�����
//		Timeui =  1 << 0,	//�^�C��UI�̕\��
//		Starui =  1 << 1,	//���̕\��
//		Effect =  1 << 2,	//����Effect
//		Clearui = 1 << 3,	//�N���AUI�̕\��
//	};
//private:
//	//�S�[���֘A
//	void Result_DataInput();
//
//	//UI�̏o���ɂ���
//	void UI_Think();
//	void UI_Create();					//�t���O�ɂ���Đ���������
//
//	//���̑��̊֐�
//	int  to_String(std::string&);
//
//private:
//	struct CreateTask
//	{
//		int createflag;						//���������t���O
//		int nextflag;						//���ɐ�������t���O
//		void SetCreateFlag(CreateFlag);
//		void SetNextFlag(CreateFlag);
//		void ResetCreateFlag();
//		void ResetNextFlag();
//	};
//	CreateTask createtask;
//
//
//	int Flag;
//	int FrameTime;				//���ʃ^�C�����i�[����
//
//	//���ʂ̍ۂɕK�v�ȃ|�C���^�@�܂��́@�t�@�C���̓ǂݍ���
//
//
//	//�t�@�C���̏o��
//	const char* TimeFilePath = "./data/Result/Result.dat";
//
//	//�摜�֘A
//	Texture image;
//	const Box2D backSrc = { 0,0,1280,720 };
//	Texture maptile;
//	const Box2D maptileSrc = { 0,0,256,256 };
//	//------------------
//	//�Œ艻����Ă��鏈��
//	//------------------
//
//public:
//	std::string taskName;
//	virtual ~Result();
//	typedef std::shared_ptr<Result> SP;
//	static Result::SP Create(bool = true);
//	Result();
//	//-------------
//	//�ύX���Ȃ�����
//	//-------------
//	bool Initialize();		//����������
//	void UpDate();			//�X�V����
//	void Render2D();		//�`�揈��
//	bool Finalize();		//�������
//
//	//���̃N���X�Ŏg�p����
//	int GetFlag();
//};