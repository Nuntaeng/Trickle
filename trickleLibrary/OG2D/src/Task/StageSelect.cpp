#include "StageSelect.h"
#include "Task\Task_Game.h"
#include "Task\Task_Title.h"
#include "Chara\Chara.h"
#include "Back\Back.h"
StageSelect::StageSelect()
{
	this->mode = Non;
	this->preMode = Non;
}

StageSelect::~StageSelect()
{
	this->Finalize();
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

	texBack.Create((std::string)"back.png");
	texCursor.Create((std::string)"Collision.png");
	texTutorial.Create((std::string)"tutorial.png");
	texStage1.Create((std::string)"stage1.png");
	texStage2.Create((std::string)"stage2.png");
	texToTitle.Create((std::string)"totitle.png");
	//�v���C���[NPC�̐���
	//auto chara = Chara::Create(std::string("player2.png"), Vec2(50, -200));
	//�w�i�̕`��
	//auto back = Back::Create(std::string("back.png"), Vec2(1920 + 200, 1080));
	//�^�O�w��
	__super::Init((std::string)"select");
	//�`�揇�w��
	__super::SetDrawOrder(0.5f);
	//�������[�h�ݒ�
	this->mode = Mode::from1;
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
			if (OGge->in->on(In::SL))	//�L�[�{�[�hB
			{
				*MapNum = 1;
			}
			if (OGge->in->on(In::SR))	//�L�[�{�[�hN
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
}

void StageSelect::Render2D()
{
	//�w�i
	{
		Box2D draw(Vec2(0, 0), OGge->window->GetSize());
		draw.OffsetSize();
		Box2D src(0, 0, 1920, 1080);
		src.OffsetSize();
		texBack.Draw(draw, src);
	}
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


}

bool StageSelect::Finalize()
{
	texBack.Finalize();
	texCursor.Finalize();
	texTutorial.Finalize();
	texStage1.Finalize();
	texStage2.Finalize();
	texToTitle.Finalize();
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
				if (this->timeCnt > 120)
				{
					//���ֈړ�
					this->mode = Mode::from2;
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
	auto chara = OGge->GetTask<Chara>("Chara");
	if (chara)
	{

	}
	//OGge->camera->SetPos(this->camera_x.quad.InOut())
}
void StageSelect::From3()
{

}
void StageSelect::From4()
{

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