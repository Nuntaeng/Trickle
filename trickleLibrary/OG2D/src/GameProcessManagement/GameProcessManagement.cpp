#include "GameProcessManagement.h"
using namespace std;
GameProcessManagement::GameProcessManagement()
{
	cout << "�i�s�Ǘ��N���X������" << endl;
}
GameProcessManagement::~GameProcessManagement()
{
	cout << "�i�s�Ǘ��N���X���" << endl;
	goals.clear();                           //vector�����
}
void GameProcessManagement::Initialize()
{
	gameclear_flag = false;                  //�����l��false�ɂ��Ă���
	timer.Start();							//�^�C�}�[���X�^�[�g������
}
void GameProcessManagement::Update()
{
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
		timer.Stop();						//�^�C�}�[�̎��Ԃ����ɖ߂�
		File_Writing();						//�t���[������������
		nowtask = Task_Ruselt;				//���ʉ�ʂֈڂ�
	}
	return nowtask;
}
void GameProcessManagement::File_Writing()
{
	Timefile = fopen(TimeFilePath, "w");			//�n�߂��琶������
	fprintf(Timefile, "%d", timer.Get_frame());
	fclose(Timefile);
}
