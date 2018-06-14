#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

#include "Task\Task_Result.h"
class FlagUI : public GameObject, public TaskObject
{
public:
	
private:
	//�t���O�֘A
	int Resultflag;
	int targetflag;
	bool flagactive;

	//Easing�֘A
	//Vec2 PrePos;
	//Easing easingX;


	//�摜�֘A
	Texture image[2];
	const Box2D Src = Box2D(0, 0, 78, 79);
	bool effectEnd;

	//�g��@�\
	bool isScaleed;
	Vec2  Center;			//�`�撆���Œ���W
	Vec2  ReSize;			//�V�������T�C�Y����Scale
	Vec2  ScaleVolume;		//�g�嗦
	Vec2  PreSize;			//�O��̃f�[�^������Ă���
	Vec2  PrePos;			//�`�撲���p

	//���̃N���X�֑��邽�ߕϐ�
	Vec2  SendPos;			//Effect�̈ʒu�����߂�
	
private:
	//�t���O�֌W
	void SetResultflag();
	void FalgJudge(int);

	//�g��@�\
	void MoveVolume();		  //�g�嗦���������㏸�����Ă����܂�
	void ResetVolume();	      //�g�嗦���グ�邽�߂̏��������s��
	void ResetCenter();		  //�����l�̍Čv�Z�����܂��i1�t���[���Ōv�Z�����ďI���������邱�Ɓj

	//���̃N���X�փf�[�^����֐��ւ̏���������֐�
	void SetSendPos(Box2D&);  //Draw��Pos���G�t�F�N�g�Ɠ����ɂ���
public:
	std::string taskName;
	virtual ~FlagUI();
	typedef std::shared_ptr<FlagUI> SP;
	static FlagUI::SP Create(Vec2& pos,int targetflag,bool = true);
	FlagUI();
	//-------------
	//�ύX���Ȃ�����
	//-------------
	bool Initialize(Vec2& pos,int&);//����������
	void UpDate();					//�X�V����
	void Render2D();				//�`�揈��
	bool Finalize();				//�������

	//���U���g�^�X�N�Ŏg�p����֐�
	bool GetEffectEnd();			//�G�t�F�N�g���o���I��������𔻒肵�܂�

	//�G�t�F�N�g�ɕK�v�Ȋ֐�
	bool GetFlag();					//�t���O��Ԃ�
	bool is_Scale();				//�g�傪�I����������Ԃ�
	void SetEffectEnd();			//�G�t�F�N�g���I��������G�t�F�N�g�̕��ŕύX������
	Vec2 GetPos();					//�G�t�F�N�g�̐������ɑ���Pos
};