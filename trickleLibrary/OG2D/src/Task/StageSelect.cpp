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
	this->decisionsoundname = "decision.wav";
	this->canVolControl = false;
	this->isPause = false;
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
	this->Wall.Create((std::string)"wall2.PNG");
	this->LadderTex.Create("mapchip2.png");
	//�v���C���[NPC�̐���
	auto chara = Chara::Create(std::string("player.png"), Vec2(400, -200));
	chara->SetDirection(Chara::Direction::RIGHT);
	chara->SetAutoFlag(true);
	//�w�i�̕`��
	auto back = Back::Create(std::string("back.png"), Vec2(1920 * 2 + 200, 1080));
	//�}�b�v����
	auto map = Map::Create(std::string("select.csv"));
	map->SetDrawOrder(0.5f);
	//�X�e�[�W�T�v�\���p�ē���
	auto board = StageAlert::Create(true, Box2D(400, 0, 1328, 550));
	auto board2 = StageAlert::Create(true, Box2D(400 + ((int)OGge->window->GetSize().x * 2), 0, 1328, 550));
	(*board) << "./data/monitor0.txt";
	(*board) << "./data/monitor1.txt";
	(*board) << "./data/monitor2.txt";
	(*board2) << "./data/monitor3.txt";
	(*board2) << "./data/monitor4.txt";
	(*board2) << "./data/monitor5.txt";
	//�T�E���h�̐���
	//BGM
	if (rm->GetSoundData((std::string)"titleBGM") == nullptr)
	{
		sound = new Sound();

		sound->create(soundname, true);
		rm->SetSoundData((std::string)"titleBGM", sound);
		//this->canVolControl = true;
		sound->play();
	}
	//���艹
	decisionsound.create(decisionsoundname, false);

	//�^�O�w��
	__super::Init((std::string)"select");
	//�`�揇�w��
	__super::SetDrawOrder(0.3f);
	//�������[�h�ݒ�
	this->mode = Mode::from1;
	//�e�X�g����
	OGge->camera->SetSize(Vec2(1920, 1080));
	OGge->camera->SetPos(Vec2(100, 0));
	this->doorNumber = 6;
	//��~�ʒu�̐ݒ�
	for (int i = 1; i <= this->doorNumber / 2; ++i)
	{
		auto gate = Gate::Create((490.f * i) + 100.f, 640.f);      //���f�[�^(490.f*i)+450.f
		gate->SetTexture(&this->Testdoor);
		this->Entrance.emplace_back(LEFT, gate->position.x - chara->Scale.x);
		this->Entrance.emplace_back(RIGTH, gate->position.x + gate->Scale.x);
	}
	for (int i = 1; i <= this->doorNumber / 2; ++i)
	{
		auto gate = Gate::Create((490.f * i) + 100.f + 1920.f, 640.f);      //���f�[�^(490.f*i)+450.f
		gate->SetTexture(&this->Testdoor);
		this->Entrance.emplace_back(LEFT, gate->position.x - chara->Scale.x);
		this->Entrance.emplace_back(RIGTH, gate->position.x + gate->Scale.x);
	}
	this->Entrance.emplace_back(LEFT, 31.f * 64.f + 1920.f - chara->Scale.x);
	auto load = OGge->GetTask<Load>("load");
	if (load)
	{
		load->Set(Load::Fead::Out);
		load->ALLTaskUpDateStop();
	}
	return true;
}

void StageSelect::UpDate()
{
	if (canVolControl)
	{
		if (rm->GetSoundData((std::string)"titleBGM") == nullptr)
		{
			sound->volume(volControl.FadeOut(this->canVolControl));
		}
		else
		{
			sound = rm->GetSoundData((std::string)"titleBGM");
			sound->volume(volControl.FadeOut(this->canVolControl));
		}
	}
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
		this->canVolControl = true;
	}
	break;
	case Mode::End:		//����
	{
		auto load = Load::Create();
		if (load)
		{
			load->AddObject(this->GetTaskName());
		}
	}
	break;
	default:
		break;
	}
	this->ModeCheck();
}

void StageSelect::PauseUpDate()
{
	OGge->camera->SetPos(this->camera_anim.Move(10.f));
	if (!this->camera_anim.isPlay())
	{
		this->timeCnt++;
		OGge->SetPause(false);
		this->isPause = false;
	}
}

void StageSelect::Render2D()
{

	//�ǂ̕`��
	{
		Box2D draw = Box2D(450, 600, 1500, 300);
		draw.OffsetSize();
		Box2D src = Box2D(0.f, 0.f, Wall.GetTextureSize().x, Wall.GetTextureSize().y);
		this->Wall.Draw(draw, src);
		//OG::LineHitDraw(&draw);
	}
	for (int i = 0; i < 8; ++i)
	{
		Box2D draw(31.f*64.f + 1920.f, i * 128.f, 128.f, 128.f);
		draw.OffsetSize();
		Box2D src(768, 256, 256, 256);
		src.OffsetSize();
		this->LadderTex.Draw(draw, src);
	}
}

