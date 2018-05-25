#include "Task_Result.h"
//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
#include "Task_Title.h"
#include "GameProcessManagement\FlagUI.h"
#include "Player\ResultPlayer.h"
#include "GameProcessManagement\ClearUI.h"
#include "GameProcessManagement\GoalTimeUI.h"
#include "GameProcessManagement\MissionUI.h"
#include "GameProcessManagement\FrameTime.h"
bool Result::Initialize()
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "Result";		//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	//������
	Result_DataInput();
	Flag_Judge();
	this->image.Create((std::string)"back.png");
	this->maptile.Create((std::string)"tile.jpg");

	SetDrawOrder(0.0f);
	{
		Vec2 windowsize = OGge->window->GetSize();
		auto player = ResultPlayer::Create(Vec2(0, (int)windowsize.y - 50 - 64),Vec2(3,0));
	}
	{
		Vec2 windowsize = OGge->window->GetSize();
		for (int i = 0; i < 3; ++i)
		{
			auto ster = FlagUI::Create(Vec2(((int)windowsize.x / 2 - 200 ) + 100 * (i + 1), 130), 1 << 0);
		}
	}
	
	{
		Vec2 windowsize = OGge->window->GetSize();
		auto clearUI = ClearUI::Create(Vec2(250,320));
		auto goaltime = GoalTimeUI::Create(Vec2(210,190));
		auto mission = MissionUI::Create(Vec2((int)windowsize.x / 2 - 200, 30));
		auto time = FrameTimeUI::Create(Vec2{},0);
	}
	std::cout << "���ʉ�ʏ����@������" << std::endl;
	return true;
}

