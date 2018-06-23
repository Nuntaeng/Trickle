#include "Task_Result.h"
#include "Chara\Chara.h"
#include "Back\Back.h"
#include "Map\Map.h"
#include "Effect/Effect.h"
#include "StageSelect.h"

Result::Result() {
	this->taskName = "Result";
	__super::Init(taskName);
	starsoundname = "kira2.wav";
}
Result::~Result() {
	this->Finalize();
}

bool Result::Initialize() {
	fontui.Create((std::string)"fontui.png");
	numberui.Create((std::string)"number.png");

	backTex.Create((std::string)"back.png");
	this->starTex.Create((std::string)"resultstar.png");
	this->frameTex.Create((std::string)"resultframe.png");
	this->stareffectTex.Create((std::string)"stareffect.png");
	//this->clearTex

	//�T�E���h�̐���
	soundstar.create(starsoundname, false);    //���̂͂܂鉹��
	soundstar.volume(1.0f);

	//sound.create(soundname, true);           //BGM������
	//sound.volume(1.0f);
	//sound.play();

	this->nowMode = Mode1;
	auto npc = Chara::Create((std::string)"player.png", Vec2(-120, 64 * 8));
	npc->SetDirection(Chara::Direction::RIGHT);
	npc->Set(Vec2(-120, 64 * 8), Vec2(64 * 2, 64 * 8), 15.f);
	Map::Create((std::string)"result.csv");
	//TIME
	time.nowWH = Vec2(0, 0);
	time.pos = Vec2(150 + 64 * 2, 280 + 32);
	for (int i = 0; i < 3; ++i) {
		//���̘g
		starFrame[i].nowWH = Vec2(0, 0);
		starFrame[i].pos = Vec2(300 + 64 + i * 200, 370 + 64 - 8 * i);
		//��
		star[i].nowWH = Vec2(512, 512);
		star[i].pos = Vec2(1280, 300);
		star[i].bezcnt = 0.0f;
		star[i].angle = -5;
		//���o���t���O
		starFlag[i] = false;
		starturn[i] = false;
		num[i] = 0;
	}
	num[3] = 0;
	cnt = 0;
	this->maxTrueNumber = -1;
	this->RoadData();
	return true;
}
void Result::UpDate() {
	OGge->camera->SetSize(Vec2(1280, 720));
	auto npc = OGge->GetTask<Chara>("Chara");
	float pretimew = 0, pretimeh = 0;
	float prestarw[3] = {}, prestarh[3] = {};
	float starytmp[3] = {};
	float presfw = 0, presfh = 0;
	switch (nowMode) {
	case Mode1:
		npc->AutoMove();
		if (!npc->isAutoPlay()) {
			this->nowMode = Mode2;
		}
		break;
	case Mode2:
		++cnt;
		//TIME
		if (time.nowWH.x < 64 * 4) {
			pretimew = time.nowWH.x;
			time.nowWH.x = time.easeX.expo.In(time.easeX.Time(3), 0.0f, 64 * 4, 3);
			time.pos.x -= (time.nowWH.x - pretimew) / 2.0f;
			if (time.nowWH.x >= 64 * 4) {
				time.nowWH.x = 64 * 4;
				time.pos.x = 150;
			}
		}
		if (time.nowWH.y < 64) {
			pretimeh = time.nowWH.y;
			time.nowWH.y = time.easeY.bounce.In(time.easeY.Time(3), 0.0f, 64, 3);
			time.pos.y -= (time.nowWH.y - pretimeh) / 2.0f;
			if (time.nowWH.y >= 64) {
				time.nowWH.y = 64;
				time.pos.y = 280;
			}
		}
		//���̘g
		for (int i = 0; i < 3; ++i) {
			if (starFrame[i].nowWH.x < 64 * 2) {
				presfw = starFrame[i].nowWH.x;
				starFrame[i].nowWH.x = starFrame[i].easeX.expo.In(starFrame[i].easeX.Time(3), 0.0f, 64 * 2, 3);
				starFrame[i].pos.x -= (starFrame[i].nowWH.x - presfw) / 2.0f;
				if (starFrame[i].nowWH.x >= 64 * 2) {
					starFrame[i].nowWH.x = 64 * 2;
					starFrame[i].pos.x = 300 + i * 200;
				}
			}
			if (starFrame[i].nowWH.y < 64 * 2) {
				presfh = starFrame[i].nowWH.y;
				starFrame[i].nowWH.y = starFrame[i].easeY.bounce.In(starFrame[i].easeY.Time(3), 0.0f, 64 * 2, 3);
				starFrame[i].pos.y -= (starFrame[i].nowWH.y - presfh) / 2.0f;
				if (starFrame[i].nowWH.y >= 64 * 2) {
					starFrame[i].nowWH.y = 64 * 2;
					starFrame[i].pos.y = 370 - i * 8;
				}
			}
		}
		if (cnt >= 100) {
			this->nowMode = Mode3;
			cnt = 0;
		}
		break;
	case Mode3:
		++cnt;
		if (cnt < 120) {
			for (int i = 0; i < 4; ++i) {
				num[i] = random::GetRand(0, 9);
			}
		}
		else {
			for (int i = 0; i < 4; ++i) {
				num[i] = this->timer[i];
			}
		}
		if (cnt >= 150) {
			this->nowMode = Mode4;
			cnt = 0;
		}
		break;
	case Mode4:
		if (this->maxTrueNumber == -1)
		{
			this->nowMode = Mode5;
			break;
		}
		++cnt;
		//���o��
		for (int i = 0; i < 3; ++i) {
			if (starFlag[i] && cnt >= 20 * i) {	
				star[i].bezcnt += 0.03f;
				star[i].angle += 15;
				//X
				star[i].pos.x = (1 - star[i].bezcnt)*(1 - star[i].bezcnt) * 1280 + 2 * (1 - star[i].bezcnt)*star[i].bezcnt * 1000 + star[i].bezcnt * star[i].bezcnt * (300 + i * 200);
					if (star[i].pos.x <= 300 + i * 200) {
						star[i].pos.x = 300 + i * 200;
					}
				//Y
				star[i].pos.y = (1 - star[i].bezcnt)*(1 - star[i].bezcnt) * 300 + 2 * (1 - star[i].bezcnt)*star[i].bezcnt * 0 + star[i].bezcnt * star[i].bezcnt * (370 - i * 8);
				if (star[i].pos.y >= 370 - i * 8) {
					star[i].pos.y = 370 - i * 8;
				}
				//W,H�k��
				star[i].nowWH.x = star[i].nowWH.y = star[i].easeX.cubic.Out(star[i].easeX.Time(5), 512, 128 - 512, 5);
				if (star[i].nowWH.x <= 128) {
					star[i].nowWH.x = star[i].nowWH.y = 128;
				}
				//��~�n�_�ɓ���
				if (star[i].pos == Vec2(300 + i * 200, 370 - i * 8) && star[i].nowWH == Vec2(128, 128)) {
					star[i].angle = -5;
					//�T�E���h�̍Đ�
					soundstar.play();

					//auto eff = Effect::Create(Vec2(300 + i * 200, 370 - i * 8), Vec2(32, 32), Vec2(256, 256), 5, 5);
					//eff->SetMode(Effect::Mode::Decrease);
					//eff->SetTexture(&this->stareffectTex);
					//eff->Set(eff->position, Vec2(eff->position.x + random::GetRand(-30, 30), eff->position.y + random::GetRand(-30, 30)));
				}
			}
		}
		if (star[this->maxTrueNumber].pos == Vec2(300 + this->maxTrueNumber * 200, 370 - this->maxTrueNumber * 8) && star[this->maxTrueNumber].nowWH == Vec2(128,128)) {
			this->nowMode = Mode5;
		}
		break;
	case Mode5:
		//�A�j���[�V�������I���܂�(�T��W�����v�{�ʒu����)�͓��͂ł��Ȃ�
		if (npc->happyCnt < 7) {
			npc->Happy(7);
			//�N���AUI�o��(������)
		}
		else {
			if (OGge->in->down(Input::in::B2))
			{
				npc->MoveReset();
				npc->Set(npc->position, Vec2(1500.f, npc->position.y), 30.f);
				this->nowMode = Mode6;
			}
		}

		break;
	case Mode6:
		//�v���C���ޏ�
		npc->AutoMove();
		if (npc->position.x >=  1450) {
			this->nowMode = Non;
			this->Kill();
		}
		break;
	case Non:
	default:
		break;
	}
}
void Result::Render2D() {
	//�w�i
	{
		backTex.Draw(Box2D(0, 0, 1280, 720), Box2D(0, 0, 1280, 720));
	}
	//���j�^�[�g
	{
		Box2D draw((1280 - 1400) / 2, 720 - 700 - 32, 1400, 700);
		draw.OffsetSize();
		Box2D src(0, 0, 1000, 500);
		frameTex.Draw(draw, src);
	}
	//Result
	{
		Box2D draw(470, 110, 64 * 6, 64);
		draw.OffsetSize();
		Box2D src = Box2D(0, 64 * 2, 64 * 6, 64);
		src.OffsetSize();
		fontui.Rotate(-5);
		fontui.Draw(draw, src);
	}
	//rm->GetTextureData((std::string)"fontui")->Draw(draw, src);
	//TIME
	{
		Box2D draw(time.pos.x, time.pos.y, time.nowWH.x, time.nowWH.y);
		draw.OffsetSize();
		Box2D src(0, 64 * 3, 64 * 4, 64);
		src.OffsetSize();
		fontui.Draw(draw, src);
	}
	//���̘g
	{
		for (int i = 0; i < 3; ++i) {
			Box2D draw(starFrame[i].pos.x, starFrame[i].pos.y, starFrame[i].nowWH.x, starFrame[i].nowWH.y);
			draw.OffsetSize();
			Box2D src(0, 0, 256, 256);
			starTex.Rotate(-5);
			starTex.Draw(draw, src);
		}
	}
	//�^�C��
	{
		if (nowMode >= Mode3) {
			//����
			for (int i = 0; i < 4; ++i) {
				Box2D draw(150 + 64 * 4 + 100 + 96 * i, 250 - 7 * i, 96, 96);
				draw.OffsetSize();
				Box2D src(64 * num[i], 0, 64, 64);
				src.OffsetSize();
				numberui.Rotate(-5);
				numberui.Draw(draw, src);
			}
			//�F
			Box2D draw(150 + 96 * 4 + 100 + 40, 260 - 17, 64, 64);
			draw.OffsetSize();
			Box2D src(64 * 10, 0, 40, 64);
			src.OffsetSize();
			numberui.Draw(draw, src);
		}
	}
	//��
	{
		if (nowMode >= Mode4) {
			for (int i = 0; i < 3; ++i) {
				Box2D draw(star[i].pos, star[i].nowWH);
				draw.OffsetSize();
				Box2D src(256, 0, 256, 256);
				src.OffsetSize();
				starTex.Rotate(star[i].angle);
				starTex.Draw(draw, src);
			}
		}
	}
}
bool Result::Finalize() {
	//�������
	this->backTex.Finalize();
	//this->clearTex.Finalize();
	this->frameTex.Finalize();
	this->fontui.Finalize();
	this->numberui.Finalize();
	this->starTex.Finalize();
	auto effects = OGge->GetTasks<Effect>("effect");
	for (auto id = effects->begin(); id != effects->end(); ++id)
	{
		(*id)->Kill();
	}
	auto npc = OGge->GetTask<Chara>("Chara");
	if (npc) { npc->Kill(); }
	auto map = OGge->GetTask<Map>("map");
	if (map) { map->Kill(); }
	//�X�e�[�W�Z���N�g�ɖ߂�
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		OGge->ChengeTask();
		StageSelect::Create();
	}

	return true;
}
void Result::RoadData()
{
	std::ifstream ifs("./data/Result/save" + std::to_string(*MapNum) + ".bin", std::ios::in | std::ios::binary);
	if (!ifs)
	{
		this->Kill();
	}
	std::string line;
	std::getline(ifs, line);
	std::istringstream* is = new std::istringstream(line);
	std::string text;
	for (int i = 0; i < 2; ++i)
	{
		int t_time;
		std::getline(*is, text, ',');
		(std::stringstream)text >> t_time;
		this->timer[i * 2] = t_time / 10;
		this->timer[i * 2 + 1] = t_time % 10;
	}
	std::getline(ifs, line);
	delete is;
	is = new std::istringstream(line);
	for (int i = 0; i < 3; ++i)
	{
		std::getline(*is, text, ',');
		if (text == "t")
		{
			this->starFlag[i] = true;
			this->maxTrueNumber = (__int8)i;
		}
	}
	delete is;
}

