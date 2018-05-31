#include "FrameTime.h"

#include "Task\Task_Result.h"
bool FrameTimeUI::Initialize(Vec2& pos,int digitselect,int& resulttime)
{
	//�^�X�N�֘A
	this->taskName = "FrameTimeUI";
	this->Init(taskName);

	//�����̌������v�Z����
	this->getframetime = resulttime;			//���U���g����擾�����^�C����������
	this->DigitNumberReset();					//�����̏�����
	this->SetFrameTime();						//�����̌v�Z
	this->digitSelectnumber = digitselect;		//���������蓖�Ă邽�߂̕ϐ�
	this->SetVector();							//�����������擾�������̂�1������Vector�Ɋi�[����

	//��{�̏��
	CreateObject(Cube, pos, Vec2(64, 64), 0);
	this->active = false;
	
	//�摜�֘A
	image.Create((std::string)"../font/math.png");
	this->SetDrawOrder(0.1f);

	//Easing�֘A
	easingX.ResetTime();
	easingX.Init();
	this->PrePos = position;
	this->easingEnd = false;

	std::cout << "�t���[���^�C��UI�@������" << std::endl;
	return true;
}
void FrameTimeUI::SetVector()
{
	int value = this->getframetime;
	for (int i = digitnumberLength; i > 0; --i)
	{
		value = this->getframetime % (int)pow(N, i);
		if (i != 1)
		{
			value = value / (int)pow(N, i - 1);
		}
		frametime.push_back(value);
	}
}
void FrameTimeUI::SetFrameTime()
{
	this->digitnumberLength = SetDigitNumber();
}
int FrameTimeUI::SetDigitNumber()
{
	int value = this->getframetime;
	int Count = 0;
	while (value != 0)
	{
		value /= N;
		++Count;
	}
	return Count;
}
void FrameTimeUI::DigitNumberReset()
{
	this->digitnumberLength = 0;
}
void FrameTimeUI::TargetTime()
{
	int Count = 0;
	for (auto it = frametime.begin(); it != frametime.end(); ++it)
	{
		if (Count == digitSelectnumber)
		{
			this->digitSelectnumber =  *it;
			return;
		}
		++Count;
	}
}
int FrameTimeUI::GetDigitNumber()
{
	return this->digitnumberLength;
}
bool FrameTimeUI::Finalize()
{
	image.Finalize();
	return true;
}
void FrameTimeUI::UpDate()
{
	if (!active)
	{
		TargetTime();
		active = true;
	}
	if (easingX.isplay())
	{
		position.x = easingX.linear.In(10, 0, this->PrePos.x, easingX.Time(10));
	}
	else
	{
		this->easingEnd = true;
	}
}
bool FrameTimeUI::GetEasingEnd()
{
	return this->easingEnd;
}
void FrameTimeUI::Render2D()
{
	Box2D draw(position, Scale);
	draw.OffsetSize();
	Box2D src = this->Src;
	src.x = src.w * digitSelectnumber;
	src.OffsetSize();
	image.Draw(draw, src);
}
FrameTimeUI::FrameTimeUI()
{
	std::cout << "�t���[���^�C��UI�@����" << std::endl;
}
FrameTimeUI::~FrameTimeUI()
{
	this->Finalize();
	std::cout << "�t���[���^�C��UI�@���" << std::endl;
}
FrameTimeUI::SP FrameTimeUI::Create(Vec2& pos,int digitselect,int& resulttime,bool flag)
{
	FrameTimeUI::SP to = FrameTimeUI::SP(new FrameTimeUI());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos,digitselect,resulttime))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}