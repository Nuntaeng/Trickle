#include "Senpuki.h"

using namespace std;

const int INITIALCOORDINATE_X = 400;	//�������W
const int INITIALCOORDINATE_Y = 200;	//�������W
const int IMAGE_SIZE = 128;			    //�摜�T�C�Y

//��������//-----------------------------------------------------------------------------
Senpuki::Senpuki(EnemyHitTest* e_pointa)
{
	//player_pointa = p_pointa;
	//enemy_pointa = e_pointa;
	position.x = INITIALCOORDINATE_X;
	position.y = INITIALCOORDINATE_Y;
	_filePath = "test.png";
	_hitbox = "Collision.png";
	flag = false;
}
//��������//-----------------------------------------------------------------------------
Senpuki::~Senpuki()
{

}
//��������//-----------------------------------------------------------------------------
void Senpuki::Initialize()
{
	//�摜�֘A//
	senimg.TextureCreate(_filePath);		//�摜�p�X�w�������
	collbox.TextureCreate(_hitbox);
	collisionCube.hitBase = Box2D((int)position.x, (int)position.y, IMAGE_SIZE, IMAGE_SIZE);
	range.hitBase = Box2D((int)position.x / 2, (int)position.y / 2, IMAGE_SIZE + (int)position.x / 4, IMAGE_SIZE + (int)position.y / 4);
}
//��������//-----------------------------------------------------------------------------
void Senpuki::UpDate()
{
	/*CheckHit(enemy_pointa,1);
	if (flag)
	{

		if (enemy_pointa->state == State::Hot)
		{
			//���𑗂�x���W�ɑ��邱�Ƃŕ��������Ă���悤�Ɍ�����
			enemy_pointa->position.x -= 1.5f;
		}
	}*/
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
	Box2D draw((int)position.x , (int)position.y,IMAGE_SIZE,IMAGE_SIZE);
	draw.OffsetSize();
	Box2D src(0, 0, IMAGE_SIZE, IMAGE_SIZE);
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
void Senpuki::CheckHit(Object* objhit , int value = 0)
{
	//value�ɂ���ē����蔻���ς���i�f�o�b�O�p�j
	switch (value)
	{
	case 0:
		flag = collisionCube.hitBox(objhit->collisionCube); //���@�Ƃ̓����蔻��
		break;
	case 1:
		flag = range.hitBox(objhit->collisionCube);         //����͈͂Ƃ̓����蔻��
		break;
	}
}