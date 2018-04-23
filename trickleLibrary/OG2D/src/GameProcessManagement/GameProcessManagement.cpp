#include "GameProcessManagement.h"
using namespace std;
GameProcessManagement::GameProcessManagement()
{

}
GameProcessManagement::~GameProcessManagement()
{
	goals.clear();                           //vector�����
}
void GameProcessManagement::Initialize()
{
	gameclear_flag = false;                  //�����l��false�ɂ��Ă���
	
}
void GameProcessManagement::Update()
{
	timer.Update();                      //�^�C�}�[���Ԃ̏o�́E�v�Z�����Ă���
	Goal_Check();                        //�S�[�������Ă���̂��ǂ����H
}
void GameProcessManagement::Set_Goal(Object* goal)
{
	if (goal->objectTag != "Goal")           //�I�u�W�F�N�g�^�O�̊m�F������
	{
	   return;
	}
	goals.push_back(goal);                   //push.back������
}
void GameProcessManagement::Goal_Check()
{
	for (auto g : goals)
	{
		if (g->objectTag == "Goal")          //�I�u�W�F�N�g�^�O��Goal�Ȃ�΁E�E�E
		{
			if (((Goal*)g)->cleared)
			{
				if (!gameclear_flag)		//1�񂾂����������邱�ƂŃX�g�b�v���ێ�������
				{
					timer.Pause();			//�^�C�}�[���X�g�b�v����
				}
				gameclear_flag = true;		//�t���O��true�ɂ���
				return;
			}
		}
	}
	timer.Frame_Set();			            //�t���[�����Ԃ��i�[����
	gameclear_flag = false;
}
TaskFlag GameProcessManagement::Goal_Event()
{
	TaskFlag nowtask = Task_Game;
	if (gameclear_flag)						//�Q�[���t���O��true�ɂȂ�����E�E�E
	{
		timer.Instrumentation_output();		//���Ԃ��o��
		timer.Stop();						//�^�C�}�[�̎��Ԃ����ɖ߂�
		nowtask = Task_Ruselt;				//���ʉ�ʂֈڂ�
	}
	return nowtask;
}