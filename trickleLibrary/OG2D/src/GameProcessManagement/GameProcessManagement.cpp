#include "GameProcessManagement.h"
#include "Goal\Goal.h"
#include "Task\Task_Game.h"
#include "Task\Task_Result.h"
GameManager::GameManager()
{
	this->Seconds = 0;
	this->Minute = 0;
	this->timeCnt = 0;
	__super::Init((std::string)"GM");
}
GameManager::~GameManager()
{
	if (*MapNum == 5 || *MapNum == 6)
	{
		this->OutData();
		Result::Create();
	}
}
void GameManager::UpDate()
{
	if (!this->isClear())
	{
		//���Ԃ��v���X����
		//60�b�𒴂����番���v���X���b�����Z�b�g
		if (!this->isMaxTime())
		{
			this->timeCnt++;
			if (this->timeCnt >= 60)
			{
				this->Seconds++;
				this->timeCnt = 0;
				if (this->Seconds >= 60)
				{
					if (this->Minute < 59)
					{
						this->Seconds = 0;
						this->Minute++;
					}
				}
			}
		}
	}
	else
	{
		//�N���A����
		//�f�[�^�̕ۑ�
		auto game = OGge->GetTask<Game>("game");
		if (game)
		{
			game->Kill();
		}
	}
}
bool GameManager::isMaxTime()
{
	return this->Seconds >= 59 && this->Minute >= 59 ? true : false;
}
unsigned int GameManager::SecondsTime() const
{
	return this->Seconds;
}
unsigned int GameManager::MinuteTime() const
{
	return this->Minute;
}
bool GameManager::isClear()
{
	auto goals = OGge->GetTasks<Goal>("Goal");
	for (auto id = goals->begin(); id != goals->end(); ++id)
	{
		//�P�ł��N���A���Ă��Ȃ��̂Ȃ�false��Ԃ�
		if (!(*id)->GetClear())
		{
			return false;
		}
	}
	return true;
}
bool GameManager::OutData()
{
	std::string path = "./data/Result/save" + std::to_string((int)*MapNum) + ".bin";
	std::ofstream ofs(path, std::ios::out | std::ios::binary);
	if (!ofs)
	{
		std::cout << "�t�@�C�������݂��܂���" << std::endl;
	}
	//�N���A���Ă���ꍇ
	if (this->isClear())
	{
		//���Ԃ̕ۑ�
		ofs << this->Minute << "," << this->Seconds << std::endl;
		switch (*MapNum)
		{
		case 5:
			//�X�e�[�W�P�̃~�b�V����
			if (this->Minute * 60 + this->Seconds <= 120)
			{
				ofs << "t,";
			}
			else
			{
				ofs << "f," ;
			}

			if (this->Minute * 60 + this->Seconds <= 90)
			{
				ofs << "t,";
			}
			else
			{
				ofs << "f,";
			}

			if (this->Minute * 60 + this->Seconds <= 60)
			{
				ofs << "t," ;
			}
			else
			{
				ofs << "f," ;
			}
			break;
		case 6:
		{
			//�X�e�[�W�Q�̃~�b�V����
			auto goals = OGge->GetTasks<Goal>("Goal");
			for (auto id = goals->begin(); id != goals->end(); ++id)
			{
				if ((*id)->ColorCheck())
				{
					ofs << "t," ;
				}
				else
				{
					ofs << "f," ;
				}
			}
		}
			break;
		default:
			break;
		}
	}
	else
	{
		//����ȊO(��O����)
		ofs << -1 << std::endl;
	}
	return true;
}
GameManager::SP GameManager::Create(bool flag)
{
	GameManager::SP to = GameManager::SP(new GameManager());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		return to;
	}
	return nullptr;
}

