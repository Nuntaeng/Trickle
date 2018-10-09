/**
* @file GimmickBase.h
* @brief Fan,Heater,Icemachineの基底クラスを定義する
* @author yokota0717
* @date 2018.10.9
*/

#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

/**
* @brief Fan,Heater,Icemachineの基底クラス
* @details スイッチでオンオフを切り替えるギミックはこのクラスを継承すること
*/
class GimmickBase
{
	std::string taskName;
	GameObject hitBase;
	bool active;

public:
	/**
	* @brief ギミックの向き
	*/
	enum Dir {
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};
	GimmickBase();
	~GimmickBase();

	/**
	* @brief タスクオブジェクト生成窓口
	* @param pos ギミックの本体を表示する座標(画像左上)
	* @param range 当たり判定矩形の大きさ
	* @param dir 本体の向き
	* @param active 生成した時点で動いているかどうか
	*/
	std::shared_ptr<GimmickBase> Create(Vec2 pos, Vec2 range, Dir dir, bool active);

	/**
	* @brief 自身の稼働状態を反転させる
	*/
	void changeActive();

	/**
	* @brief ある状態の水に効果を与える
	* @details Fan：水蒸気を横に動かす、Heater：氷→水,水→水蒸気、Icemachine：水→氷
	*/
	void affectWater();
};

