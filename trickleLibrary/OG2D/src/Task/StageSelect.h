#pragma once

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "VolumeControl/volumeControl.h"

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
		Vec2 Move(const Easing::Name = Easing::Name::Linear, const Easing::Mode = Easing::Mode::InOut, const float = 10.f);
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

	Texture* Testdoor;		//�h�A�̉摜
	Texture* Wall;           //�ǂ̉摜
	Texture* LadderTex;
	Texture* totitleTex;		//�^�C�g���ɖ߂�Ŕ�
	Texture* moreTex;

	//�T�E���h�̃t�@�C�����i�[
	std::string soundname;     
	std::string decisionsoundname;      //���艹

	std::vector<std::pair<Direction, float>> Entrance;	//���ɑ΂��Ă̌����Ƃ��̍��W
	//�e�����Ǘ�
	enum Mode
	{
		Non,
		createTask,
		objectMoveTask,
		waitTask,
		afterMoveTask,
		End,
	};
	Mode mode;
	Mode preMode;
	//�e�����֐�
	void CreateTask();
	void ObjectMoveTask();
	void WaitTask();
	void AfterMoveTask();

	unsigned __int64 timeCnt;
	int nowPos;
	unsigned __int8 doorNumber;			//�ݒu����h�A�̖���
	bool isPause;
	void ModeCheck();
	bool CheckTime(int);
	void GateClose();
	Easing camera_x;
	Easing camera_y;

	bool canVolControl;

public:
	StageSelect();
	virtual ~StageSelect();
	bool Initialize();
	void UpDate() override;
	void PauseUpDate() override;
	void Render2D() override;
	bool Finalize();

	enum State
	{
		Tutorial1,
		Tutorial2,
		Tutorial3,
		Stage1,
		Stage2,
		Stage3,
		ToTitle,
	};
	State state;
	Sound* sound;
	Sound decisionsound;
	VolumeControl volControl;

	typedef std::shared_ptr<StageSelect> SP;
	static SP Create(bool = true);
};