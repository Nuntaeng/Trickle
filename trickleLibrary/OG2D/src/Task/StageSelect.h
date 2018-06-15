#pragma once

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class StageSelect : public TaskObject
{
	//�A�j���[�V�����pclass
	class Animation
	{
		Easing easing_x;
		Easing easing_y;
		Vec2 StartPos;
		Vec2 EndPos;
	public:
		Vec2 Move();
		Vec2 Move(const float time);
		Animation();
		void Set(Vec2&, Vec2&);
		bool isPlay() const;
	};

	//������̉E�������𔻒肳����p
	enum Direction
	{
		LEFT,
		RIGTH,
	};

	Animation camera_anim;

	Texture Testdoor;		//�h�A�̉摜
	Texture Wall;           //�ǂ̉摜

	std::string soundname;     //�T�E���h�̃t�@�C�����i�[

	std::vector<std::pair<Direction, float>> Entrance;	//���ɑ΂��Ă̌����Ƃ��̍��W
	//�e�����Ǘ�
	enum Mode
	{
		Non,
		from1,
		from2,
		from3,
		from4,
		End,
	};
	Mode mode;
	Mode preMode;
	//�e�����֐�
	void From1();
	void From2();
	void From3();
	void From4();

	int timeCnt;
	int nowPos;
	void ModeCheck();
	bool CheckTime(int);
	void GateClose();
	Easing camera_x;
	Easing camera_y;

public:
	StageSelect();
	virtual ~StageSelect();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();

	enum State
	{
		Tutorial,
		Stage1,
		Stage2,
		ToTitle,
	};
	State state;
	Sound* sound;

	typedef std::shared_ptr<StageSelect> SP;
	static SP Create(bool = true);
};