#include "Switch.h"
using namespace std;

//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする

bool Switch::Initialize(Vec2 pos)
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "Switch";			//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

									//座標の設定
	position = pos;
	//当たり判定の実装
	CreateObject(Cube, position, Vec2(64, 64), 0.0f);
	//オブジェクトタグの追加
	objectTag = "Switch";
	//スイッチの切り替えフラグをONにする
	is_on = false;

	return true;
}
void Switch::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------
}

void Switch::Render2D()
{
	//--------------------
	//描画時に行う処理を記述
	//--------------------
	Box2D draw(this->position, this->Scale);
	draw.OffsetSize();

}

bool Switch::Finalize()
{
	//-----------------------------------------
	//このオブジェクトが消滅するときに行う処理を記述
	//-----------------------------------------
	
	//次のタスクを作るかかつアプリケーションが終了予定かどうか
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		targets.clear();
		image.Finalize();
		//自分を消す場合はKillを使う
		this->Kill();
	}
	return true;
}
bool Switch::isON()
{
	//切り替えフラグを返す
	return is_on;
}
void Switch::ON_OFF()
{
	//trueとfalseの切り替えフラグを切り替える
	is_on = !is_on;
	//スイッチのONOFFが切り替わった時だけターゲットのChangeState()を呼び出す
	for (auto t : targets)
	{
		if (t->objectTag == "Fan")
		{
			//スイッチを押すと・・・
			((Fan*)t)->ChangeState();
		}
	}
}
void Switch::SetTarget(GameObject* t)
{
	//あとで加熱器と製氷機のタグも追加すること
	if (t->objectTag != "Fan") { return; }
	targets.push_back(t);
}
//----------------------------
//ここから下はclass名のみ変更する
//ほかは変更しないこと
//----------------------------
Switch::Switch()
{

}

Switch::~Switch()
{
	this->Finalize();
}

Switch::SP Switch::Create(bool flag_, Vec2 pos)
{
	Switch::SP to = Switch::SP(new Switch());
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