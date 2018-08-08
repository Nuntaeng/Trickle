#include "GameProcessManagement.h"
#include "Goal\Goal.h"
#include "Task\Task_Game.h"
#include "Task\Task_Result.h"
#include "Task\StageSelect.h"
#include "Load\LoadLogo.h"
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
	//	if (*MapNum == 5 || *MapNum == 6)
	//	{
	//		OGge->ChengeTask();
	//		Result::Create();
	//	}
	//	else
	//	{
	//		if (*MapNum < 4)
	//		{
	//			*MapNum = *MapNum + 1;
	//			auto next = Game::Create();
	//		}
	//		//���Ƀ`���[�g���A�����T���Ă�����͎̂��̃`���[�g���A���ֈړ�
	//		else if (*MapNum == 4)
	//		{
	//			//�`���[�g���A���I���ŃZ���N�g�ɖ߂�
	//			auto next = StageSelect::Create();
	//		}
	//	}


		//�X�e�[�W���z�p
		switch (*MapNum)
		{
		case 1:
		case 2:
		case 3:
		case 5:
		case 6:
		case 7:
		case 9:
		case 10:
		case 11:
			*MapNum = *MapNum + 1;
			Game::Create();
			break;
		case 4:
		case 8:
		case 12:
			StageSelect::Create();
			break;
		case 13:
		case 14:
		case 15:
			OGge->ChengeTask();
			Result::Create();
			break;
		default:
			break;
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
				auto load = Load::Create();
				if (load)
				{
					load->AddObject(game->GetTaskName());
				}
				//���݂̋L�^��ۑ�
				this->OutData();
				//���݂̍ő�L�^�Ƃ̔�r
				this->ComparisonData();
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
	/*for (int i = 1; i <= 6; ++i)
	{
		std::ofstream ofs("./data/Result/data" + std::to_string(i) + ".bin", std::ios::out | std::ios::binary);
		ofs << -1 << std::endl;
		ofs.close();
		ofs.open("./data/Result/save" + std::to_string(i) + ".bin", std::ios::out | std::ios::binary);
		ofs << -1 << std::endl;
		ofs.close();
	}*/
	//�X�e�[�W���z�p
	for (int i = 1; i <= 15; ++i)
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
		//switch (*MapNum)
		//{
		//case 1:
		//	//�Ƃ肠�����ǂݍ��ݎ��ɃG���[��f���Ȃ��悤�ɉ��̒l������Ă���
		//	for(int i = 0;i < 3;++i)
		//	{
		//		ofs << "t,";
		//		this->M_flag[i] = true;
		//	}
		//	break;
		//case 2:
		//	for (int i = 0; i < 3; ++i)
		//	{
		//		ofs << "t,";
		//		this->M_flag[i] = true;
		//	}
		//	break;
		//case 3:
		//	for (int i = 0; i < 3; ++i)
		//	{
		//		ofs << "t,";
		//		this->M_flag[i] = true;
		//	}
		//	break;
		//case 4:
		//	for (int i = 1; i <= 3; ++i)
		//	{
		//		std::ifstream ifs("./data/Result/save" + std::to_string(i) + ".bin", std::ios::in | std::ios::binary);
		//		if (!ifs)
		//		{
		//			ofs << "f,";
		//		}
		//		std::string line;
		//		std::getline(ifs, line);
		//		std::istringstream* is = new std::istringstream(line);
		//		std::string text;
		//		int timer;
		//		std::getline(*is, text, ',');
		//		(std::stringstream)text >> timer;
		//		if (timer != -1)
		//		{
		//			ofs << "t,";
		//			this->M_flag[i] = true;
		//		}
		//		else
		//		{
		//			ofs << "f,";
		//		}
		//		delete is;
		//		ifs.close();
		//	}
		//	break;
		//case 5:
		//{
		//	//�X�e�[�W�P�̃~�b�V����
		//	if (this->Minute * 60 + this->Seconds <= 180)
		//	{
		//		ofs << "t,";
		//		this->M_flag[0] = true;
		//	}
		//	else
		//	{
		//		ofs << "f,";
		//	}

		//	if (this->Minute * 60 + this->Seconds <= 120)
		//	{
		//		ofs << "t,";
		//		this->M_flag[1] = true;
		//	}
		//	else
		//	{
		//		ofs << "f,";
		//	}

		//	if (this->Minute * 60 + this->Seconds <= 60)
		//	{
		//		ofs << "t,";
		//		this->M_flag[2] = true;
		//	}
		//	else
		//	{
		//		ofs << "f,";
		//	}
		//}
		//	break;
		//case 6:
		//{
		//	//�X�e�[�W�Q�̃~�b�V����
		//	auto goals = OGge->GetTasks<Goal>("Goal");
		//	unsigned __int8 i = 0;
		//	for (auto id = goals->begin(); id != goals->end(); ++id)
		//	{
		//		if ((*id)->ColorCheck())
		//		{
		//			ofs << "t," ;
		//			this->M_flag[i] = true;
		//		}
		//		else
		//		{
		//			ofs << "f," ;
		//		}
		//		++i;
		//	}
		//}
		//	break;
		//default:
		//	break;
		//}
		//�X�e�[�W���z�p
		switch (*MapNum)
		{
		case 1:
		case 2:
		case 3:
		case 5:
		case 6:
		case 7:
		case 9:
		case 10:
		case 11:
			for (int i = 0; i < 3; ++i)
			{
				ofs << "t,";
				this->M_flag[i] = true;
			}
			break;
		case 4:
		case 8:
		case 12:
			for (int i = *MapNum - 3; i <= *MapNum - 1; ++i)
			{
				std::ifstream ifs("./data/Result/save" + std::to_string(i) + ".bin", std::ios::in | std::ios::binary);
				if (!ifs)
				{
					ofs << "f,";
				}
				std::string line;
				std::getline(ifs, line);
				std::istringstream* is = new std::istringstream(line);
				std::string text;
				int timer;
				std::getline(*is, text, ',');
				(std::stringstream)text >> timer;
				if (timer != -1)
				{
					ofs << "t,";
					this->M_flag[i] = true;
				}
				else
				{
					ofs << "f,";
				}
				delete is;
				ifs.close();
			}
			break;
		case 13:
		{
			//�X�e�[�W�P�̃~�b�V����
			if (this->Minute * 60 + this->Seconds <= 180)
			{
				ofs << "t,";
				this->M_flag[0] = true;
			}
			else
			{
				ofs << "f,";
			}

			if (this->Minute * 60 + this->Seconds <= 120)
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
				ofs << "t,";
				this->M_flag[2] = true;
			}
			else
			{
				ofs << "f,";
			}
		}
		break;
		case 14:
		{
			//�X�e�[�W�Q�̃~�b�V����
			if (this->Minute * 60 + this->Seconds <= 180)
			{
				ofs << "t,";
				this->M_flag[0] = true;
			}
			else
			{
				ofs << "f,";
			}

			if (this->Minute * 60 + this->Seconds <= 120)
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
				ofs << "t,";
				this->M_flag[2] = true;
			}
			else
			{
				ofs << "f,";
			}
		}
			break;
		case 15:
		{
			//�X�e�[�W�Q�̃~�b�V����
			auto goals = OGge->GetTasks<Goal>("Goal");
			unsigned __int8 i = 0;
			for (auto id = goals->begin(); id != goals->end(); ++id)
			{
				if ((*id)->ColorCheck())
				{
					ofs << "t,";
					this->M_flag[i] = true;
				}
				else
				{
					ofs << "f,";
				}
				++i;
			}
		}
		break;
		}
	}
	else
	{
		//����ȊO(��O����)
		ofs << -1 << std::endl;
	}
	ofs.close();
	/*if (*MapNum >= 1 && *MapNum <= 3)
	{
		ofs.open("./data/Result/save4.bin", std::ios::out | std::ios::binary);
		ofs << -2 << "," << -2 << std::endl;
		for (int i = 1; i <= 3; ++i)
		{
			std::ifstream ifs("./data/Result/save" + std::to_string(i) + ".bin", std::ios::in | std::ios::binary);
			if (!ifs)
			{
				ofs << "f,";
			}
			else
			{
				std::string line;
				std::getline(ifs, line);
				std::istringstream* is = new std::istringstream(line);
				std::string text;
				int timer;
				std::getline(*is, text, ',');
				(std::stringstream)text >> timer;
				if (timer != -1)
				{
					ofs << "t,";
					this->M_flag[i - 1] = true;
				}
				else
				{
					ofs << "f,";
					this->M_flag[i - 1] = false;
				}
				delete is;
			}
			ifs.close();
		}
		ofs.close();
	}*/
	//�X�e�[�W���z�p
	switch(*MapNum)
	{
	case 1:
	case 2:
	case 3:
	{
		ofs.open("./data/Result/save4.bin", std::ios::out | std::ios::binary);
		ofs << -2 << "," << -2 << std::endl;
		for (int i = 1; i <= 3; ++i)
		{
			std::ifstream ifs("./data/Result/save" + std::to_string(i) + ".bin", std::ios::in | std::ios::binary);
			if (!ifs)
			{
				ofs << "f,";
			}
			else
			{
				std::string line;
				std::getline(ifs, line);
				std::istringstream* is = new std::istringstream(line);
				std::string text;
				int timer;
				std::getline(*is, text, ',');
				(std::stringstream)text >> timer;
				if (timer != -1)
				{
					ofs << "t,";
					this->M_flag[i - 1] = true;
				}
				else
				{
					ofs << "f,";
					this->M_flag[i - 1] = false;
				}
				delete is;
			}
			ifs.close();
		}
		ofs.close();
	}
	break;
	case 5:
	case 6:
	case 7:
	{
		ofs.open("./data/Result/save4.bin", std::ios::out | std::ios::binary);
		ofs << -2 << "," << -2 << std::endl;
		for (int i = 5; i <= 7; ++i)
		{
			std::ifstream ifs("./data/Result/save" + std::to_string(i) + ".bin", std::ios::in | std::ios::binary);
			if (!ifs)
			{
				ofs << "f,";
			}
			else
			{
				std::string line;
				std::getline(ifs, line);
				std::istringstream* is = new std::istringstream(line);
				std::string text;
				int timer;
				std::getline(*is, text, ',');
				(std::stringstream)text >> timer;
				if (timer != -1)
				{
					ofs << "t,";
					this->M_flag[i - 5] = true;
				}
				else
				{
					ofs << "f,";
					this->M_flag[i - 5] = false;
				}
				delete is;
			}
			ifs.close();
		}
		ofs.close();
	}
	break;
	case 9:
	case 10:
	case 11:
	{
		ofs.open("./data/Result/save4.bin", std::ios::out | std::ios::binary);
		ofs << -2 << "," << -2 << std::endl;
		for (int i = 9; i <= 11; ++i)
		{
			std::ifstream ifs("./data/Result/save" + std::to_string(i) + ".bin", std::ios::in | std::ios::binary);
			if (!ifs)
			{
				ofs << "f,";
			}
			else
			{
				std::string line;
				std::getline(ifs, line);
				std::istringstream* is = new std::istringstream(line);
				std::string text;
				int timer;
				std::getline(*is, text, ',');
				(std::stringstream)text >> timer;
				if (timer != -1)
				{
					ofs << "t,";
					this->M_flag[i - 9] = true;
				}
				else
				{
					ofs << "f,";
					this->M_flag[i - 9] = false;
				}
				delete is;
			}
			ifs.close();
		}
		ofs.close();
	}
		break;
	}
	return true;
}
bool GameManager::ComparisonData()
{
	//�O�̌��ʂ����锠
	int time[2] = { 0,0 };
	bool flag[3] = { false,false,false };
	switch (*MapNum)
	{
	//case 5:
	//case 6:
	//{
	//	std::ifstream ifs("./data/Result/data" + std::to_string(*MapNum) + ".bin", std::ios::in | std::ios::binary);
	//	if (ifs)
	//	{
	//		std::string line;
	//		std::getline(ifs, line);
	//		std::istringstream* is = new std::istringstream(line);
	//		std::string text;
	//		for (int i = 0; i < 2; ++i)
	//		{
	//			std::getline(*is, text, ',');
	//			(std::stringstream)text >> time[i];
	//			if (time[i] == -1)
	//			{
	//				//�ǂݍ��񂾃f�[�^��-1�̏ꍇ�G���[�Ȃ̂Ńt�@�C�������݂��Ȃ����������l�t�@�C��������̃f�[�^�ŏ㏑������
	//				this->OutFileData();
	//				delete is;
	//				return true;
	//			}
	//		}
	//		std::getline(ifs, line);
	//		delete is;
	//		is = new std::istringstream(line);
	//		for (int i = 0; i < 3; ++i)
	//		{
	//			std::getline(*is, text, ',');
	//			if (text == "t")
	//			{
	//				flag[i] = true;
	//			}
	//		}
	//		delete is;
	//	}
	//	else
	//	{
	//		//�t�@�C�������݂��Ȃ��ꍇ
	//		OutFileData();
	//		return true;
	//	}
	//	//���펞�̍ő�L�^�ێ��̏������ݏ���
	//	std::ofstream ofs("./data/Result/data" + std::to_string(*MapNum) + ".bin", std::ios::out | std::ios::binary);
	//	if (this->isClear())
	//	{
	//		//�`���[�g���A���S�p����
	//		if (time[0] == -2 && time[1] == -2)
	//		{
	//			ofs << this->Minute << "," << this->Seconds << std::endl;
	//		}
	//		//�^�C���̑�������ۑ�����
	//		else if ((int)this->Minute * 60 + (int)this->Seconds < time[0] * 60 + time[1])
	//		{
	//			ofs << this->Minute << "," << this->Seconds << std::endl;
	//		}
	//		else
	//		{
	//			ofs << time[0] << "," << time[1] << std::endl;
	//		}
	//		for (int i = 0; i < 3; ++i)
	//		{
	//			//�O�񂩍���ŃN���A���Ă���t����������
	//			if (this->M_flag[i] || flag[i])
	//			{
	//				ofs << "t,";
	//			}
	//			else
	//			{
	//				ofs << "f,";
	//			}
	//		}
	//	}
	//	else
	//	{
	//		//�G���[��-1������Ă���
	//		ofs << -1 << std::endl;
	//	}
	//	ofs.close();
	//}
	//break;
	//�X�e�[�W���z�p
	case 13:
	case 14:
	case 15:
	{
		std::ifstream ifs("./data/result/data" + std::to_string(*MapNum) + ".bin", std::ios::in | std::ios::binary);
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
		std::ofstream ofs("./data/result/data" + std::to_string(*MapNum) + ".bin", std::ios::out | std::ios::binary);
		if (this->isClear())
		{
			//�`���[�g���A���S�p����
			if (time[0] == -2 && time[1] == -2)
			{
				ofs << this->Minute << "," << this->Seconds << std::endl;
			}
			//�^�C���̑�������ۑ�����
			else if ((int)this->Minute * 60 + (int)this->Seconds < time[0] * 60 + time[1])
			{
				ofs << this->Minute << "," << this->Seconds << std::endl;
			}
			else
			{
				ofs << time[0] << "," << time[1] << std::endl;
			}
			for (int i = 0; i < 3; ++i)
			{
				//�O�񂩍���ŃN���A���Ă���t����������
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
			//�G���[��-1������Ă���
			ofs << -1 << std::endl;
		}
		ofs.close();
	}
		break;
	}
	

	if (*MapNum >= 1 && *MapNum <= 4)
	{
		//�Z�[�u�ɓ����Ă�^�C����flag�������Ă���
		std::ifstream ifs("./data/Result/save4.bin", std::ios::in | std::ios::binary);
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
				else
				{
					flag[i] = false;
				}
			}
			delete is;
		}
		int timers[2] = { 0,0 };
		bool flags[3] = { false,false,false };
		ifs.close();
		ifs.open("./data/Result/data4.bin", std::ios::in | std::ios::binary);
		if (ifs)
		{
			std::string line;
			std::getline(ifs, line);
			std::istringstream* is = new std::istringstream(line);
			std::string text;
			for (int i = 0; i < 2; ++i)
			{
				std::getline(*is, text, ',');
				(std::stringstream)text >> timers[i];
				if (timers[0] == -1)
				{
					std::ofstream ofs("./data/Result/data4.bin", std::ios::out | std::ios::binary);
					ofs << time[0] << "," << time[1] << std::endl;
					for (int i = 0; i < 3; ++i)
					{
						if (flag[i])
						{
							ofs << "t,";
						}
						else
						{
							ofs << "f,";
						}
					}
					ifs.close();
					ofs.close();
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
					flags[i] = true;
				}
				else
				{
					flags[i] = false;
				}
			}
			delete is;
		}
		ifs.close();
		std::ofstream ofs("./data/Result/data4.bin", std::ios::out | std::ios::binary);
		if (time[0] == -2 && time[1] == -2)
		{
			ofs << timers[0] << "," << timers[1] << std::endl;
		}
		else if (timers[0] == -2 && timers[1] == -2)
		{
			ofs << time[0] << "," << time[1] << std::endl;
		}
		else if (timers[0] * 60 + timers[1] < time[0] * 60 + time[1])
		{
			ofs << timers[0] << "," << timers[1] << std::endl;
		}
		else
		{
			ofs << time[0] << "," << time[1] << std::endl;
		}
		for (int i = 0; i < 3; ++i)
		{
			if (flag[i] || flags[i])
			{
				ofs << "t,";
			}
			else
			{
				ofs << "f,";
			}
		}
		ofs.close();
		
	}
	//�X�e�[�W���z�p
	else if (*MapNum >= 5 && *MapNum <= 8)
	{
		//�Z�[�u�ɓ����Ă�^�C����flag�������Ă���
		std::ifstream ifs("./data/Result/save8.bin", std::ios::in | std::ios::binary);
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
				else
				{
					flag[i] = false;
				}
			}
			delete is;
		}
		int timers[2] = { 0,0 };
		bool flags[3] = { false,false,false };
		ifs.close();
		ifs.open("./data/Result/data8.bin", std::ios::in | std::ios::binary);
		if (ifs)
		{
			std::string line;
			std::getline(ifs, line);
			std::istringstream* is = new std::istringstream(line);
			std::string text;
			for (int i = 0; i < 2; ++i)
			{
				std::getline(*is, text, ',');
				(std::stringstream)text >> timers[i];
				if (timers[0] == -1)
				{
					std::ofstream ofs("./data/Result/data8.bin", std::ios::out | std::ios::binary);
					ofs << time[0] << "," << time[1] << std::endl;
					for (int i = 0; i < 3; ++i)
					{
						if (flag[i])
						{
							ofs << "t,";
						}
						else
						{
							ofs << "f,";
						}
					}
					ifs.close();
					ofs.close();
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
					flags[i] = true;
				}
				else
				{
					flags[i] = false;
				}
			}
			delete is;
		}
		ifs.close();
		std::ofstream ofs("./data/Result/data8.bin", std::ios::out | std::ios::binary);
		if (time[0] == -2 && time[1] == -2)
		{
			ofs << timers[0] << "," << timers[1] << std::endl;
		}
		else if (timers[0] == -2 && timers[1] == -2)
		{
			ofs << time[0] << "," << time[1] << std::endl;
		}
		else if (timers[0] * 60 + timers[1] < time[0] * 60 + time[1])
		{
			ofs << timers[0] << "," << timers[1] << std::endl;
		}
		else
		{
			ofs << time[0] << "," << time[1] << std::endl;
		}
		for (int i = 0; i < 3; ++i)
		{
			if (flag[i] || flags[i])
			{
				ofs << "t,";
			}
			else
			{
				ofs << "f,";
			}
		}
		ofs.close();
	}
	else if(*MapNum >= 9 && *MapNum <= 12)
	{
		//�Z�[�u�ɓ����Ă�^�C����flag�������Ă���
		std::ifstream ifs("./data/Result/save12.bin", std::ios::in | std::ios::binary);
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
				else
				{
					flag[i] = false;
				}
			}
			delete is;
		}
		int timers[2] = { 0,0 };
		bool flags[3] = { false,false,false };
		ifs.close();
		ifs.open("./data/Result/data12.bin", std::ios::in | std::ios::binary);
		if (ifs)
		{
			std::string line;
			std::getline(ifs, line);
			std::istringstream* is = new std::istringstream(line);
			std::string text;
			for (int i = 0; i < 2; ++i)
			{
				std::getline(*is, text, ',');
				(std::stringstream)text >> timers[i];
				if (timers[0] == -1)
				{
					std::ofstream ofs("./data/Result/data12.bin", std::ios::out | std::ios::binary);
					ofs << time[0] << "," << time[1] << std::endl;
					for (int i = 0; i < 3; ++i)
					{
						if (flag[i])
						{
							ofs << "t,";
						}
						else
						{
							ofs << "f,";
						}
					}
					ifs.close();
					ofs.close();
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
					flags[i] = true;
				}
				else
				{
					flags[i] = false;
				}
			}
			delete is;
		}
		ifs.close();
		std::ofstream ofs("./data/Result/data12.bin", std::ios::out | std::ios::binary);
		if (time[0] == -2 && time[1] == -2)
		{
			ofs << timers[0] << "," << timers[1] << std::endl;
		}
		else if (timers[0] == -2 && timers[1] == -2)
		{
			ofs << time[0] << "," << time[1] << std::endl;
		}
		else if (timers[0] * 60 + timers[1] < time[0] * 60 + time[1])
		{
			ofs << timers[0] << "," << timers[1] << std::endl;
		}
		else
		{
			ofs << time[0] << "," << time[1] << std::endl;
		}
		for (int i = 0; i < 3; ++i)
		{
			if (flag[i] || flags[i])
			{
				ofs << "t,";
			}
			else
			{
				ofs << "f,";
			}
		}
		ofs.close();
	}
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

