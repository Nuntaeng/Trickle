#include "Senpuki.h"

using namespace std;

const int INITIALCOORDINATE_X = 400;	//�������W
const int INITIALCOORDINATE_Y = 200;	//�������W
const int IMAGE_SIZE_X = 32;			//�摜�T�C�Y
const int IMAGE_SIZE_Y = 32;			//�摜�T�C�Y
const float WIND = 1.5f;				//���́i���̋����j

//��������//-----------------------------------------------------------------------------
Senpuki::Senpuki(/*EnemyHitTest* e_pointa*/)
{
	//player_pointa = p_pointa;
	//enemy_pointa = e_pointa;
	
	position.x = INITIALCOORDINATE_X;
	position.y = INITIALCOORDINATE_Y;
	_filePath = "prototype.png";
	_hitbox = "Collision.png";
	flag = false;
	objectTag = "Senpuki";
}
//��������//-----------------------------------------------------------------------------
Senpuki::~Senpuki()
{

}
//��������//-----------------------------------------------------------------------------
void Senpuki::Initialize()
{
	CreateObject(Objform::Cube, position, Vec2(IMAGE_SIZE_X, IMAGE_SIZE_Y), 0);
	/*position.x = INITIALCOORDINATE_X;
	position.y = INITIALCOORDINATE_Y;
	CreateObject(Objform::Cube, position, Vec2(IMAGE_SIZE, IMAGE_SIZE), 0);
	_filePath = "test.png";
	_hitbox = "Collision.png";
	flag = false;*/

	//�摜�֘A//
	senimg.TextureCreate(_filePath);		//�摜�p�X�w�������
	collbox.TextureCreate(_hitbox);
	//collisionCube.hitBase = Box2D((int)position.x, (int)position.y, IMAGE_SIZE, IMAGE_SIZE);
	//range.hitBase = Box2D((int)position.x / 2, (int)position.y / 2, IMAGE_SIZE + (int)position.x / 4, IMAGE_SIZE + (int)position.y / 4);
}
//��������//-----------------------------------------------------------------------------
void Senpuki::UpDate()
{

}
//��������//-----------------------------------------------------------------------------
void Senpuki::Finalize()
{
	senimg.Finalize();				
	collbox.Finalize();
}
//��������//-----------------------------------------------------------------------------
void Senpuki::Render()
{
	//��@
	Box2D draw((int)position.x , (int)position.y,IMAGE_SIZE_X,IMAGE_SIZE_Y);
	draw.OffsetSize();
	Box2D src(IMAGE_SIZE_X * 11, 0, IMAGE_SIZE_X, IMAGE_SIZE_Y);
	//�����蔻��̕`��i�f�o�b�O���̂ݓK���j
	/*
	Box2D Colldraw(draw);
	Colldraw.OffsetSize();
	Box2D Collsrc(src);*/
	senimg.Draw(draw, src);
	//collbox.Draw(draw, src);
}
//��������//-----------------------------------------------------------------------------
//  �֐�  //-----------------------------------------------------------------------------
//��������//-----------------------------------------------------------------------------
void Senpuki::CheckHit(int value)
{
	//CheckHit(enemy_pointa,1);
	//value�ɂ���ē����蔻���ς���i�f�o�b�O�p�j
	Object::CollisionProcess = [&](const Object& o_)
	{
		if (o_.objectTag == "Player")	//Player�̓����蔻��
		{
			flag = true;				//Player�Ɛڂ��Ă���
			if (flag)
			{
				switch (value)
				{
				case 0:
					//flag = collisionCube.hitBox(objhit->collisionCube); //���@�Ƃ̓����蔻��
					if (((Water&)o_).GetState() == Water::State::GAS)//Player�������C�̏�ԂȂ�΁E�E�E
					{
						//���𑗂�x���W�ɑ��邱�Ƃŕ��������Ă���悤�Ɍ�����
						//o_.position.x -= WIND;
					}
					break;
				case 1:
					//flag = range.hitBox(objhit->collisionCube);         //����͈͂Ƃ̓����蔻��
					break;
				}
			}
		}
		else
		{
			flag = false;
		}
	};
}