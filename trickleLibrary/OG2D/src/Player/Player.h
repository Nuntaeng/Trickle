#pragma once
//______________________________//
//|プレイヤ                    |//
//|履歴：2018/03/23横田	       |//
//|履歴：2018/03/26劉韋君　    |//
//|履歴：2018/03/29劉韋君　    |//
//|履歴：2018/03/30木務　    |//
//|____________________________|//
#include "CollisionManager\CollisionManager.h"
#include "Bucket\bucket.h"
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Player :public Object {

	struct Move {
		Vec2 est;
		float angle;
	};

	enum Direction
	{
		LEFT,
		RIGHT,
	};

	const std::array<std::string, 2> WALKABLE_CHIPS{
		"Floor",
		"Soil"
	};

private:
	void JumpMove();
	void CheckFoot();
	void CheckHead();
	void CheckLeft();
	void CheckRight();
	bool isWalkable(std::string);

public:
	void Initialize();
	void UpDate();
	void Render();
	void Finalize();

	/**
	 * @brief	当たり判定に登録する
	 * @param	当たり判定管理者のアドレス値
	 */
	void Register(CollisionManager*);

private:
	const std::string fileName = "player.png";
	const float MOVE_SPEED = 10.f;					//移動スピード
	const float JUMP_POWER = -20.f;					//ジャンプパワー
	const float GRAVITY = 0.98f;					//重力加速度

	Texture playerimg;
	Move move;
	Vec2 est;										//移動量
	Direction direction;							//向きを格納する変数

	// 判定に使ってる、深夜テンションなんでしんどい
	Object footBase;
	Object headBase;
	Object leftBase;
	Object rightBase;
};