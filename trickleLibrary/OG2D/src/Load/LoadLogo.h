#pragma once

#include "OGSystem\OGSystem.h"

class Load : public TaskObject
{
public:
	enum Fead
	{
		In, Out
	};
private:
	Texture image;	//画像
	Box2D draw;		//毎回宣言するよりここに書いてある方が処理が軽くなるのではの検証をしています。
	Box2D src;		//
	Texture tex;
	Color* color;
	Fead mode;
	std::vector<std::string> deleteObject;
public:
	Load();
	virtual ~Load();
	typedef std::shared_ptr<Load> SP;
	static SP Create(bool = true);
	void Draw();		//強制描画を行う
	void Render2D() override;
	void PauseUpDate() override;
	void UpDate() override;
	void Set(const Fead&);
	Fead Get() const;
	void AddObject(const std::string&);
};