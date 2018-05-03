#include "Player.h"

Player::Player()
{
	
}

Player::~Player()
{

}

void Player::Initialize()
{
	//�I�u�W�F�N�g�̏�����
	Object::CreateObject(Cube, Vec2(200.f, 200.0f), Vec2(64.0f, 64.f), 0.0f);
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
}

void Player::Update()
{
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
		if (gameEngine->in.down(In::B2))
		{
			//���ɖ߂�
			this->state = State::NORMAL;
			//�����Ă��锻������ɖ߂�
			this->haveBucket->hold = false;
			this->inv = 10;
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
	switch (this->motion)
	{
	case Motion::Normal:
		if (!this->FootCheck())
		{
			//�n�ʂ��Ȃ��ꍇ�ɗ��������Ɉڍs
			this->motion = Motion::Fall;
			break;
		}
		if (gameEngine->in.on(In::B1))
		{
			//�������Ă��Ȃ����̂݃W�����v���L��
			this->motion = Motion::Jump;
			this->moveCnt = 0;
		}
		if (gameEngine->in.down(In::B2))
		{
			//�o�P�c������
			if (this->BucketHit() && this->inv == 0) 
			{
				this->state = State::BUCKET;
			}
		}
		if (this->state != State::BUCKET) {
			if (this->InputDown())
			{
				if (this->FootCheck("Ladder"))
				{
					//��q��ԂɈڍs
					this->motion = Motion::Ladder;
					//�A�j���[�V������ԂɈڍs
					this->state = State::ANIMATION;
					//�J�E���g���Z�b�g
					this->moveCnt = 0;
					//�ړ��l�����ׂă��Z�b�g
					this->est = { 0.f,0.f };
				}
			}
			if (this->InputUp())
			{
				if (this->ObjectHit("Ladder"))
				{
					this->motion = Motion::Ladder;
					this->state = State::ANIMATION;
					this->moveCnt = 0;
					this->est = { 0.f,0.f };
				}
			}
		}
		this->BlockHit();
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
			if (gameEngine->in.on(In::B1))
			{
				this->motion = Motion::Jump;
				this->moveCnt = 0;
			}
			if (this->InputUp())
			{
				Vec2 e = { 0.f,-5.0f };
				this->MoveCheck(e, "Floor");
				if (this->HeadCheck("Ladder", 1))
				{
					this->motion = Motion::Normal;
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
				Vec2 e = { 0.f,5.0f };
				this->MoveCheck(e, "Floor");
				if (this->FootCheck("Ladder", 1))
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
	}
	//�d�͂Ƃ��Ƃ��̈ړ������̌v�Z
	if (this->state != State::ANIMATION)
	{
		this->Friction();
	}
	//�͂������ȊO�͍��E�ړ����ł���
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
	//�ŏI�I�Ȉړ��l�𔽉f������
	this->MoveCheck(this->est);
}

void Player::Render()
{
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	//�������Ȃ�摜���t�ɂ���
	if (direction == Direction::LEFT) {
		int k = src.w;
		src.w = src.x;
		src.x = k;
	}
	this->playerimg->Draw(draw, src);
	this->LineDraw();
}

void Player::Finalize()
{
	//�e�N�X�`���̉��

	//�ێ��I�u�W�F�N�g�̏��̉��
	this->AllDelete();
}

Vec2 Player::GetEst() const {
	return est;
}

void Player::AddObject(Object* obj_)
{
	this->objects.push_back(obj_);
}

void Player::DeleteObject(Object* obj_)
{
	for (auto id = this->objects.begin(); id != this->objects.end(); ++id)
	{
		if ((*id) == obj_)
		{
			this->objects.erase(id);
		}
	}
}

void Player::AllDelete()
{
	this->objects.clear();
	this->buckets.clear();
	this->blocks.clear();
}

bool Player::HeadCheck()
{
	Object head;
	head.CreateObject(Objform::Cube, Vec2(this->position.x,this->position.y - 1.0f), Vec2(this->Scale.x, 1.0f), 0.0f);
	for (int i = 0; i < this->objects.size(); ++i)
	{
		if (this->objects[i]->objectTag == "Floor" || this->objects[i]->objectTag == "Net" || this->objects[i]->objectTag == "Soil")
		{
			if (head.hit(*this->objects[i]))
			{
				return true;
			}
		}
	}
	for (int i = 0; i < this->blocks.size(); ++i)
	{
		if (head.hit(*this->blocks[i]))
		{
			return true;
		}
	}
	return false;
}

bool Player::HeadCheck(std::string objname_, int n)
{
	Object head;
	head.CreateObject(Objform::Cube, Vec2(this->position.x + 1.f, this->position.y - 1.0f), Vec2(this->Scale.x - 1.f, 1.0f), 0.0f);
	if (n == 0) {
		for (int j = 0; j < this->objects.size(); ++j)
		{
			if (this->objects[j]->objectTag == objname_)
			{
				if (head.hit(*this->objects[j]))
				{
					this->animation.SetAnimaVec(this->position, this->objects[j]->position);
					return true;
				}
			}
		}
	}
	else
	{
		for (int j = 0; j < this->objects.size(); ++j)
		{
			if (this->objects[j]->objectTag != objname_)
			{
				if (head.hit(*this->objects[j]))
				{
					this->animation.SetAnimaVec(this->position, Vec2(this->objects[j]->position.x, this->objects[j]->position.y - 1.0f));
					return true;
				}
			}
		}
	}
	return false;
}

bool Player::FootCheck()
{
	Object foot;
	foot.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y + this->Scale.y), Vec2(this->Scale.x, 1.0f), 0.0f);
	for (int j = 0; j < this->objects.size(); ++j)
	{
		if (this->objects[j]->objectTag == "Floor" || this->objects[j]->objectTag == "Net" || this->objects[j]->objectTag == "Soil")
		{
			if (foot.hit(*this->objects[j]))
			{
				return true;
			}
		}
	}
	for (int i = 0; i < this->blocks.size(); ++i)
	{
		if (foot.hit(*this->blocks[i]))
		{
			return true;
		}
	}
	return false;
}

bool Player::FootCheck(std::string objname_,int n)
{
	Object foot;
	foot.CreateObject(Objform::Cube, Vec2(this->position.x + 1.f, this->position.y + this->Scale.y + 1.1f), Vec2(this->Scale.x - 1.f, 1.0f), 0.0f);
	if (n == 0) {
		for (int j = 0; j < this->objects.size(); ++j)
		{
			if (this->objects[j]->objectTag == objname_)
			{
				if (foot.hit(*this->objects[j]))
				{
					this->animation.SetAnimaVec(this->position, Vec2(this->objects[j]->position.x, this->objects[j]->position.y + 10.f));
					return true;
				}
			}
		}
	}
	else
	{
		for (int j = 0; j < this->objects.size(); ++j)
		{
			if (this->objects[j]->objectTag != objname_)
			{
				if (foot.hit(*this->objects[j]))
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Player::MoveCheck(Vec2 est)
{
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
		for (int i = 0; i < this->objects.size(); ++i)
		{
			if (this->hit(*this->objects[i]))
			{
				if (this->objects[i]->objectTag == "Floor"/* || this->objects[i]->objectTag == "Ladder"*/ || this->objects[i]->objectTag == "Net") {
					this->position.x = preX;
					break;
				}
			}
		}
		for (int i = 0; i < this->blocks.size(); ++i)
		{
			if (this->hit(*this->blocks[i]))
			{
				this->position.x = preX;
				break;
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
		for (int i = 0; i < this->objects.size(); ++i)
		{
			if (this->hit(*this->objects[i]))
			{
				if (this->objects[i]->objectTag == "Floor"/* || this->objects[i]->objectTag == "Ladder"*/ || this->objects[i]->objectTag == "Net") {
					this->position.y = preY;
					break;
				}
			}
		}
		for (int i = 0; i < this->blocks.size(); ++i)
		{
			if (this->hit(*this->blocks[i]))
			{
				this->position.y = preY;
				break;
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
	for (int i = 0; i < this->buckets.size(); ++i)
	{
		if (this->hit(*this->buckets[i]))
		{
			this->buckets[i]->hold = true;
			this->haveBucket = this->buckets[i];
			return true;
		}
	}
	return false;
}

void Player::BucketMove()
{
	this->haveBucket->position = { this->position.x,this->position.y - this->haveBucket->Scale.y };
}

void Player::AddBucket(Bucket* bucket)
{
	this->buckets.push_back(bucket);
}

bool Player::DeleteBucket(Bucket* bucket)
{
	for (auto id = this->buckets.begin(); id != this->buckets.end(); ++id)
	{
		if ((*id) == bucket)
		{
			this->buckets.erase(id);
			return true;
		}
	}
	return false;
}

void Player::Animation::SetAnimaVec(Vec2 start_, Vec2 end_)
{
	this->startVec = start_;
	this->endVec = end_;
	this->animationVec = { this->endVec.x - this->startVec.x ,this->endVec.y - this->startVec.y };
}

void Player::Animation::Initialize()
{
	this->animationVec = { 0.f,0.f };
	this->startVec = { 0.f,0.f };
	this->endVec = { 0.f,0.f };
}

Vec2 Player::Animation::Move()
{
	Vec2 move = { 0.f,0.f };
	if (this->animationVec.x != 0.f)
	{
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
	if (this->animationVec.y != 0.f)
	{
		if (this->animationVec.y >= 1.0f)
		{
			move.y += 1.0f;
			this->animationVec.y -= 1.0f;
		}
		else if (this->animationVec.y <= -1.0f)
		{
			move.y -= 1.0f;
			this->animationVec.y += 1.0f;
		}
		else
		{
			move.y += this->animationVec.y;
			this->animationVec.y = 0.f;
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

void Player::MoveCheck(Vec2 est, std::string objname_)
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
		for (int i = 0; i < this->objects.size(); ++i)
		{
			if (this->hit(*this->objects[i]))
			{
				if (this->objects[i]->objectTag == "Floor" || this->objects[i]->objectTag == "") {
					this->position.y = preY;
					break;
				}
			}
		}
	}
}

bool Player::ObjectHit(std::string objname_)
{
	for (int i = 0; i < this->objects.size(); ++i)
	{
		if (this->hit(*this->objects[i]))
		{
			if (this->objects[i]->objectTag == objname_) 
			{
				this->animation.SetAnimaVec(this->position, Vec2(this->objects[i]->position.x, this->position.y));
				return true;
			}
		}
	}
	return false;
}

void Player::AddBlock(Block* block)
{
	this->blocks.push_back(block);
}

bool Player::DeleteBlock(Block* block)
{
	for (auto id = this->blocks.begin(); id != this->blocks.end(); ++id)
	{
		if ((*id) == block)
		{
			this->blocks.erase(id);
			return true;
		}
	}
	return false;
}

bool Player::BlockHit()
{
	Object left;
	left.CreateObject(Objform::Cube, Vec2(this->position.x - 1.0f, this->position.y), Vec2(1.0f,this->Scale.y), 0.0f);
	Object right;
	right.CreateObject(Objform::Cube, Vec2(this->position.x + this->Scale.x, this->position.y), Vec2(1.0f, this->Scale.y), 0.0f);
	for (int i = 0; i < this->blocks.size(); ++i)
	{
		if (left.hit(*this->blocks[i]))
		{
			//std::cout << "LEFT :Hit" << std::endl;
			this->blocks[i]->PlCheckHit(left, *blocks[i]);
			this->blocks[i]->GetMove(this->est);
		}
		if (right.hit(*this->blocks[i]))
		{
			//std::cout << "RIGHT:Hit" << std::endl;
			this->blocks[i]->PlCheckHit(right, *blocks[i]);
			this->blocks[i]->GetMove(this->est);
		}
	}
	return false;
}

void Player::SetTexture(Texture* texture)
{
	this->playerimg = texture;
}