#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class FrameTimeUI : public GameObject, public TaskObject 
{
	typedef std::shared_ptr<FrameTimeUI> SP;
	std::string taskName;
	Texture image;
	int getframetime;
	std::vector<int> frametime;
	int digitnumberLength;
	int digitSelectnumber;

	const Box2D Src = { 0,0,64,128 };
	const int N = 10;		//1�̈ʂ��Ƃɐ��l������ݒ�

	bool Finalize();
	void UpDate();
	void Render2D();
	void SetFrameTime();
	void SetVector();
	int  SetDigitNumber();		//�t���[���^�C���̌�������͂���
	void DigitNumberReset();	//�t���[���^�C���̌��������Z�b�g����
	int  GetDigitNumber();		//�t���[���^�C���̌�����Ԃ�
	int  GetResultFrameTime();	//���U���g��ʂ���̃^�C����Ԃ�
	int  TargetTime();			//�^�[�Q�b�g�̃^�C����������
public:
	static FrameTimeUI::SP Create(Vec2& pos,int digitSelect,bool = true);
	bool Initialize(Vec2& pos,int digitSelect);
	FrameTimeUI();
	virtual ~FrameTimeUI();
};