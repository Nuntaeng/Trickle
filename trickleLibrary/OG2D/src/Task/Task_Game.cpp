#include "Task_Game.h"
void Game::Initialize()
{
	Vec2 bucketpos[2] = {
		{100,250},
		{200,250}
	};
	std::cout << "Game������" << std::endl;
	player.Initialize();
	/*for (int i = 0; i < 2; ++i)
	{
		auto w = new Bucket(Vec2(bucketpos[i].x, bucketpos[i].y));
		bucket.push_back(w);
	}
	for (int i = 0; i < bucket.size(); ++i)
	{
		bucket[i]->Initialize();
		cm.AddChild(bucket[i]);
	}*/
	bucket.Initialize(bucketpos[0]);
	cm.AddChild(&bucket);
	back.Initialize();
	map.LoadMap("prototype.txt");
	
	// �����蔻��e�X�g
	player.Register(&cm);
	//cm.AddChild(&bucket);
	for (auto& i : map.hitBase)
		for (auto& j : i)
			if (j.objectTag.length() > 0)
				cm.AddChild(&j);
	gameEngine->DebugFunction = true;
}

TaskFlag Game::UpDate()
{
	//timecnt++;
	//if (timecnt >= 120)
	if(Input::KeyInputDown(Input::Key::L))
	{
		timecnt = 0;
		//Water����
		auto w = new Water(Vec2(150, 100));
		water.push_back(w);
		cm.AddChild(water[water.size() - 1]);
	}

	// �e�X�g�p
	// ------------------------------------------
	if (Input::KeyInputDown(Input::Key::C)) {
		//for (int i = 0; i < 2; ++i) {
		//	if (bucket[i]->capacity > 0) {
		//		Water* sizuku = bucket[i]->Spill();
		//		water.push_back(sizuku);
		//		//cm += sizuku;
		//		cm.AddChild(water[water.size() - 1]);
		//	}
		//}
		if (bucket.capacity > 0) {
				Water* sizuku = bucket.Spill();
				water.push_back(sizuku);
				//cm += sizuku;
				cm.AddChild(water[water.size() - 1]);
		}
	}
	// ------------------------------------------
	for (int i = 0; i < water.size(); ++i)
	{
		water[i]->Update();
		if (water[i]->GetSituation() == Water::Situation::CreaDelete)
		{
			cm - water[i];
			water[i]->Finalize();
			water.erase(water.begin() + i);
		}
	}
	player.UpDate();
	/*for (int i = 0; i < 2; ++i) {
		player.TakeBucket(bucket[i]);
	}*/
	player.TakeBucket(&bucket);

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
	if (Input::KeyInputDown(Input::U))
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
	if (Input::KeyInputOn(Input::H))
	{
		bucket.position.x -= 3.0f;
	}
	if (Input::KeyInputOn(Input::K))
	{
		bucket.position.x += 3.0f;
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
	/*for (int i = 0; i < bucket.size(); ++i) {
		bucket[i]->Render();
	}*/
	bucket.Render();
	map.MapRender();
	back.Render();
}

void Game::Finalize()
{
	std::cout << "Game���" << std::endl;
	back.Finalize();
	map.Finalize();
	player.Finalize();
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
	}
	while (!this->water.empty())
	{
		this->water.pop_back();
	}
	cm.Destroy();
}