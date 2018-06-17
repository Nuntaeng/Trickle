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
	this->happyCnt = 0;					//�N���A��Ԃ̃J�E���g
	this->motion = Motion::Normal;		//motion������
	this->isAuto = true;				//�I�[�g�ړ��ݒ��������
	this->isCollision = true;			//�����蔻��ݒ菉����
	this->MoveCnt = 0;					//�ړ��J�E���g������
	this->Radius = Vec2(1.0f, 0.9f);	//�����蔻��𐧌�
	this->isCollisionNow = -1;			//�����蔻��J�E���g��������
	this->isAutoOff = false;			//�I�[�g�ړ��`�F�b�N��������
	this->isAutoMode = false;			//�I�[�g���[�h��������
	this->Restriction_x = nullptr;
}
Chara::~Chara()
{
	//�摜�̉��
	this->Image.Finalize();
	if (player) {
		this->player->Destroy();
	}
	if (recorder) {
		this->recorder->Destroy();
	}
	if (this->Restriction_x)
	{
		delete this->Restriction_x;
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
	else if (recorder) {
		if (OGge->in->on(Input::in::CL)) {
			this->move.x = -5.0f;
			this->direction = Direction::LEFT;
		}
		if (OGge->in->on(Input::in::CR)) {
			this->move.x = 5.0f;
			this->direction = Direction::RIGHT;
		}
		if (OGge->in->on(Input::in::B1)) {
			this->AutoJump();
		}
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
		
	}
	if (this->motion != Happy_N && this->motion != Happy_J && this->motion != Happy_F) {
		if (this->move.x == 0) { this->motion = Normal; }
		else { this->motion = Walk; }
		if (this->move.y > 0) { this->motion = Motion::Fall; }
		if (this->move.y < 0) { this->motion = Motion::Jump_M; }
		if (this->EndPos.y != 0) { this->motion = Motion::Ladder; }
	}
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
	if (this->Restriction_x)
	{
		if (this->direction == Direction::LEFT)
		{
			if (draw.x < *this->Restriction_x)
			{
				draw.x = *this->Restriction_x;
				src.x += this->srcX - (this->srcX * ((draw.w - draw.x) / this->Scale.x));
			}
		}
		else
		{
			if (draw.w > *this->Restriction_x)
			{
				draw.w = *this->Restriction_x;
				src.x += this->srcX - (this->srcX * ((draw.w - draw.x) / this->Scale.x));
			}
		}
	}
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
		float k = src.w;
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
void Chara::Happy(int count)
{
	//�W�����v����
	if (this->happyCnt < count-1) {
		//���[�V������ς���
		if (this->move.y > 0) {
			this->motion = Motion::Happy_J;
		}
		else {
			this->motion = Motion::Happy_F;
		}
		//������ς���
		if (this->happyCnt % 2 == 0) {
			this->direction = Direction::LEFT;
			this->move.x = -2;
		}
		else {
			this->direction = Direction::RIGHT;
			this->move.x = 2;
		}
		//�W�����v����
		if (this->FootCheck() && this->move.y == 0) {
			this->motion = Motion::Happy_N;
			if (this->happyCnt < count - 2) {
				this->move.y = this->JUMP_POWER - 5.f;
			}
			++this->happyCnt;
		}
	}
	//�I������烂�[�V��������
	else {
		this->motion = Motion::Normal;
		++this->happyCnt;
	}
}
void Chara::AutoMove()
{
	//�I�[�g���[�h��true�Ȃ�ݒ肵�Ă���ړ����s��
	if(this->isAutoMode)
	{
		this->move.x = this->easing_x.quad.InOut(this->easing_x.Time(this->time), this->startPos.x, this->EndPos.x, this->time) - this->position.x;
		this->move.y = this->easing_y.quad.InOut(this->easing_y.Time(this->time), this->startPos.y, this->EndPos.y, this->time) - this->position.y;
		this->isAutoMode = this->easing_x.isplay() || this->easing_y.isplay();
		this->isAutoOff = !this->easing_x.isplay() || !this->easing_y.isplay();
	}
	else
	{
		//�����łȂ���Ό��X�p�ӂ���Ă���ړ����s��
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
	this->easing_y.ResetTime();
	this->SetAutoMode(true);
	this->SetAutoFlag(false);
}
bool Chara::isAutoPlay() const
{
	//�C�[�W���O�̈ړ����s���Ă��邩��Ԃ�
	return this->easing_x.isplay() || this->easing_y.isplay();
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
	this->player = RecPlayer::Create("TitleMovement.txt", true);
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
	this->player->SetEndCallback([&]() -> bool {
		float judgeDirection = 790.f - this->position.x;
		if (abs(judgeDirection) > 5.f) {
			if (judgeDirection > 0) {
				this->move.x = 5.f;
				this->direction = Direction::RIGHT;
				return false;
			}
			if (judgeDirection < 0) {
				this->move.x = -5.f;
				this->direction = Direction::LEFT;
				return false;
			}
		}
		this->move.x = judgeDirection;
		this->direction = (judgeDirection < 0) ? Direction::LEFT : Direction::RIGHT;
		return true;
	});
}
void Chara::SetRecordEnable()
{
	this->isAuto = false;
	this->isAutoOff = true;
	recorder = Recorder::Create("TitleMovement.txt", true);
	recorder->ActivateKeyRecord(OGge->in);
	(*recorder) >> Input::in::CL;
	(*recorder) >> Input::in::CR;
	(*recorder) >> Input::in::B1;
	recorder->RecordStart();
}
bool Chara::AutoJump()
{
	//�W�����v�l���ړ��l�ɂ����
	this->move.y = this->JUMP_POWER;
	return true;
}
void Chara::SetRestriction(const float x_)
{
	if (this->Restriction_x)
	{
		delete this->Restriction_x;
	}
	this->Restriction_x = new float(x_);
}
Box2D Chara::returnSrc(Motion motion)
{
	Box2D src(0, 0, this->srcX, this->srcY);	//����src�i��ŏ��������j
	switch (motion)
	{
	case Motion::Normal:
		src = Box2D(this->idle[this->AnimCnt / 3 % 10] * this->srcX, 0, this->srcX, this->srcY);
		break;

	case Motion::Walk:
		src = Box2D(this->walk[this->AnimCnt / 3 % 9] * this->srcX, this->srcY, this->srcX, this->srcY);
		break;

	case Motion::Jump_M:
		src = Box2D(0 * this->srcX, 2 * this->srcY, this->srcX, this->srcY);
		break;

	case Motion::Fall:
		src = Box2D(1 * this->srcX, 2 * this->srcY, this->srcX, this->srcY);
		break;

	case Motion::Ladder:
		src = Box2D(this->ladder[this->AnimCnt / 15 % 2] * this->srcX, 3 * this->srcY, this->srcX, this->srcY);
		break;

	case Motion::Happy_N:
		src = Box2D(2* 641, 10 * this->srcY, 641, this->srcY);
		break;
	case Motion::Happy_J:
		src = Box2D(0 * 641, 10 * this->srcY, 641, this->srcY);
		break;
	case Motion::Happy_F:
		src = Box2D(1 * 641, 10 * this->srcY, 641, this->srcY);
		break;
	}
	return src;
}