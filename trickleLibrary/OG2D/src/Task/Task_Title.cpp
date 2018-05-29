#include "Task_Title.h"
#include "Task\Task_Option.h"
#include "Task\StageSelect.h"
#include "Water\water.h"
#include "Map\Map.h"
#include "Back\Back.h"
#include "Chara\Chara.h"
Title::Title()
{
	this->mode = Non;
	this->preMode = Non;
	this->timeCnt = 0;
	this->tex_a = 0.0f;
	this->cursor_a = 0.0f;
	this->cursorNum = 0;
	this->isGierAng = false;
	this->flowerVolume = 0.f;
	this->soundname = "title.wav";     //�T�E���h�̃t�@�C����	
	this->sound = nullptr;
}

Title::~Title()
{
	this->Finalize();
}

bool Title::Initialize()
{
	std::cout << "Title������" << std::endl;
	//�w�i�ǂݍ���
	auto back = Back::Create((std::string)"back.png", 1440, 810);
	//���S�I�u�W�F�N�g����
	this->Logo.CreateObject(Cube, Vec2(400, 250), Vec2(640, 384), 0.0f);
	this->Logo.Radius = { 1.0f,0.5f };
	//�����ʒu�ݒ�
	//startPos = Vec2(720.f - 128.f,624.f + 30.f);
	startPos = Vec2(720.f - 128.f, 624.f + 129.f + 30.f);
	closePos = Vec2(720.f - 128.f, 624.f + 258.f + 30.f);
	//�z��Ǘ����s��
	//this->cursorPos[0] = { this->startPos.x - 30.f - 64.f,this->startPos.y };
	this->cursorPos[0] = { this->startPos.x - 30.f - 64.f,this->startPos.y };
	this->cursorPos[1] = { this->closePos.x - 30.f - 64.f,this->closePos.y };
	//�摜�ǂݍ���
	texCursor.Create((std::string)"gear.png");
	texStart.Create((std::string)"start.png");
	texClose.Create((std::string)"close.png");
	texPause.Create((std::string)"pause.png");
	this->texLogo.Create((std::string)"logo.png");
	this->GierLogo.Create((std::string)"gearofi.png");
	this->flowerLogo.Create((std::string)"flower.png");
	//�T�E���h�̐���
	sound = new Sound();
	sound->create(soundname, true);
	rm->SetSoundData((std::string)"titleBGM", sound);
	//�J�����ʒu�̈ړ�
	OGge->camera->SetPos(Vec2(OGge->window->GetSize().x / 2, 0.f));
	//���ǂݍ��݂Ɛ���
	auto water = Water::Create(Vec2(500.f, 0.f));
	waterTex.Create((std::string)"waterTex.png");
	water->SetTexture(&this->waterTex);
	water->SetMaxSize(Vec2(128, 128));

	//�}�b�v����(�n�ʗp)
	auto map = Map::Create((std::string)"title.csv");
	//���̈ʒu�Ŏg�p����
	this->nextTaskCheck = 0;
	//�^�O�ݒ�
	__super::Init((std::string)"title");
	//�`�揇�̌���
	__super::SetDrawOrder(0.5f);
	//�J�����̒��S�̃^�[�Q�b�g��o�^
	this->cm.SetObject(&(*water));
	//�J�����̃T�C�Y�ƈʒu�𒲐�
	OGge->camera->SetSize(Vec2(960 / 2, 540 / 2));
	OGge->camera->SetPos(Vec2(500 - (480 / 2), 0));
	//�J�����̉�ʊO�ݒ�
	this->cm.SetSize(Box2D(Vec2(0, 0), OGge->window->GetSize() * 2));
	//this->cm.SetRange(Box2D(100.f, 100.f, OGge->window->GetSize().x - 200.f, OGge->window->GetSize().y - 800.f));//���͈Ӗ����Ȃ��Ȃ�
	//�J�n���̃��[�h�ݒ�
	this->mode = Mode::from1;
	return true;
}

