#include "Task_Result.h"
using namespace std;
Result::Result()
{
	cout << "���ʉ�ʏ���������" << endl;
}
Result::~Result()
{
	cout << "���ʉ�ʏ������" << endl;
}
void Result::Initialize()
{
	Timer_Input();				//�^�C���̏o��
}
TaskFlag Result::Update()
{
	TaskFlag nowTask = TaskFlag::Task_Ruselt;
	if (gameEngine->in.key.down(Input::KeyBoard::S))
	{
		nowTask = Task_Title;
	}
	return nowTask;
}
void Result::Render()
{
	Box2D draw(Vec2(0,0),Vec2(0,0));
	draw.OffsetSize();
	Box2D src(Vec2(0, 0), Vec2(0, 0));
	src.OffsetSize();
	image.Draw(draw, src);
}
void Result::Finalize()
{
	image.Finalize();
}
void Result::Timer_Input()
{
	int i;
	file = fopen(TimeFilePath, "r");
	fscanf(file, "%d", &i);
	fclose(file);
	int sec, min, hour;
	sec = i % 60;
	min = i / 60;
	hour = i / 60 / 60;
	cout << hour << "����" << min << "��" << sec << "�b" << endl;
}