void Result::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------
	//�^�C�g���V�[���֑J��
	if (OGge->in->down(In::B2))
	{
		Kill();
	}
}
void Result::Render2D()
{
	//--------------------
	//�`�掞�ɍs���������L�q
	//--------------------
	Vec2 windowsize = OGge->window->GetSize();
	{
		Box2D draw(Vec2(0, 0), windowsize);
		draw.OffsetSize();
		Box2D src = this->backSrc;
		src.OffsetSize();
		image.Draw(draw, src);
	}
	{
		int count = 0;
		for (int y = windowsize.y - 50; y <= windowsize.y; y += 64)
		{
			for (int x = 0; x <= windowsize.x / 64; ++x)
			{
				Box2D draw(Vec2(x * 64, (int)windowsize.y - 50 + count * 64), Vec2(64, 64));
				draw.OffsetSize();
				Box2D src = this->maptileSrc;
				src.OffsetSize();
				maptile.Draw(draw, src);
			}
			count++;
		}
		
	}
}
bool Result::Finalize()
{
	//-----------------------------------------
	//���̃I�u�W�F�N�g�����ł���Ƃ��ɍs���������L�q
	//-----------------------------------------
	//���̃^�X�N����邩���A�v���P�[�V�������I���\�肩�ǂ���
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		image.Finalize();
		maptile.Finalize();

		auto player = OGge->GetTasks<ResultPlayer>("ResultPlayer");
		auto ster = OGge->GetTasks<FlagUI>("Ster");
		auto clear = OGge->GetTasks<ClearUI>("ClearUI");
		auto goaltime = OGge->GetTasks<GoalTimeUI>("GoalTimeUI");
		auto mission = OGge->GetTasks<MissionUI>("MissionUI");
		auto frametime = OGge->GetTasks<FrameTimeUI>("FrameTimeUI");

		for (auto id = (*ster).begin(); id != (*ster).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*player).begin(); id != (*player).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*clear).begin(); id != (*clear).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*goaltime).begin(); id != (*goaltime).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*mission).begin(); id != (*mission).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*frametime).begin(); id != (*frametime).end(); ++id)
		{
			(*id)->Kill();
		}
		auto title = Title::Create();
	}
	return true;
}
bool Result::Flag_Judge()
{
	bool active = false;
	if ((Flag & Result::Flag1) == Result::Flag1)
	{
		//�t���O�P�������Ă���
		active = true;
		std::cout << "Goal" << std::endl;
	}
	if ((Flag & Result::Flag2) == Result::Flag2)
	{
		//�t���O�Q�������Ă���
		active = true;
		std::cout << "30�b�ȓ��ɃS�[��������" << std::endl;
	}
	if ((Flag & Result::Flag3) == Result::Flag3)
	{
		//�t���O�R�������Ă���
		std::cout << "60�b�ȓ��ɃS�[��������" << std::endl;
		active = true;
	}
	if ((Flag & Result::Flag4) == Result::Flag4)
	{
		//�t���O�S�������Ă���
		std::cout << "���ʂɃS�[��������" << std::endl;
		active = true;
	}
	if (Flag & 0x0F)
	{
		std::cout << "�}�X�^�[�N���A" << std::endl;
	}
	return active;
}
bool Result::Flag_Judge(Result::Achievement achive1, Result::Achievement achive2)
{
	if ((Flag & achive1) == achive1 && (Flag & achive2) == achive2)
	{
		return true;
	}
	return false;
}
bool Result::Flag_Judge(Result::Achievement achive1, Result::Achievement achive2, Result::Achievement achive3)
{
	if ((Flag & achive1) == achive1 && (Flag & achive2) == achive2 && (Flag & achive3) == achive3)
	{
		return true;
	}
	return false;
}
void Result::Flag_Input(Result::Achievement achive)
{
	Flag |= achive;
}
int Result::Get_Flag()
{
	return Flag;
}
int Result::GetFrameTime()
{
	return FrameTime;
}
void Result::Flag_Judge_Clear()
{
	Flag &= ~Flag;
}
void Result::Result_DataInput()
{
	std::string GameFalg;			//�Q�[���t���O
								//�f�[�^�̓ǂݍ���
	std::ifstream fin(TimeFilePath);

	if (!fin)
	{
		return;
	}
	//�ǂݍ��񂾃f�[�^�����Ă����ϐ�
	std::string line;
	//���s���I�����_�܂ł̕����̕������line�ɓ����
	std::getline(fin, line);
	//������𑀍삷�邽�߂̓��̓N���X�A���ڃA�N�Z�X����
	std::istringstream _fin(line);
	//�ꎚ�������ݕϐ�
	std::string text;
	//_fin�ɓ����Ă��镶���񂩂�','�܂ł̕�����text�ɂ����
	std::getline(_fin, text, ',');
	//text�̃f�[�^��ϐ��ɂ����
	(std::stringstream)text >> FrameTime;
	if (FrameTime <= 30)//30�b�ȓ��ɃS�[��
	{
		Flag_Input(Result::Achievement::Flag2);
		Flag_Input(Result::Achievement::Flag3);
		Flag_Input(Result::Achievement::Flag4);
	}
	else if (FrameTime <= 60)//60�b�ȓ��ɃS�[��
	{
		Flag_Input(Result::Achievement::Flag3);
		Flag_Input(Result::Achievement::Flag4);
	}
	else
	{
		Flag_Input(Result::Achievement::Flag4);
	}
	std::getline(_fin, text, ',');
	(std::stringstream)text >> GameFalg;
	if (GameFalg == "GameClear")		//�Q�[�����N���A
	{
		Flag_Input(Result::Achievement::Flag1);
	}
	//���Ԃ̌v�Z
	int sec, min, hour;
	sec = FrameTime % 60;
	min = FrameTime / 60;
	hour = min / 60;
	std::cout << hour << "����" << min << "��" << sec << "�b" << std::endl;

	fin.close();


}
//----------------------------
//�������牺��class���̂ݕύX����
//�ق��͕ύX���Ȃ�����
//----------------------------
Result::Result()
{
	std::cout << "���ʉ�ʏ����@����" << std::endl;
	//�J�������W�����ɖ߂�
	OGge->camera->SetPos(Vec2(0, 0));
	//�J�����̃T�C�Y�����ɖ߂�
	OGge->camera->SetSize(OGge->window->GetSize());
	FrameTime = 0;
	Flag_Judge_Clear();
}

Result::~Result()
{
	this->Finalize();
	std::cout << "���ʉ�ʏ����@���" << std::endl;
}

Result::SP Result::Create(bool flag_)
{

	Result::SP to = Result::SP(new Result());
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