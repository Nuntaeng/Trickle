#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class GameClearCamera : public GameObject , public TaskObject
{
private:
	std::string taskName;	//�^�X�N��
	bool cameraMovefinish;	//�J�����̈ړ����I�����Ă���H
	bool active;			//���݃J�������ړ������H
	bool Move;				//��������������
	Vec2 cameraPos;			//�J�����̍��W�l
	Vec2 cameraMove;		//�J�����̈ړ���
private:
	void CameraMove();
	void Flag_Reset();
	void Set_CameraSpeed(Vec2& moveVec);
private:
	bool Finalize();
	void UpDate();
	void Render2D();
public:
	bool GetCameraMoveFinish();
	void SetCameraPos();	//���݂̃J�������W��������
public:
	typedef std::shared_ptr<GameClearCamera> SP;
	GameClearCamera();
	virtual ~GameClearCamera();
	static GameClearCamera::SP Create(bool = true);
	bool Initialize();
};