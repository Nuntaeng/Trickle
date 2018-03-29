#include "Kanetuki.h"
using namespace std;

const int POS_X = 600;
const int POS_Y = 100;			

const int IMAGE_SIZE_X = 32;	//�摜�T�C�YX���W
const int IMAGE_SIZE_Y = 32;	//�摜�T�C�YY���W

const int HOTTIME = 1;			//�����C�ɂȂ�܂ł̎���
const int HOT_TIME = 180;		//�����C�ɕω����鎞��

//��������//-----------------------------------------------------------------------------
Kanetuki::Kanetuki(/*EnemyHitTest* e_pointa*/)
{
	//player_pointa = p_pointa;

	//EnemyHitTest�N���X�̏����擾����
	//enemy_pointa = e_pointa;     

	_filePath = "prototype.png";	
	position = Vec2(POS_X, POS_Y);
	flag = false;
	Count = 0;
	objectTag = "Kanetuki";
}

//��������//-----------------------------------------------------------------------------
Kanetuki::~Kanetuki()
{
	//delete player_pointa;
	//delete enemy_pointa;
}
//��������//-----------------------------------------------------------------------------
void Kanetuki::Initialize()
{
	/*_filePath = "Kanetuki.jpg";
	position = Vec2(POS_X, POS_Y);
	CreateObject(Objform::Cube, position, Vec2(IMAGE_SIZE, IMAGE_SIZE), 0);
	flag = false;
	Count = 0;*/
	image.TextureCreate(_filePath);
	CreateObject(Objform::Cube, position, Vec2(IMAGE_SIZE_X, IMAGE_SIZE_Y), 0);
}
//��������//-----------------------------------------------------------------------------
void Kanetuki::UpDate()
{
	//collisionCube.hitBase = Box2D((int)position.x + 100, (int)position.y /2 + 128, IMAGE_SIZE, IMAGE_SIZE);

	// ___________________________________________________ //
	//| Player�ɓ�������̎��Ԃ����Ɛ����C�ɕω����܂�|//
	//|___________________________________________________|//

}
//��������//-----------------------------------------------------------------------------
void Kanetuki::Render()
{
	Box2D draw((int)position.x, (int)position.y, IMAGE_SIZE_X, IMAGE_SIZE_Y);
	draw.OffsetSize();
	Box2D src(IMAGE_SIZE_X * 10, 0, IMAGE_SIZE_X, IMAGE_SIZE_Y);
	image.Draw(draw, src);
}
//��������//-----------------------------------------------------------------------------
void Kanetuki::Finalize()
{
	image.Finalize();
}
//��������//-----------------------------------------------------------------------------
//  �֐�  //-----------------------------------------------------------------------------
//��������//-----------------------------------------------------------------------------
void Kanetuki::CheckHit()
{
	Object::CollisionProcess = [&](const Object& o_)
	{
		if (o_.objectTag == "Water")
		{
			flag = true;
			if (flag)								//Player�Ɛڂ��Ă�Ƃ�
			{
				if (((Water&)o_).GetState() == Water::State::SOLID)
				{
					Count += HOTTIME;				//���M�J�E���^�𑝂₷

					if (Count >= HOT_TIME)			//���M�J�E���^������ɒB������
					{
						//�����C�̏�Ԃɂ���
						((Water&)o_).SetState(Water::State::GAS);
					}
				}
			}
			else
			{
				//cout << "false" << endl;
				Count = 0;							//���M�J�E���^�����ɖ߂�
			}
		}
		else
		{
			flag = false;
		}
	};
}