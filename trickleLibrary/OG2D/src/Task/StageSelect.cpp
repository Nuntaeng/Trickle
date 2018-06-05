#include "StageSelect.h"
#include "Task\Task_Game.h"
#include "Task\Task_Title.h"
#include "Task\Task_StageAlert.h"
#include "Chara\Chara.h"
#include "Back\Back.h"
#include "Map\Map.h"
#include "Load\LoadLogo.h"
#include "Gate\Gate.h"

StageSelect::StageSelect()
{
	this->mode = Non;
	this->preMode = Non;
	this->timeCnt = 0;
	this->nowPos = -1;
	this->soundname = "title.wav";      //�T�E���h�̃t�@�C�����i�[
}

StageSelect::~StageSelect()
{
	this->Finalize();
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		if (state == State::ToTitle)
		{
			auto nexttask = Title::Create();
			nexttask->BackTitleSkip();
		}
		else
		{
			auto nexttask = Game::Create();
		}
	}
}

bool StageSelect::Initialize()
{
	//�摜�̓ǂݍ���
	this->Testdoor.Create((std::string)"door.png");
	//�v���C���[NPC�̐���
	auto chara = Chara::Create(std::string("player2.png"), Vec2(400, -200));
	chara->SetDirection(Chara::Direction::RIGHT);
	chara->SetAutoFlag(true);
	//�w�i�̕`��
	auto back = Back::Create(std::string("back.png"), Vec2(1920 + 200, 1080));
	//�}�b�v����
	auto map = Map::Create(std::string("select.csv"));
	map->SetDrawOrder(0.1f);
	//�X�e�[�W�T�v�\���p�ē���
	auto board = StageAlert::Create();
	//�T�E���h�̐���
	//�^�O�w��
	__super::Init((std::string)"select");
	//�`�揇�w��
	__super::SetDrawOrder(0.5f);
	//�������[�h�ݒ�
	this->mode = Mode::from1;
	//�e�X�g����
	OGge->camera->SetSize(Vec2(1920, 1080));
	OGge->camera->SetPos(Vec2(100, 0));
	//��~�ʒu�̐ݒ�
	for (int i = 1; i <= 3; ++i)
	{
		auto gate = Gate::Create((400.f * i) + 450.f, 640.f);
		gate->SetTexture(&this->Testdoor);
		this->Entrance.emplace_back(LEFT, gate->position.x - chara->Scale.x);
		this->Entrance.emplace_back(RIGTH, gate->position.x + gate->Scale.x);
	}
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (map->_arr[y][x] == 23)
			{
				//��q�ʒu(x���W)�̌���
				this->Entrance.emplace_back(LEFT, map->hitBase[y][x].position.x - chara->Scale.x);
			}
		}
	}
	//�ǂݍ��ݏI���Ń��[�h��ʂ�j��
	auto load = OGge->GetTasks<Load>("load");
	for (auto id = load->begin(); id != load->end(); ++id)
	{
		(*id)->Kill();
	}
	return true;
}

void StageSelect::UpDate()
{
	switch (this->mode)
	{
	case Mode::from1:	//�������痎���ƍd��
	{
		this->From1();
	}
	break;
	case Mode::from2:	//�L�����ƃJ�����̉��ړ�
	{
		this->From2();
	}
	break;
	case Mode::from3:	//����҂�
	{
		this->From3();
	}
	break;
	case Mode::from4:	//����㏈��
	{
		this->From4();
	}
	break;
	case Mode::End:		//����
	{
		this->Kill();
	}
	break;
	default:
		break;
	}
	this->ModeCheck();
}

void StageSelect::Render2D()
{
	
}

bool StageSelect::Finalize()
{
	//�摜�̉��
	this->Testdoor.Finalize();
	//�T�E���h�̉��
	delete rm->GetSoundData((std::string)"titleBGM");
	rm->DeleteSound((std::string)"titleBGM");
	//���̃I�u�W�F�N�g���Ő����������̂��폜����
	auto chara = OGge->GetTasks<Chara>("Chara");
	for (auto id = (*chara).begin(); id != (*chara).end(); ++id)
	{
		(*id)->Kill();
	}
	auto back = OGge->GetTasks<Back>("back");
	for (auto id = (*back).begin(); id != (*back).end(); ++id)
	{
		(*id)->Kill();
	}
	auto map = OGge->GetTasks<Map>("map");
	for (auto id = (*map).begin(); id != (*map).end(); ++id)
	{
		(*id)->Kill();
	}
	auto gates = OGge->GetTasks<Gate>("gate");
	for (auto id = gates->begin(); id != gates->end(); ++id)
	{
		(*id)->Kill();
	}
	auto alert = OGge->GetTasks<StageAlert>("stagealert");
	for (auto id = alert->begin(); id != alert->end(); ++id)
	{
		(*id)->Kill();
	}
	//����񂷂ׂč폜
	this->Entrance.clear();
	return true;
}

