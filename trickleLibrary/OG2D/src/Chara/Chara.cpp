#include "Chara.h"
#include "Map\Map.h"

Chara::Chara(std::string& path, Vec2& pos)
	:MOVE_SPEED(5.f), JUMP_POWER(-5.0f), MAX_FALL(30.f), GRAVITY((9.8f / 60.f / 60.f * 32) * 5), FIN_SPEED(0.5f)
{							   
	this->position = pos;	//�ʒu�ݒ�
	this->Image.Create(path);	//�摜�ݒ�
	this->CreateObject(Cube, pos, Vec2(128, 128), 0.0f);	//�I�u�W�F�N�g����
	this->taskName = "Chara";	//�^�X�N������
	__super::Init(this->taskName);	//�^�X�N�����I�u�W�F�N�g�ɂ����f
	__super::SetDrawOrder(1.0f);	//�`�揇��o�^
	this->objectTag = this->taskName;	//�^�O��o�^
	this->direction = Direction::LEFT;	//������ݒ�
	this->AnimCnt = 0;					//�A�j���[�V�����J�E���g��������
	this->motion = Motion::Normal;
	this->isAuto = true;				//�I�[�g�ړ��ݒ��������
	this->isCollision = true;			//�����蔻��ݒ菉����
	this->MoveCnt = 0;					//�ړ��J�E���g������
	this->Radius = Vec2(1.0f, 0.9f);	//�����蔻��𐧌�
	this->isCollisionNow = -1;			//�����蔻��J�E���g��������
	this->isAutoOff = false;			//�I�[�g�ړ��`�F�b�N��������
	this->isAutoMode = false;			//�I�[�g���[�h��������
}
Chara::~Chara()
{
	//�摜�̉��
	this->Image.Finalize();
	if (player) {
		this->player->Destroy();
	}
}
void Chara::UpDate()
{
	++AnimCnt;				//�A�j���[�V�����J�E���g�𑝂₷
	//�I�[�g�@�\��؂��Ă��Ȃ���ԂŃI�[�g���������Ȃ��
	if (this->isAuto && !this->isAutoOff)
	{
		//�L�����ɓo�^����Ă���I�[�g�ړ����s��
		//�����Ŏ��ۂ͊O���t�@�C�������𓾂ăI�[�g�������������
		this->AutoMove();
	}
	else
	{
		//�����łȂ���
		//�ړ��l���Ȃ��Ȃ�J�E���g�𑝂₷
		if (this->move.x == 0 && this->move.y == 0)
		{	
			//10�͒����Ȃ��悤�ɐ������Ă���
			if (this->MoveCnt <= 10)
			{
				this->MoveCnt++;
			}
		}
		else
		{
			//�ړ����Ă���Ԃ̓J�E���g��0�ɂ��Ă���
			this->MoveCnt = 0;
		}
		//if (this->move.x == 0) { this->motion = Motion::Normal; }
		//if (this->move.x != 0) { this->motion = Motion::Walk; }
		
	}
	if (this->move.x == 0)
	{
		this->motion = Normal;
	}
	else
	{
		this->motion = Walk;
	}
	if (this->move.y > 0) { this->motion = Motion::Fall; }
	if (this->move.y < 0) { this->motion = Motion::Jump_M; }
	//�J�E���g��10�𒴂��Ă���Ȃ�΃I�[�g�ړ��ֈڍs����
	if (this->MoveCnt > 10)
	{
		this->isAuto = true;
	}
	//���E�ړ��̌��Z�����Əd�͌v�Z
	this->Friction(this->move);
	//�ړ��l������ۂ̈ړ����s��
	this->MoveCheck(this->move);
}
void Chara::Render2D()
{
	//�`��ʒu�ƃT�C�Y���w��
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();

	Box2D src = this->returnSrc(this->motion);
	src.OffsetSize();
	//�ړ��l�ɍ��킹�Č��������킹��
	//�����炭�����ł��ׂ��ł͂Ȃ��̂Ō���C�����܂�
	if (this->move.x > 0)
	{
		this->direction = Direction::RIGHT;
	}
	if (this->move.x < 0)
	{
		this->direction = Direction::LEFT;
	}
	//�������Ȃ�摜���t�ɂ���
	if (direction == Direction::RIGHT) {
		int k = src.w;
		src.w = src.x;
		src.x = k;
	}
	//�`��
	this->Image.Draw(draw, src);
}
void Chara::Friction(Vec2& est)
{
	//���ړ��̌��Z����
	if (est.x > 0)
	{
		est.x = std::max(est.x - this->FIN_SPEED, 0.f);
	}
	else
	{
		est.x = std::min(est.x + this->FIN_SPEED, 0.f);
	}
	//�����ɒn�ʂ��Ȃ����A�܂��͈ړ��l���}�C�i�X�̎�
	if (!this->FootCheck() || est.y < 0)
	{
		//�d�͌v�Z
		est.y = std::min(est.y + this->GRAVITY, this->MAX_FALL);
	}
	else
	{
		//�ړ��l��0�ɂ���
		est.y = 0.0f;
	}
}
void Chara::MoveCheck(Vec2 est)
{
	auto map = OGge->GetTask<Map>("map");
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
		//�����蔻����s���J�E���g�ł���}�b�v�����݂��Ă��蓖���蔻����s���ݒ�̏ꍇ
		if (this->isCollisionNow != 0)
		{
			if (map && this->isCollision)
			{
				if (map->MapHitCheck(*this))
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
		//�����蔻����s���J�E���g�ł���}�b�v�����݂��Ă��蓖���蔻����s���ݒ�̏ꍇ
		if (this->isCollisionNow != 0)
		{
			if (map && this->isCollision)
			{

				if (map->MapHitCheck(*this))
				{
					this->position.y = preY;
					break;
				}
			}
		}
	}
}
bool Chara::FootCheck()
{
	//�����蔻����s���J�E���g�łȂ��Ȃ�false��Ԃ�
	if (this->isCollisionNow == 0)
	{
		return false;
	}
	//��������𐶐�
	GameObject foot;
	foot.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y + this->Scale.y), Vec2(this->Scale.x, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (map && this->isCollision)
	{
		if (map->MapHitCheck(foot))
		{
			return true;
		}
	}
	return false;
}
bool Chara::Jump()
{
	//�W�����v�l���ړ��l�ɂ����
	this->move.y = this->JUMP_POWER;
	//�J�E���g�𑝂₷(�����蔻��������������͕���������)
	this->IsCollisionCheck();
	return true;
}
void Chara::AutoMove()
{
	//�I�[�g���[�h��true�Ȃ�ݒ肵�Ă���ړ����s��
	if(this->isAutoMode)
	{
		this->move.x = this->easing_x.quad.InOut(this->easing_x.Time(this->time), this->startPos.x, this->EndPos.x, this->time) - this->position.x;
		this->isAutoMode = this->easing_x.isplay();
		this->isAutoOff = !this->easing_x.isplay();
	}
	else
	{
		//�����łȂ���Ό��X�p�ӂ���Ă���ړ����s��
		/*if (this->position.x > 1100 || this->position.x < 200)
		{
			if (this->direction == Direction::LEFT)
			{
				this->direction = Direction::RIGHT;
			}
			else
			{
				this->direction = Direction::LEFT;
			}
		}
		if (this->direction == Direction::LEFT)
		{
			this->move.x = -5.0f;
		}
		else
		{
			this->move.x = 5.0f;
		}*/

		if (player) {
			player->SetPlay();
			player->Play();
		}
	}
}
void Chara::ManualMove(Vec2& est)
{
	//�蓮�ړ��l�����̂܂ܓ����
	this->isAuto = false;
	this->MoveCnt = 0;
	this->move = est;
}
void Chara::IsCollisionCheck()
{
	//�J�E���g�𑝂₷
	this->isCollisionNow++;
}
bool Chara::CollisionNumCheck(__int8 num)
{
	//���������ׂĂ��̌��ʂ�Ԃ�
	return this->isCollisionNow == num ? true : false;
}
void Chara::MoveReset()
{
	//0,0�ɏ�����
	this->move = { 0,0 };
}
void Chara::SetDirection(const Direction& set)
{
	//�������㏑��
	this->direction = set;
}
void Chara::SetAutoFlag(const bool flag)
{
	//�I�[�g���[�h�̐ݒ���㏑��
	this->isAutoOff = flag;
}
Vec2 Chara::GetMove() const
{
	//�ړ��l��Ԃ�
	return this->move;
}
void Chara::SetAutoMode(const bool flag)
{
	//�I�[�g���[�h�ݒ���㏑��
	this->isAutoMode = flag;
}
void Chara::Set(const Vec2& start_, const Vec2& end_,const float time_)
{
	//�J�n�ʒu��o�^
	this->startPos = start_;
	//�I���ʒu��o�^
	this->EndPos = end_;
	//�ړ����Ԃ�o�^
	this->time = time_;
	//�I���ʒu����̈ړ��l�ɏ㏑��
	this->EndPos -= this->startPos;
	this->easing_x.ResetTime();
	this->SetAutoMode(true);
	this->SetAutoFlag(false);
}
bool Chara::isAutoPlay() const
{
	//�C�[�W���O�̈ړ����s���Ă��邩��Ԃ�
	return this->easing_x.isplay();
}
Chara::Direction Chara::nowDirection() const
{
	//������Ԃ�
	return this->direction;
}
Chara::SP Chara::Create(std::string& path, Vec2& pos, bool flag)
{
	Chara::SP to = Chara::SP(new Chara(path, pos));
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		return to;
	}
	return nullptr;
}
void Chara::SetReplayEnable()
{
	this->player = RecPlayer::Create("PlayerAct.txt", true);
	this->player->SetPause();
	this->player->SetRepeat(true);
	this->player->AddKeyEvent(Input::in::CL, RecDef::KeyState::PRESS, [&]() {
		this->move.x = -5.0f;
		this->direction = Direction::LEFT;
	});
	this->player->AddKeyEvent(Input::in::CR, RecDef::KeyState::PRESS, [&]() {
		this->move.x = 5.0f;
		this->direction = Direction::RIGHT;
	});
	this->player->AddKeyEvent(Input::in::B1, RecDef::KeyState::PRESS, [&]() {
		this->AutoJump();
	});
}
bool Chara::AutoJump()
{
	//�W�����v�l���ړ��l�ɂ����
	this->move.y = this->JUMP_POWER;
	return true;
}
Box2D Chara::returnSrc(Motion motion)
{
	Motion motion_ = motion;

	Box2D src2(0, 0, 550, 550);	//����src�i��ŏ��������j
	if (motion_ == Motion::Normal) {
		Box2D src(this->idle[this->AnimCnt / 3 % 10] * 550, 0, 550, 550);
		return src;
	}

	if (motion_ == Motion::Walk) {
		Box2D src(this->walk[this->AnimCnt / 3 % 9] * 550, 550, 550, 550);
		return src;
	}

	if (motion_ == Motion::Jump_M) {
		Box2D src(0 * 550, 2 * 550, 550, 550);
		return src;
	}

	if (motion_ == Motion::Fall) {
		Box2D src(1 * 550, 2 * 550, 550, 550);
		return src;
	}
	return src2;
}