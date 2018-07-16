#include "water.h"
#include "Map\Map.h"
#include "Block\block.h"
#include "Player\Player.h"
#include "Effect\Effect.h"
#include "Gimmick\NO_MOVE\Door.h"
//#include "Paint\Paint.h"
Water::Water(Vec2 pos)
	:MAX_FALL(15.f), GRAVITY((9.8f / 60.f / 60.f*32.f) * 5), FIN_SPEED(1.0f), RAIN_TIME(180)
{
	//�^�O�ݒ�
	this->objectTag = "water";
	//�`��ő�ŏ��T�C�Y
	this->minSize = { 0,0 };
	this->maxSize = { 64,64 };
	//�o�ߎ��ԏ�����
	this->setTime = 0;
	//�I�u�W�F�N�g�̐���
	CreateObject(Objform::Cube, pos, this->minSize, 0.f);
	//�����X�e�[�^�X�̐ݒ�
	this->nowSituation = Water::Situation::Newfrom;
	this->currentState = Water::State::LIQUID;
	this->preState = Water::State::LIQUID;
	//�����ێ�����
	this->volume = 0.5f;
	//���G���ԏ�����
	this->invi = 0;
	//�J���[�l�̏�����
	this->color_a = { 1,1,1,1 };
	//�ړ��l�̏�����
	this->move = { 0,0 };
	//�o�ߎ��ԏ�����
	this->nowTime = 0;
	//���݃J���[��ݒ�
	this->color = Paint::PaintColor::Normal;
	//ID��ݒ�
	auto waters = OGge->GetTasks<Water>("water");
	int i = 0;
	auto ids = waters->begin();
	while (ids != waters->end())
	{
		if ((*ids)->id == i)
		{
			++i;
			ids = waters->begin();
		}
		else
		{
			++ids;
		}
	}
	this->id = i;
	//�T�E���h�̃t�@�C�����ݒ�
	soundname = "water-drop3.wav";
	//������Ԃ̏�����
	this->hold = false;
	//�����蔻��𐧌�
	this->Radius = { 0.5f,0.9f };
	//�^�O�̎w��
	__super::Init((std::string)"water");
	//�`��D��x�̐ݒ�
	__super::SetDrawOrder(0.2f);
}

Water::~Water()
{

}


bool Water::Initialize()
{
	soundplay = true;
	sound.create(soundname, false);

	return true;
}

void Water::UpDate()
{
	if (this->invi > 0)
	{
		this->invi--;
	}
	this->CheckState();
	switch (this->currentState) {
	case Water::State::LIQUID:
		this->objectTag = "Water";
		//������
		switch (this->nowSituation)
		{
		case Water::Situation::Newfrom:
			this->nowSituation = Water::UpNewform();
			break;
		case Water::Situation::Normal:
			this->nowSituation = Water::UpNormal();
			this->nowMove = this->move;
			this->MoveWATERCheck(this->nowMove);
			break;
		case Water::Situation::Deleteform:
			this->nowSituation = Water::UpDeleteform();
			break;
		case Water::Situation::CreaDelete:
			this->Kill();
			soundplay = true;
			break;
		}
		break;
	case Water::State::GAS:
		switch (this->nowSituation)
		{
		case Water::Situation::Normal:
			//�����C����
			if (!this->HeadCheck((std::string)"Floor"))
			{
				this->move.y = -3.0f;
				this->nowTime = 0;
			}
			else
			{
				this->move.y = 0;
				if (this->GetMove().x == 0 && this->GetMove().y == 0)
				{
					this->nowTime++;
				}
			}
			//�Î~���Ԃ��J���~�炷���ԕ��𒴂����Ƃ�
			if (this->RAIN_TIME < this->nowTime)
			{
				this->nowSituation = Situation::Rainfrom;
				this->nowTime = 0;
			}
			else
			{
				this->nowMove = this->move;
				this->MoveGASCheck(this->nowMove);
				this->Friction();
			}
			//��ʊO����
			if (this->position.y < 0.f - this->Scale.y)
			{
				this->Kill();
			}
			break;
		case Water::Situation::Rainfrom:
			if (this->nowTime < 10)
			{
				if (this->nowTime % 2 == 0)
				{
					float rand = random::GetRand(this->position.x + 12, this->position.x + this->maxSize.x - 12.f);
					auto water = Water::Create(Vec2(rand, this->position.y + this->maxSize.x / 2));
					water->SetMaxSize(Vec2(32, 32));
					water->SetTexture(rm->GetTextureData((std::string)"waterTex"));
					water->SetWaterVolume(this->volume / 5.f);
					water->SetColor(this->color);
				}
				this->nowTime++;
			}
			else
			{
				//�J���o���������Ƃ����������c��
				this->nowTime++;
				this->color_a.alpha -= 0.02f;
				if (this->nowTime > 40)
				{
					this->Kill();
				}
			}
			break;
		}
	case Water::State::SOLID:
		//�X����
		if (this->HeadSolidCheck())
		{
			this->SolidMelt();
		}
		if (!this->hold)
		{
			this->Friction();	
			this->nowMove = this->move;
			this->MoveSOILDCheck(this->nowMove);
		}
		break;
	}
}

