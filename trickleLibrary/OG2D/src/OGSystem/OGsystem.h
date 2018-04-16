#pragma once
//______________________________//
//|�V�X�e���N���X�Q              |//
//|�����F2018/03/20���q��       |//
//|�����F2018/03/23���q��		   |//
//|____________________________|//
#include "Camera\Camera.h"
#include "Window\Window.h"
#include "Audio\Audio.h"
#include "FPS\FPS.h"
#include "Input\Input.h"
#include "Font\Font.h"
#include "Texture\Texture.h"
#include "Collision\Collision.h"
#include "Audio\Sound.h"
#include "Font\Font.h"
/*
#include "Audio\StreamingSound.h"
*/
class EngineSystem
{
public:
	EngineSystem();
	EngineSystem(int widht, int height, char* name, bool screen);
	~EngineSystem();
	Camera2D::SP camera;
	Window::SP window;
	FPS::SP fps;
	Input in;
	void Initialize();
	void Update();
	void SetWindow(int width, int height, char* name, bool screen);
	bool DebugFunction;
	void SetPause(const bool ispause_);
	bool GetPause() const;
	void SetVolume(const float value_);
	float GetVolime() const;
	void GameEnd();
	bool GetEnd() const;
private:
	bool end;
	float volume;
	int w_wi;
	int w_he;
	char* w_na;
	bool w_sc;
	bool isPause;
};

extern EngineSystem* gameEngine;