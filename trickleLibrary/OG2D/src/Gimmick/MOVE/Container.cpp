#include "Container.h"

using namespace std;


//-------------------------------------------------------------------------
//����
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//������������
//--------------------------------------------------------------------------
void Container_::Initialize()
{
	cout << "�e�평����" << endl;
	//pl_.Initialize();
	youki_.Initialize();
}
//--------------------------------------------------------------------------
//�������X�V
//--------------------------------------------------------------------------
void Container_::UpDate()
{
	//TaskFlag nowtask = Container;
	//pl_.UpDate();
	youki_.UpDate();

	//youki_.hitCheck = youki_.hit(pl_);         //�����蔻��

	//�v���C�����e������������ꍇ�̍��W�ݒ�
	if (youki_.hold)
	{
		/*youki_.position.x = pl_.position.x + 20;
		youki_.position.y = pl_.position.y + 30;*/
	}

	//return nowtask;
}

//----------------------------------------------------------------------------
//���������
//----------------------------------------------------------------------------
void Container_::Finalize()
{
	cout << "�e����" << endl;
	//pl_.Finalize();
	youki_.Finalize();
}
//----------------------------------------------------------------------------
//�������`��
//----------------------------------------------------------------------------
void Container_::Render()
{
	//pl_.Render();
	youki_.Render();
}

//-------------------------------------------------------------------------------
//�e��
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//�e�큙������
//-------------------------------------------------------------------------------
void Youki::Initialize()
{
	cout << "�e��̏�����" << endl;
	this->water = 0.0f;         //�����l�Ƃ��Đ��͓����Ă��Ȃ�
	this->ContainerImg.TextureCreate(this->fileName);
	this->hold = false;
	//position.x = 10;
	//position.y = 100;
	//Scale.x = 128.0f;
	//Scale.y = 128.0f;
	//CreateObject(Cube, Vec2(200.0f, 300.0f), Vec2(128.0f, 128.0f), 0.0f);
	
	//�֐��e�X�g�p
	Box2D pos=Box2D(200.0f,300.0f,128.0f,128.0f);
	CreateNew(pos);

	this->hitCheck = false;
}
//--------------------------------------------------------------------------------------
//�e�큙�X�V
//--------------------------------------------------------------------------------------
//TaskFlag Youki::UpDate()
void Youki::UpDate()
{
	//-------------------------------------------------------------------------------
	//�e���������
	//-------------------------------------------------------------------------------
	if (this->hold == false)           //�v���C�����e��������Ă��Ȃ�
	{
		if (this->hitCheck)            //�v���C�����e������Ă�ꏊ�ɋ���
		{
			//if (Input::KeyInputDown(Input::S))
			if(gameEngine->in.down(In::S))
			{
				this->hold = true;
			}
		}
	}
	//---------------------------------------------------------------------------------
	//�e��𗣂�����
	//---------------------------------------------------------------------------------
	if (this->hold == true)
	{
		//if (Input::KeyInputDown(Input::S))
		if(gameEngine->in.down(In::S))
		{
			this->hold = false;
		}
	}
}
//------------------------------------------------------------------------------
//�e�큙���
//------------------------------------------------------------------------------
void Youki::Finalize()
{
	cout << "�e��̊J��" << endl;
	this->ContainerImg.Finalize();
}
//------------------------------------------------------------------------------
//�e�큙�`��
//------------------------------------------------------------------------------
void Youki::Render()
{
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	if (hitCheck)
	{
		src.y += 128;
		src.OffsetSize();
	}
	this->ContainerImg.Draw(draw, src);
}

void Youki::CreateNew(Box2D pos)
{
	cout << "����" << endl;
	CreateObject(Cube, Vec2(pos.x, pos.y), Vec2(pos.w, pos.h), 0.0f);
}


//---------------------------------------------------------------------------------
//�v���C���[�e�X�g�p
//---------------------------------------------------------------------------------
//void Player::Initialize()
//{
//	cout << "�v���C�����̏�����" << endl;
//	this->PlImg.TextureCreate(this->fileName);
//	//position.x = 10;
//	//position.y = 100;
//	//Scale.x = 128.0f;
//	//Scale.y = 128.0f;
//	CreateObject(Cube, Vec2(200.0f, 400.0f), Vec2(128.0f, 128.0f), 0.0f);
//	this->hitCheck = false;
//}
//void Player::UpDate()
//{
//	//if (Input::KeyInputOn(Input::UP))
//	if(gameEngine->in.down(In::UP))
//	{
//		this->position.y += 1.0f;
//	}
//	//if (Input::KeyInputOn(Input::DOWN))
//	if(gameEngine->in.down(In::DOWN))
//	{
//		this->position.y -= 1.0f;
//	}
//	//if (Input::KeyInputOn(Input::RIGHT))
//	if(gameEngine->in.down(In::RIGHT))
//	{
//		this->position.x += 1.0f;
//	}
//	//if (Input::KeyInputOn(Input::LEFT))
//	if(gameEngine->in.down(In::LEFT))
//	{
//		this->position.x -= 1.0f;
//	}
//	//if (Input::KeyInputOn(Input::Q))
//	if(gameEngine->in.down(In::Q))
//	{
//		this->angle -= 1.0f;
//	}
//	//if (Input::KeyInputOn(Input::E))
//	if(gameEngine->in.down(In::E))
//	{
//		this->angle += 1.0f;
//	}
//}
//void Player::Finalize()
//{
//	cout << "�v���C�����̊J��" << endl;
//	this->PlImg.Finalize();
//}
//void Player::Render()
//{
//	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
//	draw.OffsetSize();
//	Box2D src(0, 0, 128, 128);
//	if (hitCheck)
//	{
//		src.y += 128;
//		src.OffsetSize();
//	}
//	this->PlImg.Draw(draw, src);
//}