#pragma once

#include "OGSystem\OGSystem.h"

class Load : public TaskObject
{
	Texture image;	//画像
	Box2D draw;		//毎回宣言するよりここに書いてある方が処理が軽くなるのではの検証をしています。
	Box2D src;		//
	Texture tex;
public:
private:
	void UpDate();
	Color* color;
public:
	Load();
	virtual ~Load();
	typedef std::shared_ptr<Load> SP;
	static SP Create(bool = true);
	void Draw();		//強制描画を行う
	void Render2D();
};