#include "ClearUI.h"
bool ClearUI::Initialize(Vec2& pos)
{
	//�^�X�N�֘A
	this->taskName = "ClearUI";
	this->Init(taskName);

	//��{�̏��
	CreateObject(Cube, pos, Vec2(512, 96), 0);

	//�摜�֘A
	this->SetDrawOrder(0.1f);
	image.Create((std::string)"ClearUI.png");
	//�g��@�\�֘A
	this->ResetVolume();
	this->ResetVolumeFlag();

	std::cout << "�N���AUI�@������" << std::endl;
	return true;
}
void ClearUI::ResetVolume()
{
	this->Volume = 0;
}
void ClearUI::ResetVolumeFlag()
{
	this->Volumefinish = false;
}
void ClearUI::SetVolumeFlag(bool flag)
{
	this->Volumefinish = flag;
}
bool ClearUI::GetVolumeFlag()
{
	return this->Volumefinish;
}
bool ClearUI::Finalize()
{
	image.Finalize();
	return true;
}
void ClearUI::UpDate()
{
	this->MoveVolume();
}
void ClearUI::MoveVolume()
{
	this->Volume += 0.02f;
	if (this->Volume >= 1.0f)
	{
		this->Volume = 1.0f;
		//�g�傪�I������
		this->SetVolumeFlag(true);
	}
}
void ClearUI::Render2D()
{
	Box2D draw((this->position.x + this->Scale.x) - (this->Scale.x * (this->Volume / 1.0f)), (this->position.y + this->Scale.y) - (this->Scale.y * (this->Volume /1.0f)),this->Scale.x * (this->Volume * (this->Volume / 1.0f)) , this->Scale.y * (this->Volume * (this->Volume / 1.0f)));
	draw.OffsetSize();

	//�g��@�\
	Box2D src = this->Src;
	src.x = src.x * (src.x * (this->Volume / 1.f));
	src.y = src.y * (src.y * (this->Volume / 1.f));
	src.OffsetSize();

	image.Draw(draw, src);
}
ClearUI::ClearUI()
{
	std::cout << "�N���AUI�@����" << std::endl;
}
ClearUI::~ClearUI()
{
	this->Finalize();
	std::cout << "�N���AUI�@���" << std::endl;
}
ClearUI::SP ClearUI::Create(Vec2& pos, bool flag)
{
	ClearUI::SP to = ClearUI::SP(new ClearUI());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}