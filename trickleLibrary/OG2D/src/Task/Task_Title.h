#pragma once
//______________________________//
//|�^�C�g���^�X�N               |//
//|�����F2018/03/20���q��       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "Map\Map.h"

class Title:public TaskObject
{
	Texture texCursor;
	Texture texStart;
	Texture texClose;
	Texture texPause;

	Vec2 startPos;
	Vec2 pausePos;
	Vec2 closePos;
	Vec2 cursorPos;

	int nextTaskCheck;

public:
	Title();
	virtual ~Title();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();

	void CursorMove();
	//��������//
	//�ǉ��ϐ�//
	//��������//
	Sound sound;

	enum State
	{
		Start,        //�Q�[���X�^�[�g
		Pause,         //�ݒ�
		Close        //�Q�[�������
	};
	State state;

	typedef std::shared_ptr<Title> SP;
	static SP Create(bool = true);
};