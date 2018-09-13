#include "Door.h"
#include "Player\Player.h"
Door::Door(const Vec2& pos, const Vec2& size, const bool isOpen,const Direction& di)
{
	this->objectTag = "Door";
	__super::Init(this->objectTag);
	__super::SetDrawOrder(0.5f);
	auto doors = OGge->GetTasks<Door>(this->objectTag);
	//�������ꂽ���̂��I�����ȊO�������邱�Ƃ�����Ȃ炱����
	//for (auto id = doors->begin(); id != doors->end(); ++id)
	//{
	//}
	//�Ȃ���ΊȈՌ^
	this->id = (unsigned __int8)doors->size();
	this->isOpen = this->preIsOpen = isOpen;
	this->image = nullptr;
	this->originPos = pos;
	this->CreateObject(Cube, pos, size);
	if (this->isOpen)
	{
		this->timeCnt = 0.01f;
	}
	else
	{
		this->timeCnt = 1.f;
	}
	//this->position.y = this->originPos.y - (this->Scale.y * (1.f - this->timeCnt));
	this->isMove = false;
	this->direction = di;
	if (this->direction == Direction::HEIGHT)
	{
		//�c�̏ꍇy���W��o�^
		this->ch_Value[0] = &this->position.y;
		this->ch_Value[1] = &this->originPos.y;
		this->ch_Value[2] = &this->Scale.y;
		this->rotate = 0.f;
	}
	else
	{
		//���̏ꍇx���W��o�^
		this->ch_Value[0] = &this->position.x;
		this->ch_Value[1] = &this->originPos.x;
		this->ch_Value[2] = &this->Scale.y;
		this->rotate = 90.f;
		this->angle = 90.f;
	}
	*this->ch_Value[0] = *this->ch_Value[1] - (*this->ch_Value[2] * (1.f - this->timeCnt));
}
Door::~Door()
{
	
}
void Door::UpDate()
{
	//if (this->isOpen != this->preIsOpen)
	this->isMove = true;
	//�J����
	if (this->isOpen)
	{
		this->timeCnt -= 0.01f;
		//this->position.y = this->originPos.y - (this->Scale.y * (1.f - this->timeCnt));
		*this->ch_Value[0] = *this->ch_Value[1] - (*this->ch_Value[2] * (1.f - this->timeCnt));
		auto players = OGge->GetTasks<Player>("Player");
		for (auto id = players->begin(); id != players->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->hit(*(*id)))
				{
					//���ɖ߂�
					this->timeCnt += 0.01f;
					//this->position.y = this->originPos.y - (this->Scale.y * (1.f - this->timeCnt));
					*this->ch_Value[0] = *this->ch_Value[1] - (*this->ch_Value[2] * (1.f - this->timeCnt));
				}
			}
		}
		if (this->timeCnt <= 0.01f)
		{
			this->timeCnt = 0.01f;
			this->preIsOpen = this->isOpen;
			this->isMove = false;
		}
	}
		//�߂�
	else
	{
		this->timeCnt += 0.01f;
		//this->position.y = this->originPos.y - (this->Scale.y * (1.f - this->timeCnt));
		*this->ch_Value[0] = *this->ch_Value[1] - (*this->ch_Value[2] * (1.f - this->timeCnt));
		auto players = OGge->GetTasks<Player>("Player");
		for (auto id = players->begin(); id != players->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->hit(*(*id)))
				{
					//���ɖ߂�
					this->timeCnt -= 0.01f;
					//this->position.y = this->originPos.y - (this->Scale.y * (1.f - this->timeCnt));
					*this->ch_Value[0] = *this->ch_Value[1] - (*this->ch_Value[2] * (1.f - this->timeCnt));
				}
			}
		}
		if (this->timeCnt >= 1.0f)
		{
			this->timeCnt = 1.0f;
			this->preIsOpen = this->isOpen;
			this->isMove = false;
		}
	}
}
void Door::Render2D()
{
	if (this->image)
	{
		//this->draw = { this->position,Vec2(this->Scale.x,this->Scale.y * this->timeCnt) };
		this->draw = { this->position.x,this->position.y,this->Scale.x,this->Scale.y };
		draw.OffsetSize();
		this->src = { this->image->GetTextureSize().x / 8.f,0.f,this->image->GetTextureSize().x / 16.f ,this->image->GetTextureSize().y };
		//this->src = { 0,256,128,0 };
		src.OffsetSize();
		this->image->Rotate(this->rotate);
		this->image->Draw(this->draw, this->src);
		this->LineDraw();
	}
}
bool Door::ToOpen()
{
	if (!this->isOpen)
	{
		this->isOpen = true;
	}
	return false;
}
bool Door::ToClose()
{
	if (this->isOpen)
	{
		this->isOpen = false;
	}
	return false;
}
bool Door::changeIsOpen()
{
	this->isOpen = !this->isOpen;
	return this->isOpen;
}
bool Door::IsOpen() const
{
	return this->isOpen;
}
void Door::SetTexture(Texture* tex)
{
	this->image = tex;
}
unsigned __int8 Door::GetID() const
{
	return this->id;
}
bool Door::IsMove() const
{
	return this->isMove;
}
Door::SP Door::Create(const Vec2& pos,const Vec2& size,const bool isOpen,const Direction& di)
{
	Door::SP to = Door::SP(new Door(pos, size, isOpen, di));
	if (to)
	{
		to->me = to;
		OGge->SetTaskObject(to);
		return to;
	}
	return nullptr;
}