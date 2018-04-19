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

	Vec2 blockpos = Vec2(1536, 100);

	//�W���X�e�B�����̃M�~�b�N�̏ꍇ

	//Vec2 gimmickpos[6]
	//{
	//	{ 64 * 19,64 * 8 },     //�X�C�b�` ��
	//	{ 64 * 18,64 * 15 },    //���M�� ��
	//	{ 64 * 11,64 * 7 },     //��@ ��
	//	{ 64 * 19 ,64 * 10 },   //��@ ��
	//	{ 64 * 12 ,64 * 14 },	//�X�C�b�` ��
	//	{ 64 * 19,64 * 15 },    //���M�� �E
	//};


	std::cout << "Game" << std::endl;
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

	block.Initialize(blockpos);
	cm.AddChild(&block);

	back.Initialize();
	map.LoadMap("prototype.txt");
	
	
	player.Register(&cm);
	//cm.AddChild(&bucket);
	for (auto& i : map.hitBase)
		for (auto& j : i)
			if (j.objectTag.length() > 0)
				cm.AddChild(&j);
	gameEngine->DebugFunction = true;
	goal.Initialize();
	cm.AddChild(&goal);

	//���c����

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

	//�W���X�e�B���� ���݂͐��X�@�������܂�

	//senpuki.SetParent(&map);                    //map�̃A�h���X�l���i�[����
	//for (int i = 0; i < 2; ++i)
	//{
	//	senpuki.SetParent(&switch_, i);      //Switch�̃A�h���X�l���i�[���� &switch_[0]
	//}

	//senpuki.Set_Pos(gimmickpos[2]);             //��@�̏�̍��W�l��vector�ɓo�^����
	//senpuki.Set_Pos(gimmickpos[3]);             //��@�̉��̍��W�l��vector�ɓo�^����
	//switch_.Set_Pos(gimmickpos[0]);             //�X�C�b�`�̏�̍��W�l��vector�ɓo�^����
	//switch_.Set_Pos(gimmickpos[4]);             //�X�C�b�`�̉��̍��W�l��vector�ɓo�^����
	//											//kanetuki.Input_Pos(gimmickpos[1]);        //���M�@�̍��W�l��vector�ɓo�^����
	//											//kanetuki.Input_Pos(gimmickpos[5]);        //���M�@�̍��W�l��vector�ɓo�^����
	//seihyouki.Input_Pos(gimmickpos[1]);         //������

	////�M�~�b�N�̏�����

	//senpuki.Initialize(gimmickpos[2]);			//��@�̏����������Ɉڂ�iVec2 ��@�̍��W�j
	//switch_.Initlaize();        //Switch�N���X�̏���������������(Vec2 �������W)
	//							//kanetuki.Initialize();                                  //���M�@�𓮂���
	//seihyouki.Initialize();

	////�����蔻���`��o�^����
	//cm.AddChild(&switch_.hitBace[0]);           //Switch�̃A�h���X��vector objs��puth.back()
	//cm.AddChild(&switch_.hitBace[1]);           //Switch�̃A�h���X��ǉ�
	//cm.AddChild(&senpuki);
	//cm.AddChild(&senpuki.range);                //����͈͂̃A�h���X���Q�Ƃ���
	//											//cm.AddChild(&kanetuki.hitBace[0]);          //�����蔻���`��o�^����
	//											//cm.AddChild(&kanetuki.hitBace[1]);          //�����蔻���`��o�^����
	//cm.AddChild(&seihyouki.hitBace);            //�����蔻���`��o�^����

}
//-------------------------------------------------------------------------------------------------
TaskFlag Game::Update()
{
	timecnt++;
	if (timecnt >= 120)
		//if(gameEngine->input.DOWN(Input::Key::L))
	{
		timecnt = 0;
		//Water?��?��?��?��
		auto w = new Water(Vec2(150, 100));
		water.push_back(w);
		cm.AddChild(water[water.size() - 1]);
	}

	
//-------------------------------------------------------------------------------------------------
	if (gameEngine->in.down(Input::in::B3, 0)/* || gameEngine->gamepad[0].DOWN(GLFW_JOYSTICK_3)*/) {
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
//-------------------------------------------------------------------------------------------------
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
	player.Update();
	/*for (int i = 0; i < 2; ++i) {
	player.TakeBucket(bucket[i]);
	}*/
	player.TakeBucket(&bucket);

	block.Update(map, block);
	bucket.Update(map, bucket);

	/*block.maphitF = map.MapHitCheck(block.footBase);
	block.maphitH = map.MapHitCheck(block.headBase);
	block.maphitL = map.MapHitCheck(block.leftBase);
	block.maphitR = map.MapHitCheck(block.rightBase);*/

	block.PlCheckHitF(player);
	block.PlCheckHitH(player);
	block.PlCheckHitL(player);
	block.PlCheckHitR(player);
	
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

	//�J��������
	Camera_move();


	TaskFlag nowtask = Task_Game;
	if (gameEngine->in.down(Input::in::D2, 0)/*|| gameEngine->gamepad[0].DOWN(GLFW_JOYSTICK_8)*/)
	{
		nowtask = Task_Title;
	}
	return nowtask;
}
//-------------------------------------------------------------------------------------------------
void Game::Render2D()
{
	//�w�i�`��
	back.Render();
	//�v���C���[�`��
	player.Render();
	for (int i = 0; i < water.size(); ++i)
	{
		water[i]->Render();
	}
	block.Render();
	goal.Render();
	bucket.Render();
	//�}�b�v�`�b�v�̕`��
	map.MapRender();
	
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
	}
	while (!this->water.empty())
	{
		this->water.pop_back();
	}
	for (int i = 0; i < 2; ++i) {
		swich[i].Finalize();
		fan[i].Finalize();
	}
	cm.Destroy();
}
//-------------------------------------------------------------------------------------------------
//�J��������
void Game::Camera_move()
{
	////�f�o�b�O�p
	//std::cout << gameEngine->camera->GetSize().x << "//"<<gameEngine->camera->GetPos().x << std::endl;
	////�J�����̈ړ�
	//gameEngine->camera->MovePos(player.GetEst());

	////�J��������
	//Vec2 NowCameraPos = gameEngine->camera->GetPos();
	//Vec2 NowCameraSize = gameEngine->camera->GetSize();

	////�v���C���[����ʒ���
	//float PlayerCenter_x = NowCameraSize.x / 2.0f;
	//float PlayerCenter_y = NowCameraSize.y / 2.0f;
	////�J�������W�����߂�
	//float camera_x = float(player.position.x) - PlayerCenter_x;
	//float camera_y = float(player.position.y) - PlayerCenter_y;
	////�J�����̍��W���X�V
	//NowCameraPos.x = camera_x;
	//NowCameraPos.y = camera_y;


	////���E�̃X�N���[���͈͂̐ݒ�(�T�C�Y��10����1)
	//float Boundary = NowCameraSize.x / 10.0f;
	////���݃X�N���[���l�ƃv���C���[�̍��W�̍����C��
	//Vec2 NowPlayerPos = { player.position.x - NowCameraPos.x,player.position.y - NowCameraPos.y };
	////x���W
	//if (NowPlayerPos.x < Boundary){
	//	NowCameraPos.x = NowPlayerPos.x - Boundary;
	//}
	//if (NowPlayerPos.x > NowCameraSize.x - Boundary){
	//	NowCameraPos.x = (NowPlayerPos.x + NowCameraPos.x) - NowPlayerPos.x + Boundary;
	//}
	////y���W
	//if (NowPlayerPos.y < Boundary){
	//	NowCameraPos.y = NowPlayerPos.y - Boundary;
	//}
	//if (NowPlayerPos.y > NowCameraSize.y - Boundary){
	//	NowCameraPos.y = (NowCameraSize.y + NowCameraPos.y) - NowPlayerPos.y + Boundary;
	//}


	//----------------------------------------------------------------------------------------
	//�������牡�c�ҏW

	Vec2 NowCameraPos = gameEngine->camera->GetPos();
	Vec2 NowCameraSize = gameEngine->camera->GetSize();

	//�J�����������Ȃ��͈�
	float NoMoveLeft = NowCameraPos.x + NowCameraSize.x*(7.0f / 16.0f);
	float NoMoveRight = NowCameraPos.x + NowCameraSize.x*(9.0f / 16.0f);
	float NoMoveUp = NowCameraPos.y + NowCameraSize.y*(7.0f / 16.0f);
	float NoMoveBottom = NowCameraPos.y + NowCameraSize.y*(9.0f / 16.0f);
	Vec2 cameracenter = Vec2(NowCameraPos.x + NowCameraSize.x*0.5f, NowCameraPos.y + NowCameraSize.y*0.5f);
	Vec2 playercenter = Vec2(player.position.x + player.Scale.x*0.5f, player.position.y + player.Scale.y*0.5f);
	//�����蔻�莞�̏����͏I�������Ȃ̂�player.est�͍l������K�v�Ȃ��H
	//�v���C�����J�����̓����Ȃ��͈͂𒴂��Ă�����J�����ړ�
	//x��
	if (playercenter.x < NoMoveLeft) {
		float cameraest = NoMoveLeft - playercenter.x;
		NowCameraPos.x -= cameraest;
	}
	if (playercenter.x > NoMoveRight) {
		float cameraest = playercenter.x - NoMoveRight;
		NowCameraPos.x += cameraest;
	}
	//y��
	if (playercenter.y < NoMoveUp) {
		float cameraest = NoMoveUp - playercenter.y;
		NowCameraPos.y -= cameraest;
	}
	if (playercenter.y > NoMoveBottom) {
		float cameraest = playercenter.y - NoMoveBottom;
		NowCameraPos.y += cameraest;
	}
	//y���͓����Ȃ��Ă��������H
	//NowCameraPos.y = playercenter.y - cameracenter.y;    //���ӁF�߂荞�݂̉e���ł߂�����K�^���܂�

	//�����܂ŉ��c
	//-----------------------------------------------------------------------------------------------

	//��ʊO����
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