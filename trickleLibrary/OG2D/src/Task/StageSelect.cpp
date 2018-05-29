#include "StageSelect.h"
#include "Task\Task_Game.h"
#include "Task\Task_Title.h"
#include "Chara\Chara.h"
#include "Back\Back.h"
#include "Map\Map.h"
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
	for (int i = 2; i >= 0; --i)
	{
		delete this->gate[i];
	}
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		if (state == State::ToTitle)
		{
			auto nexttask = Title::Create();
		}
		else
		{
			auto nexttask = Game::Create();
		}
	}
}

bool StageSelect::Initialize()
{
	cursorPos.x = 600.0f;
	cursorPos.y = 100.0f;

	tutorialPos = Vec2(700.0f, 100.0f);
	stage1Pos = Vec2(700.0f, 200.0f);
	stage2Pos = Vec2(700.0f, 300.0f);
	toTitlePos = Vec2(700.0f, 400.0f);

	Vec2 kari = toTitlePos;
	toTitlePos = stage2Pos;
	stage2Pos = kari;
	//�摜�̓ǂݍ���
	texBack.Create((std::string)"back.png");
	texCursor.Create((std::string)"Collision.png");
	texTutorial.Create((std::string)"tutorial.png");
	texStage1.Create((std::string)"stage1.png");
	texStage2.Create((std::string)"stage2.png");
	texToTitle.Create((std::string)"totitle.png");
	this->Testdoor.Create((std::string)"testResource.png");
	//�v���C���[NPC�̐���
	auto chara = Chara::Create(std::string("player2.png"), Vec2(10, -200));
	chara->SetDirection(Chara::Direction::RIGHT);
	chara->SetAutoFlag(true);
	//�w�i�̕`��
	auto back = Back::Create(std::string("back.png"), Vec2(1920 + 200, 1080));
	//�}�b�v����
	auto map = Map::Create(std::string("select.csv"));
	map->SetDrawOrder(0.1f);
	//�T�E���h�̐���
	/*sound.create(soundname, true);
	sound.volume(1.0f);
	OGge->soundManager->SetSound(&sound);

	sound.play();*/
	//sound = rm->GetSoundData(std::string(""));
	//�^�O�w��
	__super::Init((std::string)"select");
	//�`�揇�w��
	__super::SetDrawOrder(0.5f);
	//�������[�h�ݒ�
	this->mode = Mode::from1;
	//�e�X�g����
	OGge->camera->SetSize(Vec2(1920, 1080));
	//��~�ʒu�̐ݒ�
	for (int i = 1; i <= 3; ++i)
	{
		this->gate[i - 1] = new GameObject(Cube, Vec2(400 * i + 450, 640), Vec2(128, 256), 0.0f);
		this->Entrance.emplace_back(LEFT, gate[i - 1]->position.x - chara->Scale.x);
		this->Entrance.emplace_back(RIGTH, gate[i - 1]->position.x + gate[i - 1]->Scale.x);
	}
	return true;
}

