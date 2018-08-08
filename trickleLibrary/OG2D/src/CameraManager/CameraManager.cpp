#include "CameraManager.h"

CameraManager::CameraManager()
{
	this->target = nullptr;
}

CameraManager::~CameraManager()
{
	if (this->target != nullptr)
	{
		this->target = nullptr;
	}
}

void CameraManager::SetObject(GameObject* object)
{
	this->target = object;
}

void CameraManager::SetRange(Box2D& range_)
{
	this->Range = range_;
}

void CameraManager::SetSize(Box2D& size_)
{
	this->Size = size_;
}

void CameraManager::move()
{
	//�ړ��l������
	this->est = { 0,0 };
	this->Range = { 100.f,100.f,OGge->camera->GetSize().x - 200.f,OGge->camera->GetSize().y - 200.f };
	//���l�̌v�Z
	this->RealRange = { OGge->camera->GetPos().x + this->Range.x,
						OGge->camera->GetPos().y + this->Range.y,
						OGge->camera->GetPos().x + this->Range.x + this->Range.w,
						OGge->camera->GetPos().y + this->Range.y + this->Range.h };
	//OG::LineHitDraw(&this->RealRange);
	if (this->target != nullptr)
	{
		this->pretarget = { this->target->position,this->target->Scale };
		//�w��͈͊O����
		/*if (this->RealRange.x > this->target->position.x)
		{
			this->est.x += this->target->position.x - this->RealRange.x;
		}
		if (this->RealRange.y > this->target->position.y)
		{
			this->est.y += this->target->position.y - this->RealRange.y;
		}
		if (this->RealRange.w < this->target->position.x + this->target->Scale.x)
		{
			this->est.x += (this->target->position.x + this->target->Scale.x) - this->RealRange.w;
		}
		if (this->RealRange.h < this->target->position.y + this->target->Scale.y)
		{
			this->est.y += (this->target->position.y + this->target->Scale.y) - this->RealRange.h;
		}*/
	}
	//�w��͈͊O����
	/*if (this->RealRange.x > this->pretarget.x)
	{
		this->est.x += this->pretarget.x - this->RealRange.x;
	}*/
	/*if (this->RealRange.y > this->pretarget.y)
	{
		this->est.y += this->pretarget.y - this->RealRange.y;
	}*/
	/*if (this->RealRange.w < this->pretarget.x + this->pretarget.w)
	{
		this->est.x += (this->pretarget.x + this->pretarget.w) - this->RealRange.w;
	}*/
	if (this->RealRange.h < this->pretarget.y + this->pretarget.h)
	{
		this->est.y += (this->pretarget.y + this->pretarget.h) - this->RealRange.h;
	}
	//�ړ��l�𑗂�
	OGge->camera->MovePos(this->est);
	//��ʊO����
	if (this->Size.x > OGge->camera->GetPos().x)
	{
		OGge->camera->SetPos_x(this->Size.x);
	}
	if (this->Size.y > OGge->camera->GetPos().y)
	{
		OGge->camera->SetPos_y(this->Size.y);
	}
	if (this->Size.w < OGge->camera->GetPos().x + OGge->camera->GetSize().x)
	{
		OGge->camera->SetPos_x(this->Size.w - OGge->camera->GetSize().x);
	}
	if (this->Size.h < OGge->camera->GetPos().y + OGge->camera->GetSize().y)
	{
		OGge->camera->SetPos_y(this->Size.h - OGge->camera->GetSize().y);
	}
}

void CameraManager::DeleteObject()
{
	this->target = nullptr;
}

CameraEasing::CameraEasing()
{
	this->start = nullptr;
	this->end = nullptr;
}
CameraEasing::~CameraEasing()
{
	if (this->start)
	{
		delete this->start;
	}
	if (this->end)
	{
		delete this->end;
	}
}
void CameraEasing::Set(const Vec2& end)
{
	//�I���n�_���o�^����Ă���ꍇ
	if (this->end)
	{
		//�O��ƌ��݂������Ȃ�Ȃɂ��s��Ȃ�
		if (*this->end == end)
		{
			//�I��
			return;
		}
		else
		{
			//�ʂȂ�O��̃f�[�^���폜���Ă���
			delete this->end;
			this->end = nullptr;
			if (this->start)
			{
				delete this->start;
				this->start = nullptr;
			}
		}
	}
	//�^�C���̏�����
	this->easing_x.ResetTime();
	this->easing_y.ResetTime();
	//�X�^�[�g�n�_�͍��̈ʒu
	this->start = new Vec2(OGge->camera->GetPos());
	//�I���n�_��o�^
	this->end = new Vec2(end);
	//�I���̈ʒu�̃x�N�g�������߂�
	*this->end = *this->end - *this->start;
}
void CameraEasing::CameraMove()
{
	if (this->end && this->start)
	{
		OGge->camera->SetPos(
			Vec2(
				this->easing_x.linear.In(this->easing_x.Time(1), this->start->x, this->end->x, 1), 
				this->easing_y.linear.In(this->easing_y.Time(1), this->start->y, this->end->y, 1)
			)
		);
	}
}
bool CameraEasing::IsPlay()
{
	return this->easing_x.isplay() || this->easing_y.isplay() ? true : false;
}