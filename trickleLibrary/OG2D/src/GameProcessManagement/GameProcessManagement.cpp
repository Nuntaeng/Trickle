#include "GameProcessManagement.h"
using namespace std;

//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����

bool GameProcessManagement::Initialize()
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "GameProcessManagement";		//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	gameclear_flag = false;                 //�����l��false�ɂ��Ă���
	timer.Start();							//�^�C�}�[���X�^�[�g������

	return true;
}
void GameProcessManagement::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------

	Goal_Check();                        //�S�[�������Ă���̂��ǂ����H
}

void GameProcessManagement::Render2D()
{
	//--------------------
	//�`�掞�ɍs���������L�q
	//--------------------
	
}

bool GameProcessManagement::Finalize()
{
	//-----------------------------------------
	//���̃I�u�W�F�N�g�����ł���Ƃ��ɍs���������L�q
	//-----------------------------------------
	
	//���̃^�X�N����邩���A�v���P�[�V�������I���\�肩�ǂ���
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		goals.clear();                           //vector�����
		//�����������ꍇ��Kill���g��
		this->Kill();
	}
	return true;
}
void GameProcessManagement::Set_Goal(GameObject* goal)
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
void GameProcessManagement::Goal_Event()
{
	if (gameclear_flag)						//�Q�[���t���O��true�ɂȂ�����E�E�E
	{
		timer.Stop();						//�^�C�}�[�̎��Ԃ����ɖ߂�
		File_Writing();						//�t���[������������
		//���ʉ�ʂ֍s��

	}
}
void GameProcessManagement::File_Writing()
{
	ofstream fin(TimeFilePath);				//�t�@�C���̃p�X�̎w��
	fin << timer.Get_frame();				//�^�C�}�[�̃t���[��������������
	fin << ',';								//,�̏�������
	if (gameclear_flag)
	{
		fin << "GameClear";					//�Q�[���N���A�t���O
		fin << ',';							//,�̏�������
	}
	else
	{
		fin << "NoGame";					//�Q�[�����N���A
		fin << ',';							//,�̏�������
	}
	fin.close();							//�t�@�C�������
}
//----------------------------
//�������牺��class���̂ݕύX����
//�ق��͕ύX���Ȃ�����
//----------------------------
GameProcessManagement::GameProcessManagement()
{

}

GameProcessManagement::~GameProcessManagement()
{
	this->Finalize();
}

GameProcessManagement::SP GameProcessManagement::Create(bool flag_)
{
	GameProcessManagement::SP to = GameProcessManagement::SP(new GameProcessManagement());
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