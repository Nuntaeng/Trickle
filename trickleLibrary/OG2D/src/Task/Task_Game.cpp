#include "Task_Game.h"
#define ADD_FUNCTION(a) \
	[](std::vector<Object*>* objs_) { a(objs_); }
//-------------------------------------------------------------------------------------------------
void Game::Initialize()
{
	Vec2 bucketpos[2] = {
		{ 100,250 },
		{ 200,250 }
	};

	Vec2 blockpos = Vec2(1536, 100);  //1536,100


	std::cout << "Game" << std::endl;

	//バケツ初期処理
	bucket.Initialize(bucketpos[0]);
	cm.AddChild(&bucket);
	//ブロック初期処理
	block.Initialize(blockpos);
	cm.AddChild(&block);
	//背景初期処理
	back.Initialize();
	//マップ初期処理
	map.LoadMap("prototype.txt");
	//水初期処理
	this->waterTex.TextureCreate("watertest.png");
	//プレイヤー初期処理
	this->playerTex.TextureCreate("player.png");
	player.Initialize();
	this->player.SetTexture(&this->playerTex);
	for (int y = 0; y < map.mapSize.y; ++y)
	{
		for (int x = 0; x < map.mapSize.x; ++x)
		{
			player.AddObject(&map.hitBase[y][x]);
		}
	}
	player.AddBucket(&this->bucket);
	player.AddBlock(&this->block);
	this->timecnt = 0;
	//cm.AddChild(&bucket);
	for (auto& i : map.hitBase)
		for (auto& j : i)
			if (j.objectTag.length() > 0)
				cm.AddChild(&j);
	gameEngine->DebugFunction = true;
	goal.Initialize();
	cm.AddChild(&goal);

	//横田さん風

	Vec2 fanpos[2] = { Vec2(64 * 11,64 * 7), Vec2(64 * 19,64 * 10) };
	float fanrange[2] = { 18,6 };
	for (int i = 0; i < 2; ++i) {
		swich[i].Initialize(Vec2(64 * (10 + i * 2), 64 * 14));
		fan[i].Initialize(fanpos[i], fanrange[i], (i == 0) ? Fan::Dir::RIGHT : Fan::Dir::LEFT, (i == 0) ? true : false);
		cm.AddChild(&swich[i]);
		cm.AddChild(&fan[i]);
	}
	for (int i = 0; i < 2; ++i) {
		swich[i].SetTarget(&fan[0]);
		swich[i].SetTarget(&fan[1]);
	}
	swich[0].ON_OFF();

	for (int i = 0; i < 2; ++i)
	{
		cm.AddChild(&seihyouki[i].hitBace);
	}
	for (int i = 0; i < 2; ++i)
	{
		if (seihyouki[i].Create(Vec2(64 * 6 + i * 64, 64 * 10), Vec2(64, 64)))
		{
			seihyouki[i].Set_pointa();
		}
	}

	gameprocess.Set_Goal(&goal);
	gameprocess.Initialize();
	auto w = new Water(Vec2(150, 100));
	w->SetTexture(&this->waterTex);
	for (int y = 0; y < map.mapSize.y; ++y)
	{
		for (int x = 0; x < map.mapSize.x; ++x)
		{
			w->AddObject(&map.hitBase[y][x]);
		}
	}
	for (int i = 0; i < this->water.size(); ++i)
	{
		w->AddObject(this->water[i]);
		this->water[i]->AddObject(w);
	}
	water.push_back(w);
	cm.AddChild(water[water.size() - 1]);
}
//-------------------------------------------------------------------------------------------------
TaskFlag Game::Update()
{
	gameprocess.Update();
	
	timecnt++;
	if (timecnt >= 120)
	{
		timecnt = 0;
		//Water?ｿｽ?ｿｽ?ｿｽ?ｿｽ
		auto w = new Water(Vec2(150, 100));
		w->SetTexture(&this->waterTex);
		for (int y = 0; y < map.mapSize.y; ++y)
		{
			for (int x = 0; x < map.mapSize.x; ++x)
			{
				w->AddObject(&map.hitBase[y][x]);
			}
		}
		for (int i = 0; i < this->water.size(); ++i)
		{
			w->AddObject(this->water[i]);
			this->water[i]->AddObject(w);
		}
		water.push_back(w);
		cm.AddChild(water[water.size() - 1]);
	}

	
//-------------------------------------------------------------------------------------------------
	if (gameEngine->in.down(Input::in::B3, 0)) {
		if (bucket.capacity > 0) {
			Water* sizuku = bucket.Spill();
			sizuku->SetTexture(&this->waterTex);
			for (int y = 0; y < map.mapSize.y; ++y)
			{
				for (int x = 0; x < map.mapSize.x; ++x)
				{
					sizuku->AddObject(&map.hitBase[y][x]);
				}
			}
			for (int i = 0; i < this->water.size(); ++i)
			{
				sizuku->AddObject(this->water[i]);
				this->water[i]->AddObject(sizuku);
			}
			water.push_back(sizuku);
			//cm += sizuku;
			cm.AddChild(water[water.size() - 1]);
		}
	}
//-------------------------------------------------------------------------------------------------
	for (int i = 0; i < water.size(); ++i)
	{
		water[i]->Update();
		if (water[i]->GetSituation() == Water::Situation::CreaDelete)
		{
			cm - water[i];
			water[i]->Finalize();
			delete water[i];
			for (int j = 0; j < water.size(); ++j)
			{
				if (i != j)
				{
					water[j]->DeleteObject(water[i]);
				}
			}
			water.erase(water.begin() + i);
		}
	}
	player.Update();

	block.Update(map, block, player);
	bucket.Update(map, bucket);

	block.PlCheckHit(player, block);
	
	for (int i = 0; i < 2; ++i)
	{
		seihyouki[i].CheckHit();
	}

	cm.Run();
	if (gameEngine->in.key.on(Input::KeyBoard::A))
	{
		gameEngine->camera->MovePos(Vec2(-3.0f, 0.0f));
	}
	if (gameEngine->in.key.on(Input::KeyBoard::D))
	{
		gameEngine->camera->MovePos(Vec2(+3.0f, 0.0f));
	}
	if (gameEngine->in.key.on(Input::KeyBoard::W))
	{
		gameEngine->camera->MovePos(Vec2(0.0f, -3.0f));
	}
	if (gameEngine->in.key.on(Input::KeyBoard::S))
	{
		gameEngine->camera->MovePos(Vec2(0.0f, 3.0f));
	}
	if (gameEngine->in.Pad_Connection) {
		Vec2 cameraest = { 0,0 };
		cameraest.x = gameEngine->in.pad[0].axis(Input::GamePad::AXIS_RIGHT_X) *10.f;
		cameraest.y = gameEngine->in.pad[0].axis(Input::GamePad::AXIS_RIGHT_Y) * 10.f;
		cameraest.y = -cameraest.y;
		gameEngine->camera->MovePos(cameraest);
	}
	if (gameEngine->in.key.down(Input::KeyBoard::U))
	{
		for (int i = 0; i < water.size(); ++i)
		{
			if (water[i]->GetState() == Water::State::LIQUID)
			{
				water[i]->SetState(Water::State::GAS);
			}
			else
			{
				water[i]->SetState(Water::State::LIQUID);
			}
		}
	}
	if (gameEngine->in.key.on(Input::KeyBoard::H))
	{
		bucket.position.x -= 3.0f;
	}
	if (gameEngine->in.key.on(Input::KeyBoard::K))
	{
		bucket.position.x += 3.0f;
	}
	if (gameEngine->in.key.down(In::I))
	{
		for (int i = 0; i < water.size(); ++i)
		{
			if (water[i]->GetState() == Water::State::LIQUID)
			{
				water[i]->SetState(Water::State::SOLID);
			}
			else
			{
				water[i]->SetState(Water::State::LIQUID);
			}
		}
	}

	//カメラ処理
	Camera_move();


	TaskFlag nowtask = Task_Game;
	nowtask = gameprocess.Goal_Event();
	if (gameEngine->in.down(Input::in::D2, 0))
	{
		nowtask = Task_Title;
	}
	return nowtask;
}
//-------------------------------------------------------------------------------------------------
void Game::Render2D()
{
	//背景描画
	back.Render();
	//マップチップの描画
	map.MapRender();
	//ブロック描画
	block.Render();
	//ゴール描画
	goal.Render();
	//バケツ描画
	bucket.Render();
	//プレイヤー描画
	player.Render();
	//水描画
	for (int i = 0; i < water.size(); ++i)
	{
		water[i]->Render();
	}
}
//-------------------------------------------------------------------------------------------------
void Game::Finalize()
{
	std::cout << "Game" << std::endl;
	block.Finalize();
	back.Finalize();
	map.Finalize();
	player.Finalize();
	goal.Finalize();
	//for (int i = 0; i < bucket.size(); ++i) {
	//	bucket[i]->Finalize();
	//}
	//for (int i = 0; i < bucket.size(); ++i)
	//{
	//	this->bucket.pop_back();
	//}
	bucket.Finalize();
	for (int i = 0; i < water.size(); ++i)
	{
		water[i]->Finalize();
		delete water[i];
	}
	water.clear();
	for (int i = 0; i < 2; ++i) {
		swich[i].Finalize();
		fan[i].Finalize();
	}
	this->waterTex.Finalize();
	this->playerTex.Finalize();
	cm.Destroy();
}
//-------------------------------------------------------------------------------------------------
//カメラ処理
void Game::Camera_move()
{
	//デバッグ用
	//std::cout << gameEngine->camera->GetSize().x << "//"<<gameEngine->camera->GetPos().x << std::endl;
	//カメラの移動
	gameEngine->camera->MovePos(player.GetEst());

	//カメラ処理
	Vec2 NowCameraPos = gameEngine->camera->GetPos();
	Vec2 NowCameraSize = gameEngine->camera->GetSize();

	//プレイヤーを画面中央
	float PlayerCenter_x = NowCameraSize.x / 2.0f;
	float PlayerCenter_y = NowCameraSize.y / 2.0f;
	//カメラ座標を求める
	float camera_x = float(player.position.x) - PlayerCenter_x;
	float camera_y = float(player.position.y) - PlayerCenter_y;
	//カメラの座標を更新
	NowCameraPos.x = camera_x;
	NowCameraPos.y = camera_y;


	//左右のスクロール範囲の設定(サイズの10分の1)
	float Boundary = NowCameraSize.x / 10.0f;
	//現在スクロール値とプレイヤーの座標の差を修正
	Vec2 NowPlayerPos = { player.position.x - NowCameraPos.x,player.position.y - NowCameraPos.y };
	//x座標
	if (NowPlayerPos.x < Boundary){
		NowCameraPos.x = NowPlayerPos.x - Boundary;
	}
	if (NowPlayerPos.x > NowCameraSize.x - Boundary){
		NowCameraPos.x = (NowPlayerPos.x + NowCameraPos.x) - NowPlayerPos.x + Boundary;
	}
	//y座標
	if (NowPlayerPos.y < Boundary){
		NowCameraPos.y = NowPlayerPos.y - Boundary;
	}
	if (NowPlayerPos.y > NowCameraSize.y - Boundary){
		NowCameraPos.y = (NowCameraSize.y + NowCameraPos.y) - NowPlayerPos.y + Boundary;
	}
	//画面外処理
	if (NowCameraPos.x < 0) {
		NowCameraPos.x = 0;
	}
	if (NowCameraPos.x + NowCameraSize.x > 34 * map.DrawSize.x) {
		NowCameraPos.x = (34 * map.DrawSize.x) - NowCameraSize.x;
	}
	if (NowCameraPos.y < 0) {
		NowCameraPos.y = 0;
	}
	if (NowCameraPos.y + NowCameraSize.y > 16 * map.DrawSize.y) {
		NowCameraPos.y = (16 * map.DrawSize.y) - NowCameraSize.y;
	}
	gameEngine->camera->SetPos(NowCameraPos);
}