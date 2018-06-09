#include "Task_Game.h"
#include "Task\Task_Result.h"
#include "Map\Map.h"
#include "Player\Player.h"
#include "Block\block.h"
#include "Bucket\bucket.h"
#include "Goal\Goal.h"
#include "Water\water.h"
#include "GameProcessManagement\GameProcessManagement.h"
#include "UI\UI.h"
#include "Gimmick\NO_MOVE\Kanetuki.h"
#include "Gimmick\NO_MOVE\Seihyouki.h"
#include "Gimmick\NO_MOVE\Senpuki.h"
#include "Gimmick\NO_MOVE\Switch.h"

#include "GameProcessManagement\GameClearCamera.h"
#include "GameProcessManagement\Timer.h"
#include "Task\Task_Pause.h"
#include "Task\StageSelect.h"
#include "Back\Back.h"
#include "Task_Title.h"
#include "Effect\Effect.h"

#define ADD_FUNCTION(a) \
	[](std::vector<GameObject*>* objs_) { a(objs_); }

Game::Game()
{
	gamesoundname = "game.wav";
	tutorialsoundname = "tutorial.wav";
	//this->ResetKillCount();
}

Game::~Game()
{
	//��������Ǝ���scene�̐���
	this->Finalize();
	//OGge->DeleteTasks();
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		if (OGge->in->on(In::D1) && OGge->in->on(In::D2) && OGge->in->on(In::L1) && OGge->in->on(In::R1))
		{
			auto next = Title::Create();
		}
		else
		{
			if (*MapNum < 4)
			{
				*MapNum = *MapNum + 1;
				auto next = Game::Create();
			}
			//���Ƀ`���[�g���A�����T���Ă�����͎̂��̃`���[�g���A���ֈړ�
			else if (*MapNum == 4)
			{
				//�`���[�g���A���I���ŃZ���N�g�ɖ߂�
				auto next = StageSelect::Create();
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
bool Game::Initialize()
{
	auto backImage = Back::Create(std::string("back.png"), 1920, 1080);
	//Pause�^�X�N�̐���
	auto pause = Pause::Create();

	////switch�܂ł͂��̂܂�
	//Vec2 bucketpos[2] = {
	//	{ 150,250 },
	//	{ 400,800 }
	//};

	//Vec2 blockpos = Vec2(1536, 70);  //1536,100
	_waterpos = { 200,100 };
	Vec2 fanpos[2] = { Vec2(64 * 12,64 * 7), Vec2(64 * 20,64 * 10) };
	float fanrange[2] = { 16,7 };

	std::cout << "Game������" << std::endl;

	//��@�摜�ǂݍ���
	this->fanTex.Create((std::string)"fan.png");
	this->playerTex.Create((std::string)"player.png");
	rm->SetTextureData((std::string)"playerTex", &this->playerTex);
	this->PaintTex.Create("paintTest.png");
	rm->SetTextureData((std::string)"paintTex", &this->PaintTex);
	this->EffectTest.Create("EffectTest.png");
	rm->SetTextureData((std::string)"Effect", &this->EffectTest);
	//ui����
	UImng_.reset(new UImanager());
	UImng_->Initialize(*MapNum);
	//�}�b�v��������
	switch (*MapNum)
	{
	case 0:
		//txt�ǂݍ��ݏ������̂ō폜���Ă��܂��B
		this->Kill();
		break;
	case 1:		//�`���[�g���A���P
	{
		//map����
		auto mapload = Map::Create((std::string)"tutorial1.csv");
		//���̈ʒu
		_waterpos.x = 64 * 7;
		_waterpos.y = 64 * 15;
		//�`���[�g���A���̃T�E���h�Ɏg�p
		sound.create(tutorialsoundname, true);
		sound.volume(1.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();
	}
	break;
	case 2:		//�`���[�g���A���Q
	{
		//map����
		auto mapload = Map::Create((std::string)"tutorial2.csv");
		//���̈ʒu(��)
		_waterpos.x = 64 * 8;
		//�`���[�g���A���̃T�E���h�Ɏg�p
		sound.create(tutorialsoundname, true);
		sound.volume(1.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

	}
	break;
	case 3:		//�`���[�g���A���R
		//�ʒu�ύX
		_waterpos.x = 6 * 64;
		_waterpos.y = 64 * 12;
		{
			//map����
			auto mapload = Map::Create((std::string)"tutorial3.csv");
			//�`���[�g���A���̃T�E���h�Ɏg�p
			sound.create(tutorialsoundname, true);
			sound.volume(1.0f);
			OGge->soundManager->SetSound(&sound);
			sound.play();

			//���M�퐶��
			auto kanetuki1 = Kanetuki::Create(Vec2(64 * 21, 64 * 17), Vec2(64 * 2, 64), false);
			//auto kanetuki2 = Kanetuki::Create(Vec2(64 * 22, 64 * 17), false);
			//��@����
			auto fan = Fan::Create(Vec2(64 * 14, 64 * 7), 13, Fan::Dir::RIGHT, true);
			//���M��p�X�C�b�`����
			auto swich = Switch::Create(Vec2(64 * 18, 64 * 16), std::vector<std::shared_ptr<GameObject>>{kanetuki1/*, kanetuki2*/}, Switch::TargetType::Heater);
		}
		break;
	case 4:		//�`���[�g���A���S
	{
		//map����
		auto mapload = Map::Create((std::string)"tutorial4.csv");
		//���̈ʒu
		_waterpos.x = 64 * 5;
		_waterpos.y = 64 * 2;
		//�`���[�g���A���̃T�E���h�Ɏg�p
		sound.create(tutorialsoundname, true);
		sound.volume(1.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();
		//���M�퐶��
		auto kanetuki = Kanetuki::Create(Vec2(17 * 64, 18 * 64), Vec2(64, 64), false);
		//���X�@����
		auto seihyouki = Seihyouki::Create(Vec2(4 * 64, 10 * 64), Vec2(64 * 2, 64));
		//���X�@�p�X�C�b�`����
		auto iceSwitch = Switch::Create(Vec2(64 * 7, 64 * 8), std::vector<std::shared_ptr<GameObject>>{seihyouki}, Switch::TargetType::IceMachine);
		//���M��p�X�C�b�`����
		auto heaterSwitch = Switch::Create(Vec2(64 * 14, 64 * 15), std::vector<std::shared_ptr<GameObject>>{kanetuki}, Switch::TargetType::Heater);
	}
	break;
	case 5:		//�X�e�[�W�P
	{
		//map����
		auto mapload = Map::Create((std::string)"stage1.csv");

		//�Q�[���̃T�E���h�Ɏg�p
		sound.create(gamesoundname, true);
		sound.volume(1.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//�X�C�b�`��Ώۂɂ�����@�̐���
		auto fan1 = Fan::Create(fanpos[1], fanrange[1], Fan::Dir::LEFT, false);
		//fan��Ώۂɂ�����@�̐����i�X�C�b�`�ɂ���Đ�@�����ւ��邱�Ƃ��ł���j
		auto fan2 = Fan::Create(fanpos[0], fanrange[0], Fan::Dir::RIGHT, true);
		//���M�퐶��
		auto kanetuki1 = Kanetuki::Create(Vec2(64 * 19, 64 * 15 - 32), Vec2(64 * 2, 84), false);		//ToDo:�ʒu��ς���̂ł͂Ȃ�����͈͂��L���邱��
		//auto kanetuki2 = Kanetuki::Create(Vec2(64 * 20, 64 * 15 - 32), false);
		//���X�@����
		auto seihyouki1 = Seihyouki::Create(Vec2(64 * 6, 64 * 7), Vec2(64 * 2, 64));
		//auto seihyouki2 = Seihyouki::Create(Vec2(64 * 7, 64 * 7));

		//�X�C�b�`�̐���
		//��@�p
		{auto swith = Switch::Create(Vec2(64 * 18, 64 * 8), std::vector<std::shared_ptr<GameObject>>{ fan1, fan2 }, Switch::TargetType::Fan); }
		//���M��p
		{auto swith = Switch::Create(Vec2(64 * 17, 64 * 14), std::vector<std::shared_ptr<GameObject>>{ kanetuki1/*, kanetuki2*/ }, Switch::TargetType::Heater); }
		//���X�@�p
		{auto swith = Switch::Create(Vec2(64 * 5, 64 * 5), std::vector<std::shared_ptr<GameObject>>{ seihyouki1/*, seihyouki2*/ }, Switch::TargetType::IceMachine); }

		//�u���b�N����
		for (int i = 0; i < 1; ++i)
		{
			auto block = Block::Create(Vec2(1536, 70));
		}
	}
	break;
	case 6:
	{
		//map����
		auto mapload = Map::Create((std::string)"stage2.csv");
		//���̈ʒu
		_waterpos.x = 64 * 9 + 32;
		_waterpos.y = 64 * 3;

		//�Q�[���̃T�E���h�Ɏg�p
		sound.create(gamesoundname, true);
		sound.volume(1.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//��@
		Vec2 fanpos[5] = { Vec2(64 * 11,64 * 6),Vec2(64 * 20,64 * 6),Vec2(64 * 25,64 * 17),Vec2(64 * 30,64 * 23),Vec2(64 * 34,64 * 27) };
		auto fan1 = Fan::Create(fanpos[0], 7, Fan::Dir::LEFT, true);
		auto fan2 = Fan::Create(fanpos[1], 12, Fan::Dir::RIGHT, true);
		auto fan3 = Fan::Create(fanpos[2], 15, Fan::Dir::LEFT, true);
		auto fan4 = Fan::Create(fanpos[3], 8, Fan::Dir::RIGHT, true);
		auto fan5 = Fan::Create(fanpos[4], 4.5f, Fan::Dir::LEFT, false);
		//���M��
		auto kanetsuki1 = Kanetuki::Create(Vec2(64 * 21, 64 * 21 - 20), Vec2(64 * 3, 84), false);
		//auto kanetsuki2 = Kanetuki::Create(Vec2(64 * 22, 64 * 21 - 20), false);
		//auto kanetsuki3 = Kanetuki::Create(Vec2(64 * 23, 64 * 21 - 20), false);
		auto kanetsuki4 = Kanetuki::Create(Vec2(64 * 18, 64 * 29), Vec2(64 * 5, 64 + 32), true);
		//auto kanetsuki5 = Kanetuki::Create(Vec2(64 * 19, 64 * 29 + 32), true);
		//auto kanetsuki6 = Kanetuki::Create(Vec2(64 * 20, 64 * 29 + 32), true);
		//auto kanetsuki7 = Kanetuki::Create(Vec2(64 * 21, 64 * 29 + 32), true);
		//auto kanetsuki8 = Kanetuki::Create(Vec2(64 * 22, 64 * 29 + 32), true);
		auto kanetsuki9 = Kanetuki::Create(Vec2(64 * 33, 64 * 32 - 20), Vec2(64 * 2, 84) , true);
		//auto kanetsuki10 = Kanetuki::Create(Vec2(64 * 34, 64 * 32 - 20), true);
		//���X�@
		auto seihyouki1 = Seihyouki::Create(Vec2(64 * 9, 64 * 12), Vec2(64 * 2, 64));
		//auto seihyouki2 = Seihyouki::Create(Vec2(64 * 10, 64 * 12));
		auto seihyouki3 = Seihyouki::Create(Vec2(64 * 9, 64 * 22), Vec2(64 * 2, 64));
		//auto seihyouki4 = Seihyouki::Create(Vec2(64 * 10, 64 * 22));
		//��@�X�C�b�`
		auto fanSwitch1 = Switch::Create(Vec2(64 * 19, 64 * 12), std::vector<std::shared_ptr<GameObject>>{fan2, fan3}, Switch::TargetType::Fan);
		auto fanSwitch2 = Switch::Create(Vec2(64 * 31, 64 * 31), std::vector<std::shared_ptr<GameObject>>{fan4, fan5}, Switch::TargetType::Fan);
		//���M��X�C�b�`
		auto heaterSwitch1 = Switch::Create(Vec2(64 * 20, 64 * 20), std::vector<std::shared_ptr<GameObject>>{kanetsuki1/*, kanetsuki2, kanetsuki3*/}, Switch::TargetType::Heater);
	//	auto heaterSwitch2 = Switch::Create(Vec2(64 * 35, 64 * 31), std::vector<std::shared_ptr<GameObject>>{kanetsuki5, kanetsuki6, kanetsuki7}, Switch::TargetType::Heater);
		//���X�@�X�C�b�`
		auto iceSwitch = Switch::Create(Vec2(64 * 12, 64 * 20), std::vector<std::shared_ptr<GameObject>>{seihyouki1, /*seihyouki2,*/ seihyouki3/*, seihyouki4*/}, Switch::TargetType::IceMachine);
		//�u���b�N
		auto block = Block::Create(Vec2(64 * 20, 64 * 29));
		auto block2 = Block::Create(Vec2(64 * 33, 64 * 10));
		//this->Kill();
		break;
	}
	default:
		std::cout << "�}�b�v�ԍ������݂��܂���" << std::endl;
		break;
	}
	//����������
	{
		//���摜�̓ǂݍ���
		this->waterTex.Create("waterTex.png");
		this->waterRed.Create("WaterRed.png");
		this->waterBlue.Create("WaterBlue.png");
		this->waterPurple.Create("WaterPurple.png");
		//���\�[�X�Ǘ�class�փf�[�^��n��
		rm->SetTextureData((std::string)"waterTex", &this->waterTex);
		rm->SetTextureData((std::string)"waterRed", &this->waterRed);
		rm->SetTextureData((std::string)"waterBlue", &this->waterBlue);
		rm->SetTextureData((std::string)"waterPurple", &this->waterPurple);
	}

	//���������ō~���Ă��鎞�Ԃ̏�����
	this->timecnt = 0;
	//���̐���
	auto water = Water::Create(_waterpos);
	//�摜��n��
	water->SetTexture(&this->waterTex);
	switch (*MapNum)
	{
	case 3:
		//�v���C���[�̈ʒu��ύX
	//	player->SetPos(Vec2(200, 400));
		break;
	default:
		break;
	}
	//�^�X�N�ɖ��O��o�^
	__super::Init((std::string)"game");
	//�Q�[���N���A����𐶐�
	auto gameprocess = GameProcessManagement::Create();
	return true;
}
//-------------------------------------------------------------------------------------------------
void Game::UpDate()
{
	timecnt++;
	if (timecnt >= 120)
	{
		timecnt = 0;
		auto water = Water::Create(_waterpos);
		water->SetTexture(&this->waterTex);
	}
	//�J��������
	Camera_move();

	// Pause����
	if (OGge->in->key.down(In::D2)){
		OGge->SetPause(true);
	}

	//UI
	UImng_->UpDate();

	if (OGge->in->on(In::D1) && OGge->in->on(In::D2))
	{
		this->Kill();
	}

	if (OGge->in->key.down(In::E))
	{
		auto player = OGge->GetTask<Player>("Player");
		if (player)
		{
			auto effect = Effect::Create(player->position, Vec2(64, 64), Vec2(64, 64), 13, 60, 5);
			effect->SetTexture(rm->GetTextureData((std::string)"Effect"));
			effect->Set(effect->position, Vec2(effect->position.x, effect->position.y - 200));
		}
	}

	{
		auto goal = OGge->GetTask<Goal>("Goal");
		if (goal != nullptr)
		{
			if (OGge->in->key.down(Input::KeyBoard::Q))
			{
				goal->cleared = true;
			}
		}

		auto cameraMove = OGge->GetTask<GameClearCamera>("GameClearCamera");
		if (cameraMove != nullptr)
		{
			if (cameraMove->GetCameraMoveFinish())
			{
				this->Kill();
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------
void Game::Render2D()
{

}
//-------------------------------------------------------------------------------------------------
bool Game::Finalize()
{
	std::cout << "Game���" << std::endl;
	//�e�I�u�W�F�N�g�����݂��Ă���ꍇ��Kill����B
	auto map = OGge->GetTask<Map>("map");
	if (map)
	{
		map->Kill();
	}
	auto block = OGge->GetTasks<Block>("block");
	for (auto id = (*block).begin(); id != (*block).end(); ++id)
	{
		(*id)->Kill();
	}
	auto UIs = OGge->GetTasks<UI>("UI");
	for (auto id = (*UIs).begin(); id != (*UIs).end(); ++id)
	{
		(*id)->Kill();
	}
	auto buckets = OGge->GetTasks<Bucket>("bucket");
	for (auto id = (*buckets).begin(); id != (*buckets).end(); ++id)
	{
		(*id)->Kill();
	}
	auto goals = OGge->GetTasks<Goal>("Goal");
	for (auto id = (*goals).begin(); id != (*goals).end(); ++id)
	{
		(*id)->Kill();
	}
	auto kanetukis = OGge->GetTasks<Kanetuki>("Kanetuki");
	for (auto id = (*kanetukis).begin(); id != (*kanetukis).end(); ++id)
	{
		(*id)->Kill();
	}
	auto fans = OGge->GetTasks<Fan>("Senpuki");
	for (auto id = (*fans).begin(); id != (*fans).end(); ++id)
	{
		(*id)->Kill();
	}
	auto seihyoukis = OGge->GetTasks<Seihyouki>("Seihyouki");
	for (auto id = (*seihyoukis).begin(); id != (*seihyoukis).end(); ++id)
	{
		(*id)->Kill();
	}
	auto players = OGge->GetTasks<Player>("Player");
	for (auto id = (*players).begin(); id != (*players).end(); ++id)
	{
		(*id)->Kill();
	}
	auto gamepros = OGge->GetTasks<GameProcessManagement>("GameProcessManagement");
	for (auto id = (*gamepros).begin(); id != (*gamepros).end(); ++id)
	{
		(*id)->Kill();
	}
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		(*id)->Kill();
	}
	auto gamecamera = OGge->GetTasks<GameClearCamera>("GameClearCamera");
	for (auto id = (*gamecamera).begin(); id != (*gamecamera).end(); ++id)
	{
		(*id)->Kill();
	}
	auto timers = OGge->GetTasks<Timer>("Timer");
	for (auto id = (*timers).begin(); id != (*timers).end(); ++id)
	{
		(*id)->Kill();
	}
	/*auto pauses = OGge->GetTasks<Pause>("pause");
	for (auto id = pauses->begin(); id != pauses->end(); ++id)
	{
		(*id)->Kill();
	}*/
	auto back = OGge->GetTask<Back>("back");
	if (back)
	{
		back->Kill();
	}
	auto switches = OGge->GetTasks<Switch>("Switch");
	for (auto id = switches->begin(); id != switches->end(); ++id)
	{
		(*id)->Kill();
	}
	rm->DeleteTexture((std::string)"playerTex");
	rm->DeleteTexture((std::string)"waterTex");
	rm->DeleteTexture((std::string)"Effect");
	rm->DeleteTexture((std::string)"paintTex");
	this->waterTex.Finalize();
	this->playerTex.Finalize();
	this->fanTex.Finalize();
	this->EffectTest.Finalize();
	this->waterBlue.Finalize();
	this->waterPurple.Finalize();
	this->waterRed.Finalize();
	this->PaintTex.Finalize();
	return true;
}
//-------------------------------------------------------------------------------------------------
//�J��������
void Game::Camera_move()
{
	//�f�o�b�O�p
	//std::cout << OGge->camera->GetSize().x << "//"<<OGge->camera->GetPos().x << std::endl;
	//�J�����̈ړ�
	auto goal = OGge->GetTask<Goal>("Goal");
	if (goal != nullptr)
	{
		if (goal->ClearCheck())
		{
			return;
		}
	}
	auto player = OGge->GetTask<Player>("Player");
	auto map = OGge->GetTask<Map>("map");
	if (player && map)
	{
		OGge->camera->MovePos(player->GetEst());

		//�J��������
		Vec2 NowCameraPos = OGge->camera->GetPos();
		Vec2 NowCameraSize = OGge->camera->GetSize();

		//�v���C���[����ʒ���
		float PlayerCenter_x = NowCameraSize.x / 2.0f;
		float PlayerCenter_y = NowCameraSize.y / 2.0f;
		//�J�������W�����߂�
		float camera_x = float(player->GetPos().x) - PlayerCenter_x;
		float camera_y = float(player->GetPos().y) - PlayerCenter_y;
		//�J�����̍��W���X�V
		NowCameraPos.x = camera_x;
		NowCameraPos.y = camera_y;


		//���E�̃X�N���[���͈͂̐ݒ�(�T�C�Y��10����1)
		float Boundary = NowCameraSize.x / 10.0f;
		//���݃X�N���[���l�ƃv���C���[�̍��W�̍����C��
		Vec2 NowPlayerPos = { player->GetPos().x - NowCameraPos.x,player->GetPos().y - NowCameraPos.y };
		//x���W
		if (NowPlayerPos.x < Boundary) {
			NowCameraPos.x = NowPlayerPos.x - Boundary;
		}
		if (NowPlayerPos.x > NowCameraSize.x - Boundary) {
			NowCameraPos.x = (NowPlayerPos.x + NowCameraPos.x) - NowPlayerPos.x + Boundary;
		}
		//y���W
		if (NowPlayerPos.y < Boundary) {
			NowCameraPos.y = NowPlayerPos.y - Boundary;
		}
		if (NowPlayerPos.y > NowCameraSize.y - Boundary) {
			NowCameraPos.y = (NowCameraSize.y + NowCameraPos.y) - NowPlayerPos.y + Boundary;
		}
		//��ʊO����
		if (NowCameraPos.x < 0) {
			NowCameraPos.x = 0;
		}
		if (NowCameraPos.x + NowCameraSize.x >(map->mapSize.x - 1) * map->DrawSize.x) {
			NowCameraPos.x = ((map->mapSize.x - 1)* map->DrawSize.x) - NowCameraSize.x;
		}
		if (NowCameraPos.y < 0) {
			NowCameraPos.y = 0;
		}
		if (NowCameraPos.y + NowCameraSize.y >(map->mapSize.y)* map->DrawSize.y) {
			NowCameraPos.y = ((map->mapSize.y)* map->DrawSize.y) - NowCameraSize.y;
		}

		OGge->camera->SetPos(NowCameraPos);
	}
}

Game::SP Game::Create(bool flag_)
{
	auto to = Game::SP(new Game());
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