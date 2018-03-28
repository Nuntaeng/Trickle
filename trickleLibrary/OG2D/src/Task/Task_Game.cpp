#include "Task_Game.h"
void Game::Initialize()
{
	std::cout << "Game初期化" << std::endl;
	player.Initialize();
	back.Initialize();
	map.LoadMap("prototype.txt");
	
	// 当たり判定テスト
	for (auto& i : map.hitBase)
		for (auto& j : i)
			if (j.objectTag.length() > 0)
				cm.AddChild(&j);
	cm.AddChild(&player);
	cm.AddChild(&player.footBase);
	auto w = new Water();
	water.push_back(w);
	cm.AddChild(water[water.size() - 1]);
	this->timecnt = 0;
}

TaskFlag Game::UpDate()
{
	//timecnt++;
	//if (timecnt >= 60)
	//{
	//	timecnt = 0;
	//	//Water生成
	//	auto w = new Water();
	//	water.push_back(w);
	//	cm.AddChild(water[water.size() - 1]);
	//}
	for (int i = 0; i < water.size(); ++i)
	{
		water[i]->Update();
	}
	player.UpDate();
	cm.Run();
	if (Input::KeyInputOn(Input::A))
	{
		gameEngine->camera->Move(Vec2(-3.0f, 0.0f));
	}
	if (Input::KeyInputOn(Input::D))
	{
		gameEngine->camera->Move(Vec2(+3.0f, 0.0f));
	}
	if (Input::KeyInputOn(Input::W))
	{
		gameEngine->camera->Move(Vec2(0.0f, -3.0f));
	}
	if (Input::KeyInputOn(Input::S))
	{
		gameEngine->camera->Move(Vec2(0.0f, 3.0f));
	}
	TaskFlag nowtask = Task_Game;
	if (Input::KeyInputUp(Input::SPACE))
	{
		nowtask = Task_Title;
	}
	return nowtask;
}

void Game::Render2D()
{
	for (int i = 0; i < water.size(); ++i)
	{
		water[i]->Render();
	}
	player.Render();
	map.MapRender();
	back.Render();
}

void Game::Finalize()
{
	std::cout << "Game解放" << std::endl;
	back.Finalize();
	map.Finalize();
	player.Finalize();
	for (int i = 0; i < water.size(); ++i)
	{
		water[i]->Finalize();
	}
	while (!this->water.empty())
	{
		this->water.pop_back();
	}
	cm.Destroy();
}