void StageSelect::UpDate()
{
	CursorMove();

	if (OGge->in->down(In::B2))
	{
		switch (state) {
		case Tutorial:
			*MapNum = 3;
			if (OGge->in->on(In::SL))
			{
				*MapNum = 1;
			}
			if (OGge->in->on(In::SR))
			{
				*MapNum = 2;
			}
			break;
		case Stage1:
			*MapNum = 5;	break;
		case Stage2:	//������
						//*MapNum = 6;	break;
			break;
		case ToTitle:
			break;
		default:
			*MapNum = 0;	break;
		}
		this->Kill();
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
	//�J�[�\��
	{
		Box2D draw(cursorPos.x, cursorPos.y, 64.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 128, 128);
		src.OffsetSize();
		texCursor.Draw(draw, src);
	}
	//�`���[�g���A��
	{
		Box2D draw(tutorialPos.x, tutorialPos.y, 256.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 256);
		src.OffsetSize();
		texTutorial.Draw(draw, src);
	}
	//�X�e�[�W�P
	{
		Box2D draw(stage1Pos.x, stage1Pos.y, 256.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 256);
		src.OffsetSize();
		texStage1.Draw(draw, src);
	}
	//�X�e�[�W�Q
	{
		/*Box2D draw(stage2Pos.x, stage2Pos.y, 256.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 256);
		src.OffsetSize();
		texStage2.Draw(draw, src);*/
	}
	//�^�C�g���ɖ߂�
	{
		Box2D draw(toTitlePos.x, toTitlePos.y, 256.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 256);
		src.OffsetSize();
		texToTitle.Draw(draw, src);
	}
	//�h�A
	for (int i = 0; i < 3; ++i)
	{
		Box2D draw(this->gate[i]->position, this->gate[i]->Scale);
		draw.OffsetSize();
		Box2D src(0.f, 0.f, this->Testdoor.GetTextureSize().x, this->Testdoor.GetTextureSize().y);
		this->Testdoor.Draw(draw, src);
	}
}

bool StageSelect::Finalize()
{
	texBack.Finalize();
	texCursor.Finalize();
	texTutorial.Finalize();
	texStage1.Finalize();
	texStage2.Finalize();
	texToTitle.Finalize();
	this->Testdoor.Finalize();
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
	return true;
}

void StageSelect::CursorMove() {
	if (cursorPos.y > tutorialPos.y)
	{
		if (OGge->in->down(In::CU))
		{
			cursorPos.y -= 100.0f;
		}
	}
	if (cursorPos.y < toTitlePos.y)
	{
		if (OGge->in->down(In::CD))
		{
			cursorPos.y += 100.0f;
		}
	}

	if (cursorPos.y == tutorialPos.y)
	{
		state = Tutorial;
	}
	if (cursorPos.y == stage1Pos.y)
	{
		state = Stage1;
	}
	if (cursorPos.y == stage2Pos.y)
	{
		state = Stage2;
	}
	if (cursorPos.y == toTitlePos.y)
	{
		state = ToTitle;
	}

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
				if (this->timeCnt > 60)
				{
					//���ֈړ�
					this->mode = Mode::from2;
					this->camera_anim.Set(OGge->camera->GetPos(), Vec2(OGge->camera->GetPos().x + 200, OGge->camera->GetPos().y));
					this->nowPos = 0;
					chara->Set(chara->position, Vec2(this->Entrance[this->nowPos].second, chara->position.y));
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
	//�L�����̏����擾
	auto chara = OGge->GetTask<Chara>("Chara");
	//���݂��Ă���ꍇ
	if (chara)
	{
		//�����ړ���������
		//chara->ManualMove(Vec2(3.0f, 0.0f));
	}
	//�J�����̈ʒu�𑗂�
	OGge->camera->SetPos(this->camera_anim.Move());
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
			if (OGge->in->down(In::CL))
			{
				if (chara->nowDirection() == Chara::Direction::LEFT)
				{
					if (this->nowPos > 1)
					{
						this->nowPos -= 2;
					}
				}
				else
				{
					if (this->nowPos > 0)
					{
						this->nowPos -= 1;
					}
				}
				chara->Set(chara->position, Vec2(this->Entrance[this->nowPos].second, chara->position.y));
			}
			if (OGge->in->down(In::CR))
			{
				if (chara->nowDirection() == Chara::Direction::RIGHT)
				{
					if (this->nowPos < 4)
					{
						this->nowPos += 2;
					}
				}
				else
				{
					if (this->nowPos < 5)
					{
						this->nowPos += 1;
					}
				}
				chara->Set(chara->position, Vec2(this->Entrance[this->nowPos].second, chara->position.y));

			}
			if (OGge->in->key.down(In::ENTER))
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
				default:
					this->state = State::ToTitle;
					break;
				}
				chara->Set(chara->position, Vec2(this->gate[this->nowPos / 2]->position.x, chara->position.y));
				this->mode = Mode::from4;
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
			this->mode = Mode::End;
		}
	}
	else
	{
		this->mode = Mode::End;
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

bool StageSelect::Animation::isPlay() const
{
	if (this->easing_x.isplay() || this->easing_y.isplay())
	{
		return true;
	}
	return false;
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