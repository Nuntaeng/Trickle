#pragma once
//______________________________//
//|�^�C�g���^�X�N               |//
//|�����F2018/03/20���q��       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "CameraManager\CameraManager.h"
#include "VolumeControl/volumeControl.h"

class Title :public TaskObject
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
		from8,
		from9,
		from10,
		from11,
		End,
	};

	Texture texCursor;

	Texture texEffect;
	Texture effect03;

	Texture GierLogo;
	Texture flowerLogo;

	Texture texLogo;

	Texture forTransform;
	//�e�X�g�ǉ�
	Texture monitorTex;
	Texture fontTex;
	

	std::string soundname;
	std::string soundcursorname;
	std::string sounddecisionname;
	std::string soundflowername;

	//�I�����̕����̏ꏊ�ɂ���
	Vec2 startPos;
	Vec2 closePos;
	Box2D textPos[2];
	Box2D cursorPos[3];

	//�e�X�g�ǉ�
	Vec2 creditpos;      //�N���W�b�g�ɕ����̈ʒu
	Vec2 dataDeletepos;  //�f�[�^�����������̈ʒu
	//�\������T�C�Y�i�[
	Vec2 startsize;      
	Vec2 closesize;
	Vec2 creditsize;
	Vec2 dataDeletesize;
	//�f�[�^�������Ƃ��̑I�����̈ʒu
	Vec2 yespos;         
	Vec2 nopos;
	float monitorSpos;    //���j�^�[�̍��[�̈ʒu
	float monitorEpos;    //���j�^�[�̉E�[�̈ʒu
	float monitorsize;    //���j�^�[�̃T�C�Y

	enum nowmove          //���j�^�[���̕����̓���
	{
		in,       //�����Ă���
		out,      //�o�Ă���
		non       //�ҋ@��
	};
	nowmove start;
	nowmove close;
	nowmove credit;
	nowmove dataDelete;

	enum Del             //�f�[�^�������������Ȃ����̍ŏI�m�F�p
	{
		yes,
		no,
	};
	Del del;

	Box2D intextsrc;      //���j�^�[�ɓ����Ă���Ƃ���src�̋���
	Box2D outtextsrc;     //���j�^�[����o�Ă����Ƃ���src�̋���
	float textspeed;      //�I�����镶������������

	Texture waterTex;

	Animation cameraPos;
	Animation cameraSize;

	CameraManager cm;
	GameObject Logo;

	Mode mode;
	Mode preMode;

	Time demoTimer;
	int curPlayVideo = 0;
	const static std::string DEMO_VIDEOS[];
	const float DEMO_LIMIT = 10.f;
	float trans_a = 0.f;

	void ModeCheck();

	int nextTaskCheck;

	float tex_a;
	float cursor_a;
	__int8 cursorNum;      //0=start,1=credit,2=delete,3=exit,
	float press_a;
	float press_delta_a;

	int gierCnt;
	bool isGierAng;
	float flowerVolume;
	bool isSkip;

	void SkipMove();
	bool skipInoutFlag;

public:
	Title();
	virtual ~Title();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();
	void Skip();
	void BackTitleSkip();
	int timeCnt;

	bool PressAnyKey();          //B�L�[�������Ă�����true��Ԃ�
	bool pressAnyKey;
	//�I�����̕����̈ړ��ɂ���
	Vec2 TextMoveout(Vec2 pos);        
	Vec2 TextMovein(Vec2 pos,Vec2 size,Vec2 outsize,float maxsize);
	Vec2 TextSizeout(Vec2 pos, Vec2 size, float maxsize);
	Vec2 TextSizein(Vec2 pos,Vec2 size,float maxsize);

	bool nowmoveL;        //���ݍ��ɓ����Ă��邩
	bool nowmoveR;        //���݉E�ɓ����Ă��邩
	//�����̍ő剡�T�C�Y�i�[
	float startmax;
	float closemax;
	float creditmax;
	float datadeletemax;

	void CursorMove();      //�g��Ȃ��Ȃ��č폜�\��

	void SetPauseEveryChild(const bool&);

	enum State
	{
		Start,        //�Q�[���X�^�[�g
		Pause,         //�ݒ�
		Close        //�Q�[�������
	};
	State state;
	Sound* sound;
	Sound cursorsound;
	Sound decisionsound;
	Sound flowersound;
	VolumeControl volControl;

	bool canVolControl;

	bool soundstart;

	typedef std::shared_ptr<Title> SP;
	static SP Create(bool = true);
};
