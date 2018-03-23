#include "Task_Game.h"
void Game::Initialize()
{
	std::cout << "Game������" << std::endl;
	player.Initialize();
	back.Initialize();
}

TaskFlag Game::UpDate()
{
	player.UpDate();

	TaskFlag nowtask = Task_Game;
	if (Key::KeyInputUp(GLFW_KEY_SPACE))
	{
		nowtask = Task_Title;
	}
	return nowtask;
}

void Game::Render2D()
{
	player.Render();
	back.Render();
}

void Game::Finalize()
{
	std::cout << "Game���" << std::endl;
	back.Finalize();
	player.Finalize();
}