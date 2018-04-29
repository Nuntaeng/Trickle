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
	Result_DataInput();
	Flag_Judge();
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
void Result::Result_DataInput()
{
	int Frametime;				//�^�C�����t���[���i�[����
	string GameFalg;			//�Q�[���t���O
	//�f�[�^�̓ǂݍ���
	ifstream fin(TimeFilePath);

	if (!fin)
	{
		return;
	}
	//�ǂݍ��񂾃f�[�^�����Ă����ϐ�
	string line;
	//���s���I�����_�܂ł̕����̕������line�ɓ����
	getline(fin, line);
	//������𑀍삷�邽�߂̓��̓N���X�A���ڃA�N�Z�X����
	istringstream _fin(line);
	//�ꎚ�������ݕϐ�
	string text;
	//_fin�ɓ����Ă��镶���񂩂�','�܂ł̕�����text�ɂ����
	getline(_fin, text, ',');
	//text�̃f�[�^��ϐ��ɂ����
	(stringstream)text >> Frametime;
	getline(_fin, text, ',');
	(stringstream)text >> GameFalg;
	if (GameFalg == "GameClear")		//�Q�[�����N���A
	{
		Flag_Input(Result::Achievement::Flag1);
	}
	//���Ԃ̌v�Z
	int sec, min, hour;
	sec = Frametime % 60;
	min = Frametime / 60;
	hour = Frametime / 60 / 60;
	cout << hour << "����" << min << "��" << sec << "�b" << endl;

	fin.close();

	
}
bool Result::Flag_Judge()
{
	if ((Flag & Result::Flag1 )== Result::Flag1)
	{
		//�t���O�P�������Ă���
		cout << "Goal" << endl;
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
void Result::Set_pointa(Goal* obj)
{
	g_pointa = obj;
}