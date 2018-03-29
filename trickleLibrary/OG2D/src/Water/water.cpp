#include "water.h"



Water::Water(Vec2 pos) {
	//�^�O�ݒ�
	this->objectTag = "Water";
	//�Փ˔���
	Object::CollisionProcess = [&](const Object& o_) {
		if (o_.objectTag == "Floor") {
			this->isCollided = true;
		}
		if (o_.objectTag == "baketu")
		{
			if (this->GetState() == Water::State::LIQUID && this->GetSituation() == Water::Situation::Normal) {
				this->SetSituation(Water::Situation::CreaDelete);
			}
		}
	};
	//�`�挳�摜���W
	this->drawRange[Water::State::LIQUID] = Box2D(0, 0, 128, 128);
	this->drawRange[Water::State::GAS] = Box2D(128, 0, 128, 128);
	this->drawRange[Water::State::SOLID] = Box2D(256, 0, 128, 128);
	//�`��ő�ŏ��T�C�Y
	this->minSize = { 0,0 };
	this->maxSize = { 64,64 };
	//�o�ߎ��ԏ�����
	this->setTime = 0;
	//�I�u�W�F�N�g�̐���
	CreateObject(Objform::Cube, pos, this->minSize, 0.f);
	//�e�N�X�`���̓ǂݍ���
	tex.TextureCreate("watertest.png");
	//�Փ˔���̏�����
	this->isCollided = false;
	//�����X�e�[�^�X�̐ݒ�
	this->nowSituation = Water::Situation::Newfrom;
	this->currentState = Water::State::LIQUID;
	//�����ێ�����
	this->volume = 0.5;
	this->invi = 0;
}

Water::~Water() {
	//�e�N�X�`���̉��
	tex.Finalize();
}


bool Water::Initialize() {
	this->objectTag = "Water";
	Object::CollisionProcess = [&](const Object& o_) {
		if (o_.objectTag == "Floor") {
			this->isCollided = true;
		}
	};
	CreateObject(Objform::Cube, Vec2(100, 100), Vec2(64, 64), 0.f);
	this->isCollided = false;
	return true;
}

void Water::Update() {
	if (this->invi > 0)
	{
		this->invi--;
	}
	switch (this->currentState) {
	case Water::State::LIQUID:
		//������
		switch (this->nowSituation)
		{
		case Water::Situation::Newfrom:
			this->nowSituation = Water::UpNewform();
			break;
		case Water::Situation::Normal:
			this->nowSituation = Water::UpNormal();
			break;
		case Water::Situation::Deleteform:
			this->nowSituation = Water::UpDeleteform();
			break;
		case Water::Situation::CreaDelete:
			break;
		}
		break;
	case Water::State::GAS:
		//�����C����
		this->Scale = { this->maxSize.x,this->maxSize.y };
		if (!this->isCollided)
		{
			this->position.y -= 2.f;
		}
		break;
	case Water::State::SOLID:
		//�X����
		break;
	}
}

Water::Situation Water::UpNewform()
{
	Water::Situation now = this->nowSituation;
	this->setTime++;
	this->Scale.x += 2;
	this->Scale.y += 2;
	this->position.x--;
	if (this->setTime >= this->maxSize.x / 2)
	{
		now = Water::Situation::Normal;
	}
	return now;
}

Water::Situation Water::UpDeleteform()
{
	Water::Situation now = this->nowSituation;
	this->setTime++;
	this->Scale.x -= 2;
	this->Scale.y -= 2;
	this->position.y += 2;
	this->position.x++;
	if (this->setTime >= this->maxSize.x)
	{
		now = Water::Situation::CreaDelete;
	}
	return now;
}

Water::Situation Water::UpNormal()
{
	Water::Situation now = this->nowSituation;
	if (!this->isCollided)
	{
		position.y += 5.0f;
	}
	else
	{
		now = Water::Situation::Deleteform;
	}
	return now;
}

void Water::Render() {
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src = drawRange[currentState];
	src.OffsetSize();
	tex.Draw(draw, src);
}

void Water::Finalize() {
	tex.Finalize();
	//delete this;
}

void Water::SetState(const State& s_) {
	this->currentState = s_;
}

Water::State Water::GetState() const {
	return currentState;
}

void Water::SetSituation(const Situation& s_)
{
	this->nowSituation = s_;
}

Water::Situation Water::GetSituation() const
{
	return this->nowSituation;
}

float Water::waterMove()
{
	float _v = 0;
	if (Water::Situation::Normal == this->nowSituation && Water::State::LIQUID == this->currentState)
	{
		_v = this->volume;
		this->volume = 0.f;
	}	
	return _v;
}

float Water::GetWaterVolume() const
{
	return this->volume;
}