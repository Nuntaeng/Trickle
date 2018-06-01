#include "GoalTimeUI.h"
bool GoalTimeUI::Initialize(Vec2& pos)
{
	//�^�X�N�֘A
	this->taskName = "GoalTimeUI";
	this->Init(taskName);

	//��{�̏��
	CreateObject(Cube, pos, Vec2(448, 90), 0);
	

	//�摜�֘A
	image.Create((std::string)"TimeUI.png");
	this->SetDrawOrder(0.1f);

	//Easing�֘A
	this->PrePos = position;
	this->easingX.ResetTime();
	this->easingX.Init();
	this->easingEnd = false;

	std::cout << "�S�[���^�C��UI�@������" << std::endl;
	return true;
}
bool GoalTimeUI::Finalize()
{
	image.Finalize();
	return true;
}
void GoalTimeUI::UpDate()
{
	if (easingX.isplay())
	{
		position.x = easingX.linear.In(10, 0, this->PrePos.x, easingX.Time(10));
	}
	else
	{
		easingEnd = true;
	}
}
void GoalTimeUI::Render2D()
{
	Box2D draw(position, Scale);
	draw.OffsetSize();
	Box2D src = this->Src;
	src.OffsetSize();
	image.Draw(draw,src);
}
bool GoalTimeUI::GetEasingEnd()
{
	return easingEnd;
}
GoalTimeUI::GoalTimeUI()
{
	std::cout << "�S�[���^�C��UI�@����" << std::endl;
}
GoalTimeUI::~GoalTimeUI()
{
	this->Finalize();
	std::cout << "�S�[���^�C��UI�@���" << std::endl;
}
GoalTimeUI::SP GoalTimeUI::Create(Vec2& pos, bool flag)
{
	GoalTimeUI::SP to = GoalTimeUI::SP(new GoalTimeUI());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}