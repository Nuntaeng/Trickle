#include "Task_Result.h"
//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
#include "Task\StageSelect.h"
#include "GameProcessManagement\FlagUI.h"
#include "Player\ResultPlayer.h"
#include "GameProcessManagement\ClearUI.h"
#include "GameProcessManagement\GoalTimeUI.h"
#include "GameProcessManagement\MissionUI.h"
#include "GameProcessManagement\FrameTime.h"
#include "Effect/SterEffect.h"
#include "GameProcessManagement/GameProcessManagement.h"
#include "Effect\SterEffect.h"

///285 

bool Result::Initialize()
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "Result";		//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	//フラグの設定
	this->Result_DataInput();

	this->image.Create((std::string)"back.png");
	this->maptile.Create((std::string)"tile.jpg");

	SetDrawOrder(0.0f);

	Vec2 camerasize = OGge->camera->GetSize();
	Vec2 windowsize = OGge->window->GetSize();
	//カメラのサイズとウィンドウにおけるアスペクト比の計算
	Vec2 aspect = Vec2(camerasize.x / windowsize.x, camerasize.y / windowsize.y);

	//生成フラグをリセットする
	this->createtask.ResetCreateFlag();
	this->createtask.ResetNextFlag();
	this->createtask.SetNextFlag(CreateFlag::Timeui);

	//リザルト画面に表示にする
	auto player = ResultPlayer::Create(Vec2(-96, (int)camerasize.y - 50 - 96), Vec2(3, 0));
	auto mission = MissionUI::Create();
	std::cout << "結果画面処理　初期化" << std::endl;
	return true;
}

