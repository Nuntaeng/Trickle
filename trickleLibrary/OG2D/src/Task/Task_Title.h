#pragma once
//______________________________//
//|�^�C�g���^�X�N               |//
//|�����F2018/03/20���q��       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "CameraManager\CameraManager.h"

class Title:public TaskObject
{
	class Animation
	{
		Easing easing_x;
		Easing easing_y;
		Vec2 StartPos;
		Vec2 EndPos;
	public:
		Vec2 Move();
		Animation();
		void Set(Vec2&, Vec2&);
		bool isPlay() const;
	};

	

	enum Mode
	{
		Non,
		from1,
		from2,
		from3,
		from4,
		from5,
		from6,
		from7,
		End,
	};
	Texture texCursor;
	Texture texStart;
	Texture texClose;
	Texture texPause;

	Texture texLogo;

	Vec2 startPos;
	Vec2 pausePos;
	Vec2 closePos;
	Vec2 cursorPos[3];

	//Texture back;
	Texture waterTex;

	Animation cameraPos;
	Animation cameraSize;

	GameObject testObj;
	//Texture test;
	CameraManager cm;
	GameObject Logo;

	Mode mode;
	Mode preMode;

	void ModeCheck();

	int nextTaskCheck;

	float tex_a;
	float cursor_a;
	__int8 cursorNum;

public:
	Title();
	virtual ~Title();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();

	int timeCnt;

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

class Chara : public GameObject, public TaskObject
{
	enum Direction						//�������Ǘ�
	{
		LEFT,
		RIGHT,
	};
	Texture Image;
	Vec2 move;
	const float MOVE_SPEED = 5.f;								//�ړ��X�s�[�h
	const float JUMP_POWER = -13.f;								//�W�����v�p���[
	const float MAX_FALL = 15.f;								//�����ő呬�x
	const float GRAVITY = (9.8f / 60.f / 60.f * 32) * 10;		//�d�͉����x
	const float FIN_SPEED = 0.5f;								//���C
	Direction direction;										//�������i�[����ϐ�
	std::string taskName;										//��
	int AnimCnt;
	bool isAuto;
	bool isCollision;			
	int MoveCnt;
public:
	Chara(std::string&,Vec2&);
	virtual ~Chara();
	typedef std::shared_ptr<Chara> SP;
	static SP Create(std::string&, Vec2&, bool = true);
	void UpDate();
	void Render2D();
	void Friction();
	void MoveCheck(Vec2&);
	bool FootCheck();
	bool Jump();
	void AutoMove();
	void ManualMove(Vec2&);
};