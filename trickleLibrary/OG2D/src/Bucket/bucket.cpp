#include "Bucket\bucket.h"
#include "Water\water.h"
#include "Map\Map.h"
#include "Player\Player.h"
Bucket::Bucket() {
	this->invi = 0;
}

Bucket::Bucket(Vec2& pos) {
	this->position = pos;
	this->invi = 0;
	//�T�E���h�̃t�@�C����
	putsoundname = "bucket-put1.wav";
	dropsoundname = "spoil.wav";
}

Bucket::~Bucket() {
	this->Finalize();
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{

	}
}

bool Bucket::Initialize(Vec2& pos)
{
	this->position = pos;
	gravity = Vec2(0.0f, 0.0f);
	hold = false;
	this->capacity = 0;
	this->CreateObject(Objform::Cube, pos, Vec2(64.f, 64.f), 0.f);
	this->objectTag = "Bucket";
	//�T�E���h��A�����ČĂ΂Ȃ����߂̃t���b�O
	putsoundplay = true;

	//�T�E���h�̐����@�������ڂ���
	soundD.create(dropsoundname, false);
	soundD.volume(1.0f);
	OGge->soundManager->SetSound(&soundD);

	//�T�E���h�̐��� �o�P�c��u����
	soundP.create(putsoundname, false);
	soundP.volume(1.0f);
	OGge->soundManager->SetSound(&soundP);


	tex.Create((std::string)"bucket.png");
	__super::Init((std::string)"bucket");
	__super::SetDrawOrder(0.5f);
	this->IsOutCheck = false;
	this->WaterOutTime = 0;
	return true;
}

void Bucket::UpDate() {
	if (this->invi > 0)
	{
		--this->invi;
	}
	if (hold)
	{
		//�T�E���h���Đ�����̂�����
		putsoundplay = true;
		gravity.y = 0.0f;
	}
	gravity.y += 5.0f;
	if (this->BucketWaterCreate())	//�o�P�c���琅���o������
	{
		if (!this->IsOutCheck)
		{
			auto player = OGge->GetTask<Player>("Player");
			player->SetMotion(Player::Motion::Spill);
			this->IsOutCheck = true;
		}
	}
	if (this->IsOutCheck)
	{
		this->WaterOutTime++;
		if (this->WaterOutTime > 10)
		{
			
			//�������ڂ����̍Đ�
			soundD.play();

			auto water = Water::Create(Vec2(this->position.x + (this->Scale.x / 2) -32.f, this->position.y - 20.f));
			water->SetSituation(Water::Situation::Normal);
			water->SetScale(Vec2(64, 64));
			water->SetWaterVolume(capacity);     //�������鐅�̗ʂɁA�o�P�c�ɓ����Ă������̗ʂ𔽉f������
			this->capacity = 0.f;
			//70�J�E���g���͎��̐��������󂯂Ȃ�
			this->invi = 70;
			auto tex = rm->GetTextureData((std::string)"waterTex");
			if (tex)
			{
				water->SetTexture(tex);
			}
			else
			{
				water->Kill();
			}
			this->IsOutCheck = false;
			this->WaterOutTime = 0;
		}
	}
	//���������������̏���
	this->WaterIsHitCheck();
	if (!hold)
	{
		CheckMove(gravity);
	}
}

void Bucket::Render2D() {
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
	Box2D src(GetSpriteCrop());
	src.OffsetSize();
	tex.Rotate(this->angle);
	tex.Draw(draw, src);
}

bool Bucket::Finalize() {
	tex.Finalize();
	return true;
}

Box2D Bucket::GetSpriteCrop() const {
	if (capacity > 0.f && capacity < 1.0f)
	{
		return BUCKET_WATER;
	}
	else if (capacity >= 1.0f)
	{
		return BUCKET_WATERMAX;
	}
	return BUCKET_NOTHING;
}

//-----------------------------------------------------------------------------------------------
//�߂荞�܂Ȃ�����
void Bucket::CheckMove(Vec2 &e_)
{
	//x���ɂ���
	while (e_.x != 0.0f)
	{
		float preX = this->position.x;

		if (e_.x >= 1.0f)
		{
			this->position.x += 1.0f;
			e_.x -= 1.0f;
		}
		else if (e_.x <= -1.0f)
		{
			this->position.x -= 1.0f;
			e_.x += 1.0f;
		}
		else
		{
			this->position.x += e_.x;
			e_.x = 0.0f;
		}

		if (isObjectCollided())
		{
			this->position.x = preX;
			break;
		}
	}
	//y���ɂ���
	while (e_.y != 0.0f)
	{
		float preY = this->position.y;

		if (e_.y >= 1.0f)
		{
			this->position.y += 1.0f;
			e_.y -= 1.0f;
		}
		else if (e_.y <= -1.0f)
		{
			this->position.y -= 1.0f;
			e_.y += 1.0f;
		}
		else
		{
			this->position.y += e_.y;
			e_.y = 0.0f;
		}

		if (isObjectCollided())
		{
			this->position.y = preY;
			break;
		}
	}
}

bool Bucket::isObjectCollided() {
	bool hitMap = false;
	bool hitBlock = false;
	auto map = OGge->GetTask<Map>("map");
	auto block = OGge->GetTask<Block>("block");
	if (map) {
		hitMap = map->MapHitCheck(*this);
		/*if (hitMap == false)
		{
			for (int y = 0; y < map->mapSize.y; ++y)
			{
				for (int x = 0; x < map->mapSize.x; ++x)
				{

					{
						if (map->_arr[y][x] != 23 && map->_arr[y][x] != 24)
						{
							hitMap = map->hitBase[y][x].hit(*this);
						}
					}
				}
			}
		}*/
		if (hitMap == true)
		{
			if (putsoundplay)    //�T�E���h�����Đ��������ǂ����̔��f
			{
				soundP.play();
				putsoundplay = false;
			}
		}
	}
	if (block) {
		hitBlock = block->hit(*this);
	}
	return hitMap || hitBlock;

	//if (!map) {
	//	return false;
	//}
	//auto block = OGge->GetTask<Block>("block");
	//if (!block)
	//	return false;

	//return map->MapHitCheck(*this) ||
	//	block->hit(*this);
}

void Bucket::HoldCheck(bool flag)
{
	this->hold = flag;
}


bool Bucket::GetHold() const
{
	return this->hold;
}

bool Bucket::BucketWaterCreate()
{
	return this->hold && OGge->in->down(In::B3) && this->capacity > 0.f;
}

Bucket::SP Bucket::Create(Vec2& pos, bool flag_)
{
	auto to = Bucket::SP(new Bucket(pos));
	if (to)
	{
		to->me = to;
		if (flag_)
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

void Bucket::WaterIsHitCheck()
{
	if (this->invi > 0 || this->capacity >= 1.0f)
	{
		return;
	}
	auto waters = OGge->GetTasks<Water>("water");
	for (int i = 0; i < (*waters).size(); ++i)
	{
		if (this->hit(*(*waters)[i]))
		{
			this->capacity += (*waters)[i]->waterMove();
		}
	}
}