Water::Situation Water::UpNewform()
{
	Water::Situation now = this->nowSituation;
	this->setTime++;
	this->Scale.x += 2;
	this->Scale.y += 2;
	this->position.x--;
	if (this->setTime >= this->maxSize.x / 2)
	{
		now = Water::Situation::Normal;
	}
	return now;
}

Water::Situation Water::UpDeleteform()
{
	Water::Situation now = this->nowSituation;
	++this->nowTime;
	if (this->nowTime >= 72)
	{
		now = Water::Situation::CreaDelete;
	}
	if (soundplay)
	{
		volControl.Play(&this->position, 1000.0f, 1.0f, sound);

		sound.play();
		soundplay = false;   //�A�����čĐ�����邱�Ƃ�h��
	}
	return now;
}

Water::Situation Water::UpNormal()
{
	
	Water::Situation now = this->nowSituation;
	auto map = OGge->GetTask<Map>("map");
	if ((map && map->HitCheck(*this, 0) || this->FootCheck((std::string)"Floor") || this->FootCheck((std::string)"Soil") || this->FootCheck((std::string)"Ladder")))
	{
		now = Water::Situation::Deleteform;
		this->nowTime = 0;
	}
	else
	{
		this->Friction();
	}
	return now;
}

void Water::Render2D()
{
	if (this->nowSituation == Situation::CreaDelete && this->currentState == State::LIQUID)
	{
		return;
	}
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 256, 256);
	if (this->currentState == State::GAS)
	{
		src.x += 256;
	}
	if (this->currentState == State::SOLID)
	{
		src.x += 512;
	}
	if (this->currentState == State::LIQUID && this->nowSituation == Situation::Deleteform)
	{
		src.y += 256;
		src.x = (float)((this->nowTime / 6) * 256);
	}
	src.OffsetSize();
	this->tex->Draw(draw, src, color_a);
	LineDraw();
}

bool Water::Finalize()
{
	return true;
}

void Water::SetState(const State& s_)
{
	this->currentState = s_;
}

Water::State Water::GetState() const
{
	return currentState;
}

void Water::SetSituation(const Situation& s_)
{
	this->nowSituation = s_;
}

Water::Situation Water::GetSituation() const
{
	return this->nowSituation;
}

float Water::waterMove()
{
	float _v = 0;
	if (this->IsBucket())
	{
		_v = this->volume;
		this->volume = 0.f;
	}
	else
	{
		return 0.0f;
	}
	this->Kill();
	return _v;
}

float Water::GetWaterVolume() const
{
	return this->volume;
}

void Water::SetTexture(Texture* texture)
{
	this->tex = texture;
}

