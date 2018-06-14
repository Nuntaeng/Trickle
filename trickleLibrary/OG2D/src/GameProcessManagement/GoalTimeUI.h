#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class GoalTimeUI : public GameObject, public TaskObject
{
private:
	//�^�X�N�֘A
	std::string taskName;
	
	//struct Mat3x3
	//{
	//	enum MatFormat
	//	{
	//		Unix,	//�P��
	//		Rotate,	//��]
	//		Scale,	//�g��k��
	//		Move,	//�ړ�
	//	};
	//	float mat[9];
	//	Mat3x3 Create(float mat[], MatFormat);
	//};


	//�摜�֘A
	Texture image;
	//const Box2D Src = {0,0,227,90};
	const Box2D Src = { 0,64 * 3,640,768 / 12 };

	//�g��@�\
	Vec2  Center;			//�`�撆���Œ���W
	Vec2  ReSize;			//�V�������T�C�Y����Scale
	Vec2  ScaleVolume;		//�g�嗦
	Vec2  PreSize;			//�O��̃f�[�^������Ă���

	//Mat3x3 mat;

private:
	bool Initialize(Vec2&);
	bool Finalize();
	void UpDate();
	void Render2D();
	GoalTimeUI();

	//�g��@�\�֘A
	void MoveVolume();		  //�g�嗦���������㏸�����Ă����܂�
	void ResetVolume();	      //�g�嗦���グ�邽�߂̏��������s��
	void ResetCenter();		  //�����l�̍Čv�Z�����܂��i1�t���[���Ōv�Z�����ďI���������邱�Ɓj

public:
	typedef std::shared_ptr<GoalTimeUI> SP;
	static GoalTimeUI::SP Create(Vec2& pos, bool = true);
	virtual ~GoalTimeUI();

};