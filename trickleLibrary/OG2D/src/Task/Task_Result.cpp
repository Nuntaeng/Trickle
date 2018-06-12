#include "Task_Result.h"
//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
#include "Task\StageSelect.h"
#include "GameProcessManagement\FlagUI.h"
#include "Player\ResultPlayer.h"
#include "GameProcessManagement\ClearUI.h"
#include "GameProcessManagement\GoalTimeUI.h"
#include "GameProcessManagement\MissionUI.h"
#include "GameProcessManagement\FrameTime.h"
#include "Effect/SterEffect.h"
#include "GameProcessManagement/GameProcessManagement.h"
#include "Effect\SterEffect.h"

///285 

bool Result::Initialize()
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "Result";		//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	//�t���O�̐ݒ�
	this->Result_DataInput();

	this->image.Create((std::string)"back.png");
	this->maptile.Create((std::string)"tile.jpg");

	SetDrawOrder(0.0f);

	Vec2 camerasize = OGge->camera->GetSize();
	Vec2 windowsize = OGge->window->GetSize();
	//�J�����̃T�C�Y�ƃE�B���h�E�ɂ�����A�X�y�N�g��̌v�Z
	Vec2 aspect = Vec2(camerasize.x / windowsize.x, camerasize.y / windowsize.y);

	//�����t���O�����Z�b�g����
	this->createtask.ResetCreateFlag();
	this->createtask.ResetNextFlag();
	this->createtask.SetNextFlag(CreateFlag::Timeui);

	//���U���g��ʂɕ\���ɂ���
	auto player = ResultPlayer::Create(Vec2(-96, (int)camerasize.y - 50 - 96), Vec2(3, 0));
	auto mission = MissionUI::Create();
	std::cout << "���ʉ�ʏ����@������" << std::endl;
	return true;
}

