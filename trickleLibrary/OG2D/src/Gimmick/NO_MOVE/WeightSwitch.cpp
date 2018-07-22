#include "WeightSwitch.h"

//�����蔻�������K�v�̂���t�@�C���̓ǂݍ���
#include "Block/block.h"
#include "Bucket/bucket.h"
#include "Water/water.h"
#include "Player/Player.h"

WeightSwitch::WeightSwitch(const Vec2& pos_, const Vec2& size_, const float mass_)     //���W�A�傫���A�K�v�ȏd��
{
	std::cout << "�X�C�b�`����" << std::endl;
	this->objectTag = "WeightSwitch";
	this->taskName = "WeightSwitch";
	__super::Init(this->objectTag);
	__super::SetDrawOrder(0.5f);              //�`�揇��ݒ�
	auto WSwitch = OGge->GetTasks<WeightSwitch>(this->objectTag);

	CreateObject(Cube, pos_, size_);         //�I�u�W�F�N�g�𐶐�
	head.CreateObject(Cube, Vec2(pos_.x, pos_.y - 1.0f), Vec2(size_.x, 1.0f));     //�ق��̃I�u�W�F�N�g�Ƃ̓����蔻��p�I�u�W�F�N�g�̐���
	this->maxmass = mass_;                   //�����J���d�����i�[
	this->totalmass = 0.0f;                  //����Ă�����̂̑����̏d���i�[
	this->nowActive = false;                 //�������J���邩
	this->premass = 0.0f;
	this->isPushed = false;                  //��x�ł��X�C�b�`�������ꂽ��

	//�����̃I�u�W�F�N�g�Ɠ����蔻������Ă悢��
	this->canPlhitCheck = true;         //�v���C��
	this->canBlockhitCheck = true;      //�u���b�N
	this->canIcehitCheck = true;        //�X
	this->canBuckethitCheck = true;     //�o�P�c
}
WeightSwitch::~WeightSwitch()
{
	std::cout << "�X�C�b�`������" << std::endl;
	this->image = nullptr;
}


void WeightSwitch::UpDate()
{
	this->Getmass();
	//���̋쓮�ɂ���
	if (this->totalmass >= this->maxmass)      //�����J���d���ɂȂ���
	{
		this->nowActive = true;
		if (state == Nomal)
		{
			this->Scale.y -= 20.0f;     //�����߂荞�ރo�O����
			this->position.y += 20.0f;
		}
		this->state = Riding;
		this->isPushed = true;
	}
	else                                      //�܂��y��
	{
		this->nowActive = false;
		if (state == Riding)
		{
			this->position.y -= 20.0f;
			this->Scale.y += 20.0f;
		}
		this->state = Nomal;
	}
}
void WeightSwitch::Render2D()
{
	//��Ԃɂ���ĕ`��摜��ς���@������
	//if (state == Nomal)
	//{

	//}
	//if (state == Riding)
	//{

	//}

	//�X�C�b�`�̕`��
	this->draw = Box2D(this->position, this->Scale);
	draw.OffsetSize();
	this->src = Box2D(0, 0, 128, 128);
	src.OffsetSize();
	this->image->Draw(draw, src);
	this->LineDraw();
}

