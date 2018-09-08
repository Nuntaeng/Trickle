#pragma once

/*
* @file Task_Pause.h
* @brief �|�[�Y�^�X�N�N���X
* @author yokota_mariko
* @date 2018.9.9
*/

#include "OGSystem\OGsystem.h"
#include "Map\Map.h"

class Pause : public TaskObject
{
	//! �摜�A���Ƃ�ResoureManager�ɓo�^����
	Texture texCursor;
	Texture* texChoices;
	Texture texTransparentBack;
	//! �e�N�X�`���̃J���[
	Color texColor;
	//! �ʒu�ϐ�
	Vec2 RestartPos;
	Vec2 ReturnPos;
	Vec2 stageselectPos;
	Vec2 cursorPos;
	//! �J�[�\�����ԃA���O��
	unsigned int gearAng;
	//! �J�����������Ă��邩
	bool isCameraMoving;
	//! �J�[�\���ʒu���ʗp
	int stateNum;
	//! �T�E���h�̃t�@�C�����i�[
	std::string cursorsoundname;
	std::string dicisionsoundname;
	//! �}�b�v�^�X�N
	std::shared_ptr<Map> map;

	Pause();
	void ReleasePause();
	void MoveCamera();
	void CreateNextTask();
	void CreateLoad();
	bool checkCameraHitMap(Vec2 v);
	void setTexPos();
	void moveCursor();
public:
	//�T�E���h�ϐ�
	Sound cursorsound;
	Sound decisionsound;
	//! �I�����̏�Ԉꗗ
	enum State {
		Non,			//! ����`
		BackToGame,		//! �Q�[���ɖ߂�
		Restart,		//! ���X�^�[�g
		StageSelect,	//! �X�e�[�W�Z���N�g�ɖ߂�
	};
	//! �I�����̏��
	State state;

	virtual ~Pause();
	bool Initialize();
	void Render2D();
	bool Finalize();
	void PauseUpDate();
	bool imageFlag;
	//! �X�}�[�g�|�C���^�̕ʖ���`
	typedef std::shared_ptr<Pause> SP;
	//! �^�X�N�������\�b�h
	static SP Create(bool flag = true);
};