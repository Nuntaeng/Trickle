#include "GameProcessManagement.h"
using namespace std;
//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
#include "Goal\Goal.h"
#include "Task\Task_Result.h"
#include "Task/StageSelect.h"

bool GameProcessManagement::Initialize()
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "GameProcessManagement";		//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	gameclear_flag = false;                 //�����l��false�ɂ��Ă���
	pause_flag = false;
	timer = Timer::Create();
	timer->Start();							//�^�C�}�[���X�^�[�g������

	cout << "�i�s�Ǘ��N���X�@������" << endl;
	return true;
}
void GameProcessManagement::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------
	Goal_Check();                        //�S�[����S�Ă��Ă���̂��ǂ����H
	Goal_Event();
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
	if (timer != nullptr)
	{
		timer->Kill();
	}
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		//�S�[�������Ă���
		if (gameclear_flag)
		{//�|�[�Y�������s���Ă��Ȃ�
			if (!pause_flag)
			{
				//���Ԃ��Ⴄ�ƃ��U���g��ʂ̕\�����ł��܂���
				//�`���[�g���A���ł͕\�����Ȃ�
				if (*MapNum == 5 || *MapNum == 6)
				{
					auto result = Result::Create();
					pause_flag = true;
				}
			}
		}
	}
	return true;
}
void GameProcessManagement::Goal_Check()
{
	if (!gameclear_flag)
	{
		auto goal = OGge->GetTasks<Goal>("Goal");
		//�S�[��������i�[����Vector��p�ӂ���
		std::vector<bool> goalCheck;
		//�S�[��������i�[����Vector�Ƀf�[�^������
		for (auto id = (*goal).begin(); id != (*goal).end(); ++id)
		{
			goalCheck.push_back((*id)->isGoal());
		}

		//�v�f�𒲂ׂ�
		if (std::all_of(goalCheck.begin(), goalCheck.end(), [](bool flag) {return flag == true; }))
		{
			timer->Pause();
			gameclear_flag = true;
			goalCheck.clear();
			return;
		}
		//�N���A���Ă��Ȃ��Ƃ��̓^�C�}�[�𓮂���
		timer->Frame_Set();
		goalCheck.clear();
	}
}
void GameProcessManagement::Goal_Event()
{
	//�S�[����������E�E�E
	if (gameclear_flag)						//�Q�[���t���O��true�ɂȂ�����E�E�E
	{
		File_Writing();						//�t���[������������
		timer->Stop();						//�^�C�}�[�̎��Ԃ����ɖ߂�
	}
}
void GameProcessManagement::File_Writing()
{
	ofstream fin(TimeFilePath);							//�t�@�C���̃p�X�̎w��
	fin << timer->Get_frame() << "," << std::endl;		//�^�C�}�[�̃t���[��������������
	if (gameclear_flag)
	{
		switch (*MapNum)
		{
		case 5:
			fin << "Stage1";
			fin << ",";
			//�e���̒B�����ڂɂ��Ĕ�������ăt���O����������
			this->mission.Flag_Judge(*MapNum,fin);
			fin << "," << std::endl;
			break;
		case 6:
			fin << "Stage2";
			fin << ",";
			//�e���̒B�����ڂɂ��Ĕ�������ăt���O����������
			this->mission.Flag_Judge(*MapNum,fin);
			fin << "," << std::endl;
			break;
		}
	}
	fin.close();							//�t�@�C�������
}
bool GameProcessManagement::isAllGoal()
{
	return this->gameclear_flag;
}
int GameProcessManagement::GetFlag()
{
	return this->mission.Flag;
}
void GameProcessManagement::Mission::Flag_Input(GameProcessManagement::Achievement flag)
{
	this->Flag |= flag;
}
void GameProcessManagement::Mission::Flag_Judge_Clear()
{
	this->Flag &= ~this->Flag;
}
void GameProcessManagement::Mission::Flag_Judge(unsigned short& mapnumber , std::ofstream& fin)
{
	//�����������@IF
	//�t���O��������
	//�t�@�C���Ƀf�[�^������
	switch (mapnumber)
	{
	case 5:
		//�����������ɓ��͂���

		break;
	case 6:
		//�����������ɓ��͂���

		break;
	default:
		break;
	}
}
GameProcessManagement::GameProcessManagement()
{
	cout << "�i�s�Ǘ��N���X�@����" << endl;
}

GameProcessManagement::~GameProcessManagement()
{
	this->Finalize();
	cout << "�i�s�Ǘ��N���X�@���" << endl;
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