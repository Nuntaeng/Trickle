//______________________________//
//|動くギミック  スイッチ      |//
//|履歴：2018/03/29 横尾	   |//
//|履歴：2018/03/31 横尾　     |//
//|履歴：2018/04/01 横尾       |//
//|履歴: 2018/04/02 横尾       |//
//|履歴: 2018/04/03 横尾       |//
//|履歴：2018/04/07 横尾       |//
//|履歴：2018/05/24 横尾       |//
//|____________________________|//
#pragma once
//必要読み込みファイル
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

#include "Player\Player.h"
class Switch : public GameObject, public TaskObject
{
	//-------------------------------------------
	//各自で制作するときに使用するものはここに記述する
	//-------------------------------------------
public:
	bool GetisON();
private:
	std::shared_ptr<Player>target;
	bool is_on;
	//------------------
	//固定化されている処理
	//------------------
private:
	bool CheckHit();
	void ON_OFF();
	void SetTarget(std::shared_ptr<Player> &target);
public:
	std::string taskName;
	virtual ~Switch();
	typedef std::shared_ptr<Switch> SP;
	static Switch::SP Create(Vec2& pos,std::shared_ptr<Player> &target,bool is_on,bool = true);
	Switch();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize(Vec2& pos, std::shared_ptr<Player>&target,bool is_on);	//初期化処理
	void UpDate();				//更新処理
	void Render2D();			//描画処理
	bool Finalize();			//解放処理
};