void Water::Friction()
{
	if (this->move.x > 0)
	{
		this->move.x = std::max(this->move.x - this->FIN_SPEED, 0.f);
	}
	else
	{
		this->move.x = std::min(this->move.x + this->FIN_SPEED, 0.f);
	}
	if (this->currentState != State::GAS)
	{
		if (!this->FootCheck(std::string("Floor")) || !this->FootSolidCheck() || this->move.y < 0)
		{
			this->move.y = std::min(this->move.y + this->GRAVITY, this->MAX_FALL);
		}
		else
		{
			this->move.y = 0.0f;
		}
	}
}
bool Water::FootCheck(std::string& objtag, int n)
{
	GameObject foot;
	float x_ = this->Scale.x - (this->Scale.x * this->Radius.x);
	float y_ = this->Scale.y - (this->Scale.y * this->Radius.y);
	foot.CreateObject(Objform::Cube, Vec2(this->position.x + (x_ / 2.f), this->position.y + this->Scale.y + (y_ / 2.f) + 0.1f), Vec2(this->Scale.x - x_, 0.9f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (!map)
	{
		return false;
	}
	if (map->HitCheck(foot, objtag))
	{
		return true;
	}
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = blocks->begin(); id != blocks->end(); ++id)
	{
		if (foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (foot.hit(*(*id)))
			{
				return true;
			}
		}
	}
	auto doors = OGge->GetTasks<Door>("Door");
	for (auto id = doors->begin(); id != doors->end(); ++id)
	{
		if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (this->CubeHit(*(*id)))
			{
				return true;
			}
		}
	}
	if (this->currentState == State::SOLID)
	{
		auto buckets = OGge->GetTasks<Bucket>("bucket");
		for (auto id = buckets->begin(); id != buckets->end(); ++id)
		{
			if (foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (foot.hit(*(*id)))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Water::FootSolidCheck()
{
	GameObject foot;
	float x_ = this->Scale.x - (this->Scale.x * this->Radius.x);
	float y_ = this->Scale.y - (this->Scale.y * this->Radius.y);
	foot.CreateObject(Objform::Cube, Vec2(this->position.x + (x_ / 2.f), this->position.y + this->Scale.y + (y_ / 2.f) + 0.1f), Vec2(this->Scale.x - x_, 0.9f), 0.0f);
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if (this->id != (*id)->id)
		{
			if ((*id)->objectTag == "SOLID")
			{
				if (foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
				{
					if (foot.CubeHit(*(*id)))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Water::MoveWATERCheck(Vec2& est)
{
	auto map = OGge->GetTask<Map>("map");
	auto doors = OGge->GetTasks<Door>("Door");
	if (!map)
	{
		this->position += est;
		return;
	}
	while (est.x != 0.f)
	{
		float preX = this->position.x;
		if (est.x >= 1.f)
		{
			this->position.x += 1.f;
			est.x -= 1.f;
		}
		else if (est.x <= -1.f)
		{
			this->position.x -= 1.f;
			est.x += 1.f;
		}
		else
		{
			this->position.x += est.x;
			est.x = 0.f;
		}
		if (map->HitCheck(*this, 0))
		{
			this->position.x = preX;
			break;
		}
		for (auto id = doors->begin(); id != doors->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.x = preX;
					break;
				}
			}
		}
	}
	while (est.y != 0.f)
	{
		float preY = this->position.y;
		if (est.y >= 1.f)
		{
			this->position.y += 1.f;
			est.y -= 1.f;
		}
		else if (est.y <= -1.f)
		{
			this->position.y -= 1.f;
			est.y += 1.f;
		}
		else
		{
			this->position.y += est.y;
			est.y = 0.f;
		}
		if (map->HitCheck(*this, 0))
		{
			this->position.y = preY;
			break;
		}
		for (auto id = doors->begin(); id != doors->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.y = preY;
					break;
				}
			}
		}
	}
}

void Water::MoveGASCheck(Vec2& est)
{
	auto map = OGge->GetTask<Map>("map");
	auto doors = OGge->GetTasks<Door>("Door");
	while (est.x != 0.f)
	{
		float preX = this->position.x;
		if (est.x >= 1.f)
		{
			this->position.x += 1.f;
			est.x -= 1.f;
		}
		else if (est.x <= -1.f)
		{
			this->position.x -= 1.f;
			est.x += 1.f;
		}
		else
		{
			this->position.x += est.x;
			est.x = 0.f;
		}
		if (map->HitCheck(*this, 0))
		{
			this->position.x = preX;
			break;
		}
		for (auto id = doors->begin(); id != doors->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.x = preX;
					break;
				}
			}
		}
	}
	while (est.y != 0.f)
	{
		float preY = this->position.y;
		if (est.y >= 1.f)
		{
			this->position.y += 1.f;
			est.y -= 1.f;
		}
		else if (est.y <= -1.f)
		{
			this->position.y -= 1.f;
			est.y += 1.f;
		}
		else
		{
			this->position.y += est.y;
			est.y = 0.f;
		}
		if (map->HitCheck(*this, 0))
		{
			this->position.y = preY;
			break;
		}
		for (auto id = doors->begin(); id != doors->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.y = preY;
					break;
				}
			}
		}
	}
}

void Water::MoveSOILDCheck(Vec2& est)
{
	auto map = OGge->GetTask<Map>("map");
	auto waters = OGge->GetTasks<Water>("water");
	auto blocks = OGge->GetTasks<Block>("block");
	auto doors = OGge->GetTasks<Door>("Door");
	while (est.x != 0.f)
	{
		float preX = this->position.x;
		if (est.x >= 1.f)
		{
			this->position.x += 1.f;
			est.x -= 1.f;
		}
		else if (est.x <= -1.f)
		{
			this->position.x -= 1.f;
			est.x += 1.f;
		}
		else
		{
			this->position.x += est.x;
			est.x = 0.f;
		}
		if (map->HitCheck(*this, 1))
		{
			this->position.x = preX;
			break;
		}
		for (auto id = waters->begin(); id != waters->end(); ++id)
		{
			if (this->id != (*id)->id)
			{
				if ((*id)->objectTag == "SOLID")
				{
					if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
					{
						if (this->CubeHit(*(*id)))
						{
							this->position.x = preX;
							break;
						}
					}
				}
			}
		}
		for (auto id = blocks->begin(); id != blocks->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.x = preX;
					break;
				}
			}
		}
		for (auto id = doors->begin(); id != doors->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.x = preX;
					break;
				}
			}
		}
	}
	while (est.y != 0.f)
	{
		float preY = this->position.y;
		if (est.y >= 1.f)
		{
			this->position.y += 1.f;
			est.y -= 1.f;
		}
		else if (est.y <= -1.f)
		{
			this->position.y -= 1.f;
			est.y += 1.f;
		}
		else
		{
			this->position.y += est.y;
			est.y = 0.f;
		}
		if (map->HitCheck(*this, 1))
		{
			this->position.y = preY;
			break;
		}
		for (auto id = waters->begin(); id != waters->end(); ++id)
		{
			if (this->id != (*id)->id)
			{
				if ((*id)->objectTag == "SOLID")
				{
					if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
					{
						if (this->CubeHit(*(*id)))
						{
							this->position.y = preY;
							break;
						}
					}
				}
			}
		}
		for (auto id = blocks->begin(); id != blocks->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.y = preY;
					break;
				}
			}
		}
		for (auto id = doors->begin(); id != doors->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.y = preY;
					break;
				}
			}
		}
	}
}

