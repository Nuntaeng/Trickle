#include "EnemyHitTest.h"

const int INITIALCOORDINATE_X = 100;	//�������W
const int INITIALCOORDINATE_Y = 100;	//�������W

const int IMAGE_SIZE = 128;				//�摜�T�C�Y
const int SPEED = 3;					//ENEMY SPEED

EnemyHitTest::EnemyHitTest()
{
	position.x = INITIALCOORDINATE_X;
	position.y = INITIALCOORDINATE_Y;
	state = State::Frieze;
}
EnemyHitTest::~EnemyHitTest()
{

}
void EnemyHitTest::Initialize()
{
	collisionCube.hitBase = Box2D((int)position.x, (int)position.y, IMAGE_SIZE, IMAGE_SIZE); //�����蔻���ݒ肷��
	_filePath = "player.png";
	image.TextureCreate(_filePath);
}
void EnemyHitTest::Finalize()
{
	image.Finalize();

	
}
void EnemyHitTest::UpDate()
{
	Move();
}
void EnemyHitTest::Render()
{
	Box2D draw((int)position.x, (int)position.y, IMAGE_SIZE, IMAGE_SIZE);
	Box2D src(0, 0, IMAGE_SIZE, IMAGE_SIZE);
	draw.OffsetSize();							//���W�l�̍Đݒ���s��
	image.Draw(draw, src);

}
void EnemyHitTest::Move()
{
	if (Input::KeyInputOn(Input::LEFT))
	{
		position.x -= SPEED;
	}
	if (Input::KeyInputOn(Input::RIGHT))
	{
		position.x += SPEED;
	}
	if (Input::KeyInputOn(Input::UP))
	{
		position.y -= SPEED;
	}
	if (Input::KeyInputOn(Input::DOWN))
	{
		position.y += SPEED;
	}
	//���W�̍X�V
	collisionCube.hitBase.x = position.x;
	collisionCube.hitBase.y = position.y;
	std::cout << "���݂�Enemy���W" << "(" << position.x << "," << position.y << ")" << std::endl;
}
