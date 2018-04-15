#include "Timer.h"
using namespace std;
Timer::Timer()
{

}
Timer::~Timer()
{

}
void Timer::Initialize()
{
	//���Ԃ̃[���N���A
	frame_time = 0;               //1�t���[�����ƂɊi�[����^�C��
	frame_time_sec = 0;           //�b
	frame_time_min = 0;           //��
	frame_time_hours = 0;         //��

}
void Timer::Update()
{
	Instrumentation();            //�^�C�}�[�̌v�Z������
	Instrumentation_output();     //�^�C�}�[�̏o�͂�����
}
void Timer::Instrumentation()
{
	frame_time++;                 //�^�C�}�[�𓮂���
	//�v�Z��
	if (frame_time == 60)         //�^�C�}�[��60�t���[����������E�E�E
	{
		frame_time_sec += frame_time / 60;                         //�b�̌v�Z
		frame_time = 0;                                            //�[���N���A
		if (frame_time_sec == 60) //60�b�ɂȂ�����E�E�E
		{
			frame_time_min += frame_time_sec / 60;                 //���̌v�Z
			frame_time_sec = 0;                                    //�[���N���A
		}
		if (frame_time_min == 60) //60���ɂȂ�����E�E�E
		{
			frame_time_hours += frame_time_min / 60;               //���Ԃ̌v�Z
			frame_time_min = 0;                                    //�[���N���A
		}
	}
}
void Timer::Instrumentation_output()
{
	if (frame_time % 60 == 0) //60�t���[���ɂ���񂾂��o�͂��܂�
	{
		cout << frame_time_hours << "����" << frame_time_min << "��" << frame_time_sec << "�b" << endl;
	}
}
void Timer::Instrumentation_output(Timer& timer_)
{
	cout << timer_.frame_time_hours << "����" << timer_.frame_time_min << "��" << timer_.frame_time_sec << "�b" << endl;
}