bool Water::HeadCheck(std::string& objtag, int n)
{
	GameObject head;
	float x_ = this->Scale.x - (this->Scale.x * this->Radius.x);
	float y_ = this->Scale.y - (this->Scale.y * this->Radius.y);

	head.CreateObject(Objform::Cube, Vec2(this->position.x + (x_ / 2.f), this->position.y + (y_ / 2.f) - 1.0f), Vec2(this->Scale.x - x_, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (map->HitCheck(head, 0))
	{
		return true;
	}
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = blocks->begin(); id != blocks->end(); ++id)
	{
		if (head.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (head.hit(*(*id)))
			{
				return true;
			}
		}
	}
	return false;
}

bool Water::HeadSolidCheck()
{
	GameObject head;
	float x_ = this->Scale.x - (this->Scale.x * this->Radius.x);
	float y_ = this->Scale.y - (this->Scale.y * this->Radius.y);
	head.CreateObject(Objform::Cube, Vec2(this->position.x + (x_ / 2.f), this->position.y + (y_ / 2.f) - 3.0f), Vec2(this->Scale.x - x_, 3.0f), 0.0f);
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if (this->id != (*id)->id)
		{
			if (head.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if ((*id)->objectTag == "SOLID")
				{
					if (head.CubeHit(*(*id)))
					{
						return true;
					}
				}
			}
		}
	}
	auto doors = OGge->GetTasks<Door>("Door");
	for (auto id = doors->begin(); id != doors->end(); ++id)
	{
		if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (this->CubeHit(*(*id)))
			{
				return true;
			}
		}
	}
	return false;
}

bool Water::SetColor(const Paint::PaintColor& color)
{
	//�F�̕ω��͉t�̂̎��Ɍ��肷��
	if (this->currentState == State::LIQUID)
	{
		if (this->color == Paint::PaintColor::Purple)
		{
			//���Ȃ�F�̕ω����s��Ȃ�
		}
		else if (this->color == Paint::PaintColor::Blue && color == Paint::PaintColor::Red)
		{
			//�ƐԂŎ���
			this->color = Paint::PaintColor::Purple;
		}
		else if (this->color == Paint::PaintColor::Red && color == Paint::PaintColor::Blue)
		{
			//�ԂƐŎ���
			this->color = Paint::PaintColor::Purple;
		}
		else
		{
			//����ȊO�͂��̂܂ܕω�������
			this->color = color;
		}
	}
	//�F�ɍ��킹�Ďg�p����摜��ς���
	switch (this->color)
	{
	case Paint::PaintColor::Red:
		this->SetTexture(rm->GetTextureData((std::string)"waterRed"));
		break;
	case Paint::PaintColor::Blue:
		this->SetTexture(rm->GetTextureData((std::string)"waterBlue"));
		break;
	case Paint::PaintColor::Purple:
		this->SetTexture(rm->GetTextureData((std::string)"waterPurple"));
		break;
	default:
		this->SetTexture(rm->GetTextureData((std::string)"waterTex"));
		break;
	}
	return true;
}

