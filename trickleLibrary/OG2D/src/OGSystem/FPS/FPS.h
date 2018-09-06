#pragma once
#include "OGSystem\_OGsystem.h"

class FPS {
public:
	FPS();							//�R���X�g���N�^
	~FPS();							//�f�X�g���N�^
	void Update();					//�X�V����
	/**
	*@brief	:�t���[���`�F�b�N
	*@return:�b�ԃt���[���ɒB���Ă���Ȃ�true
	*/
	bool FrameCheck();
private:
	float lastTime;					//�O�t���[���^�C��
	int count;						//�J�E���g��
	GLfloat fps;					//fps�l
	//! frame rate
	int framerate;
	//! oneframetime
	float oneFrameTime;
};
