#include "Task_Result.h"
using namespace std;
Result::Result()
{
	cout << "���ʉ�ʏ���������" << endl;
	FrameTime = 0;
	Flag_Judge_Clear();
}
Result::~Result()
{
	cout << "���ʉ�ʏ������" << endl;
}
void Result::Initialize()
{
	Result_DataInput();
	Flag_Judge();
	this->image.TextureCreate((std::string)"outlook.png");
}
TaskFlag Result::Update()
{
	TaskFlag nowTask = TaskFlag::Task_Ruselt;
	if (gameEngine->in.down(In::B2))
	{
		nowTask = Task_Title;
	}
	return nowTask;
}
void Result::Render()
{
	Box2D draw(Vec2(0,0),gameEngine->window->GetSize());
	draw.OffsetSize();
	Box2D src(Vec2(0, 0), Vec2(1280, 720));
	src.OffsetSize();
	image.Draw(draw, src);
}
void Result::Finalize()
{
	image.Finalize();
}
void Result::Result_DataInput()
{
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
	(stringstream)text >> FrameTime;
	if (FrameTime <= 30)//30�b�ȓ��ɃS�[��
	{
		Flag_Input(Result::Achievement::Flag2);
		Flag_Input(Result::Achievement::Flag3);
		Flag_Input(Result::Achievement::Flag4);
	}
	else if (FrameTime <= 60)//60�b�ȓ��ɃS�[��
	{
		Flag_Input(Result::Achievement::Flag3);
		Flag_Input(Result::Achievement::Flag4);
	}
	else
	{
		Flag_Input(Result::Achievement::Flag4);
	}
	getline(_fin, text, ',');
	(stringstream)text >> GameFalg;
	if (GameFalg == "GameClear")		//�Q�[�����N���A
	{
		Flag_Input(Result::Achievement::Flag1);
	}
	//���Ԃ̌v�Z
	int sec, min, hour;
	sec = FrameTime % 60;
	min = FrameTime / 60;
	hour = min / 60;
	cout << hour << "����" << min << "��" << sec << "�b" << endl;

	fin.close();

	
}
bool Result::Flag_Judge()
{
	bool active = false;
	if ((Flag & Result::Flag1 )== Result::Flag1)
	{
		//�t���O�P�������Ă���
		active = true;
		cout << "Goal" << endl;
	}
	if ((Flag & Result::Flag2) == Result::Flag2)
	{
		//�t���O�Q�������Ă���
		active = true;
		cout << "30�b�ȓ��ɃS�[��������" << endl;
	}
	if ((Flag & Result::Flag3) == Result::Flag3)
	{
		//�t���O�R�������Ă���
		cout << "60�b�ȓ��ɃS�[��������" << endl;
		active = true;
	}
	if ((Flag & Result::Flag4) == Result::Flag4)
	{
		//�t���O�S�������Ă���
		cout << "���ʂɃS�[��������" << endl;
		active = true;
	}
	if (Flag & 0x0F)
	{
		cout << "�}�X�^�[�N���A" << endl;
	}
	return active;
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