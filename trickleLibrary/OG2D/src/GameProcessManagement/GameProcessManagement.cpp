#include "GameProcessManagement.h"
using namespace std;
//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
#include "Goal\Goal.h"
#include "Task\Task_Result.h"
#include "Task/StageSelect.h"

bool GameProcessManagement::Initialize()
{
	//�^�X�N�֘A
	this->taskName = "GameProcessManagement";		//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	//�t���O�֘A
	gameclear_flag = false;                 //�����l��false�ɂ��Ă���
	pause_flag = false;
	this->mission.Flag = 0;

	timer = Timer::Create();



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
		//timer->Frame_Set();
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
			this->Flag_Judge(*MapNum,fin);
			break;
		case 6:
			fin << "Stage2";
			fin << ",";
			//�e���̒B�����ڂɂ��Ĕ�������ăt���O����������
			this->Flag_Judge(*MapNum,fin);
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
void GameProcessManagement::Flag_Judge(unsigned short& mapnumber, std::ofstream& fin)
{
	//�����������@IF
	//�t���O��������
	//�t�@�C���Ƀf�[�^������
	int cleartime = this->timer->GetTime();

	switch (mapnumber)
	{
	case 5:
		//�����������ɓ��͂���
		//�t���O�P�̏��� 30�b�ȓ��ɃS�[��������
		if (cleartime <= 30)
		{
			fin << "Flag1" << ",";
			this->mission.Flag_Input(Achievement::Flag1);
			fin << "Flag2" << ",";
			this->mission.Flag_Input(Achievement::Flag2);
			fin << "Flag3" << ",";
			this->mission.Flag_Input(Achievement::Flag3);
			fin << std::endl;
		}
		//�t���O�Q�̏��� 60�b�ȓ��ɃS�[��������
		if (cleartime <= 60)
		{
			fin << "Flag2" << ",";
			this->mission.Flag_Input(Achievement::Flag2);
			fin << "Flag3" << ",";
			this->mission.Flag_Input(Achievement::Flag3);
			fin << std::endl;
		}
		//�t���O�R�̏��� 120�b�ȓ��ɃS�[��������
		if (cleartime <= 120)
		{
			fin << "Flag3" << ",";
			this->mission.Flag_Input(Achievement::Flag3);
			fin << std::endl;
		}
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