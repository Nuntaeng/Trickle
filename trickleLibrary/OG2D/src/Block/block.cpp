#include "Block/block.h"   //�ύX����
#include "Player\Player.h"
#include "Map\Map.h"
#include "Effect\Effect.h"
Block::Block() {
	this->Cnt = 0;
}

Block::Block(Vec2& pos) {
	this->position = pos;
	this->soundname = "blockMove.wav";
}

Block::~Block() {
	this->Finalize();
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{

	}
}

bool Block::Initialize(Vec2& pos) {
	//speed = 0.0f;
	//���ړ������l
	speed.x = 0.0f;
	speed.y = 0.0f;    //�s�v
					   //�d�͏����l
	gravity.x = 0.0f;  //�s�v
	gravity.y = 0.0f;

	this->plhit = false;

	//�v���C���Ƃ̓����蔻��t���b�O�@�g��Ȃ��Ȃ���
	plhitH = false;
	plhitF = false;
	plhitL = false;
	plhitR = false;

	//�T�E���h�̐���
	sound.create(soundname, false);
	sound.volume(1.0f);
	this->soundstart = true;

	GameObject::CreateObject(Objform::Cube, pos, Vec2(160.f, 160.f), 0.f);       //�I�u�W�F�N�g�̐���
	GameObject::objectTag = "Block";
	/*GameObject::CollisionProcess = [&](const GameObject& o_) {

	};*/

	tex.Create((std::string)"block.png");
	__super::Init((std::string)"block");

	isPushed = false;

	return true;
}

void Block::UpDate() {
	//�ǉ�����----------------------------------------------------------------------------
	footBase.position = Vec2(this->position.x, this->position.y + this->Scale.y);
	headBase.position = Vec2(this->position.x, this->position.y - 1.f);
	leftBase.position = Vec2(this->position.x - 1.f, this->position.y);
	rightBase.position = Vec2(this->position.x + this->Scale.x, this->position.y);
	//------------------------------------------------------------------------------------

	//���݂̏�Ԋm�F�p
	/*if (maphitF)
	{
	std::cout << "�����ڐG" << std::endl;
	}
	if (maphitH)
	{
	std::cout << "����ڐG" << std::endl;

	}
	if (maphitL)
	{
	std::cout << "�����ڐG" << std::endl;

	}
	if (maphitR)
	{
	std::cout << "�E���ڐG" << std::endl;
	}

	std::cout << "this->GameObject=" << position.x << "," << position.y << "," << Scale.x << "," << Scale.y << std::endl;
	std::cout << "headBase=" << headBase.position.x << "," << headBase.position.y << "," << headBase.Scale.x << "," << headBase.Scale.y << std::endl;
	std::cout << "footBase=" << footBase.position.x << "," << footBase.position.y << "," << footBase.Scale.x << "," << footBase.Scale.y << std::endl;
	std::cout << "rightBase=" << rightBase.position.x << "," << rightBase.position.y << "," << rightBase.Scale.x << "," << rightBase.Scale.y << std::endl;
	std::cout << "leftBase=" << leftBase.position.x << "," << leftBase.position.y << "," << leftBase.Scale.x << "," << leftBase.Scale.y << std::endl;
	*/
	auto p = OGge->GetTask<Player>("Player");
	if (p)
	{
		//this->PlCheckHit(*p);
		if (isPushed)
		{
			if (p->position.x < this->position.x)
			{
				//speed.x = 5.0f;�̓e�X�g�p�ɐݒ�
				//speed.x = 5.0f;
				//CheckMove(speed);
			}
			if (p->position.x > this->position.x)
			{
				//speed.x = -5.0f;
				//CheckMove(speed);
			}

			if (soundstart)
			{
				sound.play();
				soundstart = false;
			}
		}

		else
		{
			soundstart = true;
			sound.stop();
		}
	}
	gravity.y = 6.0f;
	Vec2 move = this->gravity;
	CheckMove(move);
}

void Block::Render2D() {
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
	Box2D src(0, 0, 256, 256);
	src.OffsetSize();
	tex.Draw(draw, src);
}

bool Block::Finalize() {
	tex.Finalize();
	return true;
}

Vec2 Block::GetMove(Vec2& move)       //move�Ƀv���C������󂯎��ړ��ʂ�����
{
	speed.x = move.x;
	this->CheckMove(speed);
	return speed;
}
//�߂荞�񂾒l��Ԃ�����
Vec2 Block::BackMove()
{
	return backmove;
}


