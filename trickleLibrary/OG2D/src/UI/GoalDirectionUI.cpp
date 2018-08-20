#include "GoalDirectionUI.h"

#include "Player/Player.h"
#include "Goal/Goal.h"

GoalDirection::GoalDirection()
{
	this->taskName = "GoalDirection";	
}
GoalDirection::~GoalDirection()
{
	this->Finalize();
}
bool GoalDirection::Initialize(std::shared_ptr<GameObject> target_)
{
	this->Init(this->taskName);

	this->CreateObject(Cube, OGge->camera->GetPos(), Vec2(96, 96), 0.f);
	this->target = target_;

	this->SetDrawOrder(1.f);

	return true;
}
bool GoalDirection::Finalize()
{
	return true;
}
void GoalDirection::SetPos(Vec2& pos)
{
	this->position = pos;
}
void GoalDirection::SetTextrue(Texture* image_ , Texture* flower)
{
	this->image = image_;
	this->flower = flower;
}
void GoalDirection::UpDate()
{
	if (!(std::static_pointer_cast<Goal>(target))->GetClear())
	{
		//�S�[���̊p�x�����߂܂�
		this->TargetDirecition();
		this->CameraPosUpDate();
	}
}
void GoalDirection::Render2D()
{
	
	if (!(std::static_pointer_cast<Goal>(target))->GetClear())
	{
		if (!this->WindowOuterCheck() && !OGge->GetPause())
		{
			{
				Box2D draw = { this->position,this->Scale };
				draw.OffsetSize();
				Box2D src = this->srcbase;
				this->image->Rotate(this->angle);
				this->image->Draw(draw, src);
			}
			{
				Box2D draw = { this->position , this->Scale };
				draw.OffsetSize();
				Box2D src = this->srcflower;
				switch (std::static_pointer_cast<Goal>(target)->GetColor())
				{
				case Paint::PaintColor::Red:
					src.x = 256;
					break;
				case Paint::PaintColor::Blue:
					src.x = 256 * 2;
					break;
				case Paint::PaintColor::Purple:
					src.x = 256 * 3;
					break;
				default:
					break;
				}
				src.OffsetSize();
				this->flower->Draw(draw, src);
			}
		}
	}
}
bool GoalDirection::WindowOuterCheck()
{
	/* �E�B���h�E�ƃS�[���̓����蔻������܂� */
	GameObject windowsize;
	windowsize.CreateObject(Cube, OGge->camera->GetPos(),OGge->camera->GetSize(), 0);
	//�����܂��ȓ����蔻�����
	if (!windowsize.IsObjectDistanceCheck(this->target->position, this->target->Scale))
	{
		return false;
	}
	return windowsize.CubeHit(*this->target);

}
//�S�[���̊p�x�����߂܂�
void GoalDirection::TargetDirecition()
{
	auto player = OGge->GetTask<Player>("Player");

	if (player != nullptr && this->target != nullptr)
	{
		float rad = std::atan2f(player->position.x + player->Scale.x / 2 - (this->target->position.x + this->target->Scale.x / 2), player->position.y + player->Scale.y / 2 - (this->target->position.y + this->target->Scale.y));
		this->angle = this->ToDeg(-rad);
	}
}
float GoalDirection::ToDeg(float radian)
{
	float d = (float)(radian * 180.f / PI);
	if (d < 0)
	{
		d += 360.f;
	}
	return d;
}
void GoalDirection::CameraPosUpDate()
{
	auto player = OGge->GetTask<Player>("Player");
	//Player�ƃS�[���̍������߂�
	Vec2 inside =
	{
		(player->position.x + player->Scale.x / 2) - (target->position.x + target->Scale.x / 2)  ,
		(player->position.y + player->Scale.y / 2) - (target->position.y + target->Scale.y / 2)
	};

	//�`�攻���`�𐶐�
	Box2D drawchecker = { OGge->camera->GetPos().x + target->Scale.x / 2 + target->Scale.x * 0.15f, OGge->camera->GetPos().y + target->Scale.y / 2 + target->Scale.y * 0.15f , OGge->camera->GetSize().x - target->Scale.x - target->Scale.x * 0.3f, OGge->camera->GetSize().y - target->Scale.y - target->Scale.y * 0.3f};
	drawchecker.OffsetSize();
	OG::LineHitDraw(&drawchecker);

	//�����������߂�
	float xx = inside.x*inside.x;
	float yy = inside.y*inside.y;
	float r = sqrt(xx + yy);

	//�����������
	float nowx = target->position.x + target->Scale.x / 2;
	float nowy = target->position.y + target->Scale.y / 2;

	Vec2 pos;
	for (int i = 0; i < r; i++) 
	{
		//���X��Player�̕����֐����������Ă���
		nowx += inside.x / r;
		nowy += inside.y / r;
		Box2D d = { nowx ,nowy, 5.0f, 5.0f };
		d.OffsetSize();
		OG::LineHitDraw(&d);
		{
			//�����蔻��
			if (d.x >= drawchecker.x && d.y >= drawchecker.y)
			{
				if (d.w <= drawchecker.w && d.h <= drawchecker.h)
				{
					pos.x = nowx - this->Scale.x / 2;
					pos.y = nowy - this->Scale.y / 2;
					this->position = pos;
					return;
				}
			}
		}
	}
}
GoalDirection::SP GoalDirection::Create(std::shared_ptr<GameObject> target, bool flag)
{
	GoalDirection::SP to = GoalDirection::SP(new GoalDirection());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(target))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
bool GoalDirection::Intersectionhit(Box2D& windowdraw ,Vec2& pos)
{
	auto player = OGge->GetTask<Player>("Player");
	Box2D draw(player->position.x + player->Scale.x / 2, player->position.y + player->Scale.y / 2, pos.x, pos.y);
	draw.OffsetSize();
	//��`���I�u�W�F�N�g��������
	GameObject hitobject;
	hitobject.CreateObject(Cube, Vec2(player->position.x + player->Scale.x / 2, player->position.y + player->Scale.y / 2), Vec2(pos.x, pos.y), 0);

	GameObject object;
	object.CreateObject(Cube, Vec2(windowdraw.x, windowdraw.y), Vec2(windowdraw.h, windowdraw.w),0);

	return false;
}




//float direction;
//////���������߂�
//Vec2 inside = {};
//inside = Vec2{ (int)player->position.x - (int)OGge->in->mouse.GetPos().x  , (int)player->position.y - (int)OGge->in->mouse.GetPos().y};
////���K��
//float sqtr = std::sqrt(inside.x * inside.x + inside.y * inside.y);
//inside = Vec2{ inside.x / sqtr , inside.y / sqtr };
////�p�x�𒲂ׂ�
//Vec2 wegiht = Vec2{ std::cosf(inside.x),-std::sinf(inside.y) };
//float directionY = std::atan2f(wegiht.y, wegiht.x);
////�㉺����
//if (directionY >= 0)
//{
//	direction += 180;
//}
//else
//{
//	direction = 0;
//}

//this->angle = direction;