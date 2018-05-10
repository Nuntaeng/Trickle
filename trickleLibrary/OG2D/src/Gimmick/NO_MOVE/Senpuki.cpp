#include "Senpuki.h"
using namespace std;

//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする

bool Fan::Initialize(Vec2 pos, float r, Fan::Dir d, bool activ)
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "Senpuki";			//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	position = pos;
	objectTag = "Fan";
	range = r;
	dir = d;
	active = activ;
	if (dir == Fan::Dir::LEFT)
	{
		CreateObject(Cube, pos, Vec2(64.0f, 64.0f), 0.0f);
		strength = -3;
		this->WindHitBase.CreateObject(Cube, Vec2(pos.x - (64 * 8), pos.y), Vec2(64 * 8, 64), 0.0f);
	}
	else
	{
		CreateObject(Cube, pos, Vec2(64.0f, 64.0f), 0.0f);
		strength = 3;
		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * 16, 64), 0.0f);
		//this->WindHitBase.CreateObject(Cube, Vec2(0,0), Vec2(0,0), 0.0f);
	}


	return true;
}
void Fan::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------

	for (auto& w : water)
	{
		//当たり判定
		//if (this->WindHitBase.hit(*w))
		//{//スイッチの状態
		//	Motion(w);
		//}
	}
}

void Fan::Render2D()
{
	//--------------------
	//描画時に行う処理を記述
	//--------------------
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();
	Box2D src(0, 0, 256, 256);
	if (this->dir == Fan::Dir::LEFT)
	{
		int k = src.w;
		src.w = src.x;
		src.x = k;
	}
	this->image->Draw(draw, src);
}

bool Fan::Finalize()
{
	//-----------------------------------------
	//このオブジェクトが消滅するときに行う処理を記述
	//-----------------------------------------

	//次のタスクを作るかかつアプリケーションが終了予定かどうか
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		switches.clear();
		this->water.clear();
		//自分を消す場合はKillを使う
		this->Kill();
	}
	return true;
}
void Fan::SetTexture(Texture* tex)
{
	this->image = tex;
}
void Fan::SetWaterPool(Water* w)
{
	this->water.push_back(w);
}
bool Fan::DeleteWaterPool(Water* w)
{
	for (auto id = this->water.begin(); id != this->water.end(); ++id)
	{
		if ((*id) == w)
		{
			this->water.erase(id);
			return true;
		}
	}
	return false;
}
void Fan::SetWindRange(Vec2& b)
{
	this->WindHitBase.Scale = b;
}
void Fan::AddSwitch(Switch* swit)
{
	switches.push_back(swit);
}
void Fan::ChangeState()
{
	active = !active;
}
void Fan::Motion(Water* w)
{
	if (active)
	{
		if (w->GetState() == Water::State::GAS)
		{
			//w->position.x += strength; // Left -1 Right 1
			w->MovePos(Vec2(strength, 0));
		}
	}
}
//----------------------------
//ここから下はclass名のみ変更する
//ほかは変更しないこと
//----------------------------
Fan::Fan()
{

}

Fan::~Fan()
{
	this->Finalize();
}

Fan::SP Fan::Create(bool flag_, Vec2 pos, float r, Fan::Dir d, bool activ)
{
	Fan::SP to = Fan::SP(new Fan());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos,r,d,activ))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
