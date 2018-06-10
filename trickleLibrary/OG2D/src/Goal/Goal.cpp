#include "Goal.h"
//�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
#include "Water\water.h"
#include "Player/Player.h"
#include "Map/Map.h"
bool Goal::Initialize()
{
	//�^�X�N�֘A
	this->taskName = "Goal";		//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	//�S�[���t���O�֘A
	this->ResetisGoal();

	//�A�j���[�V�����֘A
	this->ResetAnimetion();

	//�J�������[�h�֘A
	this->ResetCamera();

	//�摜�֘A
	tex.Create((std::string)"goal.png");
	

	//��{�̏��
	CreateObject(Objform::Cube, Vec2{}, Vec2(64, 64), 0.f);


	std::cout << "�S�[���@������" << std::endl;
	return true;
}
bool Goal::Initialize(Vec2& pos) {
	//�^�X�N�֘A
	this->taskName = "Goal";		//�������Ɏg�����߂̖���o�^����
	__super::Init(taskName);		//TaskObject���̏������s��

	//�S�[���t���O�֘A
	this->ResetisGoal();

	//�A�j���[�V�����֘A
	this->ResetAnimetion();

	//�J�������[�h�֘A
	this->ResetCamera();


	//�摜�֘A
	tex.Create((std::string)"goal.png");

	//��{�̏��
	CreateObject(Objform::Cube, pos, Vec2(64, 64), 0.f);

	std::cout << "�S�[���@������" << std::endl;
	return true;
}
void Goal::UpDate()
{
	this->Camera_Think();
	this->Camera_Motion();
}

void Goal::Render2D()
{
	//--------------------
	//�`�掞�ɍs���������L�q
	//--------------------
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src;
	if (this->cleared) 
	{
		//�A�j���[�V�����t���O��true�Ȃ�΁E�E
		if (this->isanimetion && animCnt < 99) 
		{
			//�g�傪�I�������A�j���[�V����
			//(10�J�b�g*�P�O�t���[��)-1�ɂȂ�����~�߂�
			animCnt++;
		}
		if (animCnt >= 99)
		{
			this->isanimetionfinish = true;
		}
		src = Box2D(256*(animCnt / 10), 284, 256, 284);
	}
	else 
	{
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
void Goal::ResetisGoal()
{
	this->cleared = false;
}
void Goal::ResetAnimetion()
{
	this->isanimetion = false;
	this->isanimetionfinish = false;
	this->animCnt = 0;
}
void Goal::ResetCameraMode()
{
	this->cameramode = CameraMode::NON;
}
void Goal::ResetisCameraPlay()
{
	this->iscameraPlay = false;
}
void Goal::ResetCameraCnt()
{
	
}
void Goal::ResetCameraVec()
{
	this->cameraPos = OGge->camera->GetPos();
	this->cameraSize = OGge->camera->GetSize();
}
void Goal::ResetCamera()
{
	this->ResetCameraMode();
	this->ResetisCameraPlay();
	this->ResetCameraVec();
	this->ResetCameraCnt();
	this->SetCameraSpeed(Vec2(2, 3));
}
void Goal::SetCameraSpeed(Vec2& speed)
{
	this->cameraMove = speed;
}
Goal::CameraMode Goal::GetCameraMode()
{
	return this->cameramode;
}
bool Goal::isGoal()
{
	return this->cleared;
}
bool Goal::isAnimetion()
{
	return this->isanimetion;
}
void Goal::SetCameraMode(CameraMode mode)
{
	this->cameramode = mode;
}
void Goal::Camera_Think()
{
	Goal::CameraMode nm = this->cameramode;
	switch (nm)
	{
	case Goal::NON:		//�N�����Ă��Ȃ�
		if (this->cleared)
		{
			nm = Play;
		}
		break;
	case Goal::Play:	//�N�����Ă���
		if (this->isanimetionfinish)
		{
			nm = End;
		}
		break;
	case Goal::End:		//�N������
		//�J�����̃T�C�Y�����ɖ߂�

		break;
	}
	this->SetCameraMode(nm);
}
void Goal::Camera_Motion()
{
	auto player = OGge->GetTask<Player>("Player");

	switch (this->cameramode)
	{
	case Goal::NON:
		//�N���A���Ă��Ȃ��ꍇ�����N���A������`�F�b�N���܂�
		if (!this->cleared)
		{
			if (this->ClearCheck())
			{
				this->cleared = true;
				this->iscameraPlay = true;
				this->inside = (this->position - player->position);
			}
		}
		break;
	case Goal::Play:
		break;
	case Goal::End:
		
		break;
	}
	this->cameraPos = OGge->camera->GetPos();
	this->Camera_Play();
}
void Goal::Camera_Play()
{
	auto player = OGge->GetTask<Player>("Player");
	auto map = OGge->GetTask<Map>("map");
	if (!player && !map)
	{
		std::cout << "��O" << std::endl;
		return;
	}

	//Player���猩�ăS�[���������ɂ���ꍇ
	if (inside.x < 0)
	{
		if (this->cameraPos.x < 0)
		{
			if (this->cameraPos.x >= this->cameraPos.x + this->inside.x)
			{
				this->cameraPos.x -= this->cameraMove.x;
				OGge->camera->SetPos_x(this->cameraPos.x);
			}
		}
	}
	//Player���猩�ăS�[�����E���ɂ���ꍇ
	else if (inside.x > 0)
	{
		if (this->cameraPos.x + this->cameraSize.x < map->DrawSize.x * map->mapSize.x)
		{
			if (this->cameraPos.x <= this->cameraPos.x + this->inside.x)
			{
				this->cameraPos.x += this->cameraMove.x;
				OGge->camera->SetPos_x(this->cameraPos.x);
			}
		}
	}
	//Player���猩�ăS�[������ɂ���ꍇ
	else if (inside.y < 0)
	{
		if (this->cameraPos.y < 0)
		{
			if (this->cameraPos.y >= this->cameraPos.y + this->inside.y)
			{
				cameraPos.y -= cameraMove.y;
				OGge->camera->SetPos_y(cameraPos.y);
			}
		}
	}
	else if (inside.y > 0)
	{
		if (this->cameraPos.y + this->cameraSize.y < map->DrawSize.y * map->mapSize.y)
		{
			if (this->cameraPos.y <= this->cameraPos.y + this->inside.y)
			{
				cameraPos.y += cameraMove.y;
				OGge->camera->SetPos_y(cameraPos.y);
			}
		}
	}
	else
	{
		this->isanimetion = true;
	}
}
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