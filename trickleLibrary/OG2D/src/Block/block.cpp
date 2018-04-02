#include "Block/block.h"   //�ύX����

Block::Block(){
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

	//�v���C���Ƃ̓����蔻��t���b�O
	plhitH = false;
	plhitF = false;
	plhitL = false;
	plhitR = false;
	//�}�b�v�Ƃ̓����蔻��t���b�O
	maphitH = false;
	maphitF = false;
	maphitL = false;
	maphitR = false;

	Object::CreateObject(Objform::Cube, pos, Vec2(128.f, 128.f), 0.f);       //�I�u�W�F�N�g�̐���
	Object::objectTag = "Block";
	Object::CollisionProcess = [&](const Object& o_) {

	};

	//�����蔻��p�I�u�W�F�N�g�̐���
	CreateHead();
	CreateFoot();
	CreateLeft();
	CreateRight();

	tex.TextureCreate("Collision.png");

	return true;
}

void Block::Update(Map &map, Block &block) {
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

	//�}�b�v�ɂ߂荞�܂Ȃ���������
	if (plhitL)
	{
		if (Input::KeyInputOn(Input::RIGHT))
		{
			speed.x += 5.0f;
			CheckMove(speed, map, block);
		}
	}
	if (plhitR)
	{
		if (Input::KeyInputOn(Input::LEFT))
		{
			speed.x -= 5.0f;
			CheckMove(speed, map, block);
		}
	}
		gravity.y = 4.0f;
		CheckMove(gravity, map, block);
}

void Block::Render() {
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
	Box2D src(0,0,128,128);
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

//�}�b�v�Ƃ̓����蔻��ɂ���
//---------------------------------------------------------------------------------------------------
void Block::CreateHead()
{
	headBase.CreateObject(Cube, Vec2(this->position.x, this->position.y + this->Scale.y), 
		Vec2(this->Scale.x, 1.0f), 0.0f);
	headBase.objectTag = "BlockHead";
}
void Block::CreateFoot()
{
	footBase.CreateObject(Cube, Vec2(this->position.x, this->position.y - 1.f),
		Vec2(this->Scale.x , 1.0f), 0.0f);
	footBase.objectTag = "BlockFoot";
}
void Block::CreateLeft()
{
	leftBase.CreateObject(Cube, Vec2(this->position.x - 1.f,
		this->position.y), Vec2(1.0f, this->Scale.y), 0.0f);
	leftBase.objectTag = "BlockLeft";
}
void Block::CreateRight()
{
	rightBase.CreateObject(Cube, Vec2(this->position.x + this->Scale.x, this->position.y),
		Vec2(1.0f, this->Scale.y), 0.0f);
	rightBase.objectTag = "BlockRight";
}


//�v���C���Ƃ̓����蔻��ɂ���
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

//-----------------------------------------------------------------------------------------------
//�߂荞�܂Ȃ�����
void Block::CheckMove(Vec2 &e_, Map &map, Block &block)
{
	//x���ɂ���
	while (e_.x != 0.0f)
	{
		float preX = this->position.x;
		std::cout << "preX" << preX << std::endl;

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
			this->position.x = preX;
			break;
		}
	}
	//y���ɂ���
	while (e_.y != 0.0f)
	{
		float preY = this->position.y;
		std::cout << "preY" << preY << std::endl;

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
			this->position.y = preY;
			break;
		}
	}
}
