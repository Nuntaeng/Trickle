#include "Block/block.h"   //�ύX����

Block::Block() {
}

Block::Block(Vec2 pos) {
	this->position = pos;
}

Block::~Block() {

}

bool Block::Initialize(Vec2 pos) {
	//speed = 0.0f;
	//���ړ������l
	speed.x = 0.0f;
	speed.y = 0.0f;    //�s�v
					   //�d�͏����l
	gravity.x = 0.0f;  //�s�v
	gravity.y = 0.0f;

	//�v���C���Ƃ̓����蔻��t���b�O�@�g��Ȃ��Ȃ���
	plhitH = false;
	plhitF = false;
	plhitL = false;
	plhitR = false;

	Object::CreateObject(Objform::Cube, pos, Vec2(128.f, 128.f), 0.f);       //�I�u�W�F�N�g�̐���
	Object::objectTag = "Block";
	Object::CollisionProcess = [&](const Object& o_) {

	};

	tex.TextureCreate("Collision.png");

	return true;
}

void Block::Update(Map &map, Block &block, Object &p) {
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

	std::cout << "this->Object=" << position.x << "," << position.y << "," << Scale.x << "," << Scale.y << std::endl;
	std::cout << "headBase=" << headBase.position.x << "," << headBase.position.y << "," << headBase.Scale.x << "," << headBase.Scale.y << std::endl;
	std::cout << "footBase=" << footBase.position.x << "," << footBase.position.y << "," << footBase.Scale.x << "," << footBase.Scale.y << std::endl;
	std::cout << "rightBase=" << rightBase.position.x << "," << rightBase.position.y << "," << rightBase.Scale.x << "," << rightBase.Scale.y << std::endl;
	std::cout << "leftBase=" << leftBase.position.x << "," << leftBase.position.y << "," << leftBase.Scale.x << "," << leftBase.Scale.y << std::endl;
	*/
	if (plhit)
	{
		if (p.position.x < block.position.x)
		{
			//speed.x = 5.0f;�̓e�X�g�p�ɐݒ�
			//speed.x = 5.0f;
			CheckMove(speed, map, block);
		}
		if (p.position.x > block.position.x)
		{
			//speed.x = -5.0f;
			CheckMove(speed, map, block);
		}
	}
	gravity.y = 4.0f;
	CheckMove(gravity, map, block);
}

void Block::Render() {
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	src.OffsetSize();
	tex.Draw(draw, src);
}

void Block::Finalize() {
	tex.Finalize();
}

void Block::SetParent(Object* o_) {
	parent = o_;
}

bool Block::HasParent() const {
	return parent != nullptr;
}


Vec2 Block::GetMove(Vec2 move)       //move�Ƀv���C������󂯎��ړ��ʂ�����
{
	speed.x = move.x;
	return speed;
}
//�߂荞�񂾒l��Ԃ�����
Vec2 Block::BackMove()
{
	return backmove;
}


//�v���C���Ƃ̓����蔻��ɂ��� �g��Ȃ��Ȃ���
//--------------------------------------------------------------------------------------------------------------
void Block::PlCheckHitF(Object &p)
{
	plhitF = footBase.hit(p);
}
void Block::PlCheckHitH(Object &p)
{
	plhitH = headBase.hit(p);
}
void Block::PlCheckHitR(Object &p)
{
	plhitR = rightBase.hit(p);
}
void Block::PlCheckHitL(Object &p)
{
	plhitL = leftBase.hit(p);
}

void Block::PlCheckHit(Object &p, Block &block)
{
	plhit = block.hit(p);
}

//-----------------------------------------------------------------------------------------------
//�߂荞�܂Ȃ�����
void Block::CheckMove(Vec2 &e_, Map &map, Block &block)
{
	//x���ɂ���
	while (e_.x != 0.0f)
	{
		float preX = this->position.x;

		if (e_.x >= 1.0f)
		{
			this->position.x += 1.0f;
			e_.x -= 1.0f;
		}
		else if (e_.x <= -1.0f)
		{
			this->position.x -= 1.0f;
			e_.x += 1.0f;
		}
		else
		{
			this->position.x += e_.x;
			e_.x = 0.0f;
		}

		if (map.MapHitCheck(block))
		{
			backmove.x = position.x - preX;
			this->position.x = preX;
			break;
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

		if (map.MapHitCheck(block))
		{
			backmove.y = position.y - preY;
			this->position.y = preY;
			break;
		}
	}
}