void Result::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------
	//�^�C�g���V�[���֑J��
	
	//�������܂��`�F�b�N����
	this->UI_Think();
	//�t���O�ɂ����Create����
	this->UI_Create();

	auto resultplayer = OGge->GetTask<ResultPlayer>("ResultPlayer");
	if (!resultplayer)
	{
		if (OGge->in->down(In::B2))
		{
			Kill();
		}
	}
	
}
void Result::Render2D()
{
	//--------------------
	//�`�掞�ɍs���������L�q
	//--------------------
	Vec2 camerasize = OGge->camera->GetSize();
	{
		Box2D draw(Vec2(0, 0), camerasize);
		draw.OffsetSize();
		Box2D src = this->backSrc;
		src.OffsetSize();
		image.Draw(draw, src);
	}
	{
		int count = 0;
		for (int y = camerasize.y - 50; y <= camerasize.y; y += 64)
		{
			for (int x = 0; x <= camerasize.x / 64; ++x)
			{
				Box2D draw(Vec2(x * 64, (int)camerasize.y - 50 + count * 64), Vec2(64, 64));
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
		auto effect = OGge->GetTasks<SterEffect>("SterEffect");
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
		for (auto id = (*effect).begin(); id != (*effect).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*frametime).begin(); id != (*frametime).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*mission).begin(); id != (*mission).end(); ++id)
		{
			(*id)->Kill();
		}
		auto stageselect = StageSelect::Create();
	}
	return true;
}
void Result::CreateTask::ResetCreateFlag()
{
	this->createflag &= ~this->createflag;
}
void Result::CreateTask::ResetNextFlag()
{
	this->nextflag &= ~this->nextflag;
}
void Result::CreateTask::SetCreateFlag(CreateFlag flag)
{
	this->createflag |= flag;
}
void Result::CreateTask::SetNextFlag(CreateFlag flag)
{
	this->nextflag |= flag;
}
void Result::UI_Think()
{
	switch (this->createtask.nextflag)
	{
	case 1 << 0:
		if ((this->createtask.nextflag & 0x0F) == CreateFlag::Timeui)
		{
			auto player = OGge->GetTask<ResultPlayer>("ResultPlayer");
			if (player != nullptr)
			{
				//Player���~�܂�����E�E�E
				if (player->GetResetWalkStop())
				{
					this->createtask.SetCreateFlag(CreateFlag::Timeui);
				}
			}
		}
		break;
	case 1 << 1:
		if ((this->createtask.nextflag & 0x0F) == CreateFlag::Starui)
		{
			auto frametimeUI = OGge->GetTasks<FrameTimeUI>("FrameTimeUI");
			for (auto id = (*frametimeUI).begin(); id != (*frametimeUI).end(); ++id)
			{
				//�^�C��UI�̉��o���I��������E�E�E
				if ((*id)->GetIsPlay())
				{
					this->createtask.SetCreateFlag(CreateFlag::Starui);
				}
			}
		}
		break;
	case 1 << 2:
		if ((this->createtask.nextflag & 0x0F) == CreateFlag::Effect)
		{
			auto sters = OGge->GetTasks<FlagUI>("Ster");
			for (auto id = (*sters).begin(); id != (*sters).end(); ++id)
			{
				if ((*id)->EasingEnd())
				{
					this->createtask.SetCreateFlag(CreateFlag::Effect);
				}
			}

		}
		break;
	case 1 << 3:
		if ((this->createtask.nextflag & 0x0F) == CreateFlag::Clearui)
		{
			auto sters = OGge->GetTasks<FlagUI>("Ster");
			std::vector<bool> flag;
			for (auto id = (*sters).begin(); id != (*sters).end(); ++id)
			{
				flag.push_back((*id)->GetEffectEnd());
			}
			//�S�Ă�Effect�̉��o���I��������
			for (auto id = (*sters).begin(); id != (*sters).end(); ++id)
			{
				if (std::all_of(flag.begin(), flag.end(), [](bool flag) {return flag == true; }))
				{
					this->createtask.SetCreateFlag(CreateFlag::Clearui);
				}
			}
		}
		break;
	default:
		break;
	}
}
void Result::UI_Create()
{
	///���ӁI�I�@�����̓t���O���Z�b�g����1�t���[���̂ݓ������֐��ł��B
	Vec2 camerasize = OGge->camera->GetSize();
	Vec2 windowsize = OGge->window->GetSize();
	//�J�����̃T�C�Y�ƃE�B���h�E�ɂ�����A�X�y�N�g��̌v�Z
	Vec2 aspect = Vec2(camerasize.x / windowsize.x, camerasize.y / windowsize.y);

	switch (this->createtask.createflag)
	{
	case 1 << 0:
		//Player�����̂Ƃ���܂ŕ�������E�E�E
		if ((this->createtask.createflag & CreateFlag::Timeui) == CreateFlag::Timeui)
		{
			auto goaltime = GoalTimeUI::Create(Vec2(camerasize.x * 0.15f, camerasize.y * 0.2f));
			for (int i = 0; i < 5; ++i)
			{
				auto time = FrameTimeUI::Create(Vec2(goaltime->position.x + goaltime->Scale.x + (20 + i * 64), goaltime->position.y + 20), i, FrameTime);
			}
			//��������t���O�����Z�b�g����
			this->createtask.ResetCreateFlag();
			this->createtask.ResetNextFlag();
			//���ɐ�������^�X�N
			this->createtask.SetNextFlag(CreateFlag::Starui);
		}
		break;
	case 1 << 1:
		if ((this->createtask.createflag & CreateFlag::Starui) == CreateFlag::Starui)
		{
			int selectflag[3] = {GameProcessManagement::Flag4,GameProcessManagement::Flag3,GameProcessManagement::Flag2};

			for (int i = 0; i < 3; ++i)
			{
				auto ster = FlagUI::Create(Vec2((camerasize.x / 2 - 200) + 100 * (i + 1) , camerasize.y * 0.5f), selectflag[i]);	
			}
			//�t���O�̃��Z�b�g
			this->createtask.ResetCreateFlag();
			this->createtask.ResetNextFlag();
			//���ɐ�������^�X�N
			this->createtask.SetNextFlag(CreateFlag::Effect);
		}
		break;
	case 1 << 2:
		if ((this->createtask.createflag & CreateFlag::Effect) == CreateFlag::Effect)
		{
			auto sters = OGge->GetTasks<FlagUI>("Ster");

			//�ŏ������͏����Ȃ��Ő�������
			{
				int count = 0;
				for (auto id = sters->begin(); id != sters->end(); ++id, ++count)
				{
					if (count == 0)
					{
						auto effect = SterEffect::Create((*id));
					}
					else
					{
						auto Effect = OGge->GetTasks<SterEffect>("SterEffect");
						if (!Effect)
						{
							continue;
						}
						auto effect = SterEffect::Create((*id), *(Effect->begin() + count - 1));
					}
				}
			}
			//��������t���O�����Z�b�g����
			this->createtask.ResetCreateFlag();
			this->createtask.ResetNextFlag();
			//���ɐ�������^�X�N
			this->createtask.SetNextFlag(CreateFlag::Clearui);
		}
		break;
	case 1 << 3:
		if ((this->createtask.createflag & CreateFlag::Clearui) == CreateFlag::Clearui)
		{
			auto clearui = ClearUI::Create(Vec2(camerasize.x * 0.70f, camerasize.y / 2));
			//�t���O�̃��Z�b�g
			this->createtask.ResetCreateFlag();
			this->createtask.ResetNextFlag();
			//���ɐ�������^�X�N
			this->createtask.SetNextFlag(CreateFlag::NON);
		}
		break;
	default:
		break;
	}	
}
int Result::to_String(std::string& text)
{
	std::istringstream ss;
	ss = std::istringstream(text);

	int num = atoi(text.c_str());
	ss >> num;

	return num;
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
	//�t�@�C���S�̂̃e�L�X�g��ǂݍ���
	while (std::getline(fin, line))
	{
		//������𑀍삷�邽�߂̓��̓N���X�A���ڃA�N�Z�X����
		std::istringstream _fin(line);
		//�ꎚ�������ݕϐ�
		std::string text;
		
		//�^�C���̏�������
		std::getline(_fin, text, ',');
		(std::stringstream)text >> FrameTime;

		//�X�e�[�W���Ƃ̃t���O����������
		std::string nowStagenumber;
		int nowStage = 0;

		//�t���O�̏�������
		while (std::getline(_fin, text, ','))
		{
			if (text == "Stage1")
			{
				nowStagenumber = text.substr(5);
				//�����񂩂�int�^�ɂ���
				 nowStage = this->to_String(nowStagenumber);
			}
			else if(text == "Stage2")
			{
				nowStagenumber = text.substr(5);
				//�����񂩂�int�^�ɂ���
				nowStage = this->to_String(nowStagenumber);
			}

		}

	}
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
	std::getline(_fin, text, ',');
	(std::stringstream)text >> GameFalg;


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
	OGge->camera->SetSize(Vec2(60 * 16 , 60 * 9));
	FrameTime = 0;
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