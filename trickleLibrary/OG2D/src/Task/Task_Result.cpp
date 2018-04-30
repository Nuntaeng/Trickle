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
bool Result::Flag_Judge()
{
	if ((Flag & Result::Flag1 )== Result::Flag1)
	{
		//�t���O�P�������Ă���
		return true;
	}
	if ((Flag & Result::Flag2) == Result::Flag2)
	{
		//�t���O�Q�������Ă���
		return true;
	}
	if ((Flag & Result::Flag3) == Result::Flag3)
	{
		//�t���O�R�������Ă���
		return true;
	}
	if ((Flag & Result::Flag4) == Result::Flag4)
	{
		//�t���O�S�������Ă���
		return true;
	}
	if (Flag & 0x0F)
	{
		//�S���̃t���O���������Ă���
		return true;
	}
	return false;
}
bool Result::Flag_Judge(Result::Achievement achive1, Result::Achievement achive2)
{
	if ((Flag & achive1) == achive1 && (Flag & achive2) == achive2)
	{
		return true;
	}
	return false;
}
bool Result::Flag_Judge(Result::Achievement achive1, Result::Achievement achive2, Result::Achievement achive3)
{
	if ((Flag & achive1) == achive1 && (Flag & achive2) == achive2 && (Flag & achive3) == achive3)
	{
		return true;
	}
	return false;
}
void Result::Flag_Input(Result::Achievement achive)
{
	Flag |= achive;
}
int Result::Get_Flag()
{
	return Flag;
}
void Result::Flag_Judge_Clear()
{
	Flag &= ~Flag;
}