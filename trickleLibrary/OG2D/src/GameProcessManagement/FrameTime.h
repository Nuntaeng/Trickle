#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class FrameTimeUI : public GameObject, public TaskObject 
{
	typedef std::shared_ptr<FrameTimeUI> SP;
	//�^�X�N�֘A
	std::string taskName;

	//�摜�֘A
	Texture image;
	const Box2D Src = { 0,0,64,128 };

	//��{�̏��
	int getframetime;
	std::vector<int> frametime;
	int digitnumberLength;
	int digitSelectnumber;
	bool active;
	const int N = 10;		//1�̈ʂ��Ƃɐ��l������ݒ�
	
	

	bool Finalize();
	void UpDate();
	void Render2D();
	void SetFrameTime();
	void SetVector();

	int  SetDigitNumber();		//�t���[���^�C���̌�������͂���
	void DigitNumberReset();	//�t���[���^�C���̌��������Z�b�g����
	int  GetDigitNumber();		//�t���[���^�C���̌�����Ԃ�
	void TargetTime();			//�^�[�Q�b�g�̃^�C����������

	//Easing�֘A
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
};