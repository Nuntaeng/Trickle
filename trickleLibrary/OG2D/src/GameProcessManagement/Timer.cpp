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
}
void Timer::Frame_Set()
{
	frame_time = GetTime();
}
int Timer::Get_frame()
{
	return frame_time;
}