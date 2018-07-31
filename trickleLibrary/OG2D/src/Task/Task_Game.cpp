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
#include "Gimmick\NO_MOVE\TimeSign.h"
#include "GameProcessManagement\Timer.h"
#include "Task\Task_Pause.h"
#include "Task\StageSelect.h"
#include "Back\Back.h"
#include "Task_Title.h"
#include "Effect\Effect.h"
#include "Map\Ornament.h"
#include "Load\LoadLogo.h"
#include "Gimmick\NO_MOVE\Door.h"
#include "UI/GoalDirectionUI.h"
#include "VolumeControl/volumeControl.h"
#include "Gimmick/NO_MOVE/WeightSwitch.h"

#define ADD_FUNCTION(a) \
	[](std::vector<GameObject*>* objs_) { a(objs_); }

Game::Game()
{
	gamesoundname = "game.wav";
	tutorialsoundname = "tutorial.wav";

	this->canvolControl = true;
	//this->ResetKillCount();
	OGge->camera->SetSize(Vec2(1920, 1080));
}

Game::~Game()
{
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		auto load = Load::Create();
		load->Draw();
		OGge->ChengeTask();
	}
	//��������Ǝ���scene�̐���
	this->Finalize();
	//OGge->DeleteTasks();


}

//-------------------------------------------------------------------------------------------------
bool Game::Initialize()
{
	OGge->camera->SetSize(Vec2(1280, 720));
	auto backImage = Back::Create(std::string("back.png"), 1920, 1080);

	//Pause�^�X�N�̐���
	auto pause = Pause::Create();

	Vec2 fanpos[2] = { Vec2(64 * 12,64 * 7), Vec2(64 * 20,64 * 10) };
	float fanrange[2] = { 16,7 };
	//��@�摜�ǂݍ���
	this->fanTex.Create((std::string)"fan.png");
	this->playerTex.Create((std::string)"player.png");
	rm->SetTextureData((std::string)"playerTex", &this->playerTex);
	this->fireice.Create((std::string)"fireice.png");
	rm->SetTextureData((std::string)"fireIce", &this->fireice);
	this->PaintTex.Create("paintTest.png");
	rm->SetTextureData((std::string)"paintTex", &this->PaintTex);
	this->EffectTest.Create("EffectTest.png");
	rm->SetTextureData((std::string)"Effect", &this->EffectTest);
	this->Effectsond.Create("sandsmoke.png");
	rm->SetTextureData((std::string)"sandsmoke", &this->Effectsond);
	this->texSteam.Create("steam.png");
	rm->SetTextureData(std::string("steam"), &this->texSteam);
	this->goalTex.Create("goal.png");
	rm->SetTextureData((std::string)"goalTex", &this->goalTex);
	this->goalDirectionTex.Create((std::string)"goalarrow.png");
	rm->SetTextureData((std::string)"goalDirectionTex", &this->goalDirectionTex);
	this->arrowflower.Create((std::string)"arrowflower.png");
	rm->SetTextureData((std::string)"arrowflowerTex", &this->arrowflower);
	this->doorTex.Create("door.png");
	rm->SetTextureData((std::string)"WswitchTex", &this->WswitchTex);
	this->WswitchTex.Create("Collision.png");
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
	case 1:		//���P
	{
		//map����
		auto mapload = Map::Create((std::string)"water1.csv");
		//���̈ʒu
		_waterpos = mapload->getWaterPos();
		//�`���[�g���A���̃T�E���h�Ɏg�p
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();
		break;
	}
	case 2:		//���Q
	{
		//map����
		auto mapload = Map::Create((std::string)"water2.csv");
		//���̈ʒu
		_waterpos = mapload->getWaterPos();
		//�`���[�g���A���̃T�E���h�Ɏg�p
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();
		break;
	}
	case 3:		//���R
	{
		//map����
		auto mapload = Map::Create((std::string)"water3.csv");
		//���̈ʒu
		_waterpos = mapload->getWaterPos();
		//�`���[�g���A���̃T�E���h�Ɏg�p
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		break;
	}
	case 4:		//��4
	{
		//map����
		auto mapload = Map::Create((std::string)"water4.csv");
		//���̈ʒu
		_waterpos = mapload->getWaterPos();
		//�`���[�g���A���̃T�E���h�Ɏg�p
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		break;
	}
	case 5:		//�X1
	{
		//map����
		auto mapload = Map::Create((std::string)"ice1.csv");
		//���̈ʒu
		_waterpos = mapload->getWaterPos();
		//�`���[�g���A���̃T�E���h�Ɏg�p
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//���M�퐶��
		auto kanetuki = Kanetuki::Create(Vec2(17 * 64, 18 * 64), Vec2(64, 64), Kanetuki::Angle::RIGHT, false);
		//���X�@����
		auto seihyouki = Seihyouki::Create(Vec2(4 * 64, 10 * 64), Vec2(64 * 2, 64), Seihyouki::Angle::LEFT);
		//���X�@�p�X�C�b�`����
		auto iceSwitch = Switch::Create(Vec2(64 * 7, 64 * 8), std::vector<std::shared_ptr<GameObject>>{seihyouki}, Switch::TargetType::IceMachine);
		//���M��p�X�C�b�`����
		auto heaterSwitch = Switch::Create(Vec2(64 * 14, 64 * 15), std::vector<std::shared_ptr<GameObject>>{kanetuki}, Switch::TargetType::Heater);
		break;
	}
	case 6:		//�X2
	{
		//map����
		auto mapload = Map::Create((std::string)"ice2.csv");
		//���̈ʒu
		_waterpos = mapload->getWaterPos();
		//�`���[�g���A���̃T�E���h�Ɏg�p
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//���M��
		Kanetuki::Create(Vec2(64 * 21, 64 * 8), Vec2(64 * 2, 64), Kanetuki::Angle::LEFT, true);
		//���X�@
		auto seihyouki = Seihyouki::Create(Vec2(64 * 3, 64 * 6), Vec2(64 * 2, 64), Seihyouki::Angle::RIGHT);
		//���X�@�X�C�b�`
		Switch::Create(Vec2(64 * 13, 64 * 4), std::vector<std::shared_ptr<GameObject>>{seihyouki}, Switch::TargetType::IceMachine);

		break;
	}
	case 7:		//�X3
	{
		//map����
		auto mapload = Map::Create((std::string)"ice3.csv");
		//���̈ʒu
		_waterpos = mapload->getWaterPos();
		//�`���[�g���A���̃T�E���h�Ɏg�p
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//���M��
		Kanetuki::Create(Vec2(64 * 9, 64 * 6), Vec2(64 * 5, 64 * 2), Kanetuki::Angle::BOTTOM, true);
		Kanetuki::Create(Vec2(64 * 23, 64 * 7), Vec2(64 * 3, 64 * 2), Kanetuki::Angle::BOTTOM, true);
		//���X�@
		auto seihyouki = Seihyouki::Create(Vec2(64 * 4, 64 * 4), Vec2(64 * 2.5f, 64.f), Seihyouki::Angle::RIGHT);
		//���X�@�X�C�b�`
		Switch::Create(Vec2(64 * 3, 64 * 8), std::vector<std::shared_ptr<GameObject>>{seihyouki}, Switch::TargetType::IceMachine);

		break;
	}
	case 8:		//�X4
	{
		//map����
		auto mapload = Map::Create((std::string)"ice4.csv");
		//���̈ʒu
		_waterpos = mapload->getWaterPos();
		//�`���[�g���A���̃T�E���h�Ɏg�p
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//���M��
		//Kanetuki::Create(Vec2(64 * 17, 64 * 5), Vec2(64, 64 * 2), Kanetuki::Angle::BOTTOM, true);
		//���X�@
		auto seihyouki = Seihyouki::Create(Vec2(64 * 6, 64 * 5), Vec2(64 * 2.5f, 64.f), Seihyouki::Angle::RIGHT);
		//���X�@�X�C�b�`
		Switch::Create(Vec2(64 * 5, 64 * 9), std::vector<std::shared_ptr<GameObject>>{seihyouki}, Switch::TargetType::IceMachine);
		//�d���h�A
		auto door = Door::Create(Vec2(64 * 13, 64 * 6), Vec2(32, 64 * 2), false, Door::Direction::HEIGHT);
		door->SetTexture(&doorTex);
		//�d���X�C�b�`
		auto ws = WeightSwitch::Create(Vec2(64 * 2 + 32, 64 * 9 + 34), Vec2(64 * 2, 30), 1, std::vector<std::shared_ptr<GameObject>>{door});
		ws->SetTexture(&WswitchTex);
		break;
	}
	case 9:		//���C1
	{
		//map����
		auto mapload = Map::Create((std::string)"steam1.csv");
		//���̈ʒu
		_waterpos = mapload->getWaterPos();
		//�`���[�g���A���̃T�E���h�Ɏg�p
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//���M�퐶��
		auto kanetuki1 = Kanetuki::Create(Vec2(64 * 15, 64 * 10 - 32), Vec2(64 * 2, 64+32), Kanetuki::Angle::UP, false);
		//��@����
		auto fan = Fan::Create(Vec2(64 * 11, 64 * 2), 10, Fan::Dir::RIGHT, 64 * 5, true);
		//���M��p�X�C�b�`����
		auto swich = Switch::Create(Vec2(64 * 13, 64 * 9), std::vector<std::shared_ptr<GameObject>>{kanetuki1/*, kanetuki2*/}, Switch::TargetType::Heater);
		break;
	}
	case 10:	//���C2
	{
		//map����
		auto mapload = Map::Create((std::string)"steam2.csv");
		//���̈ʒu
		_waterpos = mapload->getWaterPos();
		//�`���[�g���A���̃T�E���h�Ɏg�p
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//���M�퐶��
		Kanetuki::Create(Vec2(64 * 9, 64 * 19 - 32), Vec2(64 * 3, 64 + 32), Kanetuki::Angle::UP, true);
		//��@
		auto fan1 = Fan::Create(Vec2(64 * 8, 64 * 15), 8, Fan::Dir::RIGHT, 64, true);
		auto fan2 = Fan::Create(Vec2(64 * 17, 64 * 11), 9, Fan::Dir::LEFT, 64, false);
		auto fan3 = Fan::Create(Vec2(64 * 8, 64 * 5), 9, Fan::Dir::RIGHT, 64, false);
		auto fan4 = Fan::Create(Vec2(64 * 17, 64), 13, Fan::Dir::LEFT, 64, true);
		//��@�X�C�b�`
		Switch::Create(Vec2(64 * 12, 64 * 12), std::vector<std::shared_ptr<GameObject>>{fan1, fan2}, Switch::TargetType::Fan);
		Switch::Create(Vec2(64 * 13, 64 * 6), std::vector<std::shared_ptr<GameObject>>{fan3, fan4}, Switch::TargetType::Fan);

		break;
	}
	case 11:	//���C3
	{
		//map����
		auto mapload = Map::Create((std::string)"steam3.csv");
		//���̈ʒu
		_waterpos = mapload->getWaterPos();
		//�`���[�g���A���̃T�E���h�Ɏg�p
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		break;
	}
	case 12:	//���C4
	{
		//map����
		auto mapload = Map::Create((std::string)"steam4.csv");
		//���̈ʒu
		_waterpos = mapload->getWaterPos();
		//�`���[�g���A���̃T�E���h�Ɏg�p
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		break;
	}
	case 13:		//�X�e�[�W�P
	{
		//map����
		auto mapload = Map::Create((std::string)"stage1.csv");
		//���̈ʒu
		_waterpos = mapload->getWaterPos();

		//�e�X�g�ǉ��d���Ŕ�������switch��scale.y��30�K��ł��肢���܂�
		//auto wswitch = WeightSwitch::Create(Vec2(400, 920), Vec2(200, 30), 1.0f);
		//wswitch->SetTexture(&WswitchTex);

		//�Q�[���̃T�E���h�Ɏg�p
		sound.create(gamesoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//��@�̐���
		auto fan1 = Fan::Create(fanpos[1], fanrange[1], Fan::Dir::LEFT, 64 * 8, false);
		auto fan2 = Fan::Create(fanpos[0], fanrange[0], Fan::Dir::RIGHT, 64 * 9, true);
		//���M�퐶��
		auto kanetuki1 = Kanetuki::Create(Vec2(64 * 19, 64 * 15 - 32), Vec2(64 * 2, 84), Kanetuki::Angle::UP, false);
		//���X�@����
		auto seihyouki1 = Seihyouki::Create(Vec2(64 * 6, 64 * 7), Vec2(64 * 2, 64), Seihyouki::Angle::RIGHT);

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
		break;
	}
	case 14:	//�X�e�[�W2
	{
		//map����
		auto mapload = Map::Create((std::string)"stage2.csv");
		//���̈ʒu
		_waterpos = mapload->getWaterPos();
		//�Q�[���̃T�E���h�Ɏg�p
		sound.create(gamesoundname, true);
		sound.volume(1.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//��@
		Fan::Create(Vec2(64 * 16, 64 * 4), 7, Fan::Dir::RIGHT, 7, true);
		//���M��
		Kanetuki::Create(Vec2(64 * 16, 64 * 12 + 32), Vec2(64 * 3, 64), Kanetuki::Angle::UP, true);
		//���X�@
		auto seihyouki = Seihyouki::Create(Vec2(64 * 3, 64 * 4), Vec2(64 * 2, 64), Seihyouki::Angle::RIGHT);
		//switch
		Switch::Create(Vec2(64 * 2, 64 * 9), std::vector<std::shared_ptr<GameObject>>{seihyouki}, Switch::TargetType::IceMachine);
		//��������
		auto door1 = Door::Create(Vec2(64 * 3, 64 * 11), Vec2(64 * 3, 32), false, Door::Direction::WIDTH);
		auto door2 = Door::Create(Vec2(64 * 3, 64 * 13), Vec2(64 * 3, 32), false, Door::Direction::WIDTH);
		door1->SetTexture(&doorTex);
		door2->SetTexture(&doorTex);
		//�d���X�C�b�`
		auto ws1 = WeightSwitch::Create(Vec2(64, 64 * 9 + 34), Vec2(64, 30), 1, std::vector<std::shared_ptr<GameObject>>{door2});
		ws1->SetTexture(&WswitchTex);
		//WeightSwitch::Create(Vec2())
		break;
	}
	case 15:	//�X�e�[�W3
	{
		//map����
		auto mapload = Map::Create((std::string)"stage3.csv");
		//���̈ʒu
		_waterpos = mapload->getWaterPos();

		//�Q�[���̃T�E���h�Ɏg�p
		sound.create(gamesoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//��@
		Vec2 fanpos[5] = { Vec2(64 * 11,64 * 6),Vec2(64 * 20,64 * 4),Vec2(64 * 26,64 * 17),Vec2(64 * 30,64 * 23),Vec2(64 * 34,64 * 27) };
		auto fan1 = Fan::Create(fanpos[0], 7, Fan::Dir::LEFT, 64 * 7, true);
		auto fan2 = Fan::Create(fanpos[1], 11, Fan::Dir::RIGHT, 64 * 5, true);
		auto fan3 = Fan::Create(fanpos[2], 19, Fan::Dir::LEFT, 64 * 19, true);
		auto fan4 = Fan::Create(fanpos[3], 8, Fan::Dir::RIGHT, 64 * 2, true);
		auto fan5 = Fan::Create(fanpos[4], 4.5f, Fan::Dir::LEFT, 64 * 5, false);
		//���M��
		auto kanetsuki1 = Kanetuki::Create(Vec2(64 * 21, 64 * 21 - 20), Vec2(64 * 3, 84), Kanetuki::Angle::UP, false);
		auto kanetsuki4 = Kanetuki::Create(Vec2(64 * 18, 64 * 29), Vec2(64 * 5, 64 + 32), Kanetuki::Angle::BOTTOM, true);
		auto kanetsuki9 = Kanetuki::Create(Vec2(64 * 33, 64 * 32 - 20), Vec2(64 * 2, 84), Kanetuki::Angle::UP, true);
		//���X�@
		auto seihyouki1 = Seihyouki::Create(Vec2(64 * 9, 64 * 12), Vec2(64 * 2, 64), Seihyouki::Angle::LEFT);
		auto seihyouki3 = Seihyouki::Create(Vec2(64 * 9, 64 * 22), Vec2(64 * 2, 64), Seihyouki::Angle::LEFT);
		//��@�X�C�b�`
		auto fanSwitch1 = Switch::Create(Vec2(64 * 19, 64 * 12), std::vector<std::shared_ptr<GameObject>>{fan2, fan3}, Switch::TargetType::Fan);
		auto fanSwitch2 = Switch::Create(Vec2(64 * 31, 64 * 31), std::vector<std::shared_ptr<GameObject>>{fan4, fan5}, Switch::TargetType::Fan);
		//���M��X�C�b�`
		auto heaterSwitch1 = Switch::Create(Vec2(64 * 20, 64 * 20), std::vector<std::shared_ptr<GameObject>>{kanetsuki1/*, kanetsuki2, kanetsuki3*/}, Switch::TargetType::Heater);
		//���X�@�X�C�b�`
		auto iceSwitch = Switch::Create(Vec2(64 * 12, 64 * 20), std::vector<std::shared_ptr<GameObject>>{seihyouki1, /*seihyouki2,*/ seihyouki3/*, seihyouki4*/}, Switch::TargetType::IceMachine);
		//�u���b�N
		auto block = Block::Create(Vec2(64 * 20, 64 * 29));
		auto block2 = Block::Create(Vec2(64 * 33, 64 * 11));
		break;
	}
	//case 9:	//�`���[�g���A���X
	//{
	//	//�ʒu�ύX
	//	_waterpos.x = 6 * 64 - 25;
	//	_waterpos.y = 64 * 12;
	//	{
	//		//map����
	//		auto mapload = Map::Create((std::string)"water3.csv");
	//		//�`���[�g���A���̃T�E���h�Ɏg�p
	//		sound.create(tutorialsoundname, true);
	//		sound.volume(0.0f);
	//		OGge->soundManager->SetSound(&sound);
	//		sound.play();

	//		//���M�퐶��
	//		auto kanetuki1 = Kanetuki::Create(Vec2(64 * 21, 64 * 17), Vec2(64 * 2, 64), Kanetuki::Angle::UP, false);
	//		//auto kanetuki2 = Kanetuki::Create(Vec2(64 * 22, 64 * 17), false);
	//		//��@����
	//		auto fan = Fan::Create(Vec2(64 * 14, 64 * 7), 13, Fan::Dir::RIGHT, 64 * 5, true);
	//		//���M��p�X�C�b�`����
	//		auto swich = Switch::Create(Vec2(64 * 18, 64 * 16), std::vector<std::shared_ptr<GameObject>>{kanetuki1/*, kanetuki2*/}, Switch::TargetType::Heater);
	//		break;
	//	}
	//}
	default:
		std::cout << "�}�b�v�ԍ������݂��܂���" << std::endl;
		break;
	}	//����������
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
	auto back2Img = Back::Create("back2Test.png", 1920, 1080);
	back2Img->SetScroll();
	back2Img->SetDrawOrder(0.0f);
	//���������ō~���Ă��鎞�Ԃ̏�����
	this->timecnt = 0;
	//���̐���
	auto water = Water::Create(_waterpos);
	//�摜��n��
	water->SetTexture(&this->waterTex);

	//�^�X�N�ɖ��O��o�^
	__super::Init((std::string)"game");
	//�Q�[���N���A����𐶐�
	auto gameprocess = GameManager::Create();
	//����
	auto ornament = Ornament::Create();
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
	auto player = OGge->GetTask<Player>("Player");
	if (player)
	{
		if (OGge->in->down(In::D2) && !player->GetInput()) {
			if (!player->GetInputAuto())
			{
				OGge->SetPause(true);
			}
		}
	}

	//�t�F�[�h�A�E�g
	//�t�F�[�h�C��
	if (canvolControl)
	{
		sound.volume(volControl.FadeIn(canvolControl));
	}
	if (canvolControl == false)
	{
		sound.volume(volControl.FadeOut(true));
	}


	//UI
	UImng_->UpDate();
}
//-------------------------------------------------------------------------------------------------
void Game::Render2D()
{
	//�������ʒu�̃p�C�v
}
//-------------------------------------------------------------------------------------------------
bool Game::Finalize()
{
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
	auto gamepros = OGge->GetTasks<GameManager>("GM");
	for (auto id = (*gamepros).begin(); id != (*gamepros).end(); ++id)
	{
		(*id)->Kill();
	}
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		(*id)->Kill();
	}
	auto timers = OGge->GetTasks<Timer>("Timer");
	for (auto id = (*timers).begin(); id != (*timers).end(); ++id)
	{
		(*id)->Kill();
	}
	auto pauses = OGge->GetTasks<Pause>("pause");
	for (auto id = pauses->begin(); id != pauses->end(); ++id)
	{
		(*id)->Kill();
	}
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
	auto effects = OGge->GetTasks<Effect>("effect");
	for (auto id = effects->begin(); id != effects->end(); ++id)
	{
		(*id)->Kill();
	}
	auto ornament = OGge->GetTasks<Ornament>("Ornament");
	for (auto id = ornament->begin(); id != ornament->end(); ++id)
	{
		(*id)->Kill();
	}
	auto timer = OGge->GetTasks<TimeSign>("timesign");
	for (auto id = timer->begin(); id != timer->end(); ++id)
	{
		(*id)->Kill();
	}
	auto goalDirection = OGge->GetTasks<GoalDirection>("GoalDirection");
	for (auto id = goalDirection->begin(); id != goalDirection->end(); ++id)
	{
		(*id)->Kill();
	}
	auto doors = OGge->GetTasks<Door>("Door");
	for (auto id = doors->begin(); id != doors->end(); ++id)
	{
		(*id)->Kill();
	}
	auto ws = OGge->GetTasks<WeightSwitch>("WeightSwitch");
	for (auto id = ws->begin(); id != ws->end(); ++id) {
		(*id)->Kill();
	}
	rm->DeleteTexture((std::string)"playerTex");
	rm->DeleteTexture((std::string)"waterTex");
	rm->DeleteTexture((std::string)"Effect");
	rm->DeleteTexture((std::string)"paintTex");
	rm->DeleteTexture((std::string)"sandsmoke");
	rm->DeleteTexture((std::string)"waterRed");
	rm->DeleteTexture((std::string)"waterBlue");
	rm->DeleteTexture((std::string)"waterPurple");
	rm->DeleteTexture((std::string)"steam");
	rm->DeleteTexture((std::string)"goalTex");
	rm->DeleteTexture((std::string)"fireIce");
	rm->DeleteTexture((std::string)"goalDirectionTex");
	rm->DeleteTexture((std::string)"arrowflowerTex");
	this->waterTex.Finalize();
	this->playerTex.Finalize();
	this->fanTex.Finalize();
	this->EffectTest.Finalize();
	this->waterBlue.Finalize();
	this->waterPurple.Finalize();
	this->waterRed.Finalize();
	this->PaintTex.Finalize();
	this->Effectsond.Finalize();
	this->texSteam.Finalize();
	this->goalTex.Finalize();
	this->goalDirectionTex.Finalize();
	this->arrowflower.Finalize();
	this->doorTex.Finalize();
	return true;
}
//-------------------------------------------------------------------------------------------------
//�J��������
void Game::Camera_move()
{
	//�J�����̈ړ�
	auto goals = OGge->GetTasks<Goal>("Goal");
	for (auto id = goals->begin(); id != goals->end(); ++id)
	{
		if (!(*id)->GetLock())
		{
			return;
		}
	}
	auto player = OGge->GetTask<Player>("Player");
	auto map = OGge->GetTask<Map>("map");
	if (player && map)
	{
		if (!player->GetInputAuto())
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