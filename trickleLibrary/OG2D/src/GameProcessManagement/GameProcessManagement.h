//__________________________
//|                      //|
//|�����@2018/04/14 ���� //|
//|�����@2018/04/19 ���� //|
//|�����@2018/04/26 ���� //|
//|______________________//|
#pragma once
//�K�v�ǂݍ��݃t�@�C��
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Timer.h"

class GameProcessManagement : public GameObject,public TaskObject
{
	//-------------------------------------------
	//�e���Ő��삷��Ƃ��Ɏg�p������̂͂����ɋL�q����
	//-------------------------------------------
public:
	/*
	�S�[���I�u�W�F�N�g�̒ǉ������܂�
	�������@Object*�@�ǉ��������S�[���I�u�W�F�N�g
	���߂�@�Ȃ�
	*/
	//void Set_Goal();


	/*
	�S�[���̔�����s���܂�
	�������@�Ȃ�
	���߂�@�Ȃ�
	*/
	void Goal_Check();


	/*
	�Q�[���̃t���O�ɂ���ĕω�����C�x���g�Ǘ��֐�
	�������@�Ȃ�
	���߂�@�Q�[���t���O��Ԃ�
	*/
	void Goal_Event();

	void File_Writing();				 //�t���[������������
private:
	bool gameclear_flag;                 //�l�X�ȃt���O���i�[����
	bool pause_flag;					 //�|�[�Y��ʂ���^�C�g���֖߂ꂳ���ꍇ�̑΍�
	Timer::SP timer;                     //�^�C�}�[�̃Z�b�g������

	const char* TimeFilePath = "./data/Result/Result.dat";

	//------------------
	//�Œ艻����Ă��鏈��
	//------------------
public:
	std::string taskName;
	virtual ~GameProcessManagement();
	typedef std::shared_ptr<GameProcessManagement> SP;
	static GameProcessManagement::SP Create(bool = true);
	GameProcessManagement();
	//-------------
	//�ύX���Ȃ�����
	//-------------
	bool Initialize();		//����������
	void UpDate();			//�X�V����
	void Render2D();		//�`�揈��
	bool Finalize();		//�������
};