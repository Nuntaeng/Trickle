#include "Player.h"
#include "Bucket\bucket.h"
#include "Water\water.h"
#include "Map\Map.h"
#include "Block\block.h"
#include "Gimmick\NO_MOVE\Switch.h"

Player::Player()
{
	this->hold = false;
}
Player::~Player()
{
	this->Finalize();
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{

	}
}
bool Player::Initialize()
{
	//�I�u�W�F�N�g�̏�����
	this->CreateObject(Cube, Vec2(200.f, 200.0f), Vec2(64.0f, 64.f), 0.0f);
	this->objectTag = "Player";
	//�f�o�b�O�p�ʒu����
	//this->position = { 841,700 };
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
	__super::Init((std::string)"Player");
	return true;
}
bool Player::Initialize(Vec2& pos)
{
	this->taskName = "Player";
	__super::Init(this->taskName);
	//�I�u�W�F�N�g�̏�����
	this->CreateObject(Cube, pos, Vec2(64.0f, 64.f), 0.0f);
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
	//�A�j���[�V�����J�E���g�𑝂₷

	switch (this->state)
	{
	case State::ANIMATION:
		if (this->animation.isMove())
		{
			//�ړ�����
			this->position += this->animation.Move();
		}
		else
		{
			//�ʏ�ɖ߂�
			this->state = State::NORMAL;
		}
		break;
	case State::BUCKET:
		//�o�P�c�̒l�������ɍ��킹��
		this->BucketMove();
		if (OGge->in->down(In::B2))
		{
			this->ReleaseHold();
		}
		break;
	case State::NORMAL:
		
		break;
	}
	if (this->inv > 0)
	{
		this->inv--;
	}
	//�e��Ԃł̏����ƕʏ�Ԃւ̈ڍs
	if (this->state != State::ANIMATION)
	{
		switch (this->motion)
		{
		case Motion::Normal:
			if (!this->FootCheck())
			{
				//�n�ʂ��Ȃ��ꍇ�ɗ��������Ɉڍs
				this->motion = Motion::Fall;
				break;
			}
			if (OGge->in->on(In::B1))
			{
				if (this->FootCheck())
				{
					//�������Ă��Ȃ����̂݃W�����v���L��
					this->motion = Motion::Jump;
					this->moveCnt = 0;
				}
			}
			if (OGge->in->down(In::B2))
			{
				//�o�P�c������
				if (this->BucketHit())
				{
					this->state = State::BUCKET;
				}
			}
			if (this->state != State::BUCKET) {
				if (this->InputDown())
				{
					if (this->FootCheck((std::string)"Ladder"))
					{
						//�A�j���[�V������ԂɈڍs
						this->state = State::ANIMATION;
						//�J�E���g���Z�b�g
						this->moveCnt = 0;
						//�ړ��l�����ׂă��Z�b�g
						this->est = { 0.f,0.f };
						return;
					}
				}
				if (this->InputUp())
				{
					if (this->ObjectHit((std::string)"Ladder"))
					{
						this->state = State::ANIMATION;
						this->moveCnt = 0;
						this->est = { 0.f,0.f };
						return;
					}
				}
			}
			if (this->InputLeft() || this->InputRight())
			{
				//NORMAL�̎��A���E�{�^����������WALK�ɕς��
				this->motion = Motion::Walk;
			}
			this->TohaveObjectHit();
			if (OGge->in->down(In::B2))
			{
				animation.timeCnt = 0;
				this->SwitchCheck();
			}
			if (this->HeadSolidCheck())
			{
				this->state = State::BUCKET;
			}
			break;
		case Motion::Jump:
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
			break;
		case Motion::Fall:
			//�n�ʂɂ�����ʏ�ɖ߂�
			if (this->FootCheck())
			{
				this->motion = Motion::Normal;
			}
			break;
		case Motion::Ladder:	//��q����
								//�A�j���[�V�������ȊO
			if (this->state != State::ANIMATION)
			{
				if (OGge->in->on(In::B1))
				{
					if (this->LadderJumpCheck())
					{
						this->motion = Motion::Jump;
						this->moveCnt = 0;
					}
				}
				if (this->InputUp())
				{
					++this->animation.ladderCnt;
					Vec2 e = { 0.f,-5.0f };
					this->MoveCheck(e, (std::string)"Floor");
					if (this->HeadCheck((std::string)"Ladder", 1))
					{
						//�A�j���[�V������ԂɈڍs
						this->state = State::ANIMATION;
						//�J�E���g���Z�b�g
						this->moveCnt = 0;
						//�ړ��l�����ׂă��Z�b�g
						this->est = { 0.f,0.f };
					}
				}
				if (this->InputDown())
				{
					++this->animation.ladderCnt;
					Vec2 e = { 0.f,5.0f };
					this->MoveCheck(e, (std::string)"Floor");
					if (this->FootCheck((std::string)"Ladder", 1))
					{
						this->motion = Motion::Normal;
					}
					else
					{
						//�d�͏������s��Ȃ��̂ł����ŏI��
						return;
					}

				}
			}
			break;
		case Walk:
			if (!this->InputRight() && !this->InputLeft())
			{
				this->motion = Motion::Normal;
			}
			if (OGge->in->on(In::B1))
			{
				//�����Ă�Ƃ��̃W�����v
				this->motion = Motion::Jump;
				this->moveCnt = 0;
			}
			if (OGge->in->down(In::B2))
			{
				//�o�P�c������
				if (this->BucketHit())
				{
					this->state = State::BUCKET;
				}
				else
				{
					//�����o�P�c���Ƃ�Ȃ��Ȃ�΃X�C�b�`�̔�����s��
					this->SwitchCheck();
				}
			}
			this->TohaveObjectHit();
			if (this->HeadSolidCheck())
			{
				this->state = State::BUCKET;
			}
			break;
		case Switch_M:
			if (animation.timeCnt > 29) {
				this->motion = Motion::Normal;
			}
		}
		this->Friction();
		if (this->motion != Motion::Ladder)
		{
			if (this->InputLeft())
			{
				this->est.x = -this->MOVE_SPEED;
				this->direction = Direction::LEFT;
			}
			if (this->InputRight())
			{
				this->est.x = +this->MOVE_SPEED;
				this->direction = Direction::RIGHT;
			}
		}
	}
	//�d�͂Ƃ��Ƃ��̈ړ������̌v�Z
	/*if (this->state != State::ANIMATION)
	{
	
	}*/
	//�͂������ȊO�͍��E�ړ����ł���
	
	//�ŏI�I�Ȉړ��l�𔽉f������
	this->MoveCheck(this->est);
}
void Player::Render2D()
{
	Box2D draw;
	if (this->hold)
	{
		draw = { this->position.x,this->position.y + 64.f,this->Scale.x, this->Scale.y  - 64.f};
		draw.OffsetSize();
	}
	else
	{
		draw = { this->position.x, this->position.y, this->Scale.x, this->Scale.y };
		draw.OffsetSize();
	}

	Box2D src = this->animation.returnSrc(this->motion, this->state);
	//��-�V��������src��return����
	src.OffsetSize();

	//�������Ȃ�摜���t�ɂ���
	if (direction == Direction::RIGHT) {
		int k = src.w;
		src.w = src.x;
		src.x = k;
	}
	this->playerimg->Draw(draw, src);
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
	GameObject head;
	head.CreateObject(Objform::Cube, Vec2(this->position.x,this->position.y - 1.0f), Vec2(this->Scale.x, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (map->hitBase[y][x].objectTag == "Floor" ||
				map->hitBase[y][x].objectTag == "Net" ||
				map->hitBase[y][x].objectTag == "Soil")
			{
				if (head.hit(map->hitBase[y][x]))
				{
					return true;
				}
			}
		}
	}
	auto block = OGge->GetTask<Block>("block");
	if (block)
	{
		if (head.hit(*block))
		{
			return true;
		}
	}
	return false;
}
bool Player::HeadCheck(std::string& objname_, int n)
{
	GameObject head;
	head.CreateObject(Objform::Cube, Vec2(this->position.x + 1.f, this->position.y - 1.0f), Vec2(this->Scale.x - 1.f, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (n == 0) {
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->hitBase[y][x].objectTag == objname_)
				{
					if (head.hit(map->hitBase[y][x]))
					{
						this->animation.SetAnimaVec(this->position, map->hitBase[y][x].position);
						return true;
					}
				}
			}
		}
	}
	else
	{
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->hitBase[y][x].objectTag != objname_)
				{
					if (head.hit(map->hitBase[y][x]))
					{
						this->animation.SetAnimaVec(this->position, Vec2(map->hitBase[y][x].position.x, map->hitBase[y][x].position.y - 1.0f));
						return true;
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
	GameObject head;
	head.CreateObject(Objform::Cube, Vec2(this->position.x + 1.f, this->position.y - 1.0f), Vec2(this->Scale.x - 1.f, 1.0f), 0.0f);
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if ((*id)->objectTag == "SOLID")
		{
			if (head.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (head.hit(*(*id)))
				{
					(*id)->HoldCheck(true);
					this->hold = true;
					this->position.y -= 64.f;
					this->Scale.y += 64.f;
					return true;
					return true;
				}
			}
		}
	}
	return false;
}
bool Player::FootCheck()
{
	GameObject foot;
	foot.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y + this->Scale.y), Vec2(this->Scale.x, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (map->hitBase[y][x].objectTag == "Floor" ||
				map->hitBase[y][x].objectTag == "Net" ||
				map->hitBase[y][x].objectTag == "Soil" || 
				map->_arr[y][x] == 24)
			{
				if (foot.hit(map->hitBase[y][x]))
				{
					return true;
				}
			}
		}
	}
	auto block = OGge->GetTask<Block>("block");
	if (block) 
	{
		if (foot.hit(*block))
		{
			return true;
		}
	}
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		if (foot.hit(*(*id)))
		{
			if ((*id)->objectTag == "SOLID")
			{
				return true;
			}
		}
	}
	return false;
}
bool Player::FootCheck(std::string& objname_,int n)
{
	GameObject foot;
	foot.CreateObject(Objform::Cube, Vec2(this->position.x + 1.f, this->position.y + this->Scale.y + 1.1f), Vec2(this->Scale.x - 1.f, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (n == 0) {
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->hitBase[y][x].objectTag == objname_)
				{
					if (foot.hit(map->hitBase[y][x]))
					{
						this->animation.SetAnimaVec(this->position, Vec2(map->hitBase[y][x].position.x, map->hitBase[y][x].position.y + 10.f));
						return true;
					}
				}
			}
		}
	}
	else
	{
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->hitBase[y][x].objectTag != objname_)
				{
					if (foot.hit(map->hitBase[y][x]))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
void Player::MoveCheck(Vec2 est)
{
	auto map = OGge->GetTask<Map>("map");
	auto blocks = OGge->GetTasks<Block>("block");
	auto waters = OGge->GetTasks<Water>("water");
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
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (this->hit(map->hitBase[y][x]))
				{
					if (map->hitBase[y][x].objectTag == "Floor" ||
						map->hitBase[y][x].objectTag == "Net" || 
						map->_arr[y][x] == 24)
					{
						this->position.x = preX;
						break;
					}
				}
			}
		}
		for (auto id = blocks->begin(); id != blocks->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->hit(*(*id)))
				{
					this->position.x = preX;
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
						if (this->hit(*(*id)))
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
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (this->hit(map->hitBase[y][x]))
				{
					if (map->hitBase[y][x].objectTag == "Floor" ||
						map->hitBase[y][x].objectTag == "Net" ||
						map->_arr[y][x] == 24)
					{
						this->position.y = preY;
						break;
					}
				}
			}
		}
		for (auto id = blocks->begin(); id != blocks->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->hit(*(*id)))
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
						if (this->hit(*(*id)))
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
bool Player::BucketHit()
{
	if (this->inv != 0)
	{
		return false;
	}
	//���łɎ����Ă���Ȃ�Γ����Ȃ�
	if (this->hold)
	{
		return false;
	}
	auto bucket = OGge->GetTasks<Bucket>("bucket");
	for (auto id = (*bucket).begin(); id != (*bucket).end(); ++id)
	{
		if (this->hit(*(*id)))
		{
			(*id)->HoldCheck(true);
			this->hold = true;
			this->position.y -= 64.f;
			this->Scale.y += 64.f;
			return true;
		}
	}
	GameObject left;
	left.CreateObject(Objform::Cube, Vec2(this->position.x - 3.0f, this->position.y), Vec2(3.0f, this->Scale.y), 0.0f);
	GameObject right;
	right.CreateObject(Objform::Cube, Vec2(this->position.x + this->Scale.x, this->position.y), Vec2(3.0f, this->Scale.y), 0.0f);
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if (!(*id)->GetHold())
		{
			if ((*id)->GetState() == Water::State::SOLID)
			{
				if (left.hit(*(*id)) || right.hit(*(*id)))
				{
					(*id)->HoldCheck(true);
					this->hold = true;
					this->position.y -= 64.f;
					this->Scale.y += 64.f;
					return true;
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
		if ((*id)->hit(*this))
		{
			this->motion = Motion::Switch_M;
			(*id)->ChangeON_OFF(); 
			//(*id)->isON();	//����Ӗ�����H�߂�lbool 5.31
		}
	}
}
void Player::BucketMove()
{
	auto buckets = OGge->GetTasks<Bucket>("bucket");
	for (auto id = (*buckets).begin(); id != (*buckets).end(); ++id)
	{
		if ((*id)->GetHold())
		{
			(*id)->position = { this->position.x,this->position.y - (*id)->Scale.y  + 64.f};
		}
	}
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if ((*id)->GetHold())
		{
			(*id)->position = { this->position.x,this->position.y - (*id)->Scale.y  + 64.f};
		}
	}
}
void Player::Animation::SetAnimaVec(Vec2& start_, Vec2& end_)
{
	this->startVec = start_;
	this->endVec = end_;
	this->animationVec = { this->endVec.x - this->startVec.x ,this->endVec.y - this->startVec.y };
}
bool Player::Animation::Initialize()
{
	this->animationVec = { 0.f,0.f };
	this->startVec = { 0.f,0.f };
	this->endVec = { 0.f,0.f };
	this->timeCnt = 0;
	this->ladderCnt = 0;
	return true;
}
Vec2 Player::Animation::Move()
{
	auto player = OGge->GetTask<Player>("Player");
	Vec2 move = { 0.f,0.f };
	if (this->animationVec.x != 0.f)
	{
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
	if (this->animationVec.x == 0.f)
	{
		if (this->animationVec.y > 0.f)
		{
			move.y += this->animationVec.y;
			player->motion = Motion::Ladder;
			this->animationVec.y = 0.f;
		}
		else if (this->animationVec.y < 0.f)
		{
			move.y += this->animationVec.y;
			player->motion = Motion::Normal;
			this->animationVec.y = 0.f;
		}
		else
		{
			player->motion = Motion::Ladder;
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
Box2D Player::Animation::returnSrc(Motion motion, State state) 
{
	Box2D src(0,0, this->srcX, this->srcY);	//��{��src�i��ŏ��������j
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
			src = Box2D(1 * this->srcX, 2 *  this->srcY, this->srcX,  this->srcY);
			break;
		
		case Motion::Ladder:
			src = Box2D(this->ladder[this->ladderCnt / 8 % 2] * this->srcX, 3 *  this->srcY, this->srcX,  this->srcY);
			break;
		case Motion::Block_M:
			src = Box2D(this->walk[this->timeCnt / 3 % 9] * this->srcX, 9 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Switch_M:
			auto switchs = OGge->GetTasks<Switch>("Switch");
			for (auto id = switchs->begin(); id != switchs->end(); ++id)
			{
				if ((*id)->isON()) {
					src = Box2D(this->switch_2[this->timeCnt / 5 % 6] * this->srcX, 8 * this->srcY, this->srcX, this->srcY);
				}
				else {
					src = Box2D(this->switch_1[this->timeCnt / 5 % 6] * this->srcX, 8 * this->srcY, this->srcX, this->srcY);
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
			src = Box2D(this->idle[this->timeCnt / 3 % 10] * this->srcX, 4* this->srcY, this->srcX,  this->srcY);
			break;

		case Motion::Walk:
			src = Box2D(this->walk[this->timeCnt / 3 % 9] * this->srcX, 5 *  this->srcY, this->srcX,  this->srcY);
			break;

		case Motion::Jump:
			src = Box2D(0 * this->srcX, 7 *  this->srcY, this->srcX,  this->srcY);
			break;

		case Motion::Fall:
			src = Box2D(1 * this->srcX, 7 *  this->srcY, this->srcX,  this->srcY);
			break;
		}
	}
	return src;

}
void Player::MoveCheck(Vec2& est, std::string& objname_)
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
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (this->hit(map->hitBase[y][x]))
				{
					if (map->hitBase[y][x].objectTag == "Floor" ||
						map->hitBase[y][x].objectTag == "LadderTop")
					{
						this->position.y = preY;
						break;
					}
				}
			}
		}
	}
}
bool Player::ObjectHit(std::string& objname_)
{
	auto map = OGge->GetTask<Map>("map");
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (this->hit(map->hitBase[y][x]))
			{
				if (map->hitBase[y][x].objectTag == objname_)
				{
					this->animation.SetAnimaVec(this->position, Vec2(map->hitBase[y][x].position.x, this->position.y));
					return true;
				}
			}
		}
	}
	return false;
}
bool Player::TohaveObjectHit()
{
	GameObject left;
	left.CreateObject(Objform::Cube, Vec2(this->position.x - 1.0f, this->position.y), Vec2(1.0f,this->Scale.y), 0.0f);
	GameObject right;
	right.CreateObject(Objform::Cube, Vec2(this->position.x + this->Scale.x, this->position.y), Vec2(1.0f, this->Scale.y), 0.0f);
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = (*blocks).begin(); id != (*blocks).end(); ++id)
	{
		if (left.hit(*(*id)))
		{
			(*id)->PlCheckHit(left);
			if (this->est.x < 0)
			{
				(*id)->GetMove(this->est);
			}
		}
		if (right.hit(*(*id)))
		{
			(*id)->PlCheckHit(right);
			if (this->est.x > 0)
			{
				(*id)->GetMove(this->est);
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
				if (left.hit(*(*id)))
				{
					(*id)->MoveSolid(this->est);
				}
			}
			if (this->est.x > 0)
			{
				if (right.hit(*(*id)))
				{
					(*id)->MoveSolid(this->est);
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
		return Vec2(this->position.x, this->position.y + 64);
	}
	return this->position;
}
bool Player::ReleaseHold()
{
	if (this->hold)
	{
		if (this->PutCheck())
		{
			//���ɖ߂�
			this->state = State::NORMAL;
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
						(*id)->position.x -= this->Scale.x;
					}
					else
					{
						(*id)->position.x += this->Scale.x;
					}
				}
			}
			auto waters = OGge->GetTasks<Water>("water");
			for (auto id = waters->begin(); id != waters->end(); ++id)
			{
				if ((*id)->GetHold())
				{
					if (OGge->in->down(In::B2))
					{
						if (this->direction == Direction::LEFT)
						{
							(*id)->position.x -= this->Scale.x;
						}
						else
						{
							(*id)->position.x += this->Scale.x;
						}
					}
					(*id)->HoldCheck(false);
					(*id)->ResetMove();
					this->hold = false;
				}
			}
			this->inv = 10;
			this->position.y += 64.f;
			this->Scale.y -= 64.f;
			return true;
		}
	}
	return false;
}
bool Player::LadderJumpCheck()
{
	auto map = OGge->GetTask<Map>("map");
	if (map)
	{
		for (int y = 0; y < map->mapSize.y;++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->_arr[y][x] == 24)
				{
					if (this->hit(map->hitBase[y][x]))
					{
						return false;
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
			GameObject left;
			left.CreateObject(Cube, Vec2(this->position.x - this->Scale.x, this->position.y), this->Scale, 0.0f);
			if (map->MapHitCheck(left))
			{
				return false;
			}
		}
		else
		{
			GameObject right;
			right.CreateObject(Cube, Vec2(this->position.x + this->Scale.x, this->position.y), this->Scale, 0.0f);
			if (map->MapHitCheck(right))
			{
				return false;
			}
		}
	}
	return true;
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