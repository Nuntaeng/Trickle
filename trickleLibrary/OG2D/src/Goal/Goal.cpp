#include "Goal.h"
//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
#include "Water\water.h"
bool Goal::Initialize()
{
	//-----------------------------
	//�������ɏ������鏉�����������L�q
	//-----------------------------
	this->taskName = "Goal";		//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	cleared = false;
	goal_anim = false;
	animCnt = 0;
	this->objectTag = "Goal";
	//�e�N�X�`���̓ǂݍ���
	tex.Create((std::string)"goal.png");
	//�I�u�W�F�N�g�̐���
	CreateObject(Objform::Cube, Vec2(28 * 64, 14 * 64), Vec2(64, 64), 0.f);

	std::cout << "�S�[���@������" << std::endl;
	return true;
}
bool Goal::Initialize(Vec2& pos) {
	cleared = false;
	goal_anim = false;
	animCnt = 0;
	this->objectTag = "Goal";
	__super::Init(this->objectTag);
	//�e�N�X�`���̓ǂݍ���
	tex.Create((std::string)"goal.png");
	//�I�u�W�F�N�g�̐���
	CreateObject(Objform::Cube, pos, Vec2(64, 64), 0.f);

	
	return true;
}

void Goal::UpDate()
{
	//--------------------
	//�X�V���ɍs���������L�q
	//--------------------
	if (this->ClearCheck())
	{
		cleared = true;
	}
}

void Goal::Render2D()
{
	//--------------------
	//�`�掞�ɍs���������L�q
	//--------------------
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src;
	if (this->cleared) {
		if (this->goal_anim && animCnt < 99) {
			//�g�傪�I�������A�j���[�V����
			//(10�J�b�g*�P�O�t���[��)-1�ɂȂ�����~�߂�
			animCnt++;
		}
		src = Box2D(256*(animCnt / 10), 284, 256, 284);
	}
	else {
		src = Box2D(0, 0, 256, 256);
	}
	
	src.OffsetSize();
	tex.Draw(draw, src);
	this->LineDraw();
}

bool Goal::Finalize()
{
	//-----------------------------------------
	//���̃I�u�W�F�N�g�����ł���Ƃ��ɍs���������L�q
	//-----------------------------------------
	tex.Finalize();
	//���̃^�X�N����邩���A�v���P�[�V�������I���\�肩�ǂ���
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		
	}
	return true;
}
//void Goal::AddWater(Water* o)
//{
//	this->waters.push_back(o);
//}

//bool Goal::DeleteWater(Water* o)
//{
//	for (auto id = this->waters.begin(); id != this->waters.end(); ++id)
//	{
//		if ((*id) == o)
//		{
//			this->waters.erase(id);
//			return true;
//		}
//	}
//	return false;
//}

bool Goal::ClearCheck()
{
	auto waters = OGge->GetTasks<Water>("water");
	if (waters != nullptr)
	{
		for (int i = 0; i < (*waters).size(); ++i)
		{
			if ((*waters)[i]->hit(*this))
			{
				if ((*waters)[i]->GetSituation() == Water::Situation::Normal && (*waters)[i]->GetState() == Water::State::LIQUID)
				{
					return true;
				}
			}
		}
	}
	return false;
}
//----------------------------
//�������牺��class���̂ݕύX����
//�ق��͕ύX���Ȃ�����
//----------------------------
Goal::Goal()
{
	std::cout << "�S�[���@����" << std::endl;
}

Goal::~Goal()
{
	this->Finalize();
	std::cout << "�S�[���@���" << std::endl;
}

Goal::SP Goal::Create(bool flag_)
{
	Goal::SP to = Goal::SP(new Goal());
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

Goal::SP Goal::Create(bool flag_,Vec2& pos)
{
	Goal::SP to = Goal::SP(new Goal());
	if (to)
	{
		to->me = to;
		if (flag_)
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