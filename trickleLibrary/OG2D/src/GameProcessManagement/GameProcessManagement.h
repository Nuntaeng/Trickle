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
private:
	//��{�̏��
	bool gameclear_flag;                 //�l�X�ȃt���O���i�[����
	bool pause_flag;					 //�|�[�Y��ʂ���^�C�g���֖߂ꂳ���ꍇ�̑΍�

	//�^�C�}�[�֘A
	Timer::SP timer;                     //�^�C�}�[�̃Z�b�g������

	const char* TimeFilePath = "./data/Result/Result.dat";

private:
	//�S�[������֘A
	void Goal_Check();		//�S�[���̔�����`�F�b�N���܂�
	void Goal_Event();		//�S�Ă��S�[����ԂȂ烊�U���g��ʂɍs���܂�

	//���U���g��ʂɃf�[�^�𑗂�֐��֘A
	void File_Writing();				 //�t���[������������
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

	//���̃N���X�Ŏg�p����֐�
	bool isAllGoal();		//�S�Ă��S�[�������Ă��邩�ǂ�����Ԃ��܂�

};