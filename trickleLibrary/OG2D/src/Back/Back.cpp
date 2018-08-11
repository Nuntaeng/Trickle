#include "Back.h"
#include "Map\Map.h"
#include <string>
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
	cloud = new Cloud*[2];
	for (int i = 0; i < 2; ++i) {
		cloud[i] = new Cloud("cloud" + std::to_string(i+1) + ".png", 0.5f + i);
	}
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
	for (int i = 0; i < 2; ++i) {
		delete cloud[i];
	}
	delete[] cloud;
}

void Back::UpDate()
{
	for (int i = 0; i < 2; ++i) {
		cloud[i]->Update();
	}
}

void Back::Render2D()
{
	if (this->isScroll)
	{

		if (this->texPos)
		{
			//�摜�̕`��ʒu���}�b�v�T�C�Y�ƃJ�����̈ʒu�ƃJ�����̃T�C�Y���狁�߂�
			*this->texPos = Vec2(OGge->camera->GetPos().x - ((OGge->camera->GetPos().x / *this->Xsize) * *this->Tsize), OGge->camera->GetPos().y - (this->size.y - OGge->camera->GetSize().y) + 320);
		}
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
	//�_
	for (int i = 0; i < 2; ++i) {
		cloud[i]->Render();
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
			this->size.x = this->mapSize->x + OGge->camera->GetSize().x / 4.f;
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

Cloud::Cloud(const std::string & path, float speed) {
	Initialize(path, speed);
}

Cloud::~Cloud() {}

void Cloud::Initialize(const std::string & path, float speed) {
	cloudImg.Create(path);
	cloudPos[0] = Vec2(0, 0);
	cloudPos[1] = Vec2(-1920, 0);
	this->speed = speed;
}

void Cloud::Update() {
	for (int i = 0; i < 2; ++i) {
		cloudPos[i].x += speed;
		if (cloudPos[i].x >= 1920) {
			cloudPos[i].x = -1920;
		}
	}
}

void Cloud::Render() {
	for (int i = 0; i < 2; ++i) {
		Box2D draw(cloudPos[i].x, cloudPos[i].y, 1920.f, 1080.f);
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 720);
		cloudImg.Draw(draw, src);
	}
}