void StageSelect::From1()
{
	//�L����������
	auto chara = OGge->GetTask<Chara>("Chara");
	//���݂����ꍇ
	if (chara)
	{
		//�����蔻����s���ԍ��Ȃ��
		if (chara->CollisionNumCheck(-1))
		{
			//�n�ʂɐڐG���Ă��邩
			if (chara->FootCheck())
			{
				//���J�E���g�𒴂�����
				if (this->CheckTime(30))
				{
					//���ֈړ�
					this->mode = Mode::from2;
					this->camera_anim.Set(OGge->camera->GetPos(), Vec2(OGge->camera->GetPos().x + 100, OGge->camera->GetPos().y));
					this->nowPos = 0;
					chara->Set(chara->position, Vec2(this->Entrance[this->nowPos].second, chara->position.y), 10.f);
					auto gates = OGge->GetTasks<Gate>("gate");
					for (auto id = gates->begin(); id != gates->end(); ++id)
					{
						if (this->nowPos / 2 == (*id)->GetID())
						{
							(*id)->ToOpen();
						}
					}
				}
			}
			else
			{
				//���Ă��Ȃ�����0�ɂ��Ă���
				this->timeCnt = 0;
			}
		}
	}
}

void StageSelect::From2()
{
	//�J�����̈ʒu�𑗂�
	OGge->camera->SetPos(this->camera_anim.Move(10.f));
	//�ړ����I��������
	if (!this->camera_anim.isPlay())
	{
		//���ֈړ�
		this->mode = Mode::from3;
	}
}
void StageSelect::From3()
{
	auto chara = OGge->GetTask<Chara>("Chara");
	if (chara)
	{
		//�L�����N�^�[�������Ă��Ȃ����������͂��s��
		//�����łȂ��Ȃ�L�����N�^�[�̈ړ���ړI�n�܂ňړ�������
		if (!chara->isAutoPlay())
		{
			//Left����
			if (OGge->in->down(In::CL))
			{
				auto gates = OGge->GetTasks<Gate>("gate");
				if (chara->nowDirection() == Chara::Direction::LEFT)
				{
					if (this->nowPos > 1)
					{
						for (auto id = gates->begin(); id != gates->end(); ++id)
						{
							if (this->nowPos / 2 == (*id)->GetID())
							{
								(*id)->ToClose();
							}
						}
						this->nowPos -= 2;
						chara->Set(chara->position, Vec2(this->Entrance[this->nowPos].second, chara->position.y),10.f);
					}
				}
				else
				{
					if (this->nowPos > 0)
					{
						for (auto id = gates->begin(); id != gates->end(); ++id)
						{
							if (this->nowPos / 2 == (*id)->GetID())
							{
								(*id)->ToClose();
							}
						}
						this->nowPos -= 1;
						chara->Set(chara->position, Vec2(this->Entrance[this->nowPos].second, chara->position.y), 5.f);
					}
				}
				for (auto id = gates->begin(); id != gates->end(); ++id)
				{
					if (this->nowPos / 2 == (*id)->GetID())
					{
						(*id)->ToOpen();
					}
				}
			}
			//right����
			if (OGge->in->down(In::CR))
			{
				auto gates = OGge->GetTasks<Gate>("gate");
				if (chara->nowDirection() == Chara::Direction::RIGHT)
				{
					if (this->nowPos < 6)
					{
						for (auto id = gates->begin(); id != gates->end(); ++id)
						{
							if (this->nowPos / 2 == (*id)->GetID())
							{
								(*id)->ToClose();
							}
						}
						this->nowPos += 2;
						chara->Set(chara->position, Vec2(this->Entrance[this->nowPos].second, chara->position.y), 10.f);
					}
				}
				else
				{
					if (this->nowPos < 5)
					{
						for (auto id = gates->begin(); id != gates->end(); ++id)
						{
							if (this->nowPos / 2 == (*id)->GetID())
							{
								(*id)->ToClose();
							}
						}
						this->nowPos += 1;
						chara->Set(chara->position, Vec2(this->Entrance[this->nowPos].second, chara->position.y), 5.f);
					}
				}
				for (auto id = gates->begin(); id != gates->end(); ++id)
				{
					if (this->nowPos / 2 == (*id)->GetID())
					{
						(*id)->ToOpen();
					}
				}
			}
			//�������
			if (OGge->in->down(In::B2))
			{
				switch (this->nowPos)
				{
				case 0:
				case 1:
					this->state = State::Tutorial;
					*MapNum = 1;
					break;
				case 2:
				case 3:
					this->state = State::Stage1;
					*MapNum = 5;
					break;
				case 4:
				case 5:
					this->state = State::Stage2;
					*MapNum = 6;
					break;
				case 6:
					//��q�����
					this->state = State::ToTitle;
					break;
				default:
					this->state = State::ToTitle;
					break;
				}
				auto gates = OGge->GetTasks<Gate>("gate");
				for (auto id = gates->begin(); id != gates->end(); ++id)
				{
					if (this->nowPos / 2 == (*id)->GetID())
					{
						if (chara->nowDirection() == Chara::Direction::LEFT)
						{
							chara->Set(chara->position, Vec2((*id)->position.x - chara->Scale.x, chara->position.y), 10.0f);
							chara->SetRestriction((*id)->Get_Door_x());
							break;
						}
						else
						{
							chara->Set(chara->position, Vec2((*id)->position.x + (*id)->Scale.x, chara->position.y), 10.0f);
							chara->SetRestriction((*id)->Get_Door_w());
							break;
						}
					}
					else
					{
						//�h�A�̉��ɂ��Ȃ���(��q�̎�)
						chara->Set(chara->position, Vec2(this->Entrance[this->nowPos].second + chara->Scale.x, chara->position.y), 5.f);
					}
				}
				this->mode = Mode::from4;
			}
		}
	}

	auto board = OGge->GetTask<StageAlert>("stagealert");
	if (board) {

	}
}
void StageSelect::From4()
{
	auto chara = OGge->GetTask<Chara>("Chara");
	
	if (chara)
	{
		if (!chara->isAutoPlay())
		{
			if (this->nowPos == 6)
			{
				this->nowPos += 1;
				chara->Set(chara->position, Vec2(chara->position.x, -200.f), 30.f);
				return;
			}
			this->GateClose();
		}
	}
	else
	{
		this->GateClose();
	}
}
void StageSelect::ModeCheck()
{
	if (this->preMode != this->mode)
	{
		this->timeCnt = 0;
		this->preMode = this->mode;
	}
	else
	{
		this->timeCnt++;
	}
}

