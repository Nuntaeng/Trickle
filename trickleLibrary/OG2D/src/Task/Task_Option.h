#pragma once

//______________________________//
//|�I�v�V�����^�X�N             |//
//|����   :2018/04/17���䋱��   |//
//|                             |//
//|_____________________________|//
#include "Win\WinMain.h"
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Map\Map.h"
#include "CollisionManager\CollisionManager.h"
#include "OGSystem\Audio\Sound.h"

class Option : public Sound
{
	Texture texBack;   	std::string soundName;         //�T�E���h�̃t�@�C����
            //���̔w�i�摜�̃t�@�C����
	Texture texBar;               //���̃{�����[���\���摜
	Texture texGear;               //���̃{�����[���\���摜
public:
	void Initialize();
	TaskFlag Update();
	void Render();
	void Finalize();

	//�{�����[���̊i�[
	float vol;
	//�`��p�̕ϐ�
	float gearPos;
	float barwidth;
	float nowVol;

	//�T�E���h�̐���
	Sound sound;
	//�T�E���h�̏����ݒ�
	void Set();
	//�T�E���h�̉��ʒ���
	void VolControl();
	//�`��̈ړ�
	void DrawVol();
};