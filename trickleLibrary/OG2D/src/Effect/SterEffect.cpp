#include "SterEffect.h"

#include "GameProcessManagement\FlagUI.h"

bool SterEffect::Initialize(std::shared_ptr<GameObject> target)
{
	//�^�X�N�֘A
	this->taskName = "StarEffect";
	this->Init(taskName);

	//��{�̏��
	this->CreateObject(Cube, Vec2{}, Vec2(64, 64), 0.f);

	//�A�j���[�V�����̓���
	this->animetion.StateChenge(State::Motion);

	//Easing�֘A
	this->ResetEasing(easingX);
	this->ResetEasing(easingY);
	if (target != nullptr)
	{
		this->target = target;
	}
	this->target->position;

	//Easing�J�n�ꏊ
	if ((std::static_pointer_cast<FlagUI>)(target)->GetFlag())
	{
		//�摜�֘A
		image.Create((std::string)"Ster.png");
	}
	else
	{
		image.Create((std::string)"SterB.png");
	}

	std::cout << "�X�^�[�G�t�F�N�g�@������" << std::endl;
	return true;
}
void SterEffect::ResetEasing(Easing& easing)
{
	easing.Init();
	easing.ResetTime();
	this->isPlay = false;
}
bool SterEffect::Finalize()
{
	image.Finalize();
	return true;
}
void SterEffect::UpDate()
{
	Think();
	MotionActive();
}
void SterEffect::Render2D()
{
	{
		Box2D draw(this->position, this->Scale);
		draw.OffsetSize();
		Box2D src = this->Src;
		src.OffsetSize();
		image.Draw(draw, src);
	}
}
bool SterEffect::EasingIsPleyed()
{
	if (this->isPlay)
	{
		return true;
	}
	return false;
}
void SterEffect::Think()
{
	State nm = this->animetion.motion;
	switch (this->animetion.motion)
	{
	case State::NON:
		break;
	case State::Motion:
		if (this->isPlay)
		{
			nm = NON;
		}
		break;
	default:
		break;
	}
	this->animetion.StateChenge(nm);
}
void SterEffect::MotionActive()
{
	switch (this->animetion.motion)
	{
	case State::NON:
		//�G�t�F�N�g���o���I���������Ƃ�`����
		(std::static_pointer_cast<FlagUI>(target))->SetEffectEnd();
		this->Kill();
		break;
	case State::Motion:
		this->MoveEasing();
		break;
	default:
		break;
	}
}
void SterEffect::MoveEasing()
{
	Vec2 camerasize = OGge->camera->GetSize();

	if (easingX.isplay() || easingY.isplay())
	{
		//�E���獶
		this->position.x = easingX.cubic.Out(10, -camerasize.x + this->target->position.x, camerasize.x, easingX.Time(10));
		//�������
		this->position.y = easingY.cubic.Out(15, 120 + this->target->position.y, -120, easingY.Time(15));
	}
	else
	{
		this->isPlay = true;
	}
}
void SterEffect::Animetion::StateChenge(SterEffect::State state)
{
	this->motion = state;
}
SterEffect::SterEffect()
{
	std::cout << "�X�^�[�G�t�F�N�g�@����" << std::endl;
}
SterEffect::~SterEffect()
{
	std::cout << "�X�^�[�G�t�F�N�g�@���" << std::endl;
}
SterEffect::SP SterEffect::Create(std::shared_ptr<GameObject> target ,bool flag)
{
	SterEffect::SP to = SterEffect::SP(new SterEffect());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(target))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}