void StageSelect::GateClose()
{
	auto gates = OGge->GetTasks<Gate>("gate");
	for (auto id = gates->begin(); id != gates->end(); ++id)
	{
		if (this->nowPos / 2 == (*id)->GetID())
		{
			if ((*id)->ToClose())
			{
				this->timeCnt = 0;
			}
		}
	}
	if (this->timeCnt > 40)
	{
		this->mode = Mode::End;
	}
}


StageSelect::Animation::Animation()
{

}

void StageSelect::Animation::Set(Vec2& start_, Vec2& end_)
{
	this->StartPos = start_;
	this->EndPos = end_ - start_;
}

Vec2 StageSelect::Animation::Move()
{
	return Vec2(this->easing_x.sine.In(this->easing_x.Time(10), this->StartPos.x, this->EndPos.x, 10), this->easing_y.sine.In(this->easing_y.Time(10), this->StartPos.y, this->EndPos.y, 10));
}

Vec2 StageSelect::Animation::Move(const float time)
{
	return Vec2(this->easing_x.sine.In(this->easing_x.Time(time), this->StartPos.x, this->EndPos.x, 10), this->easing_y.sine.In(this->easing_y.Time(time), this->StartPos.y, this->EndPos.y, time));
}

bool StageSelect::Animation::isPlay() const
{
	if (this->easing_x.isplay() || this->easing_y.isplay())
	{
		return true;
	}
	return false;
}

bool StageSelect::CheckTime(int t)
{
	return this->timeCnt > t ? true : false;
}


StageSelect::SP StageSelect::Create(bool flag_)
{
	auto to = StageSelect::SP(new StageSelect());
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
