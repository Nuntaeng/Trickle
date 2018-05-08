#pragma once
//_____________________________
//|�V�X�e���N���X�Q             
//|�����F2018/03/20       
//|�����F2018/03/23		   
//|____________________________
#include "Camera\Camera.h"
#include "Window\Window.h"
#include "FPS\FPS.h"
#include "Input\Input.h"
#include "Font\Font.h"
#include "Texture\Texture.h"
#include "Collision\Collision.h"
#include "Font\Font.h"
#include "Audio\SoundManager.h"
#include "Timer\glTimer.h"
#include "Easing\easing.hpp"
#include "Audio\StreamingSound.h"
#include "Random\Random.h"

class EngineSystem
{
public:
	EngineSystem();			//�R���X�g���N�^
	EngineSystem(			//�R���X�g���N�^
		int,
		int,
		char*,
		bool = false);
	~EngineSystem();		//�f�X�g���N�^
	Camera2D::SP camera;	//�J����2D
	Window::SP window;		//Window
	FPS::SP fps;			//fps
	Audio::SP audiodevice;	//Audio
	SoundManager::SP soundManager;	//Sound�Ǘ�
	Input in;				//���͏�
	void Initialize();		//����������
	void Update();			//�X�V����
	void SetWindow(			//Window���o�^
		int,
		int,
		char*,
		bool = false);
	void SetWindowPos(Vec2&);	//Window�����ʒu�ݒ�
	void SetCursorOn(const bool);	//�J�[�\�������L��
	void SetIcon(std::string&);	//�A�C�R���g�p�摜�ݒ�
	bool DebugFunction;		//�f�o�b�O�@�\
	void SetPause(const bool);	//�|�[�Y�ݒ�
	bool GetPause() const;		//�|�[�Y��Ԃ�
	void GameEnd();				//�A�v���P�[�V�����I���o�^
	bool GetEnd() const;		//�A�v���P�[�V�����I����Ԃ�
	void ChengeTask();			//�^�X�N�ύX������
	bool GetDeleteEngine();		//�G���W���I����Ԃ�
	void SetDeleteEngine(bool);	//�G���W���I���o�^
private:
	bool end;			//�I����
	int w_wi;			//WindowSize
	int w_he;			//WindowSize
	char* w_na;			//WindowName
	bool w_sc;			//WindowMode
	bool isPause;		//PauseCheck
	bool Cursor_on;		//�J�[�\������
	std::string path = "./data/image/";	//�t�@�C���p�X
	std::string file;	//�t�@�C����
	Vec2 w_pos;			//WindowPosition
	bool DeleteEngine;	//Engine�I����
};

extern EngineSystem* gameEngine;