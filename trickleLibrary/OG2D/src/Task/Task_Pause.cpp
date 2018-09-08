/*
* @file Task_Pause.cpp
* @brief �^�X�N�N���X�̒�`
* @author yokota_mariko
* @date 2018.9.9
*/

#include "Task\Task_Pause.h"
#include "Task\Task_Title.h"
#include "Task\StageSelect.h"
#include "Task\Task_Game.h"
#include "Load\LoadLogo.h"

Pause::Pause()
	:
	cursorsoundname("cursormove.wav"),
	dicisionsoundname("decision.wav")
{
	__super::SetDrawOrder(1.0f);
}
Pause::~Pause() {
	Finalize();
	//���̃^�X�N����
	CreateNextTask();
}
bool Pause::Initialize() {
	//�摜�ǂݍ���
	texCursor.Create((std::string)"gear2.png");
	texChoices = rm->GetTextureData("fontui");
	texTransparentBack.Create("TransparentBack.png");
	//�e�N�X�`���̃��l
	texColor = { 1.f,1.f,1.f,1.f };
	//�T�E���h�̐���
	//�J�[�\���̈ړ���
	cursorsound.create(cursorsoundname, false);
	cursorsound.volume(0.7f);
	//���艹
	decisionsound.create(dicisionsoundname, false);
	//���Ԋp�x
	gearAng = 0;
	//�J�[�\���ʒu����
	stateNum = 1;
	//�J�����ړ����t���O�͐܂�
	isCameraMoving = false;
	state = Non;
	//�}�b�v�^�X�N
	map = OGge->GetTask<Map>("map");
	//�^�X�N���o�^
	__super::Init((std::string)"pause");
	return true;
}
void Pause::PauseUpDate() {
	//���ԉ�]
	++gearAng;
	if (gearAng > 360) { gearAng = 0; }
	//�J�����ړ�
	MoveCamera();
	//�e�N�X�`���ʒu�X�V
	setTexPos();
	//�e�N�X�`���̃��l
	if (isCameraMoving) {
		texColor = { 0.f,0.f,0.f,0.1f };
	}
	else {
		texColor = { 1.f,1.f,1.f,1.f };
	}
	//�J�[�\���X�V
	moveCursor();
	//X�L�[(B�{�^��)��������
	if (OGge->in->down(In::B2)) {
		//���艹�Đ�
		decisionsound.play();
		ReleasePause();
		state = (State)stateNum;
		if (state != BackToGame) {
			CreateLoad();
		}
		else {
			this->Kill();
		}
	}
	//SPACE�L�[(START�{�^��)��������
	if (OGge->in->down(In::D2)) {
		//���艹�Đ�
		decisionsound.play();
		ReleasePause();
		this->Kill();
	}
}
void Pause::Render2D() {
	Vec2 cameraPos = OGge->camera->GetPos();
	//�w�i
	{
		Box2D draw(cameraPos.x - 16, cameraPos.y - 9, 1920.f + 16.f * 2.f, 1080.f + 9.f * 2.f);
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 720);
		src.OffsetSize();
		texTransparentBack.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, 0.6f));
	}
	//�J�[�\���̕\��
	{
		Box2D draw(cursorPos.x, cursorPos.y, 64.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 200, 200);
		src.OffsetSize();
		texCursor.Rotate((float)gearAng);
		texCursor.Draw(draw, src, texColor);
	}
	//Restart
	{
		Box2D draw(RestartPos.x, RestartPos.y, 64.f * 7, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 64 * 8, 64 * 7, 64);
		src.OffsetSize();
		texChoices->Draw(draw, src, texColor);
	}
	//Return
	{
		Box2D draw(ReturnPos.x, ReturnPos.y, 64.f * 11, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 64 * 9, 64 * 11, 64);
		src.OffsetSize();
		texChoices->Draw(draw, src, texColor);
	}
	//stageselect
	{
		Box2D draw(stageselectPos.x, stageselectPos.y, 64.f * 18, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 64 * 7, 64 * 19, 64);
		src.OffsetSize();
		texChoices->Draw(draw, src, texColor);
	}
}
bool Pause::Finalize() {
	//�g�p�摜�̉��
	texCursor.Finalize();
	texTransparentBack.Finalize();

	return true;
}
Pause::SP Pause::Create(bool flag_)
{
	auto to = Pause::SP(new Pause());
	if (to)
	{
		to->me = to;
		if (flag_) {
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize()) {
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
void Pause::MoveCamera() {
	//�X�e�B�b�N�̌X���l
	float stickSlopeX = OGge->in->axis(In::AXIS_RIGHT_X);
	float stickSlopeY = OGge->in->axis(In::AXIS_RIGHT_Y) * -1.f;
	//�J�����ړ�����
	if (checkCameraHitMap(OGge->camera->GetPos() + Vec2(stickSlopeX * 5.f, stickSlopeY * 5.f))) {
		OGge->camera->MovePos(Vec2(stickSlopeX * 5.f, stickSlopeY * 5.f));
		isCameraMoving = true;
	}
	if (stickSlopeX == 0 && stickSlopeY == 0) {
		isCameraMoving = false;
	}
}
bool Pause::checkCameraHitMap(Vec2 v) {
	return (v.x > 0
		&& v.x + OGge->camera->GetSize().x < map->mapSize.x * map->DrawSize.x
		&& v.y > 0
		&& v.x + OGge->camera->GetSize().y < map->mapSize.y * map->DrawSize.y);
}
void Pause::setTexPos() {
	Vec2 basePos = OGge->camera->GetSize() + OGge->camera->GetPos();
	ReturnPos = Vec2(basePos.x - 64 * 11, basePos.y - 300.f);
	RestartPos = Vec2(basePos.x - 64 * 8, basePos.y - 200.f);
	stageselectPos = Vec2(basePos.x - 64 * 19 + 50, basePos.y - 100.f);
	switch (stateNum) {
	case BackToGame:
		cursorPos = { ReturnPos.x - 80,ReturnPos.y };
		break;
	case Restart:
		cursorPos = { RestartPos.x - 80,RestartPos.y };
		break;
	case StageSelect:
		cursorPos = { stageselectPos.x - 80,stageselectPos.y };
		break;
	default:
		cursorPos = { 0,0 };
		break;
	}
}
void Pause::moveCursor() {
	//���̈ړ�
	if (OGge->in->down(Input::CU) || OGge->in->down(In::LU)) {
		stateNum = (stateNum <= 1) ? 3 : stateNum - 1;
		//�T�E���h�̍Đ�
		cursorsound.play();
	}
	if (OGge->in->down(Input::CD) || OGge->in->down(In::LD)) {
		stateNum = (stateNum >= 3) ? 1 : stateNum + 1;
		//�T�E���h�̍Đ�
		cursorsound.play();
	}
}
void Pause::ReleasePause() {
	//�|�[�Y����
	OGge->SetPause(false);
}
void Pause::CreateNextTask() {
	switch (state) {
	case Restart:
		Game::Create();
		//CreateLoad();
		break;
	case StageSelect:
		StageSelect::Create();
		//CreateLoad();
		break;
	case BackToGame:
	case Non:
	default:
		break;
	}
}
void Pause::CreateLoad() {
	auto load = Load::Create();
	if (load)
	{
		load->AddDeleteObjectName(OGge->GetTask<Game>("game")->GetTaskName());
		load->AddDeleteObjectName(this->GetTaskName());
		load->ALLTaskUpDateStop();
	}
}