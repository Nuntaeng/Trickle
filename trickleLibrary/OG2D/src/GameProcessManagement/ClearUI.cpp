//#include "ClearUI.h"
//bool ClearUI::Initialize(Vec2& pos)
//{
//	//�^�X�N�֘A
//	this->taskName = "ClearUI";
//	this->Init(taskName);
//
//	//��{�̏��
//	CreateObject(Cube, pos, Vec2(256, 96), 30.f);
//
//
//	//�摜�֘A
//	this->SetDrawOrder(0.1f);
//	image.Create((std::string)"ClearUI.png");
//	//�g��@�\�֘A
//	this->ResetVolume();
//
//	std::cout << "�N���AUI�@������" << std::endl;
//	return true;
//}
//void ClearUI::ResetVolume()
//{
//	this->Volumefinish = false;
//	this->PreSize = this->Scale;
//	this->ReSize = {};
//	this->ScaleVolume = {};
//}
//void ClearUI::SetVolumeFlag(bool flag)
//{
//	this->Volumefinish = flag;
//}
//bool ClearUI::GetVolumeFlag()
//{
//	return this->Volumefinish;
//}
//bool ClearUI::Finalize()
//{
//	image.Finalize();
//	return true;
//}
//void ClearUI::UpDate()
//{
//	this->MoveVolume();
//}
//void ClearUI::ResetCenter() 
//{
//	//�{�������Z���� ���̃T�C�Y�@�~�@�{��
//	this->ReSize.x = this->Scale.x *  this->ScaleVolume.x;
//	this->ReSize.y = this->Scale.y *  this->ScaleVolume.y;
//
//	//���W�l�ɉe����������@(���T�C�Y�@�|�@�O��s�������T�C�Y) * 2
//	this->position.x -= (this->ReSize.x - this->PreSize.x) * 2;
//	this->position.y -= (this->ReSize.y - this->PreSize.y) * 2;
//
//	//�S�̂����߂�	���W�@�|�@���T�C�Y
//	this->Center = this->position + this->ReSize;
//
//	//���W�̒����l�����߂�
//	this->Center.x = this->Center.x / 2.f;
//	this->Center.y = this->Center.y / 2.f;
//
//	//���T�C�Y�f�[�^��ۑ����Ă���
//	this->PreSize = this->ReSize;
//}
//void ClearUI::MoveVolume()
//{
//	this->ScaleVolume.x += 0.033f;
//	this->ScaleVolume.y += 0.033f;
//	if (this->ScaleVolume.x >= 1.0f)
//	{
//		this->ScaleVolume.x = 1.0f;
//	}
//	if (this->ScaleVolume.y >= 1.0f)
//	{
//		this->ScaleVolume.y = 1.0f;
//	}
//	if (this->ScaleVolume.x >= 1.0f && this->ScaleVolume.y >= 1.0f)
//	{
//		this->SetVolumeFlag(true);
//	}
//	//�Čv�Z������
//	this->ResetCenter();
//}
//void ClearUI::Render2D()
//{
//	//��������
//	Box2D draw(this->Center.x + this->Scale.x - 20, this->Center.y + this->Scale.y , this->Scale.x * this->ScaleVolume.x, this->Scale.y * this->ScaleVolume.y);
//	draw.OffsetSize();
//
//	//�g��@�\
//	Box2D src = this->Src;
//	src.OffsetSize();
//
//	image.Draw(draw, src);
//}
//ClearUI::ClearUI()
//{
//	std::cout << "�N���AUI�@����" << std::endl;
//}
//ClearUI::~ClearUI()
//{
//	this->Finalize();
//	std::cout << "�N���AUI�@���" << std::endl;
//}
//ClearUI::SP ClearUI::Create(Vec2& pos, bool flag)
//{
//	ClearUI::SP to = ClearUI::SP(new ClearUI());
//	if (to)
//	{
//		to->me = to;
//		if (flag)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}