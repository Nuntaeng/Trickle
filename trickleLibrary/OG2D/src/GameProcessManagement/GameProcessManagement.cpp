#include "GameProcessManagement.h"
#include "Goal\Goal.h"
#include "Task\Task_Game.h"
#include "Task\Task_Result.h"
GameManager::GameManager()
{
	this->Seconds = 0;
	this->Minute = 0;
	__super::Init((std::string)"GM");
}
GameManager::~GameManager()
{
	if (*MapNum == 5 || *MapNum == 6)
	{
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
			this->Seconds++;
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
	return this->Seconds < 59 && this->Minute < 59 ? false : true;
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

