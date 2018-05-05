#include "Task_Title.h"

void Title::Initialize()
{
	std::cout << "Title������" << std::endl;
	sound.createSound(std::string("playandhope.wav"), true);
	map.LoadMap("test.txt");

	cursorPos.x = 600.0f;
	cursorPos.y = 100.0f;

	startPos = Vec2(700.0f, 100.0f);
	pausePos = Vec2(700.0f, 200.0f);
	closePos = Vec2(700.0f, 300.0f);

	texCursor.TextureCreate("Collision.png");
	texStart.TextureCreate("start.png");
	texClose.TextureCreate("close.png");
	texPause.TextureCreate("pause.png");

	//�I�v�V�����ŕύX�������ʂ𔽉f�ł��邱�Ƃ��m�F

	//sound.createSound(std::string("playandhope.wav"), true);
	//�T�E���h���̂̉��ʂ�ݒ�
	//sound.SetVolume(1.0f);
	//�T�E���h�f�[�^��SoundManager�ɓo�^
	//gameEngine->soundManager->SetSound(&sound);
	//�ő剹�ʂ��w��
	//gameEngine->soundManager->SetMaxVolume(vol);

	//�T�E���h�̉��ʂ��ő剹�ʂɍ��킹�ēK�p������
	//gameEngine->soundManager->Application();
	//�T�E���h�̍Đ�
	//sound.play();
}

TaskFlag Title::Update()
{
	TaskFlag nowtask = Task_Title;

	CursorMove();

	if (state == Start)
	{
		if (gameEngine->in.down(Input::in::D2))
		{
			nowtask = Task_StageSelect;
		}
	}

	if (state == Close)
	{
		//�Q�[�����I�����鏈���A�܂��̓^�X�N���ڍs
		if (gameEngine->in.down(Input::in::D2))
		{
			gameEngine->GameEnd();
		}
	}

	if (state == Pause)
	{
		if (gameEngine->in.down(Input::in::D2))
		{
			nowtask = Task_Option;
		}
	}

	return nowtask;
}

void Title::Render2D()
{
	map.MapRender();
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

void Title::Finalize()
{
	std::cout << "Title���" << std::endl;
	map.Finalize();

	//�g�p�摜�̉��
	texCursor.Finalize();
	texStart.Finalize();
	texClose.Finalize();
	texPause.Finalize();

	cm.Destroy();
}

void Title::CursorMove()
{
	if (cursorPos.y > startPos.y)
	{
		if (gameEngine->in.key.down(Input::KeyBoard::UP))
		{
			cursorPos.y -= 100.0f;
		}
	}
	if (cursorPos.y < closePos.y)
	{
		if (gameEngine->in.key.down(Input::KeyBoard::DOWN))
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