void Title::UpDate()
{
	//std::cout << "x:" << this->testObj.position.x << "y:" << this->testObj.position.y << std::endl;
	//----------------
	//�e�X�g
	//----------------
	if (OGge->in->key.down(In::SPACE))
	{
		this->Kill();
	}
	//�J�����̎����ړ�
	this->cm.move();
	//�M�A���񂷏ꍇ
	if (this->isGierAng)
	{
		//�l�𑝂₷
		this->gierCnt++;
		//360�x�𒴂�����0�x�ɖ߂�
		if (this->gierCnt > 360)
		{
			this->gierCnt = 0;
		}
	}
	switch (this->mode)
	{
	case from1:	//���o�����琅���ł܂�
	{
		//�����擾
		auto water = OGge->GetTask<Water>("water");
		if (water)
		{
			if (this->Logo.hit(*water) && water->GetSituation() == Water::Situation::Normal)
			{
				//�����폜���[�h�ֈڍs
				water->SetSituation(Water::Situation::Deleteform);
				this->cm.DeleteObject();
				//this->mode = from2;
				this->timeCnt = 0;
			}
			if (water->GetSituation() == Water::Situation::CreaDelete)
			{
				if (this->timeCnt < 100)
				{
					//OGge->camera->MovePos(Vec2(0, 10));
				}
				else
				{
					//this->mode = from2;
				}
			}
		}
		else
		{
			if (this->timeCnt < 81)
			{
				OGge->camera->MovePos(Vec2(0, 10));
			}
			else
			{
				this->isGierAng = true;
				this->mode = from2;
			}
		}
	}
	break;
	case from2:	//�ԍ炫�J�n����I���܂�
	{
		if (this->timeCnt < 3)
		{

		}
		//�e�X�g�p10�t���[����ړ�
		if (this->flowerVolume >= 1.0f)
		{
			//�Ԃ��炢�����_�ŃT�E���h�̍Đ����n�߂�
			sound->play();
			this->mode = from3;
			//���Ԃ��񂷏���

			//�J�����̈ړ��l��o�^
			this->cameraPos.Set(OGge->camera->GetPos(), Vec2(0, 200));
			this->cameraSize.Set(OGge->camera->GetSize(), Vec2(1440, 810));
		}
		else
		{
			if (this->flowerVolume < 1.f)
			{
				this->flowerVolume += 0.01f;
			}
		}
	}
	break;
	case from3:	//�J�����T�C�Y�ړ��J�n����I���܂�
	{
		//�ړ����s��
		OGge->camera->SetPos(this->cameraPos.Move());
		OGge->camera->SetSize(this->cameraSize.Move());
		//�����̈ړ������������ꍇ
		if (!this->cameraPos.isPlay() && !this->cameraSize.isPlay())
		{
			//����
			this->mode = from4;
		}
	}
	break;
	case from4:	//�����o��
	{
		this->tex_a += 0.01f;
		if (this->tex_a >= 1.0f)
		{
			this->mode = from5;
			auto Npc = Chara::Create((std::string)"player2.png", Vec2(1600, 628));
		}
	}
	break;
	case from5:	//���ƃv���C���[�o��
	{
		auto Npc = OGge->GetTask<Chara>("Chara");
		if (Npc)
		{
			Npc->ManualMove(Vec2(-8.f, 0.0f));
		}
		this->cursor_a += 0.01f;
		if (this->cursor_a >= 1.0f)
		{
			this->mode = from6;
		}
	}
	break;
	case from6:	//����҂����
	{
		CursorMove();

		if (OGge->in->down(Input::in::B2))
		{
			switch (this->cursorNum)
			{
			case 0:
			{
				auto chara = OGge->GetTask<Chara>("Chara");
				if (chara->position.x > 740)
				{
					chara->ManualMove(Vec2(-10.f, 0.0f));
				}
				else
				{
					chara->ManualMove(Vec2(10.f, 0.0f));
				}
				chara->Jump();
				//this->cm.SetObject(&(*chara));
				this->mode = from7;
			}
			break;
			case 1:
				OGge->GameEnd();
				break;
			case 2:
				break;
			}
		}
	}
	break;
	case from7:	//�W�����v����select�܂ł̈ړ�
	{
		//�W�����v���Ē��n���ĉ��ړ�����s��

		//if (OGge->camera->GetPos().y < 1340)
		//{
		//	//OGge->camera->MovePos(Vec2(0.0f, 10.f));
		//}
		//auto chara = OGge->GetTask<Chara>("Chara");
		//if (chara)
		//{
		//	if (chara->CollisionNumCheck(1))
		//	{
		//		if (chara->FootCheck())
		//		{
		//			if (this->timeCnt > 120)
		//			{
		//				chara->ManualMove(Vec2(5.0f, 0.0f));
		//			}
		//			else
		//			{
		//				this->timeCnt++;
		//				chara->ManualMove(Vec2(0.0f, 0.0f));
		//			}
		//		}
		//		else
		//		{
		//			this->timeCnt = 0;
		//		}
		//	}
		//	if (chara->position.x >= 1440)
		//	{
		//		this->mode = End;
		//	}
		//}

		//�~�肽�烍�[�h�����݃Z���N�g�ֈڍs����s��
		auto chara = OGge->GetTask<Chara>("Chara");
		if (chara->position.y > OGge->camera->GetPos().x + OGge->camera->GetSize().x)
		{
			this->mode = Mode::End;
		}
	}
	break;
	case End:	//Select�̓ǂݍ��݂Ǝ��g�̔j��
	{
		this->Kill();
	}
	break;
	default:
		break;
	}
	this->ModeCheck();
}

