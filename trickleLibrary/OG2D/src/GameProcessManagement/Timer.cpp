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
	frame_time = 0;               //GetTime�̎��Ԃ�������ϐ�
	frame_time_sec = 0;           //�b
	frame_time_min = 0;           //��
	frame_time_hours = 0;         //��
}

void Timer::Update()
{
	
}
void Timer::Instrumentation()
{
	
}
void Timer::Instrumentation_output(Timer& timer_)
{
	cout << timer_.frame_time_hours << "����" << timer_.frame_time_min << "��" << timer_.frame_time_sec << "�b" << endl;
}
void Timer::Frame_Set()
{
	frame_time = GetTime();
}
int Timer::Get_frame()
{
	return frame_time;
}