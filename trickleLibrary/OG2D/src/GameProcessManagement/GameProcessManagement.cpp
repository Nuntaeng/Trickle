#include "GameProcessManagement.h"
#include "Goal\Goal.h"
#include "Task\Task_Game.h"
#include "Task\Task_Result.h"
#include "Task\StageSelect.h"
GameManager::GameManager()
{
	this->Seconds = 0;
	this->Minute = 0;
	this->timeCnt = 0;
	this->isclear = false;
	for (int i = 0; i < 3; ++i)
	{
		this->M_flag[i] = false;
	}
	this->time = 0;
	__super::Init((std::string)"GM");
}
GameManager::~GameManager()
{
	if (this->isclear)
	{
		if (*MapNum == 5 || *MapNum == 6)
		{
			OGge->ChengeTask();
			Result::Create();
		}
		else
		{
			if (*MapNum < 4)
			{
				*MapNum = *MapNum + 1;
				auto next = Game::Create();
			}
			//���Ƀ`���[�g���A�����T���Ă�����͎̂��̃`���[�g���A���ֈړ�
			else if (*MapNum == 4)
			{
				//�`���[�g���A���I���ŃZ���N�g�ɖ߂�
				auto next = StageSelect::Create();
			}
		}
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
		if (this->time > 180)
		{
			//�N���A����
			//�f�[�^�̕ۑ�
			auto game = OGge->GetTask<Game>("game");
			if (game)
			{
				game->Kill();
				if (*MapNum == 5 || *MapNum == 6)
				{
					//���݂̋L�^��ۑ�
					this->OutData();
					//���݂̍ő�L�^�Ƃ̔�r
					this->ComparisonData();
				}
			}
			this->isclear = true;
		}
		else
		{
			this->time++;
		}
	}
}
void GameManager::ResetData()
{
	for (int i = 5; i <= 6; ++i)
	{
		std::ofstream ofs("./data/Result/data" + std::to_string(i) + ".bin", std::ios::out | std::ios::binary);
		ofs << -1 << std::endl;
		ofs.close();
		ofs.open("./data/Result/save" + std::to_string(i) + ".bin", std::ios::out | std::ios::binary);
		ofs << -1 << std::endl;
		ofs.close();
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
				this->M_flag[0] = true;
			}
			else
			{
				ofs << "f," ;
			}

			if (this->Minute * 60 + this->Seconds <= 90)
			{
				ofs << "t,";
				this->M_flag[1] = true;
			}
			else
			{
				ofs << "f,";
			}

			if (this->Minute * 60 + this->Seconds <= 60)
			{
				ofs << "t," ;
				this->M_flag[2] = true;
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
			unsigned __int8 i = 0;
			for (auto id = goals->begin(); id != goals->end(); ++id)
			{
				if ((*id)->ColorCheck())
				{
					ofs << "t," ;
					this->M_flag[i] = true;
				}
				else
				{
					ofs << "f," ;
				}
				++i;
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
	ofs.close();
	return true;
}
bool GameManager::ComparisonData()
{
	unsigned int time[2] = { 0,0 };
	bool flag[3] = { false,false,false };
	std::ifstream ifs("./data/Result/data" + std::to_string(*MapNum) + ".bin", std::ios::in | std::ios::binary);
	if (ifs)
	{
		std::string line;
		std::getline(ifs, line);
		std::istringstream* is = new std::istringstream(line);
		std::string text;
		for (int i = 0; i < 2; ++i)
		{
			std::getline(*is, text, ',');
			(std::stringstream)text >> time[i];
			if (time[i] == -1)
			{
				//�ǂݍ��񂾃f�[�^��-1�̏ꍇ�G���[�Ȃ̂Ńt�@�C�������݂��Ȃ����������l�t�@�C��������̃f�[�^�ŏ㏑������
				this->OutFileData();
				delete is;
				return true;
			}
		}
		std::getline(ifs, line);
		delete is;
		is = new std::istringstream(line);
		for (int i = 0; i < 3; ++i)
		{
			std::getline(*is, text, ',');
			if (text == "t")
			{
				flag[i] = true;
			}
		}
		delete is;
	}
	else
	{
		//�t�@�C�������݂��Ȃ��ꍇ
		OutFileData();
		return true;
	}
	//���펞�̍ő�L�^�ێ��̏������ݏ���
	std::ofstream ofs("./data/Result/data" + std::to_string(*MapNum) + ".bin", std::ios::out | std::ios::binary);
	if (this->isClear())
	{
		if (this->Minute * 60 + this->Seconds < time[0] * 60 + time[1])
		{
			ofs << this->Minute << "," << this->Seconds << std::endl;
		}
		else
		{
			ofs << time[0] << "," << time[1] << std::endl;
		}
		for (int i = 0; i < 3; ++i)
		{
			if (this->M_flag[i] || flag[i])
			{
				ofs << "t,";
			}
			else
			{
				ofs << "f,";
			}
		}
	}
	else
	{
		ofs << -1 << std::endl;
	}
	ofs.close();
	return true;
}
void GameManager::OutFileData()
{
	//�ő�L�^�ێ��p�̏������ݓ���
	//�������̓t�@�C�������݂��Ȃ��܂��̓t�@�C���f�[�^���G���[�̏ꍇ�̂�
	std::ofstream ofs("./data/Result/data" + std::to_string(*MapNum) + ".bin", std::ios::out | std::ios::binary);
	if (this->isClear())
	{
		//���Ԃ̕ۑ�
		ofs << this->Minute << "," << this->Seconds << std::endl;
		for (int i = 0; i < 3; ++i)
		{
			if (this->M_flag[i])
			{
				ofs << "t,";
			}
			else
			{
				ofs << "f,";
			}
		}
	}
	else
	{
		ofs << -1 << std::endl;
	}
	ofs.close();
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