Result::SP Result::Create(bool flag) {
	Result::SP to = Result::SP(new Result());
	if (to)
	{
		to->me = to;
		if (flag)
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




////�ʃ^�X�N��ʃI�u�W�F�N�g�𐶐�����ꍇ�����ɂ���class�̏����ꂽh���C���N���[�h����
//#include "Task\StageSelect.h"
//#include "GameProcessManagement\FlagUI.h"
//#include "Player\ResultPlayer.h"
//#include "GameProcessManagement\ClearUI.h"
//#include "GameProcessManagement\GoalTimeUI.h"
//#include "GameProcessManagement\MissionUI.h"
//#include "GameProcessManagement\FrameTime.h"
//#include "Effect/SterEffect.h"
////#include "GameProcessManagement/GameProcessManagement.h"
//#include "Effect\SterEffect.h"
//#include <algorithm>
/////285 
//
//bool Result::Initialize()
//{
//	//-----------------------------
//	//�������ɏ������鏉�����������L�q
//	//-----------------------------
//	this->taskName = "Result";		//�������Ɏg�����߂̖���o�^����
//	__super::Init(taskName);		//TaskObject���̏������s��
//
//	//�t���O�̐ݒ�
//	this->Result_DataInput();
//	this->Flag = 0;
//
//	this->image.Create((std::string)"back.png");
//	this->maptile.Create((std::string)"tile.jpg");
//
//	SetDrawOrder(0.0f);
//
//	Vec2 camerasize = OGge->camera->GetSize();
//	Vec2 windowsize = OGge->window->GetSize();
//	//�J�����̃T�C�Y�ƃE�B���h�E�ɂ�����A�X�y�N�g��̌v�Z
//	Vec2 aspect = Vec2(camerasize.x / windowsize.x, camerasize.y / windowsize.y);
//
//	//�����t���O�����Z�b�g����
//	this->createtask.ResetCreateFlag();
//	this->createtask.ResetNextFlag();
//	this->createtask.SetNextFlag(CreateFlag::Timeui);
//
//	//���U���g��ʂɕ\���ɂ���
//	auto player = ResultPlayer::Create(Vec2(-96, (int)camerasize.y - 50 - 96), Vec2(3, 0));
//	auto mission = MissionUI::Create();
//	std::cout << "���ʉ�ʏ����@������" << std::endl;
//	return true;
//}
//
//void Result::UpDate()
//{
//	//--------------------
//	//�X�V���ɍs���������L�q
//	//--------------------
//	//�^�C�g���V�[���֑J��
//	
//	//�������܂��`�F�b�N����
//	this->UI_Think();
//	//�t���O�ɂ����Create����
//	this->UI_Create();
//
//	auto resultplayer = OGge->GetTask<ResultPlayer>("ResultPlayer");
//	if (!resultplayer)
//	{
//		if (OGge->in->down(In::B2))
//		{
//			Kill();
//		}
//	}
//	
//}
//void Result::Render2D()
//{
//	//--------------------
//	//�`�掞�ɍs���������L�q
//	//--------------------
//	Vec2 camerasize = OGge->camera->GetSize();
//	{
//		Box2D draw(Vec2(0, 0), camerasize);
//		draw.OffsetSize();
//		Box2D src = this->backSrc;
//		src.OffsetSize();
//		image.Draw(draw, src);
//	}
//	{
//		int count = 0;
//		for (int y = camerasize.y - 50; y <= camerasize.y; y += 64)
//		{
//			for (int x = 0; x <= camerasize.x / 64; ++x)
//			{
//				Box2D draw(Vec2(x * 64, (int)camerasize.y - 50 + count * 64), Vec2(64, 64));
//				draw.OffsetSize();
//				Box2D src = this->maptileSrc;
//				src.OffsetSize();
//				maptile.Draw(draw, src);
//			}
//			count++;
//		}
//		
//	}
//}
//bool Result::Finalize()
//{
//	//-----------------------------------------
//	//���̃I�u�W�F�N�g�����ł���Ƃ��ɍs���������L�q
//	//-----------------------------------------
//	//���̃^�X�N����邩���A�v���P�[�V�������I���\�肩�ǂ���
//	if (this->GetNextTask() && !OGge->GetDeleteEngine())
//	{
//		image.Finalize();
//		maptile.Finalize();
//
//		auto player = OGge->GetTasks<ResultPlayer>("ResultPlayer");
//		auto ster = OGge->GetTasks<FlagUI>("Ster");
//		auto clear = OGge->GetTasks<ClearUI>("ClearUI");
//		auto effect = OGge->GetTasks<SterEffect>("SterEffect");
//		auto goaltime = OGge->GetTasks<GoalTimeUI>("GoalTimeUI");
//		auto mission = OGge->GetTasks<MissionUI>("MissionUI");
//		auto frametime = OGge->GetTasks<FrameTimeUI>("FrameTimeUI");
//
//		for (auto id = (*ster).begin(); id != (*ster).end(); ++id)
//		{
//			(*id)->Kill();
//		}
//		for (auto id = (*player).begin(); id != (*player).end(); ++id)
//		{
//			(*id)->Kill();
//		}
//		for (auto id = (*clear).begin(); id != (*clear).end(); ++id)
//		{
//			(*id)->Kill();
//		}
//		for (auto id = (*goaltime).begin(); id != (*goaltime).end(); ++id)
//		{
//			(*id)->Kill();
//		}
//		for (auto id = (*effect).begin(); id != (*effect).end(); ++id)
//		{
//			(*id)->Kill();
//		}
//		for (auto id = (*frametime).begin(); id != (*frametime).end(); ++id)
//		{
//			(*id)->Kill();
//		}
//		for (auto id = (*mission).begin(); id != (*mission).end(); ++id)
//		{
//			(*id)->Kill();
//		}
//		auto stageselect = StageSelect::Create();
//	}
//	return true;
//}
//void Result::CreateTask::ResetCreateFlag()
//{
//	this->createflag &= ~this->createflag;
//}
//void Result::CreateTask::ResetNextFlag()
//{
//	this->nextflag &= ~this->nextflag;
//}
//void Result::CreateTask::SetCreateFlag(CreateFlag flag)
//{
//	this->createflag |= flag;
//}
//void Result::CreateTask::SetNextFlag(CreateFlag flag)
//{
//	this->nextflag |= flag;
//}
//void Result::UI_Think()
//{
//	switch (this->createtask.nextflag)
//	{
//	case 1 << 0:
//		if ((this->createtask.nextflag & 0x0F) == CreateFlag::Timeui)
//		{
//			auto player = OGge->GetTask<ResultPlayer>("ResultPlayer");
//			auto missonUI = OGge->GetTask<MissionUI>("MissionUI");
//			if (player != nullptr && missonUI != nullptr)
//			{
//				//Player���~�܂�����E�E�E
//				if (player->GetResetWalkStop() && missonUI->isEasingPleyfinish())
//				{
//					this->createtask.SetCreateFlag(CreateFlag::Timeui);
//				}
//			}
//		}
//		break;
//	case 1 << 1:
//		if ((this->createtask.nextflag & 0x0F) == CreateFlag::Starui)
//		{
//			auto frametimeUI = OGge->GetTasks<FrameTimeUI>("FrameTimeUI");
//			for (auto id = (*frametimeUI).begin(); id != (*frametimeUI).end(); ++id)
//			{
//				this->createtask.SetCreateFlag(CreateFlag::Starui);
//			}
//		}
//		break;
//	case 1 << 2:
//		if ((this->createtask.nextflag & 0x0F) == CreateFlag::Effect)
//		{
//			auto sters = OGge->GetTasks<FlagUI>("Ster");
//			for (auto id = (*sters).begin(); id != (*sters).end(); ++id)
//			{
//				if ((*id)->is_Scale())
//				{
//					this->createtask.SetCreateFlag(CreateFlag::Effect);
//				}
//			}
//
//		}
//		break;
//	case 1 << 3:
//		if ((this->createtask.nextflag & 0x0F) == CreateFlag::Clearui)
//		{
//			auto sters = OGge->GetTasks<FlagUI>("Ster");
//			std::vector<bool> flag;
//			for (auto id = (*sters).begin(); id != (*sters).end(); ++id)
//			{
//				flag.push_back((*id)->GetEffectEnd());
//			}
//			//�S�Ă�Effect�̉��o���I��������
//			for (auto id = (*sters).begin(); id != (*sters).end(); ++id)
//			{
//				if (std::all_of(flag.begin(), flag.end(), [](bool flag) {return flag == true; }))
//				{
//					this->createtask.SetCreateFlag(CreateFlag::Clearui);
//				}
//			}
//		}
//		break;
//	default:
//		break;
//	}
//}
//void Result::UI_Create()
//{
//	///���ӁI�I�@�����̓t���O���Z�b�g����1�t���[���̂ݓ������֐��ł��B
//	Vec2 camerasize = OGge->camera->GetSize();
//	Vec2 windowsize = OGge->window->GetSize();
//	//�J�����̃T�C�Y�ƃE�B���h�E�ɂ�����A�X�y�N�g��̌v�Z
//	Vec2 aspect = Vec2(camerasize.x / windowsize.x, camerasize.y / windowsize.y);
//
//	switch (this->createtask.createflag)
//	{
//	case 1 << 0:
//		//Player�����̂Ƃ���܂ŕ�������E�E�E
//		if ((this->createtask.createflag & CreateFlag::Timeui) == CreateFlag::Timeui)
//		{
//			auto goaltime = GoalTimeUI::Create(Vec2(camerasize.x * 0.15f, camerasize.y * 0.2f));
//			for (int i = 0; i < 5; ++i)
//			{
//				auto time = FrameTimeUI::Create(Vec2(goaltime->position.x + goaltime->Scale.x + (20 + i * 64), goaltime->position.y + 20), i, FrameTime);
//			}
//			//��������t���O�����Z�b�g����
//			this->createtask.ResetCreateFlag();
//			this->createtask.ResetNextFlag();
//			//���ɐ�������^�X�N
//			this->createtask.SetNextFlag(CreateFlag::Starui);
//		}
//		break;
//	case 1 << 1:
//		if ((this->createtask.createflag & CreateFlag::Starui) == CreateFlag::Starui)
//		{
//			//int selectflag[3] = { GameProcessManagement::Flag1,GameProcessManagement::Flag2,GameProcessManagement::Flag4 };
//
//			//for (int i = 0; i < 3; ++i)
//			//{
//			//	auto ster = FlagUI::Create(Vec2((camerasize.x / 2 - 200) + 100 * (i + 1), camerasize.y * 0.5f), selectflag[i]);
//			//}
//			//�t���O�̃��Z�b�g
//			this->createtask.ResetCreateFlag();
//			this->createtask.ResetNextFlag();
//			//���ɐ�������^�X�N
//			this->createtask.SetNextFlag(CreateFlag::Effect);
//		}
//		break;
//	case 1 << 2:
//		if ((this->createtask.createflag & CreateFlag::Effect) == CreateFlag::Effect)
//		{
//			auto sters = OGge->GetTasks<FlagUI>("Ster");
//
//			//�ŏ������͏����Ȃ��Ő�������
//			{
//				int count = 0;
//				for (auto id = sters->begin(); id != sters->end(); ++id, ++count)
//				{
//					if (count == 0)
//					{
//						auto effect = SterEffect::Create((*id));
//					}
//					else
//					{
//						auto Effect = OGge->GetTasks<SterEffect>("SterEffect");
//						if (!Effect)
//						{
//							continue;
//						}
//						auto effect = SterEffect::Create((*id), *(Effect->begin() + count - 1));
//					}
//				}
//			}
//			//��������t���O�����Z�b�g����
//			this->createtask.ResetCreateFlag();
//			this->createtask.ResetNextFlag();
//			//���ɐ�������^�X�N
//			this->createtask.SetNextFlag(CreateFlag::Clearui);
//		}
//		break;
//	case 1 << 3:
//		if ((this->createtask.createflag & CreateFlag::Clearui) == CreateFlag::Clearui)
//		{
//			auto clearui = ClearUI::Create(Vec2(camerasize.x * 0.70f, camerasize.y / 2));
//			//�t���O�̃��Z�b�g
//			this->createtask.ResetCreateFlag();
//			this->createtask.ResetNextFlag();
//			//���ɐ�������^�X�N
//			this->createtask.SetNextFlag(CreateFlag::NON);
//		}
//		break;
//	default:
//		break;
//	}	
//}
//int Result::to_String(std::string& text)
//{
//	std::istringstream ss;
//	ss = std::istringstream(text);
//
//	int num = atoi(text.c_str());
//	ss >> num;
//
//	return num;
//}
//void Result::Result_DataInput()
//{
//	std::string GameFalg;			//�Q�[���t���O
//	//�f�[�^�̓ǂݍ���
//	std::ifstream fin(TimeFilePath);
//
//	if (!fin)
//	{
//		return;
//	}
//	//�ǂݍ��񂾃f�[�^�����Ă����ϐ�
//	std::string line;
//	//�t�@�C���S�̂̃e�L�X�g��ǂݍ���
//	while (std::getline(fin, line))
//	{
//		//������𑀍삷�邽�߂̓��̓N���X�A���ڃA�N�Z�X����
//		std::istringstream _fin(line);
//		//�ꎚ�������ݕϐ�
//		std::string text;
//		
//		//�^�C���̏�������
//		std::getline(_fin, text, ',');
//		(std::stringstream)text >> FrameTime;
//
//		//�X�e�[�W���Ƃ̃t���O����������
//		std::string nowStagenumber;
//		int nowStage = 0;
//
//		//�t���O�̓ǂݍ���
//		while (std::getline(_fin, text, ','))
//		{
//			if (text == "Stage1")
//			{
//				nowStagenumber = text.substr(5);
//				//�����񂩂�int�^�ɂ���
//				nowStage = this->to_String(nowStagenumber);
//			}
//			else if(text == "Stage2")
//			{
//				nowStagenumber = text.substr(5);
//				//�����񂩂�int�^�ɂ���
//				nowStage = this->to_String(nowStagenumber);
//			}
//		}
//	}
//	fin.close();
//}
//int Result::GetFlag()
//{
//	return this->Flag;
//}
////----------------------------
////�������牺��class���̂ݕύX����
////�ق��͕ύX���Ȃ�����
////----------------------------
//Result::Result()
//{
//	std::cout << "���ʉ�ʏ����@����" << std::endl;
//	//�J�������W�����ɖ߂�
//	OGge->camera->SetPos(Vec2(0, 0));
//	//�J�����̃T�C�Y�����ɖ߂�
//	OGge->camera->SetSize(Vec2(60 * 16 , 60 * 9));
//	FrameTime = 0;
//}
//
//Result::~Result()
//{
//	this->Finalize();
//	std::cout << "���ʉ�ʏ����@���" << std::endl;
//}
//
//Result::SP Result::Create(bool flag_)
//{
//
//	Result::SP to = Result::SP(new Result());
//	if (to)
//	{
//		to->me = to;
//		if (flag_)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize())
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}