//______________________________//
//|動くギミック  扇風機        |//
//|履歴：2018/03/29 横尾       |//
//|履歴：2018/03/30 横尾　     |//
//|履歴：2018/03/31 横尾       |//
//|履歴：2018/04/01 横尾       |//
//|____________________________|//

#pragma once
#include "Object\Object.h"
#include <vector>                                        //ステージによって変化する扇風機の座標を格納するため
//☆☆☆☆//
///判定をしたいギミックを追加する場合はここに記述する///
//☆☆☆☆//

#include "Water\water.h"                                 //水との当たり判定
#include "Switch.h"                                      //スイッチとの当たり判定・Switchの切り替えフラグ

class Senpuki : public Object
{
public:
	/*
	初期座標によって当たり判定矩形の生成・フラグの初期化・ラムダ式の当たり判定を行います。
	■ 引数   : Vec2 初期化座標値
	■ 戻り値 : bool 初期化成功したかを返します。（現状trueしか入りません）
	*/
	bool Initialize(Vec2);


	
	/*
	扇風機の更新処理
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	void UpDate();



	/*
	扇風機の解放処理
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	void Finalize();



	/*
	扇風機の描画処理（Mapで表示するのであまり意味がない）
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	void Render();                                       



	/*
	コンストラクタ　※何もすることありません
    ■ 引数   : なし
    ■ 戻り値 : なし
	*/
	explicit Senpuki();  



	/*
	コンストラクタ（Vec2　初期座標)
	■ 引数   : Vec2 扇風機の初期座標に設定する座標値
	■ 戻り値 : なし
	*/
	explicit Senpuki(Vec2 pos);



	/*
	デストラクタ　Object*をdeleteで削除します。
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	virtual ~Senpuki();



	/*
	Object* parent の指している場所がnullptrではないかをbool型で返します。
	■ 引数   : なし
	■ 戻り値 : bool
	*/
	bool HasParent() const;                              
				
	
	/*
	Swtich* parent に当たり判定に必要なクラスのアドレス値を代入します。
	■ 引数   : Switch* 当たり判定に必要なクラスのアドレス値
	■ 戻り値 : なし
	*/
	void SetParent(Switch* obj);


	/*
	Object* parent に当たり判定に必要なクラスのアドレス値を代入します。
	■ 引数   : Object* 当たり判定に必要なクラスのアドレス値
	■ 戻り値 : なし
	*/
	void SetParent(Object* obj);


	/*
	当たり判定をまとめた関数です。（初期化処理->ラムダ式の当たり判定の場所で採用）
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	void CheakHit();


	/*
	スイッチの切り替えフラグがあった場合に扇風機の座標を切り替えます。
	■ 引数   : const Vec2 切り替わる場所の座標値
	■ 戻り値 : Vec2
	*/
	Vec2 Switch_On_or_Off_pos(const Vec2);


	/*
	vectorに座標値を代入する関数です。
	■ 引数   : const Vec2 vectorにセット追加したい当たり判定座標値
	■ 戻り値 : なし
	*/
	void Set_Pos(const Vec2);


	/*
	スイッチの切り替えフラグによって座標値の再設定をします。
	■ 引数   : なし
	■ 戻り値 : なし
	*/
	void Switch_Swap();

	/*
	水蒸気状態になったときに扇風機によって移動をします。
	■ 引数   : Water& 水蒸気状態になった水のアドレス値
	■ 戻り値 : Vec2 移動するべき移動量
	*/
	Vec2 Water_Move(Water& o_);

	/*
	constを外す関数
	■ 引数   : typename T& constを外したいクラス
	■ 戻り値 : typaname T& constなし
	*/
	template<typename T>
	T& const_off(T& obj);
private:
	bool Water_flag;                                     //当たり判定格納変数
	bool Switch_ON_OFF;                                  //OFF(false) 上の扇風機　ON(true)　下の扇風機
	CollisionBox range;                                  //視野範囲（現在は使用していません）
	Object* parent;                                      //nullptrCheak関数
	std::vector<Vec2> Pos;                               //コンストラクタで送られたきた座標値を保存する格納倉庫
	Switch* switch_pointa;                               //switchのアドレス値を格納する変数
};