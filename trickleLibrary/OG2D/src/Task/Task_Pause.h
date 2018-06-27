#pragma once
//______________________________//
//|�|�[�Y�^�X�N                 |//
//|�����F2018/05/23     ����N�@|//
//|____________________________ |//
#include "OGSystem\OGsystem.h"
#include "Map\Map.h"

class Pause :public TaskObject
{
	Texture texCursor;
	Texture texRestart;
	Texture texReturn;
	Texture texStageSelect;
	Texture texTransparentBack;

	Vec2 RestartPos;
	Vec2 ReturnPos;
	Vec2 stageselectPos;
	Vec2 cursorPos;
	Vec2 transparentbackPos;

	int selectPos = 0;

	//�T�E���h�̃t�@�C�����i�[
	std::string cursorsoundname;
	std::string dicisionsoundname;

public:
	Pause();
	virtual ~Pause();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();
	//��������//
	void Pause_draw();
	void PauseUpDate();
	enum Select {
		Restart, Stage, Return,
	};
	Select select;

	//�J�����ړ�
	bool Pause::InputLeft() {
		return OGge->in->key.on(In::A) || OGge->in->on(In::RL);
	}
	bool Pause::InputRight() {
		return OGge->in->key.on(In::D) || OGge->in->on(In::RR);
	}
	bool Pause::InputDown() {
		return OGge->in->key.on(In::S) || OGge->in->on(In::RD);
	}
	bool Pause::InputUp() {
		return OGge->in->key.on(In::W) || OGge->in->on(In::RU);
	}

	typedef std::shared_ptr<Pause> SP;
	static SP Create(bool = true);

	//�T�E���h����
	Sound cursorsound;
	Sound decisionsound;
};