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

#define ADD_FUNCTION(a) \
	[](std::vector<GameObject*>* objs_) { a(objs_); }

Game::Game()
{

}

Game::~Game()
{
	//��������Ǝ���scene�̐���
	this->Finalize();
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		auto nextTask = Result::Create(true);
	}
}

//-------------------------------------------------------------------------------------------------
bool Game::Initialize()
{
	//switch�܂ł͂��̂܂�
	Vec2 bucketpos[2] = {
		{ 150,250 },
		{ 400,800 }
	};

	Vec2 blockpos = Vec2(1536, 100);  //1536,100
	_waterpos = { 200,100 };
	Vec2 fanpos[2] = { Vec2(64 * 12,64 * 7), Vec2(64 * 20,64 * 10) };
	float fanrange[2] = { 18,6 };

	std::cout << "Game" << std::endl;

	//��@�摜�ǂݍ���
	this->fanTex.Create((std::string)"fan.png");
	this->playerTex.Create((std::string)"player2.png");
	rm->SetTextureData((std::string)"playerTex", &this->playerTex);
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
		//ui����
		auto uiwalk = UI::Create(Vec2(200, 300), Box2D(100, 300, 200, 300), (std::string)"walkui.png", 300, 4);
		auto uijump = UI::Create(Vec2(400, 300), Box2D(400, 300, 200, 300), (std::string)"pusha.png", 300, 2);
		auto uigetbucket = UI::Create(Vec2(1200, 200), Box2D(1150, 200, 100, 200), (std::string)"pushb.png", 300, 2);
		auto uigetwater = UI::Create(Vec2(100, 200), Box2D(0, 0, 0, 0), (std::string)"arrowdown.png", 300, 1);
		auto apillwater = UI::Create(Vec2(1600, 200), Box2D(1550, 200, 300, 200), (std::string)"pushx.png", 300, 2);
		//�o�P�c����
		for (int i = 0; i < 1; ++i)
		{
			auto bucket = Bucket::Create(bucketpos[i]);
		}
		//�S�[������
		for (int i = 0; i < 1; ++i)
		{
			auto goal = Goal::Create(true, Vec2(25 * 64, 5 * 64));
		}
	}
	break;
	case 2:		//�`���[�g���A���Q
	{
		//map����
		auto mapload = Map::Create((std::string)"tutorial2.csv");
		//�o�P�c����
		for (int i = 0; i < 1; ++i)
		{
			auto bucket = Bucket::Create(bucketpos[i]);
		}
		//goal����
		for (int i = 0; i < 1; ++i)
		{
			auto goal = Goal::Create(true, Vec2(10 * 64, 10 * 64));
		}
	}
	break;
	case 3:		//�`���[�g���A���R
		//�ʒu�ύX
		_waterpos.y += 64 * 4;
		{
			//map����
			auto mapload = Map::Create((std::string)"tutorial3.csv");
			//���M�퐶��
			auto kanetuki = Kanetuki::Create(Vec2(64 * 12, 64 * 10));
			//�o�P�c����
			for (int i = 0; i < 1; ++i)
			{
				auto bucket = Bucket::Create(Vec2(100, 400));
			}
			//goal����
			for (int i = 0; i < 1; ++i)
			{
				auto goal = Goal::Create(true, Vec2(16 * 64, 8 * 64));
			}
			//��@����
			for (int i = 0; i < 1; ++i)
			{
				auto fan = Fan::Create(Vec2(64, 64 * 2), fanrange[0], Fan::Dir::RIGHT, true);
				fan->SetTexture(&this->fanTex);
				fan->SetWindRange(Vec2(64 * 15, 64));
			}
		}
		break;
	case 4:		//�`���[�g���A���S
	{
		//map����
		auto mapload = Map::Create((std::string)"tutorial4.csv");
		//���M�퐶��
		auto kanetuki = Kanetuki::Create(Vec2(16 * 64, 18 * 64));
		//�o�P�c����
		for (int i = 0; i < 1; ++i)
		{
			auto bucket = Bucket::Create(bucketpos[i]);
		}
		//���X�@����
		for (int i = 0; i < 2; ++i)
		{
			auto seihyouki = Seihyouki::Create(Vec2(4 * 64, 11 * 64));
		}
	}
	break;
	case 5:		//�X�e�[�W�P
	{
		//map����
		auto mapload = Map::Create((std::string)"stage1.csv");
		//���M�퐶��
		for (int i = 0; i < 2; ++i)
		{
			auto kanetuki = Kanetuki::Create(Vec2(64 * (18 + i), 64 * 16));
		}
		for (int i = 0; i < 2; ++i)
		{
			//���X�@����
			auto seihyouki = Seihyouki::Create(Vec2(64 * 5, 64 * 7));
			//��@����
			auto fan = Fan::Create(fanpos[i], fanrange[i], (i == 0) ? Fan::Dir::RIGHT : Fan::Dir::LEFT);
			fan->SetTexture(&this->fanTex);
		}
		auto swith = Switch::Create(Vec2(64 * 18,64 * 13),OGge->GetTask<Player>("player"),true);
		//�o�P�c����
		/*for (int i = 0; i < 2; ++i)
		{
			auto bucket = Bucket::Create(bucketpos[i]);
		}*/
		//�u���b�N����
		for (int i = 0; i < 1; ++i)
		{
			auto block = Block::Create(blockpos);
		}
		//�S�[������
		for (int i = 0; i < 1; ++i)
		{
			auto goal = Goal::Create(true);
		}
	}
	break;
	case 6:
		this->Kill();
		break;
	default:
		std::cout << "�}�b�v�ԍ������݂��܂���" << std::endl;
		break;
	}
	//����������
	{
		//���摜�̓ǂݍ���
		this->waterTex.Create((std::string)"waterTex.png");
		//���\�[�X�Ǘ�class�փf�[�^��n��
		rm->SetTextureData((std::string)"waterTex", &waterTex);
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

	if (OGge->in->on(Input::in::D2, 0) && OGge->in->on(In::D1))
	{
		this->Kill();
	}

	{
		auto goal = OGge->GetTask<Goal>("Goal");
		if (goal != nullptr)
		{
			if (OGge->in->key.down(Input::KeyBoard::ENTER))
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
	std::cout << "Game" << std::endl;
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
	rm->DeleteTexture((std::string)"playerTex");
	rm->DeleteTexture((std::string)"waterTex");
	this->waterTex.Finalize();
	this->playerTex.Finalize();
	this->fanTex.Finalize();
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
		float camera_x = float(player->position.x) - PlayerCenter_x;
		float camera_y = float(player->position.y) - PlayerCenter_y;
		//�J�����̍��W���X�V
		NowCameraPos.x = camera_x;
		NowCameraPos.y = camera_y;


		//���E�̃X�N���[���͈͂̐ݒ�(�T�C�Y��10����1)
		float Boundary = NowCameraSize.x / 10.0f;
		//���݃X�N���[���l�ƃv���C���[�̍��W�̍����C��
		Vec2 NowPlayerPos = { player->position.x - NowCameraPos.x,player->position.y - NowCameraPos.y };
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
		if (NowCameraPos.x + NowCameraSize.x > map->mapSize.x * map->DrawSize.x) {
			NowCameraPos.x = (map->mapSize.x * map->DrawSize.x) - NowCameraSize.x;
		}
		if (NowCameraPos.y < 0) {
			NowCameraPos.y = 0;
		}
		if (NowCameraPos.y + NowCameraSize.y > map->mapSize.y * map->DrawSize.y) {
			NowCameraPos.y = (map->mapSize.y * map->DrawSize.y) - NowCameraSize.y;
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