#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

#include "Task\Task_Result.h"
class FlagUI : public GameObject, public TaskObject
{
public:

public:
	void FalgJudge(int);
private:
	Texture image[2];
	int Resultflag;
	bool flagactive;
	void SetResultflag();
	const Box2D Src = Box2D(0, 0, 322, 322);
public:
	std::string taskName;
	virtual ~FlagUI();
	typedef std::shared_ptr<FlagUI> SP;
	static FlagUI::SP Create(Vec2& pos,bool = true);
	FlagUI();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize(Vec2& pos);		//初期化処理
	void UpDate();					//更新処理
	void Render2D();				//描画処理
	bool Finalize();				//解放処理
};