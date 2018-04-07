#include "Task_Game.h"
void Game::Initialize()
{
	Vec2 bucketpos[2] = {
		{100,250},
		{200,250}
	};
	Vec2 gimmickpos[6]
	{
		{ 64 * 19,64 * 8 },     //�X�C�b�`�@��
		{ 64 * 18,64 * 15 },    //���M�� ��
		{ 64 * 11,64 * 7 },     //��@ ��
		{ 64 * 19 ,64 * 10 },   //��@ ��
		{ 64 * 12 ,64 *14 },	//�X�C�b�`�@��
		{ 64 * 19,64 * 15 },    //���M��@�E
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
	goal.Initialize();
	cm.AddChild(&goal);

	//�����蔻���̏����ŃN���X�̎Q�ƂɕK�v�ȃf�[�^���擾����
	senpuki.SetParent(&map);                    //map�̃A�h���X�l���i�[����
	for (int i = 0; i < 2; ++i)
	{
		senpuki.SetParent(&switch_[i], i);      //Switch�̃A�h���X�l���i�[���� &switch_[0]
	}
	switch_[0].SetParent(&player);              //Player�̃A�h���X�l���擾����Switch�N���X��Player*�ɑ������
	switch_[1].SetParent(&player);              //�����A�h���X�l�������Ă���
	switch_[0].SetParent(&senpuki);             //��@�̃A�h���X�l���Q�Ƃ���
	switch_[1].SetParent(&senpuki);             //��@�̃A�h���X�l���Q�Ƃ���


												//�X�e�[�W��M�~�b�N����������ꍇ�̍��W�l��\�ߐݒ肵�Avector�ɑ������

	senpuki.Set_Pos(gimmickpos[2]);             //��@�̏�̍��W�l��vector�ɓo�^����
	senpuki.Set_Pos(gimmickpos[3]);             //��@�̉��̍��W�l��vector�ɓo�^����
	switch_[0].Set_Pos(gimmickpos[0]);          //�X�C�b�`�̏�̍��W�l��vector�ɓo�^����
	switch_[1].Set_Pos(gimmickpos[4]);          //�X�C�b�`�̉��̍��W�l��vector�ɓo�^����
	//kanetuki.Input_Pos(gimmickpos[1]);          //���M�@�̍��W�l��vector�ɓo�^����
	//kanetuki.Input_Pos(gimmickpos[5]);          //���M�@�̍��W�l��vector�ɓo�^����
	seihyouki.Input_Pos(gimmickpos[1]);         //������

	//�M�~�b�N�̏�����

	senpuki.Initialize(gimmickpos[2]);			//��@�̏����������Ɉڂ�iVec2 ��@�̍��W�j
	switch_[0].Initlaize(gimmickpos[0],&switch_[0]);        //Switch�N���X�̏���������������(Vec2 �������W)
	switch_[1].Initlaize(gimmickpos[4],&switch_[1]);        //Switch�N���X�̏���������������(Vec2 �������W)
	//kanetuki.Initialize();                                  //���M�@�𓮂���
	seihyouki.Initialize();

												//�����蔻���`��o�^����
	cm.AddChild(switch_);                       //Switch�̃A�h���X��vector objs��puth.back()���� &switch[0]
	cm.AddChild(&switch_[1]);                   //Switch�̃A�h���X2�ڂ�puth.back()����
	cm.AddChild(&senpuki.range);                //����͈͂̃A�h���X���Q�Ƃ���
	//cm.AddChild(&kanetuki.hitBace[0]);          //�����蔻���`��o�^����
	//cm.AddChild(&kanetuki.hitBace[1]);          //�����蔻���`��o�^����
	cm.AddChild(&seihyouki.hitBace);            //�����蔻���`��o�^����
}

TaskFlag Game::UpDate()
{
	timecnt++;
	if (timecnt >= 120)
	//if(gameEngine->input.DOWN(Input::Key::L))
	{
		timecnt = 0;
		//Water����
		auto w = new Water(Vec2(150, 100));
		water.push_back(w);
		cm.AddChild(water[water.size() - 1]);
	}

	// �e�X�g�p
	// ------------------------------------------
	if (gameEngine->input.down(Input::in::B3, 0)/* || gameEngine->gamepad[0].DOWN(GLFW_JOYSTICK_3)*/) {
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
	if (gameEngine->input.keyboard.on(Input::KeyBoard::A))
	{
		gameEngine->camera->Move(Vec2(-3.0f, 0.0f));
	}
	if (gameEngine->input.keyboard.on(Input::KeyBoard::D))
	{
		gameEngine->camera->Move(Vec2(+3.0f, 0.0f));
	}
	if (gameEngine->input.keyboard.on(Input::KeyBoard::W))
	{
		gameEngine->camera->Move(Vec2(0.0f, -3.0f));
	}
	if (gameEngine->input.keyboard.on(Input::KeyBoard::S))
	{
		gameEngine->camera->Move(Vec2(0.0f, 3.0f));
	}
	if (gameEngine->input.Pad_Connection) {
		Vec2 cameraest = { 0,0 };
		cameraest.x = gameEngine->input.gamepad[0].axis(Input::GamePad::AXIS_RIGHT_X) *10.f;
		cameraest.y = gameEngine->input.gamepad[0].axis(Input::GamePad::AXIS_RIGHT_Y) * 10.f;
		cameraest.y = -cameraest.y;
		gameEngine->camera->position += cameraest;
	}
	if (gameEngine->input.keyboard.down(Input::KeyBoard::U))
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
	if (gameEngine->input.keyboard.on(Input::KeyBoard::H))
	{
		bucket.position.x -= 3.0f;
	}
	if (gameEngine->input.keyboard.on(Input::KeyBoard::K))
	{
		bucket.position.x += 3.0f;
	}
	TaskFlag nowtask = Task_Game;
	if (gameEngine->input.down(Input::in::D2, 0)/*|| gameEngine->gamepad[0].DOWN(GLFW_JOYSTICK_8)*/)
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
	goal.Render();
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
	}
	while (!this->water.empty())
	{
		this->water.pop_back();
	}
	cm.Destroy();
}