//�������Ă���I�u�W�F�N�g�̏d�����擾
void WeightSwitch::Getmass()
{
	//�f�o�b�O�p
	std::cout <<"���݂̏d��"<< totalmass << std::endl;

	//�X�̏d���̎擾---------------------------------------------------------
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		//���Ƃ̓����蔻��
		if ((*id)->GetState() == Water::State::SOLID)
		{
			if ((*id)->CubeHit(this->head))
			{
				if (canIcehitCheck == true)
				{
					premass = totalmass;            //���Z����O�̏d�����i�[
					this->totalmass += (*id)->mass;
					canIcehitCheck = false;
					//�f�o�b�O�p
					//std::cout << this->totalmass << std::endl;
				}
			}
			else
			{
				if(canIcehitCheck==false)
				{
					canIcehitCheck = true;                    //�ϐ����I�u�W�F�N�g���Ƃɕς����ق�����������
					this->totalmass -= (*id)->mass;
					//�f�o�b�O�p
					//std::cout << this->totalmass << std::endl;
				}
			}
		}
	}
	//�o�P�c�̏d���擾-----------------------------------------------------
	auto buckets = OGge->GetTasks<Bucket>("bucket");
	for (auto id = (*buckets).begin(); id != (*buckets).end(); ++id)
	{
		//�o�P�c�Ƃ̓����蔻��
		if ((*id)->CubeHit(this->head))
		{
			if (canBuckethitCheck == true)
			{
				premass = totalmass;            //���Z����O�̏d�����i�[
				this->totalmass += (*id)->mass;
				canBuckethitCheck = false;
				//�f�o�b�O�p
				//std::cout << this->totalmass << std::endl;
			}
		}
		else
		{
			if (canBuckethitCheck == false)
			{
				canBuckethitCheck = true;
				this->totalmass -= (*id)->mass;      //�O�ɏo����d�������ɖ߂�
				//�f�o�b�O�p
				//std::cout << this->totalmass << std::endl;
			}
		}
	}
	//�u���b�N�̏d���擾--------------------------------------------------------
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = (*blocks).begin(); id != (*blocks).end(); ++id)
	{
		//�u���b�N�Ƃ̓����蔻��
		if ((*id)->CubeHit(this->head))
		{
			if (canBlockhitCheck == true)
			{
				premass = totalmass;            //���Z����O�̏d�����i�[
				this->totalmass += (*id)->mass;
				canBlockhitCheck = false;
				//�f�o�b�O�p
				//std::cout << this->totalmass << std::endl;
			}
		}
		else
		{
			if (canBlockhitCheck == false)
			{
				canBlockhitCheck = true;
				this->totalmass -= (*id)->mass;      //�O�ɏo����d�������ɖ߂�
				//�f�o�b�O�p
				//std::cout << this->totalmass << std::endl;
			}
		}
	}
	//�v���C���̏d���擾---------------------------------------------------------
	auto player = OGge->GetTask<Player>("Player");
	//�v���C���Ƃ̓����蔻��
	if (player->CubeHit(this->head))
	{
		if (canPlhitCheck == true)
		{
			premass = totalmass;            //���Z����O�̏d�����i�[
			this->totalmass += player->mass;
			canPlhitCheck = false;
			//�f�o�b�O�p
			//std::cout << this->totalmass << std::endl;
		}
	}
	else
	{
		if (canPlhitCheck == false)
		{
			this->canPlhitCheck = true;
			this->totalmass -= player->mass;
			//�f�o�b�O�p
			//std::cout << this->totalmass << std::endl;
		}
	}
}

//���݂̃X�C�b�`�̏�Ԃ�Ԃ� (�����J����̂Ɏg�p)
bool WeightSwitch::SetnowState()
{
	return nowActive;     //�X�C�b�`�̍��̏�Ԃ�Ԃ�
}

//�摜��ݒ肷��
void WeightSwitch::SetTexture(Texture* tex)
{
	this->image = tex;
}

//�X�C�b�`��������Ă��Ȃ���ԂɂȂ����Ƃ��|�W�V������߂��l��Ԃ�
float WeightSwitch::SetSwitchUpPos()
{
	if (isPushed)
	{
		if (nowActive == false)
		{
			isPushed = false;
			return -20.0f;
		}
	}
	return 0.0f;
}

//�X�C�b�`�̐����ɂ���
WeightSwitch::SP WeightSwitch::Create(const Vec2& pos, const Vec2& size, const float mass)
{
	WeightSwitch::SP to = WeightSwitch::SP(new WeightSwitch(pos, size, mass));
	if (to)
	{
		to->me = to;
		OGge->SetTaskObject(to);
		return to;
	}
	return nullptr;
}