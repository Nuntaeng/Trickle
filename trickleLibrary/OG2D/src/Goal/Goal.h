#ifndef __GOAL_H__
#define __GOAL_H__

//�K�v�ǂݍ��݃t�@�C��
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Goal : public GameObject, public TaskObject
{
public:
	enum CameraMode
	{
		//�����Ă��Ȃ�
		NON,
		//�N����
		Play,
		//�I������
		End,		
	};
private:
	//�^�X�N�֘A
	std::string taskName;

	//��{�̏��
	bool cleared;

	//�摜�֘A
	Texture tex;

	//�A�j���[�V�����֘A
	bool isanimetion;
	bool isanimetionfinish;
	int  animCnt;

	//�S�[���J�����֘A
	CameraMode cameramode;
	bool iscameraPlay;			//�J�������N�����Ă��邩�N����������Ԃ��܂�
	Vec2 cameraPos;				//�J�����̍��W�l
	Vec2 cameraMove;			//�J�����̈ړ���
	Vec2 cameraSize;			//�J�����̃T�C�Y
	Vec2 PreCameraPos;			//�ۑ����Ă����J�����̍��W
	Vec2 PreCameraSize;			//�ۑ����Ă����J�����̃T�C�Y
	Vec2 inside;				//�S�[�������Player�ƃS�[���̋������i�[���܂�
	bool camerafinish;			//�J�����̓������I������

private:
	//�^�X�N�֘A
	void UpDate();			//�X�V����
	void Render2D();		//�`�揈��
	bool Finalize();		//�������

	//��{�̏��
	bool ClearCheck();			//�S�[���̔����Ԃ��܂�


	//�A�N�Z�T���\�b�h�֘A
	void ResetisGoal();			//�S�[������̏��������s���܂�

	void ResetAnimetion();		//�A�j���[�V�����̏�����

	void ResetCameraMode();		//�J�����̃��[�h�����������܂�
	void ResetisCameraPlay();	//�J�����̋N������t���O�����������܂�
	void ResetCameraVec();		//Vector�N���X�̏�����
	void ResetCamera();			//�S�[���J�����֘A���܂Ƃ߂ď��������܂�
	void ResetCameraCnt();		//�S�[���̃J�E���^�����������܂�

	//�J�����֘A
	void Camera_Think();
	void Camera_Motion();
	void Camera_Play();			//�J�����𓮂���
public:
	virtual ~Goal();
	typedef std::shared_ptr<Goal> SP;
	static Goal::SP Create(bool);
	static Goal::SP Create(bool,Vec2&);
	Goal();
	//-------------
	//�ύX���Ȃ�����
	//-------------
	bool Initialize();		//����������
	bool Initialize(Vec2&);	//����������
	
	//���̃N���X�Ŏg�p�ł��郁�\�b�h

	//�t���O�֌W
	bool isGoal();						//�S�[�������Ă��邩�ǂ�����Ԃ�
	bool isAnimetion();					//�A�j���[�V�������I�����Ă��邩��Ԃ�

	//�J�������[�h�֘A
	CameraMode GetCameraMode();		//�J�������[�h��Ԃ�
	void SetCameraMode(CameraMode);	//�J�������[�h��ύX���܂�
	void SetCameraSpeed(Vec2&);		//�J�����𓮂����X�s�[�h��ύX���܂�
};

#endif