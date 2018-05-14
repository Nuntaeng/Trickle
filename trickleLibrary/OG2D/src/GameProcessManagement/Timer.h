#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

//__________________________
//|                      //|
//|�����@2018/04/14 ���� //|
//|�����@2018/04/15 ���� //|
//|�����@2018/04/19 ���� //|
//|�����@2018/04/26 ���� //|
//|______________________//|
class Timer : public GameObject, public TaskObject,public Time
{
	//-------------------------------------------
	//�e���Ő��삷��Ƃ��Ɏg�p������̂͂����ɋL�q����
	//-------------------------------------------
public:
	/*
	�^�C�}�[�̎��Ԃ��t���[�����ԂɊi�[����
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	void Frame_Set();

	int Get_frame();
private:
	int frame_time;                                //Time�N���X���玞�Ԃ��󂯎��֐�
	//------------------
	//�Œ艻����Ă��鏈��
	//------------------
public:
	std::string taskName;
	virtual ~Timer();
	typedef std::shared_ptr<Timer> SP;
	static Timer::SP Create(bool = true);
	Timer();
	//-------------
	//�ύX���Ȃ�����
	//-------------
	bool Initialize();		//����������
	void UpDate();			//�X�V����
	void Render2D();		//�`�揈��
	bool Finalize();		//�������
};