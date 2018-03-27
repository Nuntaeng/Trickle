#include "Task_Game.h"
void Game::Initialize()
{
	std::cout << "Game������" << std::endl;
	player.Initialize();
	back.Initialize();
	map.LoadMap("test.txt");
	cm.AddChild(&player);
}

TaskFlag Game::UpDate()
{
	cm.Run();
	player.UpDate();
	TaskFlag nowtask = Task_Game;
	if (Input::KeyInputUp(Input::SPACE))
	{
		nowtask = Task_Title;
	}
	return nowtask;
}

void Game::Render2D()
{
	player.Render();
	map.MapRender();
	back.Render();
}

void Game::Finalize()
{
	std::cout << "Game���" << std::endl;
	back.Finalize();
	map.Finalize();
	player.Finalize();
}