#include "Block.h"

using namespace std;

//�u���b�N�M�~�b�N
//--------------------------------------------------------------------
//��������������
//--------------------------------------------------------------------
void GimmickB::Initialize()
{
	cout << "�u���b�N�̏�����" << endl;
	this->BlockImg.TextureCreate(this->fileName);
	this->hitRight = false;
	this->hitLeft = false;
	this->hitbottom = true;
	this->speed = 0.0f;

	//�u���b�N�I�u�W�F�N�g�̐���
	//position.x = 100;
	//position.y = 100;
	//Scale.x = 128.0f;
	//Scale.y = 128.0f;
	CreateObject(Cube, Vec2(100.0f,100.0f), Vec2(128.0f, 128.0f), 0.0f);

	//�T�C�h�̓����蔻��p��`
	HitR = Box2D(this->Scale.x, 0.0f, 1.0f, this->Scale.y);
	HitL = Box2D(-1.0f, 0.0f , 1.0f, this->Scale.y);
}

//----------------------------------------------------------------------
//�����X�V����
//----------------------------------------------------------------------
TaskFlag GimmickB::UpDate()
{
	TaskFlag nowtask = Block;

	//���ɉ������Ƃ��̏���
	if (Input::KeyInputOn(Input::LEFT))
	{
		this->speed = -1.0f;
		if (hitRight == true)
		{
			this->position.x += this->speed;
		}
	}

	//�E�ɉ������Ƃ��̏���
	if (Input::KeyInputOn(Input::RIGHT))
	{
		this->speed = 1.0f;
		if (hitLeft == true)
		{
			this->position.x += this->speed;
		}
	}

	//�n�ʂɐڐG���Ă��Ȃ��Ƃ��̏���
	if (hitbottom == false)
	{
		if (this->speed < 5.0f)
		{
			this->speed += 0.2f;
		}
		this->position.y += speed;
	}

	return nowtask;
}

//-----------------------------------------------------------------------------
//�����������
//-----------------------------------------------------------------------------
void GimmickB::Finalize()
{
	cout << "�u���b�N�̉��" << endl;
	this->BlockImg.Finalize();
}

//------------------------------------------------------------------------------
//�����`�恙��
//------------------------------------------------------------------------------
void GimmickB::Render()
{
	//�u���b�N�{�̂̕`��
	{
		Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
		draw.OffsetSize();
		Box2D src(0, 0, 128, 128);
		this->BlockImg.Draw(draw, src);
	}

	//�E���ڐG����e�X�g�p
	{
		Box2D draw(HitR.x, HitR.y, HitR.w, HitR.h);
		draw.Offset(this->position.x,this->position.y);
		draw.OffsetSize();

		Box2D src(0, 128, 128, 128);
		this->BlockImg.Draw(draw, src);
	}
	//�����ڐG����e�X�g�p
	{
		Box2D draw(HitL.x, HitL.y, HitL.w, HitL.h);
		draw.Offset(this->position.x, this->position.y);
		draw.OffsetSize();

		Box2D src(0, 128, 128, 128);
		this->BlockImg.Draw(draw, src);
	}
}