//�v���C���Ƃ̓����蔻��ɂ��� �g��Ȃ��Ȃ���
//--------------------------------------------------------------------------------------------------------------
void Block::PlCheckHitF(GameObject &p)
{
	plhitF = footBase.hit(p);
}
void Block::PlCheckHitH(GameObject &p)
{
	plhitH = headBase.hit(p);
}
void Block::PlCheckHitR(GameObject &p)
{
	plhitR = rightBase.hit(p);
}
void Block::PlCheckHitL(GameObject &p)
{
	plhitL = leftBase.hit(p);
}

void Block::PlCheckHit(GameObject &p)
{
	if (this->IsObjectDistanceCheck(p.position, p.Scale))
	{
		plhit = this->hit(p);
	}
}

//-----------------------------------------------------------------------------------------------
//�߂荞�܂Ȃ�����
void Block::CheckMove(Vec2 &e_)
{
	float dir = 0;
	isPushed = false;

	//x���ɂ���
	while (e_.x != 0.0f)
	{
		float preX = this->position.x;

		if (e_.x >= 1.0f)
		{
			this->position.x += 1.0f;
			e_.x -= 1.0f;
			dir += 1.f;
		}
		else if (e_.x <= -1.0f)
		{
			this->position.x -= 1.0f;
			e_.x += 1.0f;
			dir -= 1.f;
		}
		else
		{
			this->position.x += e_.x;
			e_.x = 0.0f;
			dir += e_.x;
		}

		this->Cnt++;
		if (isCollideSomething())
		{
			backmove.x = position.x - preX;
			this->position.x = preX;
			Cnt = 0;
			break;
		}
		else
		{
			//�G�t�F�N�g�\������
			if (this->footCheck())
			{
				if (this->Cnt > 30)
				{
					if (dir > 0.f)
					{
						auto effect = Effect::Create(
							Vec2(this->foot.position.x + (this->Scale.x / 2), this->position.y + this->Scale.y - 32.f),
							Vec2(64, 64),
							Vec2(768, 768),
							1,
							50);
						effect->SetTexture(rm->GetTextureData((std::string)"sandsmoke"));
						effect->Set(effect->position, Vec2(effect->position.x, effect->position.y - 128.f));
						effect->SetMode(Effect::Mode::Decrease);
					}
					else if (dir < 0.f)
					{
						auto effect = Effect::Create(
							Vec2(this->foot.position.x + (this->foot.Scale.x / 2) - 32.f, this->position.y + this->Scale.y - 32.f),
							Vec2(64, 64),
							Vec2(768, 768),
							1,
							50);
						effect->SetTexture(rm->GetTextureData((std::string)"sandsmoke"));
						effect->Set(effect->position, Vec2(effect->position.x, effect->position.y - 128.f));
						effect->SetMode(Effect::Mode::Decrease);
					}
					this->Cnt = 0;
				}
			}
			isPushed = true;
		}
	}
	//y���ɂ���
	while (e_.y != 0.0f)
	{
		float preY = this->position.y;

		if (e_.y >= 1.0f)
		{
			this->position.y += 1.0f;
			e_.y -= 1.0f;
		}
		else if (e_.y <= -1.0f)
		{
			this->position.y -= 1.0f;
			e_.y += 1.0f;
		}
		else
		{
			this->position.y += e_.y;
			e_.y = 0.0f;
		}

		if (isCollideSomething())
		{
			backmove.y = position.y - preY;
			this->position.y = preY;
			break;
		}
	}
}


bool Block::isCollideSomething()
{
	auto map = OGge->GetTask<Map>("map");
	if (!map) {
		return false;
	}
	auto buckets = OGge->GetTasks<Bucket>("bucket");
	for (auto id = buckets->begin(); id != buckets->end(); ++id)
	{
		if (!(*id)->GetHold())
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

	return map->HitCheck(*this, 1);
}

bool Block::footCheck()
{
	foot.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y + this->Scale.y), Vec2(this->Scale.x, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (map && map->HitCheck(foot, "Floor"))
	{
		return true;
	}
	auto buckets = OGge->GetTasks<Bucket>("bucket");
	for (auto id = buckets->begin(); id != buckets->end(); ++id)
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

Block::SP Block::Create(Vec2& pos, bool flag_)
{
	auto to = Block::SP(new Block(pos));
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