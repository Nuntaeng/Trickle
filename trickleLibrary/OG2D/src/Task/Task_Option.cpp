#include "Task_Option.h"

void Option::Initialize()
{
	this->soundName = "playandhope.wav";

	texBack.TextureCreate("back.png");    //1920*1080
	texBar.TextureCreate("Collision.png");
	texGear.TextureCreate("Collision.png");

	this->vol = 0.5f;

	Option::Set();    //�T�E���h�̗p��
}
TaskFlag Option::Update()
{
	TaskFlag nowtask = Task_Option;

	VolControl();    //�T�E���h�̃{�����[���R���g���[��
	DrawVol();     //�ړ�����`��ɂ���

	if (gameEngine->in.down(Input::in::B1))
	{
		sound.stop();
		nowtask = Task_Title;
	}
	return nowtask;
}
void Option::Finalize()
{
	texBack.Finalize();
	texBar.Finalize();
	texGear.Finalize();
}
void Option::Render()
{
	//�w�i�̕`��
	{
		Box2D draw(Vec2(0, 0), gameEngine->window->GetSize());  //�摜�T�C�Y�͉�
		draw.OffsetSize();
		Box2D src(0, 0, 1920, 1080);
		src.OffsetSize();
		texBack.Draw(draw, src);
	}
	//���ʂ̕`��
	{
		Box2D draw(80.0f, 300.0f, barwidth, 32.0f);     //�摜�T�C�Y�͉�
		draw.OffsetSize();
		Box2D src(0, 0, 128, 128);
		src.OffsetSize();
		texBar.Draw(draw, src);
	}
	//���Ԃ̕\��
	{
		Box2D draw(gearPos + 20, 284.0f, 64.0f, 64.0f);     //�摜�T�C�Y�͉�
		draw.OffsetSize();
		Box2D src(128, 0, 128, 128);
		src.OffsetSize();
		texGear.Draw(draw, src);
	}
}

void Option::Set()
{
	sound.createSound(soundName, true);
	//�T�E���h���̂̉��ʂ�ݒ� ���������[�U�[���ύX?
	sound.SetVolume(1.0f);
	//�T�E���h�f�[�^��SoundManager�ɓo�^
	gameEngine->soundManager->SetSound(&sound);
	//�T�E���h�̍Đ�
	sound.play();
}

void Option::VolControl()
{
	//���ʒ��߂ɂ���
	//��L�[�ŉ��ʂ��グ��
	if (gameEngine->in.down(In::CU))
	{
		if (vol < 1.0f)
		{
			vol += 0.1f;
		}
	}
	//���L�[�ŉ��ʂ�������
	if (gameEngine->in.down(In::CD))
	{
		if (vol > 0.1f)
		{
			vol -= 0.1f;
		}
	}
	//�T�E���h�̉��ʂ̒����p �g�p���Ȃ�
	//sound.volume(vol);
	//�ő剹�ʂ��w��
	gameEngine->soundManager->SetMaxVolume(vol);
	//�T�E���h�̉��ʂ��ő剹�ʂɍ��킹�ēK�p������
	gameEngine->soundManager->Application();
}

//���ʒ��߉摜�̈ʒu����
void Option::DrawVol()
{
	nowVol = vol / 0.1f;
	if (nowVol >= 1)
	{
		gearPos = nowVol * 80;
		barwidth = nowVol * 80;
	}
	else
	{
		gearPos = 48;
		barwidth = nowVol * 80;
	}
}