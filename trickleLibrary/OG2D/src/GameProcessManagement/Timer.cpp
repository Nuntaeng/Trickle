#include "Timer.h"
using namespace std;

//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����

bool Timer::Initialize()
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "Timer";		//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	//���Ԃ̃[���N���A
	frame_time = 0;               //GetTime�̎��Ԃ�������ϐ�
	std::cout << "�^�C�}�[�@������" << std::endl;
	return true;
}
void Timer::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------
}

void Timer::Render2D()
{
	//--------------------
	//�`�掞�ɍs���������L�q
	//--------------------
}

bool Timer::Finalize()
{
	//-----------------------------------------
	//���̃I�u�W�F�N�g�����ł���Ƃ��ɍs���������L�q
	//-----------------------------------------
	//���̃^�X�N����邩���A�v���P�[�V�������I���\�肩�ǂ���
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		
	}
	return true;
}
void Timer::Frame_Set()
{
	frame_time = GetTime();
}
int Timer::Get_frame()
{
	return frame_time;
}
//----------------------------
//�������牺��class���̂ݕύX����
//�ق��͕ύX���Ȃ�����
//----------------------------
Timer::Timer()
{
	std::cout << "�^�C�}�[�@����" << std::endl;
}

Timer::~Timer()
{
	this->Finalize();
	std::cout << "�^�C�}�[�@���" << std::endl;
}

Timer::SP Timer::Create(bool flag_)
{
	Timer::SP to = Timer::SP(new Timer());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize())
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}