#include "Chara.h"
#include "Map\Map.h"

Chara::Chara(std::string& path, Vec2& pos)
	:MOVE_SPEED(5.f), JUMP_POWER(-5.0f), MAX_FALL(30.f), GRAVITY((9.8f / 60.f / 60.f * 32) * 5), FIN_SPEED(0.5f)
{
	this->position = pos;
	this->Image.Create(path);
	this->CreateObject(Cube, pos, Vec2(128, 128), 0.0f);
	this->taskName = "Chara";
	__super::Init(this->taskName);
	__super::SetDrawOrder(1.0f);
	this->objectTag = this->taskName;
	this->direction = Direction::LEFT;
	this->AnimCnt = 0;
	this->isAuto = true;
	this->isCollision = true;
	this->MoveCnt = 0;
	this->Radius = Vec2(1.0f, 0.9f);
	this->isCollisionNow = -1;
	this->isAutoOff = false;
<<<<<<< HEAD
=======
	this->isAutoMode = false;
>>>>>>> develop
}
Chara::~Chara()
{
	this->Image.Finalize();
}
void Chara::UpDate()
{
	//std::cout << "pos_x:" << this->position.x << "pos_y:" << this->position.y << "move_x:" << this->move.x << "move_y:" << this->move.y << std::endl;
	//�ʒu�ɉ����ē����蔻��̐ݒ��ύX���鏈��
	//�d�l���ς�������ߕs�v�ƂȂ�܂����B
	/*if (this->isCollisionNow == 0)
	{
		if (this->position.y > 1200.f)
		{
			this->isCollisionNow++;
		}
<<<<<<< HEAD
	}
=======
	}*/
	//�I�[�g�@�\��؂��Ă��Ȃ���ԂŃI�[�g���������Ȃ��
>>>>>>> develop
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
	//�A�j���[�V�����p
	int idle[10] = { 0,0,0,0,0,0,0,1,1,1 };

	if (this->AnimCnt < 30) {
		this->AnimCnt++;
	}
	if (this->AnimCnt >= 30) {
		this->AnimCnt = 0;
	}

	Box2D src(idle[this->AnimCnt / 3] * 550, 0, 550, 550);
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
	this->move.y = this->JUMP_POWER;
	this->IsCollisionCheck();
	return true;
}
void Chara::AutoMove()
{
	if(this->isAutoMode)
	{
		this->move.x = this->easing_x.quad.InOut(this->easing_x.Time(15), this->startPos.x, this->EndPos.x, 15) - this->position.x;
		this->isAutoMode = this->easing_x.isplay();
		this->isAutoOff = !this->easing_x.isplay();
	}
	else
	{
		if (this->position.x > 1100 || this->position.x < 200)
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
		}
	}
}
void Chara::ManualMove(Vec2& est)
{
	this->isAuto = false;
	this->MoveCnt = 0;
	this->move = est;
}
void Chara::IsCollisionCheck()
{
	this->isCollisionNow++;
}
bool Chara::CollisionNumCheck(__int8 num)
{
	return this->isCollisionNow == num ? true : false;
}
void Chara::MoveReset()
{
	this->move = { 0,0 };
}
void Chara::SetDirection(const Direction& set)
{
	this->direction = set;
}
void Chara::SetAutoFlag(const bool flag)
{
	this->isAutoOff = flag;
}
Vec2 Chara::GetMove() const
{
	return this->move;
}
<<<<<<< HEAD
=======
void Chara::SetAutoMode(const bool flag)
{
	this->isAutoMode = flag;
}
void Chara::Set(const Vec2& start_, const Vec2& end_)
{
	//�J�n�ʒu��o�^
	this->startPos = start_;
	//�I���ʒu��o�^
	this->EndPos = end_;
	//�I���ʒu����̈ړ��l�ɏ㏑��
	this->EndPos -= this->startPos;
	this->easing_x.ResetTime();
	this->SetAutoMode(true);
	this->SetAutoFlag(false);
}
bool Chara::isAutoPlay() const
{
	return this->easing_x.isplay();
}
Chara::Direction Chara::nowDirection() const
{
	return this->direction;
}
>>>>>>> develop
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