void Result::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------
	//タイトルシーンへ遷移
	
	//条件をまずチェックする
	this->UI_Think();
	//フラグによってCreateする
	this->UI_Create();

	auto resultplayer = OGge->GetTask<ResultPlayer>("ResultPlayer");
	if (!resultplayer)
	{
		if (OGge->in->down(In::B2))
		{
			Kill();
		}
	}
	
}
void Result::Render2D()
{
	//--------------------
	//描画時に行う処理を記述
	//--------------------
	Vec2 camerasize = OGge->camera->GetSize();
	{
		Box2D draw(Vec2(0, 0), camerasize);
		draw.OffsetSize();
		Box2D src = this->backSrc;
		src.OffsetSize();
		image.Draw(draw, src);
	}
	{
		int count = 0;
		for (int y = camerasize.y - 50; y <= camerasize.y; y += 64)
		{
			for (int x = 0; x <= camerasize.x / 64; ++x)
			{
				Box2D draw(Vec2(x * 64, (int)camerasize.y - 50 + count * 64), Vec2(64, 64));
				draw.OffsetSize();
				Box2D src = this->maptileSrc;
				src.OffsetSize();
				maptile.Draw(draw, src);
			}
			count++;
		}
		
	}
}
bool Result::Finalize()
{
	//-----------------------------------------
	//このオブジェクトが消滅するときに行う処理を記述
	//-----------------------------------------
	//次のタスクを作るかかつアプリケーションが終了予定かどうか
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		image.Finalize();
		maptile.Finalize();

		auto player = OGge->GetTasks<ResultPlayer>("ResultPlayer");
		auto ster = OGge->GetTasks<FlagUI>("Ster");
		auto clear = OGge->GetTasks<ClearUI>("ClearUI");
		auto effect = OGge->GetTasks<SterEffect>("SterEffect");
		auto goaltime = OGge->GetTasks<GoalTimeUI>("GoalTimeUI");
		auto mission = OGge->GetTasks<MissionUI>("MissionUI");
		auto frametime = OGge->GetTasks<FrameTimeUI>("FrameTimeUI");

		for (auto id = (*ster).begin(); id != (*ster).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*player).begin(); id != (*player).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*clear).begin(); id != (*clear).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*goaltime).begin(); id != (*goaltime).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*effect).begin(); id != (*effect).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*frametime).begin(); id != (*frametime).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*mission).begin(); id != (*mission).end(); ++id)
		{
			(*id)->Kill();
		}
		auto stageselect = StageSelect::Create();
	}
	return true;
}
void Result::CreateTask::ResetCreateFlag()
{
	this->createflag &= ~this->createflag;
}
void Result::CreateTask::ResetNextFlag()
{
	this->nextflag &= ~this->nextflag;
}
void Result::CreateTask::SetCreateFlag(CreateFlag flag)
{
	this->createflag |= flag;
}
void Result::CreateTask::SetNextFlag(CreateFlag flag)
{
	this->nextflag |= flag;
}
void Result::UI_Think()
{
	switch (this->createtask.nextflag)
	{
	case 1 << 0:
		if ((this->createtask.nextflag & 0x0F) == CreateFlag::Timeui)
		{
			auto player = OGge->GetTask<ResultPlayer>("ResultPlayer");
			if (player != nullptr)
			{
				//Playerが止まったら・・・
				if (player->GetResetWalkStop())
				{
					this->createtask.SetCreateFlag(CreateFlag::Timeui);
				}
			}
		}
		break;
	case 1 << 1:
		if ((this->createtask.nextflag & 0x0F) == CreateFlag::Starui)
		{
			auto frametimeUI = OGge->GetTasks<FrameTimeUI>("FrameTimeUI");
			for (auto id = (*frametimeUI).begin(); id != (*frametimeUI).end(); ++id)
			{
				//タイムUIの演出が終了したら・・・
				if ((*id)->GetIsPlay())
				{
					this->createtask.SetCreateFlag(CreateFlag::Starui);
				}
			}
		}
		break;
	case 1 << 2:
		if ((this->createtask.nextflag & 0x0F) == CreateFlag::Effect)
		{
			auto sters = OGge->GetTasks<FlagUI>("Ster");
			for (auto id = (*sters).begin(); id != (*sters).end(); ++id)
			{
				if ((*id)->EasingEnd())
				{
					this->createtask.SetCreateFlag(CreateFlag::Effect);
				}
			}

		}
		break;
	case 1 << 3:
		if ((this->createtask.nextflag & 0x0F) == CreateFlag::Clearui)
		{
			auto sters = OGge->GetTasks<FlagUI>("Ster");
			std::vector<bool> flag;
			for (auto id = (*sters).begin(); id != (*sters).end(); ++id)
			{
				flag.push_back((*id)->GetEffectEnd());
			}
			//全てのEffectの演出が終了したら
			for (auto id = (*sters).begin(); id != (*sters).end(); ++id)
			{
				if (std::all_of(flag.begin(), flag.end(), [](bool flag) {return flag == true; }))
				{
					this->createtask.SetCreateFlag(CreateFlag::Clearui);
				}
			}
		}
		break;
	default:
		break;
	}
}
void Result::UI_Create()
{
	///注意！！　ここはフラグをセットして1フレームのみ動かす関数です。
	Vec2 camerasize = OGge->camera->GetSize();
	Vec2 windowsize = OGge->window->GetSize();
	//カメラのサイズとウィンドウにおけるアスペクト比の計算
	Vec2 aspect = Vec2(camerasize.x / windowsize.x, camerasize.y / windowsize.y);

	switch (this->createtask.createflag)
	{
	case 1 << 0:
		//Playerが一定のところまで歩いたら・・・
		if ((this->createtask.createflag & CreateFlag::Timeui) == CreateFlag::Timeui)
		{
			auto goaltime = GoalTimeUI::Create(Vec2(camerasize.x * 0.15f, camerasize.y * 0.2f));
			for (int i = 0; i < 5; ++i)
			{
				auto time = FrameTimeUI::Create(Vec2(goaltime->position.x + goaltime->Scale.x + (20 + i * 64), goaltime->position.y + 20), i, FrameTime);
			}
			//生成するフラグをリセットする
			this->createtask.ResetCreateFlag();
			this->createtask.ResetNextFlag();
			//次に生成するタスク
			this->createtask.SetNextFlag(CreateFlag::Starui);
		}
		break;
	case 1 << 1:
		if ((this->createtask.createflag & CreateFlag::Starui) == CreateFlag::Starui)
		{
			int selectflag[3] = {GameProcessManagement::Flag4,GameProcessManagement::Flag3,GameProcessManagement::Flag2};

			for (int i = 0; i < 3; ++i)
			{
				auto ster = FlagUI::Create(Vec2((camerasize.x / 2 - 200) + 100 * (i + 1) , camerasize.y * 0.5f), selectflag[i]);	
			}
			//フラグのリセット
			this->createtask.ResetCreateFlag();
			this->createtask.ResetNextFlag();
			//次に生成するタスク
			this->createtask.SetNextFlag(CreateFlag::Effect);
		}
		break;
	case 1 << 2:
		if ((this->createtask.createflag & CreateFlag::Effect) == CreateFlag::Effect)
		{
			auto sters = OGge->GetTasks<FlagUI>("Ster");

			//最初だけは条件なしで生成する
			{
				int count = 0;
				for (auto id = sters->begin(); id != sters->end(); ++id, ++count)
				{
					if (count == 0)
					{
						auto effect = SterEffect::Create((*id));
					}
					else
					{
						auto Effect = OGge->GetTasks<SterEffect>("SterEffect");
						if (!Effect)
						{
							continue;
						}
						auto effect = SterEffect::Create((*id), *(Effect->begin() + count - 1));
					}
				}
			}
			//生成するフラグをリセットする
			this->createtask.ResetCreateFlag();
			this->createtask.ResetNextFlag();
			//次に生成するタスク
			this->createtask.SetNextFlag(CreateFlag::Clearui);
		}
		break;
	case 1 << 3:
		if ((this->createtask.createflag & CreateFlag::Clearui) == CreateFlag::Clearui)
		{
			auto clearui = ClearUI::Create(Vec2(camerasize.x * 0.70f, camerasize.y / 2));
			//フラグのリセット
			this->createtask.ResetCreateFlag();
			this->createtask.ResetNextFlag();
			//次に生成するタスク
			this->createtask.SetNextFlag(CreateFlag::NON);
		}
		break;
	default:
		break;
	}	
}
int Result::to_String(std::string& text)
{
	std::istringstream ss;
	ss = std::istringstream(text);

	int num = atoi(text.c_str());
	ss >> num;

	return num;
}
void Result::Result_DataInput()
{
	std::string GameFalg;			//ゲームフラグ
	//データの読み込み
	std::ifstream fin(TimeFilePath);

	if (!fin)
	{
		return;
	}
	//読み込んだデータを入れておく変数
	std::string line;
	//ファイル全体のテキストを読み込み
	while (std::getline(fin, line))
	{
		//文字列を操作するための入力クラス、直接アクセスする
		std::istringstream _fin(line);
		//一字書き込み変数
		std::string text;
		
		//タイムの書き込み
		std::getline(_fin, text, ',');
		(std::stringstream)text >> FrameTime;

		//ステージごとのフラグを書き込む
		std::string nowStagenumber;
		int nowStage = 0;

		//フラグの書き込み
		while (std::getline(_fin, text, ','))
		{
			if (text == "Stage1")
			{
				nowStagenumber = text.substr(5);
				//文字列からint型にする
				 nowStage = this->to_String(nowStagenumber);
			}
			else if(text == "Stage2")
			{
				nowStagenumber = text.substr(5);
				//文字列からint型にする
				nowStage = this->to_String(nowStagenumber);
			}

		}

	}
	//改行か終了時点までの文字の文字列をlineに入れる
	std::getline(fin, line);
	//文字列を操作するための入力クラス、直接アクセスする
	std::istringstream _fin(line);
	//一字書き込み変数
	std::string text;
	//_finに入っている文字列から','までの文字をtextにいれる
	std::getline(_fin, text, ',');
	//textのデータを変数にいれる
	(std::stringstream)text >> FrameTime;
	std::getline(_fin, text, ',');
	(std::stringstream)text >> GameFalg;


	fin.close();
}
//----------------------------
//ここから下はclass名のみ変更する
//ほかは変更しないこと
//----------------------------
Result::Result()
{
	std::cout << "結果画面処理　生成" << std::endl;
	//カメラ座標を元に戻す
	OGge->camera->SetPos(Vec2(0, 0));
	//カメラのサイズを元に戻す
	OGge->camera->SetSize(Vec2(60 * 16 , 60 * 9));
	FrameTime = 0;
}

Result::~Result()
{
	this->Finalize();
	std::cout << "結果画面処理　解放" << std::endl;
}

Result::SP Result::Create(bool flag_)
{

	Result::SP to = Result::SP(new Result());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize())
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}