void Title::Render2D()
{
	//�w�i�\��
	{
		Box2D draw(Vec2(0, 0), Vec2(1920 * 2, 1080 * 2));
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 720);
		src.OffsetSize();
		this->texLogo.Draw(draw, src, Color(0, 0, 0, 0));
	}
	//���S�\��
	{
		Box2D draw(this->Logo.position, this->Logo.Scale);
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 768);
		this->texLogo.Draw(draw, src);
	}
	{
		Box2D draw(634, 380, 52, 52);
		draw.OffsetSize();
		Box2D src(0, 0, 128, 128);
		this->GierLogo.Rotate(this->gierCnt);
		this->GierLogo.Draw(draw, src);
	}
	{
		Box2D draw(this->Logo.position.x, (this->Logo.position.y + this->Logo.Scale.y) - (this->Logo.Scale.y * (this->flowerVolume / 1.f)), this->Logo.Scale.x, (this->Logo.Scale.y * (this->flowerVolume / 1.f)));
		draw.OffsetSize();
		Box2D src(0.f, 768 - (768 * (this->flowerVolume / 1.f)), 1280.f, 768.f);
		this->flowerLogo.Draw(draw, src);
	}
	//�J�[�\���̕\��
	{
		//�\���ʒu�A�傫���͉��Q�[���X�^�[�g
		Box2D draw(cursorPos[this->cursorNum].x, cursorPos[this->cursorNum].y, 64.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 195, 195);
		src.OffsetSize();
		this->texCursor.Rotate(this->gierCnt);
		texCursor.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->cursor_a));
		Box2D draw2(cursorPos[this->cursorNum].x + 64.0f + (30.f * 2.f) + 256.f, cursorPos[this->cursorNum].y, 64.f, 64.f);
		draw2.OffsetSize();
		texCursor.Draw(draw2, src, Color(1.0f, 1.0f, 1.0f, this->cursor_a));
	}
	//�Q�[���X�^�[�g
	{
		//Box2D draw(this->startPos.x, this->startPos.y, 256.f, 64.f);
		//draw.OffsetSize();
		//Box2D src(0, 0, 256, 64);
		//src.OffsetSize();
		//texStart.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
	}
	//�I��
	{
		Box2D draw(closePos.x, closePos.y, 256.f, 64.f);
		draw.OffsetSize();
		Box2D src(0, 0, 256, 64);
		src.OffsetSize();
		texClose.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
	}
	//�ݒ�
	{
		Box2D draw(startPos.x, startPos.y, 256.f, 64.f);
		draw.OffsetSize();
		Box2D src(0, 0, 256, 64);
		src.OffsetSize();
		texStart.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
	}
}

bool Title::Finalize()
{
	std::cout << "Title���" << std::endl;

	//�g�p�摜�̉��
	texCursor.Finalize();
	texStart.Finalize();
	texClose.Finalize();
	texPause.Finalize();
	this->texLogo.Finalize();
	this->GierLogo.Finalize();
	this->flowerLogo.Finalize();

	auto back = OGge->GetTask<Back>("back");
	if (back)
	{
		back->Kill();
	}
	this->waterTex.Finalize();

	auto water = OGge->GetTasks<Water>("water");
	for (auto id = (*water).begin(); id != (*water).end(); ++id)
	{
		(*id)->Kill();
	}
	auto map = OGge->GetTask<Map>("map");
	if (map)
	{
		(*map).Kill();
	}
	auto Npc = OGge->GetTask<Chara>("Chara");
	if (Npc)
	{
		Npc->Kill();
	}

	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		OGge->ChengeTask();
		switch (this->cursorNum)
		{
		case 0:
		{
			auto stage = StageSelect::Create();
		}
		break;
		case 1:
			OGge->GameEnd();
			break;
		default:
			break;
		}
	}
	else
	{
		if (this->sound)
		{
			delete this->sound;
			this->sound = nullptr;
		}
	}

	return true;
}

void Title::CursorMove()
{
	if (OGge->in->down(In::CU))
	{
		this->cursorNum--;
	}
	if (OGge->in->down(In::CD))
	{
		this->cursorNum++;
	}
	if (this->cursorNum > 1)
	{
		this->cursorNum = 0;
	}
	if (this->cursorNum < 0)
	{
		this->cursorNum = 1;
	}
}

void Title::ModeCheck()
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

Title::Animation::Animation()
{

}

void Title::Animation::Set(Vec2& start_, Vec2& end_)
{
	this->StartPos = start_;
	this->EndPos = end_ - start_;
}

Vec2 Title::Animation::Move()
{
	return Vec2(this->easing_x.sine.In(this->easing_x.Time(10), this->StartPos.x, this->EndPos.x, 10), this->easing_y.sine.In(this->easing_y.Time(10), this->StartPos.y, this->EndPos.y, 10));
}

bool Title::Animation::isPlay() const
{
	if (this->easing_x.isplay() || this->easing_y.isplay())
	{
		return true;
	}
	return false;
}

Title::SP Title::Create(bool flag_)
{
	auto to = Title::SP(new Title());
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
