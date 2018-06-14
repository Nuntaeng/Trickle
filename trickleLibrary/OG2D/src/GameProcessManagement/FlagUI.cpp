#include "FlagUI.h"

#include "Effect\SterEffect.h"
#include "GameProcessManagement.h"

#include <bitset>
bool FlagUI::Initialize(Vec2& pos,int& target)
{
	//�^�X�N�֘A
	this->taskName = "Ster";
	this->Init(taskName);

	//��{�̏��
	CreateObject(Cube, pos, Vec2(64, 64), 0);
	//�t���O������i�[����
	Resultflag = 0;
	this->SetResultflag();
	//�^�[�Q�b�g�t���O�̐ݒ�
	targetflag = target;

	

	//Easing�֘A
	/*easingX.ResetTime();
	easingX.Init();
	this->PrePos = position;*/

	//�摜�֘A
	flagactive = false;			//�摜��ύX����ۂɔ�����r����
	SetDrawOrder(0.1f);
	image[0].Create((std::string)"Ster.png");
	image[1].Create((std::string)"SterB.png");

	//�g��@�\�֘A
	this->ResetVolume();

	//�G�t�F�N�g�֘A
	this->effectEnd = false;

	std::cout << "�~�b�V�����B���G�t�F�N�g�@������" << std::endl;
	return true;
}
void FlagUI::SetSendPos(Box2D& draw)
{
	this->SendPos.x = draw.x;
	this->SendPos.y = draw.y;
}
void FlagUI::ResetVolume()
{
	this->PrePos = this->position;
	this->ReSize = this->Scale;
	this->ScaleVolume = { 2.5f,2.5f };
	this->isScaleed = false;
}
void FlagUI::UpDate()
{
	//�t���O��������
	this->FalgJudge(targetflag);
	this->MoveVolume();
	//this->EasingMove();
}
//void FlagUI::EasingMove()
//{
//	position.x = this->easingX.back.Out(6.5f, 0, this->PrePos.x, easingX.Time(6.5f));
//}
//bool FlagUI::EasingEnd()
//{
//	return !easingX.isplay();
//}
void FlagUI::Render2D()
{
	//�ʒu�̒���
	Box2D draw(this->Center.x + this->Scale.x + this->PrePos.x / 2, this->Center.y + this->Scale.y + this->PrePos.y / 5 , this->Scale.x * this->ScaleVolume.x, this->Scale.y * this->ScaleVolume.y);
	this->SetSendPos(draw);
	draw.OffsetSize();
	
	//�g��@�\
	Box2D src = this->Src;
	src.OffsetSize();
	
	if (flagactive && effectEnd)
	{
		image[0].Draw(draw, src);
	}
	else
	{
		image[1].Draw(draw, src);
	}
}
bool FlagUI::Finalize()
{
	for (int i = 0; i < 2; ++i)
	{
		image[i].Finalize();
	}
	return true;
}
bool FlagUI::is_Scale()
{
	return this->isScaleed;
}
Vec2 FlagUI::GetPos()
{
	return this->SendPos;
}
void FlagUI::MoveVolume()
{
	this->ScaleVolume.x -= 0.033f;
	this->ScaleVolume.y -= 0.033f;
	if (this->ScaleVolume.x <= 1.0f)
	{
		this->ScaleVolume.x = 1.0f;
	}
	if (this->ScaleVolume.y <= 1.0f)
	{
		this->ScaleVolume.y = 1.0f;
	}

	if (this->ScaleVolume.x <= 1.0f && this->ScaleVolume.y <= 1.0f)
	{
		this->isScaleed = true;
		return;
	}
	this->ResetCenter();
}
void FlagUI::ResetCenter()
{
	
	//�{�������Z���� ���̃T�C�Y�@�~�@�{��
	this->ReSize.x = this->Scale.x *  this->ScaleVolume.x;
	this->ReSize.y = this->Scale.y *  this->ScaleVolume.y;

	//���W�l�ɉe����������@(���T�C�Y�@�|�@�O��s�������T�C�Y) * 2
	this->position.x -= (this->ReSize.x - this->PreSize.x) * 2;
	this->position.y -= (this->ReSize.y - this->PreSize.y) * 2;

	//�S�̂����߂�	���W�@�|�@���T�C�Y
	this->Center = this->position + this->ReSize;

	//���W�̒����l�����߂�
	this->Center.x = this->Center.x / 2.f;
	this->Center.y = this->Center.y / 2.f;

	this->PreSize = this->ReSize;
}
void FlagUI::SetResultflag()
{
	//���U���g���ɊJ�����f�[�^����~�b�V�����̃t���O���ڂ𔲂��o��
	auto result = OGge->GetTask<Result>("Result");

	if (result != nullptr)
	{
		this->Resultflag = result->GetFlag();
	}
}
void FlagUI::FalgJudge(int judge)
{
	int flag = 0;
	flag |= Resultflag;
	//�Ώۂ̃t���O�ƈ�v���Ă���
	if ((flag & judge) == judge)
	{
		flagactive = true;
	}
}
bool FlagUI::GetFlag()
{
	return this->flagactive;
}
void FlagUI::SetEffectEnd()
{
	this->effectEnd = true;
}
bool FlagUI::GetEffectEnd()
{
	return this->effectEnd;
}
FlagUI::FlagUI()
{
	std::cout << "�~�b�V�����B���G�t�F�N�g�@����" << std::endl;
}
FlagUI::~FlagUI()
{
	this->Finalize();
	std::cout << "�~�b�V�����B���G�t�F�N�g�@���" << std::endl;
}
FlagUI::SP FlagUI::Create(Vec2& pos,int target,bool flag_)
{
	FlagUI::SP to = FlagUI::SP(new FlagUI());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos,target))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
