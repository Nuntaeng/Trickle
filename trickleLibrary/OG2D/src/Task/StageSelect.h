#pragma once

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class StageSelect : public TaskObject
{
	//アニメーション用class
	class Animation
	{
		Easing easing_x;
		Easing easing_y;
		Vec2 StartPos;
		Vec2 EndPos;
	public:
		Vec2 Move();
		Vec2 Move(const float time);
		Animation();
		void Set(Vec2&, Vec2&);
		bool isPlay() const;
	};

	//入り口の右側左側を判定させる用
	enum Direction
	{
		LEFT,
		RIGTH,
	};

	Animation camera_anim;

	Texture Testdoor;		//ドアの画像

	std::string soundname;     //サウンドのファイル名格納

	std::vector<std::pair<Direction, float>> Entrance;	//扉に対しての向きとその座標
	//各処理管理
	enum Mode
	{
		Non,
		from1,
		from2,
		from3,
		from4,
		End,
	};
	Mode mode;
	Mode preMode;
	//各処理関数
	void From1();
	void From2();
	void From3();
	void From4();

	int timeCnt;
	int nowPos;
	void ModeCheck();
	bool CheckTime(int);
	void GateClose();
	Easing camera_x;
	Easing camera_y;

public:
	StageSelect();
	virtual ~StageSelect();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();

	enum State
	{
		Tutorial,
		Stage1,
		Stage2,
		ToTitle,
	};
	State state;
	Sound* sound;

	typedef std::shared_ptr<StageSelect> SP;
	static SP Create(bool = true);
};