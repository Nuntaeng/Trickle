#include "Player.h"
#include "Bucket\bucket.h"
#include "Water\water.h"
#include "Map\Map.h"
#include "Block\block.h"
#include "Gimmick\NO_MOVE\Switch.h"
#include "Gimmick\NO_MOVE\Door.h"
#include "Gimmick/NO_MOVE/WeightSwitch.h"

Player::Player()
{
	this->hold = false;
	this->isInputAuto = false;
	this->isInput = false;
	this->haveAddPos = { 0,0 };
	this->mass = 1.0f;      //��
}
Player::~Player()
{
	this->Finalize();
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{

	}
}
bool Player::Initialize(Vec2& pos)
{
	this->taskName = "Player";
	__super::Init(this->taskName);
	__super::SetDrawOrder(0.45f);
	//�I�u�W�F�N�g�̏�����
	this->CreateObject(Cube, pos, Vec2(64.0f, 80.f), 0.0f);
	this->objectTag = "Player";
	//�f�o�b�O�p�ʒu����
	//this->position = { 841,700 };
	//this->position = { 19 * 64 + 32,13 * 64 };
	//�e�N�X�`���̓ǂݍ���
	//�e�ϐ��̏�����
	this->CheckJump = true;
	this->CheckGravity = true;
	this->est = { 0.f,0.f };
	this->moveCnt = 0;
	this->inv = 0;
	//��Ԃ̏�����
	this->direction = Direction::RIGHT;
	this->motion = Motion::Normal;
	this->state = State::NORMAL;
	//�����ړ��p�l�̏�����
	this->animation.Initialize();
	return true;
}
void Player::UpDate()
{
	++animation.timeCnt;
	if (this->animation.timeCnt >= 300000)
	{
		this->animation.timeCnt = 0;
	}
	//�A�j���[�V�����J�E���g�𑝂₷
	this->StateUpDate();
	//�e��Ԃł̏����ƕʏ�Ԃւ̈ڍs
	if (this->state != State::ANIMATION)
	{
		if (!this->MotionUpDate())
		{
			//�I�����w�����ꂽ���ʂȂ�return�Ō�̏������s��Ȃ�
			return;
		}
		//�d�͂Ɩ��C�̌v�Z
		this->Friction();

		//�X�C�b�`�͂������[�V�������ς��Ȃ��̂�animation���̏�Ԃ������Ă���
		if (this->motion != Motion::Ladder && animation.animMo != Motion::Switch_M &&
			this->motion != Motion::Lift && this->motion != Lower && this->motion != Spill && this->motion != Motion::NoLower) {
			if (this->InputLeft())
			{
				this->est.x = -this->MOVE_SPEED;
				this->direction = Direction::LEFT;
			}
			else if (this->InputRight())
			{
				this->est.x = +this->MOVE_SPEED;
				this->direction = Direction::RIGHT;
			}
			else
			{
				this->est.x = this->AxisLX() * this->MOVE_SPEED;
				if (this->AxisLX() > 0)
				{
					this->direction = Direction::RIGHT;
				}
				if (this->AxisLX() < 0)
				{
					this->direction = Direction::LEFT;
				}
			}
			
		}
	}
	//�ŏI�I�Ȉړ��l�𔽉f������
	Vec2 move = this->est;
	this->MoveCheck(move);
	if (this->TohaveObjectHit() && this->state == State::NORMAL) {
		//�u���b�N������
		this->motion = Motion::Block_M;
	}
	if (this->state == State::BUCKET)
	{
		this->HaveObjectPosMove();
	}
}
void Player::Render2D()
{
	Box2D draw;
	if (this->hold)
	{
		draw = { this->position.x - 8.f,this->position.y + this->haveAddPos.y,this->Scale.x + 8.f, this->Scale.y - this->haveAddPos.y };
		draw.OffsetSize();
	}
	else
	{
		draw = { this->position.x - 8.f, this->position.y, this->Scale.x + 8.f, this->Scale.y };
		draw.OffsetSize();
	}
	{
		draw.y += 2.f;
		draw.h += 2.f;
	}
	Box2D src = this->animation.returnSrc(this->motion, this->state, this->direction);
	//��-�V��������src��return����
	src.OffsetSize();

	//�������Ȃ�摜���t�ɂ���
	if (direction == Direction::RIGHT) {
		float k = src.w;
		src.w = src.x;
		src.x = k;
	}
	this->playerimg->Draw(draw, src);
	this->LineDraw();
}
bool Player::Finalize()
{
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{

	}
	return true;
}
Vec2 Player::GetEst() const {
	return est;
}
bool Player::HeadCheck()
{
	if (this->state == State::CLEAR)
	{
		return false;
	}
	this->head.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y - 1.0f), Vec2(this->Scale.x, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (map && map->HitCheck(head, 1))
	{
		return true;
	}
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = blocks->begin(); id != blocks->end(); ++id)
	{
		if (this->head.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (this->head.CubeHit(*(*id)))
			{
				return true;
			}
		}
	}
	auto door = OGge->GetTasks<Door>("Door");
	for (auto id = door->begin(); id != door->end(); ++id)
	{
		if (head.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (head.CubeHit(*(*id)))
			{
				return true;
			}
		}
	}
	return false;
}
bool Player::HeadMapCheck(std::string& objname_, bool flag)
{
	this->head.CreateObject(Objform::Cube, Vec2(this->position.x + 1.f, this->position.y - 1.0f), Vec2(this->Scale.x - 1.f, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (head.IsObjectDistanceCheck(map->hitBase[y][x].position, map->hitBase[y][x].Scale))
			{
				if (head.CubeHit(map->hitBase[y][x]))
				{
					if (flag)
					{
						if (map->hitBase[y][x].objectTag == objname_)
						{
							this->animation.SetAnimaVec(this->position, map->hitBase[y][x].position);
							return true;
						}
					}
					else
					{
						if (map->hitBase[y][x].objectTag != objname_)
						{
							this->animation.SetAnimaVec(this->position, Vec2(map->hitBase[y][x].position.x, map->hitBase[y][x].position.y - (this->Scale.y - 64.f)));
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
bool Player::HeadSolidCheck()
{
	if (this->hold)
	{
		return false;
	}
	//���̓����蔻��
	head.CreateObject(Objform::Cube, Vec2(this->position.x + 1.f, this->position.y - 1.0f), Vec2(this->Scale.x - 1.f, this->Scale.y), 0.0f);
	//�����
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		//���肪�X�ł���
		if ((*id)->GetState() == Water::State::SOLID)
		{
			//�����̋ߕӂɑ��݂��Ă���
			if (head.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				//���肪�����Ă���X����Ȃ���
				if (!(*id)->GetHold())
				{
					//�������Ă���Ȃ��
					if (head.CubeHit(*(*id)))
					{
						(*id)->HoldCheck(true);
						this->hold = true;
						this->haveAddPos = { ((*id)->Scale.x * (*id)->Radius.x) - (this->Scale.x - ((*id)->Scale.x * (*id)->Radius.x)),((*id)->Scale.y * (*id)->Radius.y) - (this->Scale.y - ((*id)->Scale.y * (*id)->Radius.y)) + 30.f };
						this->position.y -= this->haveAddPos.y;
						this->Scale.y += this->haveAddPos.y;
						return true;
					}
				}
			}
		}
	}
	return false;
}
bool Player::SolidHitCheck()
{
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if ((*id)->objectTag == "SOLID" && !(*id)->GetHold())
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					return true;
				}
			}
		}
	}
	return false;
}
bool Player::FootCheck()
{
	this->foot.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y + this->Scale.y), Vec2(this->Scale.x, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (map && map->HitCheck(foot, 1))
	{
		return true;
	}
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = blocks->begin(); id != blocks->end(); ++id)
	{
		if (foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (foot.CubeHit(*(*id)))
			{
				return true;
			}
		}
	}
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		if (foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (foot.CubeHit(*(*id)))
			{
				if ((*id)->objectTag == "SOLID")
				{
					return true;
				}
			}
		}
	}

	//�e�X�g�ǉ�
	auto Wswitch = OGge->GetTasks<WeightSwitch>("WeightSwitch");
	for (auto id = Wswitch->begin(); id != Wswitch->end(); ++id)
	{
		if (foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (foot.CubeHit(*(*id)))
			{
				return true;
			}
		}
	}

	return false;
}
bool Player::FootMapCheck(std::string& objname_, bool flag)
{
	this->foot.CreateObject(Objform::Cube, Vec2(this->position.x + 1.f, this->position.y + this->Scale.y + 1.5f), Vec2(this->Scale.x - 1.f, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (foot.IsObjectDistanceCheck(map->hitBase[y][x].position, map->hitBase[y][x].Scale))
			{
				if (foot.CubeHit(map->hitBase[y][x]))
				{
					if (flag)
					{
						if (map->hitBase[y][x].objectTag == objname_)
						{
							this->animation.SetAnimaVec(this->position, Vec2(map->hitBase[y][x].position.x, map->hitBase[y][x].position.y + 10.f));
							return true;
						}
					}
					else
					{
						if (map->hitBase[y][x].objectTag != objname_)
						{
							//this->animation.SetAnimaVec(this->position, Vec2(map->hitBase_[y][x].position.x, map->hitBase_[y][x].position.y + 10.f));
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
bool Player::SolidFootCheck()
{
	foot.CreateObject(Objform::Cube, Vec2(this->position.x + 1.f, this->position.y + this->Scale.y), Vec2(this->Scale.x - 1.f, 64.0f), 0.0f);
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		//�X�ł��莩���̋ߕӂł���
		if ((*id)->GetState() == Water::State::SOLID && foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			//�������Ă���Ȃ��
			if (foot.CubeHit(*(*id)))
			{
				return true;
			}
		}
	}
	return false;
}
void Player::MoveCheck(Vec2& est)
{
	auto map = OGge->GetTask<Map>("map");
	if (!map)
	{
		return;
	}
	auto blocks = OGge->GetTasks<Block>("block");
	auto waters = OGge->GetTasks<Water>("water");
	auto block = OGge->GetTask<Block>("block");
	auto door = OGge->GetTasks<Door>("Door");
	//�e�X�g�ǉ�
	auto Wswitch = OGge->GetTasks<WeightSwitch>("WeightSwitch");

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
		for (auto id = door->begin(); id != door->end(); ++id)
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
		//�e�X�g�ǉ�
		for (auto id = Wswitch->begin(); id != Wswitch->end(); ++id)
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

		for (auto id = blocks->begin(); id != blocks->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					block->plhit = true;

					this->position.x = preX;
					break;
				}
				else
				{
					block->plhit = false;
				}
			}
		}
		for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
		{
			//�X�ł���
			if ((*id)->objectTag == "SOLID")
			{
				//������ԂłȂ��Ƃ��̂�
				if (!(*id)->GetHold())
				{
					if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
					{
						//�����蔻����s��
						if (this->CubeHit(*(*id)))
						{
							this->position.x = preX;
							break;
						}
					}
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
		for (auto id = door->begin(); id != door->end(); ++id)
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
		//�e�X�g�ǉ�
		for (auto id = Wswitch->begin(); id != Wswitch->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.y = preY;
					this->position.y += (*id)->SetSwitchUpPos();
					break;
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
		for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
		{
			//�X�ł���
			if ((*id)->objectTag == "SOLID")
			{
				//������ԂłȂ��Ƃ��̂�
				if (!(*id)->GetHold())
				{
					if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
					{
						//�����蔻����s��
						if (this->CubeHit(*(*id)))
						{
							this->position.y = preY;
							break;
						}
					}
				}
			}
		}
	}
}
void Player::Friction()
{
	if (this->motion == Motion::Ladder)
	{
		return;
	}
	if (this->est.x > 0)
	{
		this->est.x = std::min(this->est.x + this->FIN_SPEED, 0.f);
	}
	else
	{
		this->est.x = std::max(this->est.x - this->FIN_SPEED, 0.f);
	}
	if (!this->FootCheck() || this->est.y < 0)
	{
		this->est.y = std::min(this->est.y + this->GRAVITY, this->MAX_FALL);
	}
	else
	{
		this->est.y = 0.0f;
	}
}
bool Player::HaveObjectHit()
{
	if (this->inv > 0)
	{
		return false;
	}
	//���łɎ����Ă���Ȃ�Γ����Ȃ�
	if (this->hold || this->motion == Motion::Switch_M)
	{
		return false;
	}
	auto bucket = OGge->GetTasks<Bucket>("bucket");
	for (auto id = (*bucket).begin(); id != (*bucket).end(); ++id)
	{
		if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (this->CubeHit(*(*id)))
			{
				(*id)->HoldCheck(true);
				this->hold = true;
				this->haveAddPos = { ((*id)->Scale.x * (*id)->Radius.x) - (this->Scale.x - ((*id)->Scale.x * (*id)->Radius.x)),((*id)->Scale.y * (*id)->Radius.y) - (this->Scale.y - ((*id)->Scale.y * (*id)->Radius.y)) };
				this->position.y -= this->haveAddPos.y;
				this->Scale.y += this->haveAddPos.y;
				return true;
			}
		}
	}
	left.CreateObject(Objform::Cube, Vec2(this->position.x - 16.0f, this->position.y), Vec2(16.0f + this->Scale.x, this->Scale.y), 0.0f);
	right.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y), Vec2(16.0f + this->Scale.x, this->Scale.y), 0.0f);
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if (!(*id)->GetHold())
		{
			if ((*id)->GetState() == Water::State::SOLID)
			{
				if (left.IsObjectDistanceCheck((*id)->position, (*id)->Scale) || right.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
				{
					if (left.CubeHit(*(*id)) || right.CubeHit(*(*id)))
					{
						(*id)->HoldCheck(true);
						this->hold = true;
						this->haveAddPos = { ((*id)->Scale.x * (*id)->Radius.x) - (this->Scale.x - ((*id)->Scale.x * (*id)->Radius.x)),((*id)->Scale.y * (*id)->Radius.y) - (this->Scale.y - ((*id)->Scale.y * (*id)->Radius.y)) + 30.f };
						this->position.y -= this->haveAddPos.y;
						this->Scale.y += this->haveAddPos.y;
						return true;
					}
				}
			}
		}
	}
	return false;
}
void Player::SwitchCheck()
{
	auto switchs = OGge->GetTasks<Switch>("Switch");
	for (auto id = switchs->begin(); id != switchs->end(); ++id)
	{
		if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if ((*id)->CubeHit(*this))
			{
				//�ړ�����ʒu��Ԃ�
				this->animation.SetAnimaVec(this->position, Vec2((*id)->position));
				//�ړ�������ɃX�C�b�`�̃A�j���[�V����������悤��
				this->animation.animMo = Motion::Switch_M;
				//�ړ�����A�j���[�V�����ɕς���
				this->state = State::ANIMATION;
				this->est = { 0.f,0.f };
				return;
			}
		}
	}
}
void Player::HaveObjectPosMove()
{
	auto buckets = OGge->GetTasks<Bucket>("bucket");
	for (auto id = (*buckets).begin(); id != (*buckets).end(); ++id)
	{
		if ((*id)->GetHold())
		{
			if (this->motion == Motion::Spill) {
				if (this->direction == Direction::LEFT)
				{
					switch (animation.animCnt / 8 % 3) {
					case 0:
						(*id)->position = { this->position.x - 40,this->position.y + 30 };
						(*id)->angle = 315;
						break;
					case 1:
						(*id)->position = { this->position.x - 40,this->position.y + 60 };
						(*id)->angle = 270;
						break;
					case 2:
						(*id)->position = { this->position.x - 40,this->position.y + 30 };
						(*id)->angle = 315;
						break;
					}
				}
				else
				{
					switch (animation.animCnt / 8 % 3) {
					case 0:
						(*id)->position = { this->position.x + 40,this->position.y + 30 };
						(*id)->angle = 45;
						break;
					case 1:
						(*id)->position = { this->position.x + 40,this->position.y + 60 };
						(*id)->angle = 90;
						break;
					case 2:
						(*id)->position = { this->position.x + 40,this->position.y + 30 };
						(*id)->angle = 45;
						break;
					}
				}
			}
			else if (this->motion == Motion::Lift) {
				if (this->animation.animCnt == 0)
				{
					this->animation.animCnt = 5;
				}
				if (this->direction == Direction::LEFT)
				{
					switch (animation.animCnt / 8 % 2) {
					case 0:
						(*id)->position = { this->position.x - 40,this->position.y + 60 };
						break;
					case 1:
						(*id)->position = { this->position.x - 20,this->position.y + 30 };
						break;
					}
				}
				else
				{
					switch (animation.animCnt / 8 % 2) {
					case 0:
						(*id)->position = { this->position.x + 40,this->position.y + 60 };
						break;
					case 1:
						(*id)->position = { this->position.x + 20,this->position.y + 30 };
						break;
					}
				}
			}
			else if (this->motion == Motion::Lower) {
				if (this->direction == Direction::LEFT)
				{
					switch (animation.animCnt / 8 % 2) {
					case 0:
						(*id)->position = { this->position.x - 20,this->position.y + 30 };
						break;
					case 1:
						(*id)->position = { this->position.x - 40,this->position.y + 50 };
						break;
					}
				}
				else
				{
					switch (animation.animCnt / 8 % 2) {
					case 0:
						(*id)->position = { this->position.x + 20,this->position.y + 30 };
						break;
					case 1:
						(*id)->position = { this->position.x + 40,this->position.y + 50 };
						break;
					}
				}
			}
			else {
				if (this->direction == Direction::RIGHT)
				{
					(*id)->position = { this->position.x,this->position.y - (*id)->Scale.y + 60.f };
				}
				else
				{
					(*id)->position = { this->position.x - 8.f,this->position.y - (*id)->Scale.y + 60.f };
				}
				(*id)->angle = 0;
			}
		}
	}
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if ((*id)->GetHold())
		{
			if (this->motion == Motion::Lift) {
				if (this->animation.animCnt == 0)
				{
					this->animation.animCnt = 5;
				}
				if (this->direction == Direction::LEFT)
				{
					switch (animation.animCnt / 8 % 2) {
					case 0:
						(*id)->position = { this->position.x - 40,this->position.y - this->haveAddPos.y + 70 };
						break;
					case 1:
						(*id)->position = { this->position.x - 20,this->position.y - this->haveAddPos.y + 50 };
						break;
					}
				}
				else
				{
					switch (animation.animCnt / 8 % 2) {
					case 0:
						(*id)->position = { this->position.x + 40,this->position.y - this->haveAddPos.y + 70 };
						break;
					case 1:
						(*id)->position = { this->position.x + 20,this->position.y - this->haveAddPos.y + 50 };
						break;
					}
				}
			}
			else if (this->motion == Motion::Lower) {
				if (this->direction == Direction::LEFT)
				{
					switch (animation.animCnt / 8 % 2) {
					case 0:
						(*id)->position = { this->position.x - 20,this->position.y - this->haveAddPos.y + 50 };
						break;
					case 1:
						(*id)->position = { this->position.x - 40,this->position.y - this->haveAddPos.y + 70 };
						break;
					}
				}
				else
				{
					switch (animation.animCnt / 8 % 2) {
					case 0:
						(*id)->position = { this->position.x + 20,this->position.y - this->haveAddPos.y + 50 };
						break;
					case 1:
						(*id)->position = { this->position.x + 40,this->position.y - this->haveAddPos.y + 70 };
						break;
					}
				}
			}
			else {
				if (this->direction == Direction::RIGHT)
				{
					(*id)->position = { this->position.x,this->position.y - this->haveAddPos.y + 35.f };
				}
				else
				{
					(*id)->position = { this->position.x - 8.f,this->position.y - this->haveAddPos.y + 35.f };
				}
			}
		}
	}
}
void Player::Animation::SetAnimaVec(Vec2& start_, Vec2& end_)
{
	this->startVec = start_;
	this->endVec = end_;
	if (this->startVec == this->endVec) {
		this->same_flag = true;
	}
	this->animationVec = { this->endVec.x - this->startVec.x ,this->endVec.y - this->startVec.y };
}
bool Player::Animation::Initialize()
{
	this->animationVec = { 0.f,0.f };
	this->startVec = { 0.f,0.f };
	this->endVec = { 0.f,0.f };
	this->timeCnt = 0;
	this->animCnt = 0;
	this->animMo = Normal;
	return true;
}
Vec2 Player::Animation::Move(Motion motion_)
{
	auto player = OGge->GetTask<Player>("Player");
	Vec2 move = { 0.f,0.f };
	//X�������ړ�(�ړI�n�܂ŕ����čs��)
	if (this->animationVec.x != 0.f)
	{
		if (this->animationVec.x > 0.f)
		{
			player->direction = Player::Direction::RIGHT;
		}
		else if (this->animationVec.x < 0.f)
		{
			player->direction = Player::Direction::LEFT;
		}
		player->motion = Motion::Walk;
		if (this->animationVec.x >= 1.0f)
		{
			move.x += 1.0f;
			this->animationVec.x -= 1.0f;
		}
		else if (this->animationVec.x <= -1.0f)
		{
			move.x -= 1.0f;
			this->animationVec.x += 1.0f;
		}
		else
		{
			move.x += this->animationVec.x;
			this->animationVec.x = 0.f;
		}
	}
	//�x�������ړ�
	if (this->animationVec.x == 0.f)
	{
		//��q�ɏ��
		if (this->animationVec.y >= 0.f && motion_ == Motion::Ladder)
		{
			move.y += this->animationVec.y;
			player->motion = motion_;
			this->animationVec.y = 0.f;
			this->animMo = Motion::Normal;
		}
		//�X�C�b�`������
		else if (this->animationVec.y >= 0.f && motion_ == Motion::Switch_M)
		{
			//�X�C�b�`�̃A�j���[�V���������s����
			player->direction = Direction::RIGHT;
			auto switchs = OGge->GetTasks<Switch>("Switch");
			for (auto id = switchs->begin(); id != switchs->end(); ++id)
			{
				if ((*id)->hit(*player))
				{
					(*id)->ChangeON_OFF();
				}
			}
			//y�Ɉړ������Ȃ��悤�ɂ���
			this->animationVec.y = 0.f;
			//�v���C�����X�C�b�`�������A�j���[�V����
			player->motion = motion_;
		}
		//��q����y�ɍs���iNormal��ԁj
		else
		{
			move.y += this->animationVec.y;
			this->animCnt = 0;
			player->motion = Motion::Normal;
			this->animationVec.y = 0.f;
			this->animMo = Motion::Normal;
		}
	}
	return move;
}
bool Player::Animation::isMove()
{
	if (this->animationVec.x != 0.f || this->animationVec.y != 0.f)
	{
		return true;
	}

	return false;
}
Box2D Player::Animation::returnSrc(Motion motion, State state, Direction dir)
{
	auto player = OGge->GetTask<Player>("Player");
	Box2D src(0, 0, this->srcX, this->srcY);
	//src = Box2D(this->�w�肵���A�j���[�V�����̏��Ԃ̔z��[this->timeCnt / �f�B���C�@% �R�}��] * this->srcX, 
	//		�ǂݍ��މ摜�̍s�� * this->srcY, 
	//		this->srcX, this->Y);
	if (state == Normal) {
		switch (motion) {
		case Motion::Normal:
			src = Box2D(this->idle[this->timeCnt / 3 % 10] * this->srcX, 0, this->srcX, this->srcY);
			break;
		case Motion::Walk:
			src = Box2D(this->walk[this->timeCnt / 3 % 9] * this->srcX, this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Jump:
			src = Box2D(0 * this->srcX, 2 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Fall:
			src = Box2D(1 * this->srcX, 2 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Ladder:
			src = Box2D(this->ladder[this->animCnt / 8 % 2] * this->srcX, 3 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Block_M:
			src = Box2D(this->walk[this->timeCnt / 3 % 9] * this->srcX, 9 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Switch_M:
		{
			auto switchs = OGge->GetTasks<Switch>("Switch");
			for (auto id = switchs->begin(); id != switchs->end(); ++id) {
				if ((*id)->hit(*player)) {
					if ((*id)->isON()) {
						if (dir == Direction::LEFT)
						{
							src = Box2D(this->switch_1[this->animCnt / 5 % 5] * this->srcX, 8 * this->srcY, this->srcX, this->srcY);
						}
						else
						{
							src = Box2D(this->switch_2[this->animCnt / 5 % 5] * this->srcX, 8 * this->srcY, this->srcX, this->srcY);
						}
					}
					else {
						if (dir == Direction::LEFT)
						{
							src = Box2D(this->switch_2[this->animCnt / 5 % 5] * this->srcX, 8 * this->srcY, this->srcX, this->srcY);
						}
						else
						{
							src = Box2D(this->switch_1[this->animCnt / 5 % 5] * this->srcX, 8 * this->srcY, this->srcX, this->srcY);
						}
					}
				}
			}
		}
		break;
		}
	}
	if (state == ANIMATION)
	{
		switch (motion) {
		case Motion::Walk:
			src = Box2D(this->walk[this->timeCnt / 3 % 9] * this->srcX, this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Ladder:
			src = Box2D(0 * this->srcX, 3 * this->srcY, this->srcX, this->srcY);
			break;
		}
	}
	if (state == BUCKET) {
		switch (motion) {
		case Motion::Normal:
			src = Box2D(this->idle[this->timeCnt / 3 % 10] * this->srcX, 4 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Walk:
			src = Box2D(this->walk[this->timeCnt / 3 % 9] * this->srcX, 5 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Jump:
			src = Box2D(0 * this->srcX, 7 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Fall:
			src = Box2D(1 * this->srcX, 7 * this->srcY, this->srcX, this->srcY);
			break;

		case Motion::Lift:
			src = Box2D(this->lift[this->animCnt / 8 % 2] * this->srcX, 6 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Lower:
			src = Box2D(this->lower[this->animCnt / 8 % 2] * this->srcX, 6 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Spill:
			src = Box2D(this->spill[this->animCnt / 8 % 3] * this->srcX, 6 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::NoLower:
			src = Box2D(2 * this->srcX, 4 * this->srcY, this->srcX, this->srcY);
			break;
		}
	}
	if (state == CLEAR) {
		switch (motion) {
		case Motion::Normal:
			src = Box2D(2 * 641, 10 * this->srcY, 641, this->srcY);
			break;
		case Motion::Jump:
			src = Box2D(0 * 641, 10 * this->srcY, 641, this->srcY);
			break;
		case Motion::Fall:
			src = Box2D(1 * 641, 10 * this->srcY, 641, this->srcY);
			break;
		}
	}
	return src;

}
void Player::LadderMoveCheck(Vec2& est)
{
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
		auto map = OGge->GetTask<Map>("map");
		if (map && (map->HitCheck(*this, "Floor") || map->HitCheck(*this, "LadderTop")))
		{
			this->position.y = preY;
			break;
		}
		auto waters = OGge->GetTasks<Water>("water");
		for (auto id = waters->begin(); id != waters->end(); ++id)
		{
			if ((*id)->GetState() == Water::State::SOLID && this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
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
bool Player::MapHitCheck(std::string& objname_)
{
	auto map = OGge->GetTask<Map>("map");
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (this->IsObjectDistanceCheck(map->hitBase[y][x].position, map->hitBase[y][x].Scale))
			{
				if (this->CubeHit(map->hitBase[y][x]))
				{
					if (map->hitBase[y][x].objectTag == objname_)
					{
						this->animation.SetAnimaVec(this->position, Vec2(map->hitBase[y][x].position.x, this->position.y));
						return true;
					}
				}
			}
		}
	}
	return false;
}
bool Player::TohaveObjectHit()
{
	left.CreateObject(Objform::Cube, Vec2(this->position.x - 1.0f, this->position.y), Vec2(1.0f, this->Scale.y - 1.0f), 0.0f);
	right.CreateObject(Objform::Cube, Vec2(this->position.x + this->Scale.x, this->position.y), Vec2(1.0f, this->Scale.y - 1.0f), 0.0f);
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = (*blocks).begin(); id != (*blocks).end(); ++id)
	{
		if (left.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (left.CubeHit(*(*id)))
			{
				(*id)->PlCheckHit(left);
				if (this->est.x < 0)
				{
					(*id)->GetMove(this->est * 0.5f);
					return true;
				}
			}
		}
		if (right.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (right.CubeHit(*(*id)))
			{
				(*id)->PlCheckHit(right);
				if (this->est.x > 0)
				{
					(*id)->GetMove(this->est * 0.5f);
					return true;
				}
			}
		}
	}
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		if ((*id)->GetState() == Water::State::SOLID)
		{
			if (this->est.x < 0)
			{
				if (left.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
				{
					if (left.CubeHit(*(*id)))
					{
						if (!((*id)->MoveSolid(this->est) == Vec2(0, 0)))
						{
							return true;
						}
					}
				}
			}
			if (this->est.x > 0)
			{
				if (right.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
				{
					if (right.CubeHit(*(*id)))
					{
						if (!((*id)->MoveSolid(this->est) == Vec2(0, 0)))
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
void Player::SetTexture(Texture* texture)
{
	this->playerimg = texture;
}
Player::State Player::NowState() const
{
	return this->state;
}
void Player::SetPos(Vec2& pos)
{
	this->position = pos;
}
Vec2 Player::GetPos() const
{
	if (this->hold)
	{
		return Vec2(this->position.x, this->position.y + this->haveAddPos.y);
	}
	return this->position;
}
bool Player::ReleaseHold()
{
	if (this->hold)
	{
		if (this->PutCheck())
		{
			//�����Ă��锻������ɖ߂�
			auto bucket = OGge->GetTasks<Bucket>("bucket");
			for (auto id = bucket->begin(); id != bucket->end(); ++id)
			{
				if ((*id)->GetHold())
				{
					(*id)->HoldCheck(false);
					this->hold = false;
					if (this->direction == Direction::LEFT)
					{
						(*id)->position.x = this->position.x - 50;
					}
					else
					{
						(*id)->position.x = this->position.x + 50;
					}
				}
			}
			auto waters = OGge->GetTasks<Water>("water");
			for (auto id = waters->begin(); id != waters->end(); ++id)
			{
				if ((*id)->GetHold())
				{
					if (this->direction == Direction::LEFT)
					{
						(*id)->position.x = this->position.x - 60;
					}
					else
					{
						(*id)->position.x = this->position.x + 60;
					}
					(*id)->HoldCheck(false);
					(*id)->ResetMove();
					this->hold = false;
				}
			}
			this->inv = 10;
			this->position.y += this->haveAddPos.y;
			this->Scale.y -= this->haveAddPos.y;
			this->haveAddPos = { 0,0 };
			return true;
		}
		else
		{
			this->animation.animCnt = 0;
			this->motion = Motion::NoLower;
		}
	}
	return false;
}
bool Player::ReleaseSolid()
{
	if (this->hold)
	{
		auto waters = OGge->GetTasks<Water>("water");
		for (auto id = waters->begin(); id != waters->end(); ++id)
		{
			if ((*id)->GetHold())
			{
				(*id)->position.x = this->position.x;
				(*id)->HoldCheck(false);
				(*id)->ResetMove();
				this->hold = false;
			}
		}
		this->inv = 0;
		this->position.y += this->haveAddPos.y;
		this->Scale.y -= this->haveAddPos.y;
		this->haveAddPos = { 0,0 };
		return true;
	}
	return false;
}
bool Player::LadderJumpCheck()
{
	auto map = OGge->GetTask<Map>("map");
	if (map)
	{
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->hitBase[y][x].Getarr() == 24)
				{
					if (this->IsObjectDistanceCheck(map->hitBase[y][x].position, map->hitBase[y][x].Scale))
					{
						if (this->CubeHit(map->hitBase[y][x]))
						{
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}
bool Player::PutCheck()
{
	auto map = OGge->GetTask<Map>("map");
	if (map)
	{
		if (this->direction == Direction::LEFT)
		{
			left.CreateObject(Cube, Vec2(this->position.x - this->Scale.x, this->position.y), this->Scale, 0.0f);
			if (map->HitCheck(left,1))
			{
				return false;
			}
		}
		else
		{
			right.CreateObject(Cube, Vec2(this->position.x + this->Scale.x, this->position.y), this->Scale, 0.0f);
			if (map->HitCheck(right,1))
			{
				return false;
			}
		}
	}
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = blocks->begin(); id != blocks->end(); ++id)
	{
		if (this->direction == Direction::LEFT)
		{
			left.CreateObject(Cube, Vec2(this->position.x - this->Scale.x, this->position.y), this->Scale, 0.0f);
			if ((*id)->IsObjectDistanceCheck(left.position, left.Scale))
			{
				if ((*id)->CubeHit(left))
				{
					return false;
				}
			}
		}
		else
		{
			right.CreateObject(Cube, Vec2(this->position.x + this->Scale.x, this->position.y), this->Scale, 0.0f);
			if ((*id)->IsObjectDistanceCheck(right.position, right.Scale))
			{
				if ((*id)->CubeHit(right))
				{
					return false;
				}
			}
		}
	}
	auto doors = OGge->GetTasks<Door>("Door");
	for (auto id = doors->begin(); id != doors->end(); ++id)
	{
		if (this->direction == Direction::LEFT)
		{
			left.CreateObject(Cube, Vec2(this->position.x - this->Scale.x, this->position.y), this->Scale, 0.0f);
			if ((*id)->IsObjectDistanceCheck(left.position, left.Scale))
			{
				if ((*id)->CubeHit(left))
				{
					return false;
				}
			}
		}
		else
		{
			right.CreateObject(Cube, Vec2(this->position.x + this->Scale.x, this->position.y), this->Scale, 0.0f);
			if ((*id)->IsObjectDistanceCheck(right.position, right.Scale))
			{
				if ((*id)->CubeHit(right))
				{
					return false;
				}
			}
		}
	}
	return true;
}
void Player::SetMotion(Motion motion_)
{
	this->motion = motion_;
}
void Player::SetState(State state_)
{
	this->state = state_;
}
void Player::SetInputAuto(bool flag)
{
	this->isInputAuto = flag;
	if (this->isInputAuto)
	{
		if (this->state == State::BUCKET)
		{
			this->motion = Motion::Lower;
		}
	}
}
bool Player::GetInputAuto() const
{
	return this->isInputAuto;
}
void Player::StateUpDate()
{
	switch (this->state)
	{
	case State::ANIMATION:
		//�v���C�����ړ����鋗�����c���Ă���Ƃ�||���X�ړ����鋗�����Ȃ��Ƃ�
		if (this->animation.isMove() || animation.same_flag)
		{
			//�ړ�����
			this->position += this->animation.Move(this->animation.animMo);
			if (this->direction == Direction::LEFT)
			{
				this->est.x -= 5.0f;
			}
			else
			{
				this->est.x += 5.0f;
			}
			if (this->TohaveObjectHit())
			{
				this->state = State::NORMAL;
				this->motion = Motion::Normal;
			}
			this->est = { 0,0 };
			animation.same_flag = false;
		}
		else
		{
			//�ʏ�ɖ߂�
			this->state = State::NORMAL;
		}
		break;
	case State::BUCKET:
		//�o�P�c�̒l�������ɍ��킹��
		//this->HaveObjectPosMove();
		//�o�P�c��u������
		if (this->InputB2down() && this->FootCheck() && this->motion != Motion::NoLower)
		{
			if (this->PutCheck() && this->motion != Motion::Spill)
			{
				this->motion = Motion::Lower;
			}
			else
			{
				this->animation.animCnt = 0;
				this->motion = Motion::NoLower;
			}
		}
		break;
	case State::NORMAL:
		break;
	case State::CLEAR:
		StateClearUpdate();
		break;
	}
	//���G���Ԍ���
	if (this->inv > 0)
	{
		this->inv--;
	}
}
bool Player::MotionUpDate()
{
	switch (this->motion)
	{
	case Motion::Normal:
		if (!this->MotionNormalUpDate())
		{
			return false;
		}
		break;
	case Motion::Jump:
		if (!this->MotionJumpUpDate())
		{
			return false;
		}
		break;
	case Motion::Fall:
		//�n�ʂɂ�����ʏ�ɖ߂�
		if (this->FootCheck())
		{
			this->motion = Motion::Normal;
		}
		break;
	case Motion::Ladder:
		//��q����
		//�A�j���[�V�������ȊO
		if (this->state != State::ANIMATION)
		{
			if (!this->MotionLadderUpDate())
			{
				return false;
			}
		}
		break;
	case Walk:
		if (!this->MotionWalkUpDate())
		{
			return false;
		}
		break;
	case Switch_M:
		++this->animation.animCnt;
		//�X�C�b�`�̃A�j���[�V�������I�������(�t���C��5���R�}��5) - 1
		if (this->animation.animCnt > 24) {
			//�X�C�b�`�̃��[�V�������I���Ɠ�����悤�ɂ���
			animation.animMo = Motion::Normal;
			this->motion = Motion::Normal;
			this->state = State::NORMAL;
			this->animation.animCnt = 0;
		}
		break;
	case Block_M:
		if (this->InputB1down())
		{
			if (this->FootCheck())
			{
				//�������Ă��Ȃ����̂݃W�����v���L��
				this->motion = Motion::Jump;
				this->moveCnt = 0;
			}
		}
		if (!this->TohaveObjectHit()) {
			this->motion = Motion::Normal;
		}
		break;
	case Lift:
		++this->animation.animCnt;
		//8�t���[�����Q�R�}-�P
		if (this->animation.animCnt > 15) {
			this->motion = Motion::Normal;
			this->animation.animCnt = 0;
		}
		break;
	case Lower:
		++this->animation.animCnt;
		//8�t���[�����Q�R�}-�P
		if (this->animation.animCnt > 15) {
			this->ReleaseHold();
			this->motion = Motion::Normal;
			this->state = State::NORMAL;
			this->animation.animCnt = 0;
		}
		break;
	case Spill:
		++this->animation.animCnt;
		//8�t���[�����R�R�}-�P
		if (this->animation.animCnt > 23) {
			this->motion = Motion::Normal;
			this->animation.animCnt = 0;
		}
		break;
	case NoLower:
		if (!this->MotionNoLowerUpDate())
		{
			return false;
		}
		break;
	}
	return true;
}
bool Player::MotionNormalUpDate()
{
	if (this->InputB1down())
	{
		if (this->FootCheck())
		{
			//�������Ă��Ȃ����̂݃W�����v���L��
			this->motion = Motion::Jump;
			this->moveCnt = 0;
		}
	}
	if (this->InputB2down())
	{
		//�o�P�c������
		if (this->HaveObjectHit())
		{
			this->state = State::BUCKET;
			this->motion = Motion::Lift;
		}
		else
		{
			if (this->state == State::NORMAL) {
				//�X�C�b�`�𑀍삷��
				this->SwitchCheck();
			}
		}
	}
	//if (this->state != State::BUCKET) 
	{
		if (this->InputDown())
		{
			if (this->FootMapCheck((std::string)"Ladder", true) && !this->SolidFootCheck())
			{
				//�ړ����I��������q���[�V����������悤�ɐݒ�
				this->animation.animMo = Motion::Ladder;
				//�A�j���[�V������ԂɈڍs
				this->state = State::ANIMATION;
				//�J�E���g���Z�b�g
				this->moveCnt = 0;
				//�ړ��l�����ׂă��Z�b�g
				this->est = { 0.f,0.f };
				//�o�P�c�����낷
				if (this->hold)
				{
					this->ReleaseHold();
				}
				return false;
			}
		}
		if (this->InputUp())
		{
			if (this->MapHitCheck((std::string)"Ladder") && !this->SolidHitCheck())
			{
				this->animation.animMo = Motion::Ladder;
				this->state = State::ANIMATION;
				this->moveCnt = 0;
				this->est = { 0.f,0.f };
				if (this->hold)
				{
					this->ReleaseHold();
				}
				return false;
			}
		}
	}
	if (this->InputLeft() || this->InputRight() || this->AxisLX() != 0)
	{
		//NORMAL�̎��A���E�{�^����������WALK�ɕς��
		this->motion = Motion::Walk;
	}
	if (!this->FootCheck())
	{
		//�n�ʂ��Ȃ��ꍇ�ɗ��������Ɉڍs
		this->motion = Motion::Fall;
	}
	if (this->HeadSolidCheck())
	{
		this->state = State::BUCKET;
	}
	return true;
}
bool Player::MotionJumpUpDate()
{
	//��яo�����Ƃ��ɏ����l������
	if (this->moveCnt == 0)
	{
		this->est.y = Player::JUMP_POWER;
		this->moveCnt++;
	}
	//�������n�߂���Fall�Ɉړ�
	if (this->est.y >= 0.f)
	{
		this->motion = Fall;
	}
	//��������������㏸����߂ė����Ɉړ�
	if (this->HeadCheck())
	{
		this->est.y = 0.f;
		this->motion = Fall;
	}
	if (this->HeadSolidCheck())
	{
		this->state = State::BUCKET;
	}
	return true;
}
bool Player::MotionLadderUpDate()
{
	if (this->InputUp())
	{
		++this->animation.animCnt;
		Vec2 e = { 0.f,-5.0f };
		this->LadderMoveCheck(e);
		if (this->HeadMapCheck((std::string)"Ladder", false))
		{
			//�ړ����I��������q���[�V����������悤�ɐݒ�
			this->animation.animMo = Motion::Ladder;
			//�A�j���[�V������ԂɈڍs
			this->state = State::ANIMATION;
			//�J�E���g���Z�b�g
			this->moveCnt = 0;
			//�ړ��l�����ׂă��Z�b�g
			this->est = { 0.f,0.f };
		}
	}
	if (this->InputDown() || this->isInputAuto)
	{
		++this->animation.animCnt;
		Vec2 e = { 0.f,5.0f };
		if (this->isInputAuto)
		{
			e.y += 10.f;
		}
		this->LadderMoveCheck(e);
		if (this->FootMapCheck((std::string)"Ladder", false) || this->SolidFootCheck())
		{
			this->animation.animCnt = 0;
			this->motion = Motion::Normal;
		}
		else
		{
			//�d�͏������s��Ȃ��̂ł����ŏI��
			return false;
		}
	}
	if (this->InputLeft() || this->InputRight() || this->AxisLX() > 0.8f || this->AxisLX() < -0.8f)
	{
		if (this->LadderJumpCheck())
		{
			this->motion = Fall;
			this->animation.animCnt = 0;
			this->moveCnt = 0;
		}
	}
	return true;
}
bool Player::MotionWalkUpDate()
{
	if (!this->FootCheck())
	{
		this->motion = Motion::Fall;
		return true;
	}
	if (!this->InputRight() && !this->InputLeft() && this->AxisLX() == 0)
	{
		//���E�{�^���������Ȃ���normal�ɖ߂�
		this->motion = Motion::Normal;
	}
	if (this->InputB1down())
	{
		//�����Ă�Ƃ��̃W�����v
		this->motion = Motion::Jump;
		this->moveCnt = 0;
	}
	if (this->InputB2down())
	{
		//�o�P�c������
		if (this->HaveObjectHit())
		{
			this->state = State::BUCKET;
			this->motion = Motion::Lift;
		}
		else
		{
			//�X�C�b�`������
			if (this->state == State::NORMAL) {
				this->SwitchCheck();
			}
		}
	}
	//if (this->TohaveObjectHit() && this->state == State::NORMAL) {
	//	//�u���b�N������
	//	this->motion = Motion::Block_M;
	//}
	if (this->HeadSolidCheck())
	{
		this->state = State::BUCKET;
	}
	return true;
}
bool Player::MotionNoLowerUpDate()
{
	this->animation.animCnt++;
	if (this->animation.animCnt >= 20)
	{
		this->motion = Motion::Normal;
		this->animation.animCnt = 0;
	}
	return true;
}
void Player::StateClearUpdate()
{
	if (this->motion == Motion::Normal) {
		this->moveCnt = 0;
		this->motion = Motion::Jump;
	}
}
bool Player::InputLeft() {
	if (this->isInputAuto || this->isInput)
	{
		return false;
	}
	return OGge->in->on(Input::CL);
}
bool Player::InputRight() {
	if (this->isInputAuto || this->isInput)
	{
		return false;
	}
	return OGge->in->on(Input::CR);
}
bool Player::InputDown() {
	if (this->isInputAuto || this->isInput)
	{
		return false;
	}
	return OGge->in->on(Input::CD) || OGge->in->on(In::LD);
}
bool Player::InputUp() {
	if (this->isInputAuto || this->isInput)
	{
		return false;
	}
	return OGge->in->on(Input::CU) || OGge->in->on(In::LU);
}
float Player::AxisLX()
{
	if (this->isInputAuto || this->isInput)
	{
		return 0.0f;
	}
	if (OGge->in->axis(In::AXIS_LEFT_X) > 0.3f || OGge->in->axis(In::AXIS_LEFT_X) < -0.3f)
	{
		return OGge->in->axis(In::AXIS_LEFT_X);
	}
	return 0.0f;
}
float Player::AxisLY()
{
	if (this->isInputAuto || this->isInput)
	{
		return 0.0f;
	}
	return OGge->in->axis(In::AXIS_LEFT_Y);
}
float Player::AxisRX()
{
	if (this->isInputAuto || this->isInput)
	{
		return 0.0f;
	}
	return OGge->in->axis(In::AXIS_RIGHT_X);
}
float Player::AxisRY()
{
	if (this->isInputAuto || this->isInput)
	{
		return 0.0f;
	}
	return OGge->in->axis(In::AXIS_RIGHT_Y);
}
bool Player::InputB1down()
{
	if (this->isInputAuto || this->isInput)
	{
		return false;
	}
	return OGge->in->down(In::B1);
}
bool Player::InputB2down()
{
	if (this->isInputAuto || this->isInput)
	{
		return false;
	}
	return OGge->in->down(In::B2);
}
bool Player::InputB1on()
{
	if (this->isInputAuto || this->isInput)
	{
		return false;
	}
	return OGge->in->on(In::B1);
}
bool Player::InputB2on()
{
	if (this->isInputAuto || this->isInput)
	{
		return false;
	}
	return OGge->in->on(In::B2);
}
Player::SP Player::Create(Vec2& pos, bool flag)
{
	auto to = Player::SP(new Player());
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

void Player::SetInput(bool b)
{
	this->isInput = b;
}
bool Player::GetInput() const
{
	return this->isInput;
}