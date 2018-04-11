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
	Camera2D::SP camera;
	Window::SP window;
	Input in;
	void Initialize();
	void UpDate();
	void SetWindow(int width, int height, char* name, bool screen);
	bool DebugFunction;
private:
	int w_wi;
	int w_he;
	char* w_na;
	bool w_sc;
};

extern EngineSystem* gameEngine;