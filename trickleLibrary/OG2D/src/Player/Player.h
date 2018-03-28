#pragma once
//______________________________//
//|プレイヤ                     |//
//|履歴：2018/03/23横田	       |//
//|履歴：2018/03/26ジュン　       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Player :public Object
{
public:
	Texture playerimg;
	std::string fileName = "player.png";
	bool hitcheck;

	void Initialize();
	void UpDate();
	void Render();
	void Finalize();
	//☆☆☆☆//-----------------------------------------------------------------------------
	//追加変数//-----------------------------------------------------------------------------
	//☆☆☆☆//-----------------------------------------------------------------------------
	Vec2 est;
	//ジャンプ状態判定
	bool jumpFlag;
	//移動スピード
	const float MOVE_SPEED = 10.f;
	//ジャンプパワー
	const float JUMP_POWER = -20.f;
	//重力加速度
	const float GRAVITY = 0.98f;
	//プレイヤーの向きを表す名前空間
	enum Direction
	{
		LEFT,
		RIGHT,
	};
	//向きを格納する変数
	Direction direction;
	//☆☆☆☆//-----------------------------------------------------------------------------
	//クラスのメンバ関数
	//☆☆☆☆//-----------------------------------------------------------------------------
	//ジャンプのプロトタイプ宣言
	void JumpMove();
	//足元接触判定のプロトタイプ宣言
	void CheckFoot();
};


