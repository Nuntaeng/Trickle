#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class FrameTimeUI : public GameObject, public TaskObject 
{
	typedef std::shared_ptr<FrameTimeUI> SP;
	//�^�X�N�֘A
	std::string taskName;
	bool Finalize();
	void UpDate();
	void Render2D();


	//�摜�֘A
	Texture image;
	const Box2D Src = { 0,0,64,128 };
	int digitSelectnumber;				//���̐����ɂ���ĕ`��ɕω����N����
	int randomSelectnumber;				//�h�������[�����͂�����ŕ`�悷��
	//�摜�֘A�@�傫��
	int  ScaleanimetionCnt;				//��u�����傫����ς���A�j���[�V�����J�E���g
	bool Scaleanimeflag;				//�傫���ω��������t���O

	//��{�̏��
	struct Time
	{
		int outputtime[4];				//�S�[���^�C���̊i�[
		int Inputtime;					//�z��֓���邽�߂̃^�C��

		void InitTime();							//���Ԃ�ݒ�
		void SetTime();								//�z��ɑ������
		int GetMinutes();							//����Ԃ�
		int GetSecond();							//�b��Ԃ�

	private:
		int minutes;					//��
		int second;						//�b
		size_t digit;					//�����̌���
		std::string tostringtime;		//�����̌������v�Z����̂ɕK�v

		std::string Set_toString(int&);				//�����̐�����String�Ƃ��đ������
		void SetDigitLength(std::string&);			//�����̌������o�͂���
		int toInt(std::string&, int loop);			//string�^�@�ˁ@Int�^�ɂ��Ĉꕶ���������o���Ĕz��ɑ���@
		int toSecond();								//�b�̌v�Z
		int toMinutes();							//���̌v�Z
	};
	
	//�h�������[���֘A
	int Random();					//�����_���̒l��Ԃ�
	void ResetMoveCnt();			//�A�j���[�V�����J�E���g�����Z�b�g����
	void ResetMoveCnt(int& moveCnt);//�^�[�Q�b�g�̃J�E���g�����Z�b�g����
	void ResetDramRollisPlay();		//�t���O�̃��Z�b�g������
	void DramRoll(int time);		//�h�������[��
	bool MoveCntJudge(int& moveCnt,int time);	//���̎��Ԃ��o������true�ŏI��
	int  moveCnt;					//�h�������[���A�j���[�V�����J�E���g
	bool dramrollisPlay;			//���h�������[�������ǂ����H


	//Easing�֘A
	FrameTimeUI::Time goaltime;	//�S�[���^�C��
	Easing easingX;				//X���W��Easing
	Vec2 PrePos;				//�ۑ����Ă������W�l
	bool easingEnd;				//Easing���I����������Ԃ�
	

public:
	static FrameTimeUI::SP Create(Vec2& pos,int digitSelect,int& resulttime,bool = true);
	bool Initialize(Vec2& pos,int digitSelect,int& resulttime);
	FrameTimeUI();
	virtual ~FrameTimeUI();

	//Easing�֘A
	bool GetEasingEnd();

	//�h�������[���֘A
	bool GetDramRollIsPlay();
};