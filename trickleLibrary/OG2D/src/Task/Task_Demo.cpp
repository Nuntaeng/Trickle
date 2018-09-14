#include "Task_Demo.h"
#include "Task_Title.h"
#include "Chara\Chara.h"

Demo::SP Demo::Create(const std::string& fp_, bool flag_) {
	auto to = Demo::SP(new Demo());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(fp_))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

bool Demo::Initialize(const std::string& demoVideoPath) {
	cap.open(demoVideoPath);
	if (!cap.isOpened()) {
		std::cout << "�f���v���C�t�@�C���I�[�v���G���[!" << std::endl;
		return false;
	}
	startTime = 0.f;
	videoFPS = (float)cap.get(CV_CAP_PROP_FPS);
	delay = 0.1f / videoFPS;
	Vec2 winSize = OGge->window->GetSize();
	draw = Box2D(OGge->camera->GetPos(), OGge->camera->GetSize());
	draw.OffsetSize();
	texColor = Color(1.f, 1.f, 1.f, 1.f);
	timer.Start();
	tex.CreateID(1);
	//�ŏ���1���`����Z�b�g���Ă����Ȃ���1frame�ڂŏ��������s�̎��Ԃ𒴂��Ȃ��������ɔ|�����ł�̂ł��̑΍�
	cap >> frame;
	if (!frame.empty())
	{
		tex.Create(frame);
	}
	__super::Init((std::string)"demo");
	__super::SetDrawOrder(1.1f);
	return true;
}

void Demo::UpDate() {
	if (OGge->in->down(In::B1)) {
		deadFlag = true;
	}
	if (deadFlag) {
		Fadeout();
	}
	else if (timer.GetTime() - startTime >= delay) 
	{
		cap >> frame;
		if (frame.empty()) {
			deadFlag = true;
			return;
		}
		tex.Create(frame);
		startTime = timer.GetTime();
	}
}

void Demo::Render2D()
{
	tex.Draw(draw, Box2D(0, 0, (int)tex.GetTextureSize().x, (int)tex.GetTextureSize().y), texColor);
}

void Demo::Fadeout() {
	texColor.alpha -= 0.01f;
	if (texColor.alpha <= 0.f) {
		this->Kill();
	}
}

bool Demo::Finalize()
{
	tex.Finalize();
	frame.release();
	cap.release();
	auto title = OGge->GetTask<Title>((std::string)"title");
	if (title) {
		title->SetPauseEveryChild(false);
	}
	return true;
}
