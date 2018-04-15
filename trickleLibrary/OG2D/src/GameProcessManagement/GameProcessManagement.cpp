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
	timer.Initialize();                      //�^�C�}�[�̃^�C�����[���N���A����
}
void GameProcessManagement::Update()
{
	timer.Update();                          //�^�C�}�[���Ԃ̏o�́E�v�Z�����Ă���
	Goal_Check();
	Goal_Event();                            //�Q�[���N���A�C�x���g���Ăяo��
}
void GameProcessManagement::Set_Goal(Object* goal)
{
	//if (goal->objectTag != "Goal")           //�I�u�W�F�N�g�^�O�̊m�F������
	//{
	//   return;
	//}
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
				gameclear_flag = true;
				return;
			}
		}
	}
	gameclear_flag = false;
}
void GameProcessManagement::Goal_Event()
{
	if (gameclear_flag)
	{
		cout << "�Q�[���N���A" << endl;
	}
}