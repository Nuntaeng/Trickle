#include "Paint.h"
#include "Water\water.h"
Paint::Paint(const Vec2 & pos, const Vec2 & size, const PaintColor & color_)
{
	this->color = new PaintColor(color_);
	this->CreateObject(Cube, pos, size, 0.0f);
	this->objectTag = "Paint";
	this->image = nullptr;
	__super::Init(this->objectTag);
}
Paint::~Paint()
{
	delete this->color;
}
void Paint::UpDate()
{
	this->WaterHit();
}
void Paint::Render2D()
{
	this->draw = { this->position,this->Scale };
	draw.OffsetSize();
	this->Setsrc();
	if (this->image)
	{
		this->image->Draw(this->draw, this->src);
	}
}
Paint::SP Paint::Create(const Vec2 & pos, const Vec2 & size, const PaintColor & color_, bool flag)
{
	Paint::SP to = Paint::SP(new Paint(pos, size, color_));
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		return to;
	}
	return nullptr;
}

void Paint::SetTexture(Texture* tex)
{
	this->image = tex;
}
void Paint::Setsrc()
{
	switch (*this->color)
	{
	case PaintColor::Red:
		this->src = { 0,0,256,256 };
		break;
	case PaintColor::Blue:
		this->src = { 256,0,256,256 };
		break;
	case PaintColor::Purple:
		this->src = { 512,0,256,256 };
		break;
	}
	this->src.OffsetSize();
}
bool Paint::WaterHit()
{
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		//�����蔻����s���͈͓������ׂ�
		if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			//�����F�Ȃ疳������
			if ((*id)->GetColor() != *this->color)
			{
				//�������Ă��邩�̔���
				if (this->CubeHit(*(*id)))
				{
					//���̐F��ς���
					(*id)->SetColor(*this->color);
					//return true;
				}
			}
		}
	}
	return false;
}