bool StageSelect::Finalize()
{
	//�摜�̉��
	this->Testdoor.Finalize();
	this->Wall.Finalize();
	this->LadderTex.Finalize();
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
		auto board = OGge->GetTasks<StageAlert>("stagealert");
		//if (board) {
		//	board->setActive(true);
		//	board->SetStageData("./data/monitor0.txt");
		//}
		for (auto id = board->begin(); id != board->end(); ++id)
		{
			(*id)->setActive(true);
			(*id)->SelectFirstElement();
		}
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
			if (OGge->in->down(In::CL) || OGge->in->down(In::LL))
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
				//��ʂ��ς��Ȃ�΃J�������ړ�����
				if (this->nowPos == 5)
				{
					this->camera_anim.Set(OGge->camera->GetPos(), Vec2(200.f, 0.f));
					this->timeCnt = 0;
					this->isPause = true;
				}
				auto board = OGge->GetTasks<StageAlert>("stagealert");
				std::string curStageName = "./data/monitor" + std::to_string(this->nowPos / 2) + ".txt";
				//if (board && board->isExist(curStageName)) {
				//	//board->AnimPlay();
				//	board->SetStageData(curStageName);
				//}
				for (auto id = board->begin(); id != board->end(); ++id)
				{
					if ((*id)->isExist(curStageName))
					{
						(*id)->SetStageData(curStageName);
					}
				}
			}
			//right����
			if (OGge->in->down(In::CR) || OGge->in->down(In::LR))
			{
				auto gates = OGge->GetTasks<Gate>("gate");
				if (chara->nowDirection() == Chara::Direction::RIGHT)
				{
					if (this->nowPos < this->doorNumber * 2)
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
					if (this->nowPos < this->doorNumber * 2)
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
				//��ʂ��ς��Ȃ�J�����̈ړ�
				if (this->nowPos == 6)
				{
					this->camera_anim.Set(OGge->camera->GetPos(), Vec2(OGge->camera->GetSize().x + 200.f, 0.f));
					this->timeCnt = 0;
					this->isPause = true;
				}
				auto board = OGge->GetTasks<StageAlert>("stagealert");
				std::string curStageName = "./data/monitor" + std::to_string(this->nowPos / 2) + ".txt";
				//if (board && board->isExist(curStageName)) {
				//	//board->AnimPlay();
				//	board->SetStageData(curStageName);
				//}
				for (auto id = board->begin(); id != board->end(); ++id)
				{
					if ((*id)->isExist(curStageName))
					{
						(*id)->SetStageData(curStageName);
					}
				}
			}
			//�������
			if (OGge->in->down(In::B2))
			{
				//�T�E���h�̍Đ�
				decisionsound.play();

				switch (this->nowPos)
				{
				case 0:
				case 1:
					this->state = State::Tutorial1;
					*MapNum = 1;
					break;
				case 2:
				case 3:
					this->state = State::Tutorial2;
					*MapNum = 5;
					break;
				case 4:
				case 5:
					this->state = State::Tutorial3;
					//*MapNum = 6;
					*MapNum = 9;
					break;
				case 6:
				case 7:
					//��q�����
					this->state = State::Stage1;
					//*MapNum = 1;
					*MapNum = 13;
					break;
				case 8:
				case 9:
					this->state = State::Stage2;
					//*MapNum = 5;
					*MapNum = 14;
					break;
				case 10:
				case 11:
					this->state = State::Stage3;
					//*MapNum = 6;
					*MapNum = 15;
					break;
				case 12:
					this->state = State::ToTitle;
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
		else
		{
			if(chara->position.x >= 2016.f && chara->position.x <= 2144.f && this->isPause)
			{
				OGge->SetPause(true);
			}
		}
	}
}
void StageSelect::From4()
{
	auto chara = OGge->GetTask<Chara>("Chara");
	
	if (chara)
	{
		if (!chara->isAutoPlay())
		{
			if (this->nowPos == 12)
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
		if (this->timeCnt >= 10000)
		{
			this->timeCnt = 1000;
		}
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
	this->easing_x.ResetTime();
	this->easing_y.ResetTime();
}

Vec2 StageSelect::Animation::Move()
{
	return Vec2(this->easing_x.sine.In(this->easing_x.Time(10), this->StartPos.x, this->EndPos.x, 10), this->easing_y.sine.In(this->easing_y.Time(10), this->StartPos.y, this->EndPos.y, 10));
}

Vec2 StageSelect::Animation::Move(const float time)
{
	return Vec2(this->easing_x.sine.Out(this->easing_x.Time(time), this->StartPos.x, this->EndPos.x, 10), this->easing_y.linear.In(this->easing_y.Time(time), this->StartPos.y, this->EndPos.y, time));
}

Vec2 StageSelect::Animation::Move(const Easing::Name name, const Easing::Mode mode, const float time)
{
	switch (name)
	{
	case Easing::Name::Back:
		break;
	case Easing::Name::Bounce:
		break;
	case Easing::Name::Circ:
		break;
	case Easing::Name::Cubic:
		break;
	case Easing::Name::Elastic:
		break;
	case Easing::Name::Expo:
		break;
	case Easing::Name::Quad:
		break;
	case Easing::Name::Quart:
		break;
	case Easing::Name::Quint:
		break;
	case Easing::Name::Sine:
		break;
	default:
		break;
	}
	return Vec2(this->easing_x.sine.In(this->easing_x.Time(time), this->StartPos.x, this->EndPos.x, 10), this->easing_y.sine.In(this->easing_y.Time(time), this->StartPos.y, this->EndPos.y, time));
}

bool StageSelect::Animation::isPlay() const
{
	return this->easing_x.isplay() || this->easing_y.isplay() ? true : false;
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
