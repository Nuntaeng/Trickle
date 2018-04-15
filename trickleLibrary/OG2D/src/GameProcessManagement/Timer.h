#pragma once
#include "Object\Object.h"
#include <iostream>

//__________________________
//|                      //|
//|履歴　2018/04/14 横尾 //|
//|履歴　2018/04/15 横尾 //|
//|______________________//|

class Timer : public Object
{
public:
	/*
	コンストラクタ
	■引数　なし
	■戻り　なし
	*/
	Timer();


	/*
	デストラクタ
	■引数　なし
	■戻り　なし
	*/
	~Timer();


	/*
	タイマーのゼロクリアをする
	■引数　なし
	■戻り　なし
	*/
	void Initialize();


	/*
	タイマーの関数をまとめて呼び出す
	■引数　なし
	■戻り　なし
	*/
	void Update();


	/*
	タイマーの時間を1フレームづつ計測する
	■引数　なし
	■戻り　なし
	*/
	void Instrumentation();

	/*
	指定したタイマーの時間をコマンドプロンプトに出力する
	■引数　Timer& 出力したいタイマー
	■戻り　なし
	*/
	void Instrumentation_output(Timer&);

private:
	int frame_time;                                //フレーム時間を格納する
	int frame_time_hours;                          //〇時間
	int frame_time_min;                            //〇分
	int frame_time_sec;                            //〇秒

	//ミリ秒は未実装　1秒　=　1000ミリ秒  4分23秒17みたい感じにしたかったら・・・実装します
private:
	/*
	タイマーの時間をコマンドプロンプトに出力する
	■引数　なし
	■戻り　なし
	*/
	void Instrumentation_output();
};