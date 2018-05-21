#include "Task_Result.h"
using namespace std;
//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
#include "Task_Title.h"
#include "GameProcessManagement\FlagUI.h"
#include "Player\ResultPlayer.h"
bool Result::Initialize()
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "Result";		//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	//������
	Result_DataInput();
	Flag_Judge();
	this->image.Create((std::string)"back.png");

	SetDrawOrder(0.0f);
	{
		Vec2 windowsize = OGge->window->GetSize();
		auto player = ResultPlayer::Create(Vec2(0, (int)windowsize.y - 200),Vec2(3,0));
	}
	for (int i = 0; i < 3; ++i)
	{
		auto ster = FlagUI::Create(Vec2(100 * (i + 1), 100),1 << 0);
	}
	cout << "���ʉ�ʏ����@������" << endl;
	return true;
}

void Result::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------
	//�^�C�g���V�[���֑J��
	if (OGge->in->down(In::B2))
	{
		Kill();
	}
}
void Result::Render2D()
{
	//--------------------
	//�`�掞�ɍs���������L�q
	//--------------------
	{
		Box2D draw(Vec2(0, 0), OGge->window->GetSize());
		draw.OffsetSize();
		Box2D src(Vec2(0, 0), Vec2(1280, 720));
		src.OffsetSize();
		image.Draw(draw, src);
	}
}
bool Result::Finalize()
{
	//-----------------------------------------
	//���̃I�u�W�F�N�g�����ł���Ƃ��ɍs���������L�q
	//-----------------------------------------
	//���̃^�X�N����邩���A�v���P�[�V�������I���\�肩�ǂ���
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		image.Finalize();
		auto player = OGge->GetTask<ResultPlayer>("ResultPlayer");
		auto ster = OGge->GetTasks<FlagUI>("Ster");
		for (auto id = (*ster).begin(); id != (*ster).end(); ++id)
		{
			(*id)->Kill();
		}
		if (player)
		{
			player->Kill();
		}
		auto title = Title::Create();
	}
	return true;
}
bool Result::Flag_Judge()
{
	bool active = false;
	if ((Flag & Result::Flag1) == Result::Flag1)
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
//----------------------------
//�������牺��class���̂ݕύX����
//�ق��͕ύX���Ȃ�����
//----------------------------
Result::Result()
{
	cout << "���ʉ�ʏ����@����" << endl;
	//�J�������W�����ɖ߂�
	OGge->camera->SetPos(Vec2(0, 0));
	FrameTime = 0;
	Flag_Judge_Clear();
}

Result::~Result()
{
	this->Finalize();
	cout << "���ʉ�ʏ����@���" << endl;
}

Result::SP Result::Create(bool flag_)
{

	Result::SP to = Result::SP(new Result());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize())
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}