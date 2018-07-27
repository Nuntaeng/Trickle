#include "Back.h"
#include "Map\Map.h"
Back::Back(const std::string& path, Vec2& size_)
{
	this->size = size_;
	this->Init(path);
}

Back::Back(const std::string& path, float size_x, float size_y)
{
	this->size = { size_x,size_y };
	this->Init(path);
}

Back::Back(const std::string& path, int size_x, int size_y)
{
	this->size = { size_x,size_y };
	this->Init(path);
}

void Back::Init(const std::string& path)
{
	this->backImg.Create(path);
	__super::Init((std::string)"back");
	__super::SetDrawOrder(0.0f);
	this->isScroll = false;
	this->mapSize = nullptr;
	this->Center = nullptr;
	this->Xsize = nullptr;
	this->Tsize = nullptr;
	this->texPos = nullptr;
}

Back::~Back()
{
	this->backImg.Finalize();
	if (this->mapSize)
	{
		delete this->mapSize;
	}
	if (this->Center)
	{
		delete this->Center;
	}
	if (this->Xsize)
	{
		delete this->Xsize;
	}
	if (this->Tsize)
	{
		delete this->Tsize;
	}
	if (this->texPos)
	{
		delete this->texPos;
	}
}

void Back::UpDate()
{
	if (this->texPos)
	{
		//�摜�̕`��ʒu���}�b�v�T�C�Y�ƃJ�����̈ʒu�ƃJ�����̃T�C�Y���狁�߂�
		*this->texPos = Vec2(OGge->camera->GetPos().x - ((OGge->camera->GetPos().x / *this->Xsize) * *this->Tsize), OGge->camera->GetPos().y - (this->size.y - OGge->camera->GetSize().y));
	}
}

void Back::Render2D()
{
	if (this->isScroll)
	{
		Box2D draw(this->texPos->x, this->texPos->y, this->size.x, this->size.y);
		draw.OffsetSize();
		Box2D src(0.f, 0.f, this->backImg.GetTextureSize().x, this->backImg.GetTextureSize().y);
		this->backImg.Draw(draw, src);
	}
	else
	{
		Box2D draw(OGge->camera->GetPos(), this->size);
		draw.OffsetSize();
		Box2D src(0.f, 0.f, this->backImg.GetTextureSize().x, this->backImg.GetTextureSize().y);
		this->backImg.Draw(draw, src);
	}
}

void Back::SetScroll(bool flag)
{
	this->isScroll = flag;
	if (this->isScroll)
	{
		auto map = OGge->GetTask<Map>("map");
		if (map)
		{
			if (this->mapSize)
			{
				delete this->mapSize;
			}
			if (this->Center)
			{
				delete this->Center;
			}
			if (this->Xsize)
			{
				delete this->Xsize;
			}
			if (this->Tsize)
			{
				delete this->Tsize;
			}
			if (this->texPos)
			{
				delete this->texPos;
			}
			//�}�b�v�T�C�Y�擾
			this->mapSize = new Vec2(map->mapSize);
			*this->mapSize *= 64.f;
			//���S�擾
			this->Center = new float;
			*this->Center = this->mapSize->x / 2.f;
			//���S�ɃJ���������݂����ꍇ�̉��̃J�����ɉf��Ȃ��l���v�Z
			this->Xsize = new float;
			*this->Xsize = *this->Center - (OGge->camera->GetSize().x / 2.0f);
			//�e�N�X�`���̃T�C�Y���v�Z�ō쐬
			this->size.x = this->mapSize->x + OGge->camera->GetSize().x / 2.f;
			this->size.y = this->size.x * 9.f / 16.f;
			//�e�N�X�`���̃T�C�Y�ƃJ�����̃T�C�Y�̍����v�Z
			this->Tsize = new float;
			*this->Tsize = (this->size.x - OGge->camera->GetSize().x) / 2.0f;
			//�e�N�X�`���̈ʒu���v�Z�ŋ��߂�
			this->texPos = new Vec2(OGge->camera->GetPos().x - ((OGge->camera->GetPos().x / *this->Xsize) * *this->Tsize), OGge->camera->GetPos().y - (this->size.y - OGge->camera->GetSize().y));
		}
	}
}

Back::SP Back::Create(const std::string& path, Vec2& size_, bool flag)
{
	Back::SP to = Back::SP(new Back(path, size_));
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

Back::SP Back::Create(const std::string& path, float x, float y, bool flag)
{
	Back::SP to = Back::SP(new Back(path, x, y));
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

Back::SP Back::Create(const std::string& path, int x, int y, bool flag)
{
	Back::SP to = Back::SP(new Back(path, x, y));
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