Paint::PaintColor Water::GetColor() const
{
	return this->color;
}

void Water::MovePos(Vec2& est)
{
	this->move = est;
}

Vec2 Water::GetMove() const
{
	return this->move;
}

bool Water::IsBucket()
{
	return this->GetSituation() == Water::Situation::Normal && this->GetState() == Water::State::LIQUID && this->invi <= 0;
}

void Water::SetMaxSize(Vec2& max)
{
	this->maxSize = max;
}

void Water::SetWaterVolume(float value)
{
	this->volume = value;
}

Vec2 Water::MoveSolid(const Vec2& est)
{
	this->move.x = est.x;
	this->nowMove = move;
	this->MoveSOILDCheck(this->nowMove);
	return this->nowMove;
}

void Water::HoldCheck(bool flag)
{
	if (flag)
	{
		if (this->GetState() == State::SOLID)
		{
			this->hold = true;
			return;
		}
	}
	this->hold = false;
}

bool Water::GetHold() const
{
	return this->hold;
}

void Water::ResetMove()
{
	this->move = { 0,0 };
}

void Water::CheckState()
{
	if (this->preState != this->currentState)
	{
		this->preState = this->currentState;
		switch (this->currentState)
		{
		case State::GAS:
			this->Scale = this->maxSize;
			this->objectTag = "GAS";
			this->Radius = { 0.5f,0.8f };
			this->nowSituation = Situation::Normal;
			this->FIN_SPEED = 1.0f;
			break;
		case State::LIQUID:
			this->Radius = { 0.5f,0.9f };
			this->objectTag = "LIQUID";
			this->FIN_SPEED = 1.0f;
			break;
		case State::SOLID:
			this->Scale = this->maxSize;
			auto waters = OGge->GetTasks<Water>("water");
			for (auto id = waters->begin(); id != waters->end(); ++id)
			{
				//�����ȊO��ID�ł���
				if (this->id != (*id)->id)
				{
					//��Ԃ��X�ł���
					if ((*id)->GetState() == State::SOLID)
					{
						//�����蔻����s����Ԃɂ��鎞
						if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
						{
							//�����蔻����s��
							if (this->CubeHit(*(*id)))
							{
								//����𐅂Ɉڍs������
								(*id)->SetSituation(Situation::Normal);
								(*id)->SetState(State::LIQUID);
							}
						}
					}
				}
			}
			this->objectTag = "SOLID";
			this->Radius = { 0.7f,0.7f };
			this->nowSituation = Situation::Normal;
			this->FIN_SPEED = 0.05f;
			break;
		}
	}
}

void Water::MovePos_x(float est)
{
	this->move.x = est;
}

bool Water::SolidMelt()
{
	if (this->currentState == State::SOLID)
	{
		if (this->hold)
		{
			auto player = OGge->GetTask<Player>("Player");
			if (player)
			{
				//player->ReleaseHold();
				player->ReleaseSolid();
				player->SetState(Player::State::NORMAL);
				player->SetMotion(Player::Motion::Normal);
			}
		}
		this->SetState(State::LIQUID);
		this->SetSituation(Situation::Normal);
		//�X���n�������̃G�t�F�N�g
		auto effect = Effect::Create(
			Vec2(this->position.x + (this->Scale.x / 2.f) - (128.f / 2.f), this->position.y + this->Scale.y - (128.f / 1.5f)),
			Vec2(128, 128),
			Vec2(768, 768),
			1,
			150);
		effect->SetTexture(rm->GetTextureData((std::string)"steam"));
		effect->SetMode(Effect::Mode::Decrease);
		//effect->SetMaxSize(Vec2(80, 80));
		effect->Set(effect->position, Vec2(effect->position.x, effect->position.y - 200), 30);
	}
	return false;
}
void Water::SetScale(const Vec2& s)
{
	this->Scale = s;
}
unsigned int Water::GetID() const
{
	return this->id;
}
Water::SP Water::Create(Vec2& pos, bool flag_)
{
	auto to = Water::SP(new Water(pos));
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