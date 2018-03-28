#include "Task_Game.h"
void Game::Initialize()
{
	std::cout << "Game初期化" << std::endl;
	player.Initialize();
	back.Initialize();
	map.LoadMap("test.txt");
	if (water.Initialize())
	{
		cm.AddChild(&water);
	}
	else
	{
		std::cout << "WaterInitializeError" << std::endl;
	}

	// 当たり判定テスト
	for (auto& i : map.hitBase)
		for (auto& j : i)
			if (j.objectTag.length() > 0)
				cm.AddChild(&j);
	cm.AddChild(&player);
	
}

TaskFlag Game::UpDate()
{
	player.UpDate();
	cm.Run();
	water.Update();
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
	water.Render();
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
}