#include "Task_Title.h"
#include "Task\Task_Option.h"
#include "Task\StageSelect.h"
Title::Title()
{

}

Title::~Title()
{
	this->Finalize();
}

bool Title::Initialize()
{
	std::cout << "Title������" << std::endl;
	sound.create(std::string("playandhope.wav"), true);

	cursorPos.x = 600.0f;
	cursorPos.y = 100.0f;

	startPos = Vec2(700.0f, 100.0f);
	pausePos = Vec2(700.0f, 200.0f);
	closePos = Vec2(700.0f, 300.0f);

	texCursor.Create((std::string)"Collision.png");
	texStart.Create((std::string)"start.png");
	texClose.Create((std::string)"close.png");
	texPause.Create((std::string)"pause.png");

	//�I�v�V�����ŕύX�������ʂ𔽉f�ł��邱�Ƃ��m�F

	//sound.create(std::string("playandhope.wav"), true);
	//�T�E���h���̂̉��ʂ�ݒ�
	//sound.SetVolume(1.0f);
	//�T�E���h�f�[�^��SoundManager�ɓo�^
	//OGge->soundManager->SetSound(&sound);
	//�ő剹�ʂ��w��
	//OGge->soundManager->SetMaxVolume(vol);

	//�T�E���h�̉��ʂ��ő剹�ʂɍ��킹�ēK�p������
	//OGge->soundManager->Application();
	//�T�E���h�̍Đ�
	//sound.play();
	this->nextTaskCheck = 0;
	__super::Init((std::string)"title");
	return true;
}

void Title::UpDate()
{
	CursorMove();

	if (state == Start)
	{
		if (OGge->in->down(Input::in::B2))
		{
			
		}
	}

	if (state == Close)
	{
		//�Q�[�����I�����鏈���A�܂��̓^�X�N���ڍs
		if (OGge->in->down(Input::in::B2))
		{
			OGge->GameEnd();
		}
	}

	if (state == Pause)
	{
		if (OGge->in->down(Input::in::B2))
		{
			
		}
	}
	if (OGge->in->down(Input::in::B2))
	{
		this->Kill();
	}
}

void Title::Render2D()
{
	//�J�[�\���̕\��
	{
		//�\���ʒu�A�傫���͉��Q�[���X�^�[�g
		Box2D draw(cursorPos.x, cursorPos.y, 64.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 128, 128);
		src.OffsetSize();
		texCursor.Draw(draw, src);
	}
	//�Q�[���X�^�[�g
	{
		Box2D draw(startPos.x, startPos.y, 256.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 256, 64);
		src.OffsetSize();
		texStart.Draw(draw, src);
	}
	//�I��
	{
		Box2D draw(closePos.x, closePos.y, 256.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 256, 64);
		src.OffsetSize();
		texClose.Draw(draw, src);
	}
	//�ݒ�
	{
		Box2D draw(pausePos.x, pausePos.y, 256.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 256, 64);
		src.OffsetSize();
		texPause.Draw(draw, src);
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

	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		OGge->ChengeTask();
		switch (state)
		{
		case Close:
			OGge->GameEnd();
			break;
		case Start:
		{
			auto stage = StageSelect::Create();
		}
			break;
		case Pause:
		{
			auto option = Option::Create();
		}
			break;
		default:
			break;
		}
	}
	
	return true;
}

void Title::CursorMove()
{
	if (cursorPos.y > startPos.y)
	{
		if (OGge->in->down(In::CU))
		{
			cursorPos.y -= 100.0f;
		}
	}
	if (cursorPos.y < closePos.y)
	{
		if (OGge->in->down(In::CD))
		{
			cursorPos.y += 100.0f;
		}
	}

	if (cursorPos.y == startPos.y)
	{
		state = Start;
	}
	if (cursorPos.y == pausePos.y)
	{
		state = Pause;
	}
	if (cursorPos.y == closePos.y)
	{
		state = Close;
	}
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