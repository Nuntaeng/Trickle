#include "Task_TitleMovement.h"
#include "Back\Back.h"
#include "Chara\Chara.h"
#include "Map\Map.h"

TitleMovement::TitleMovement() {

}

TitleMovement::~TitleMovement() {
	this->Finalize();
}

bool TitleMovement::Initialize() {
	// �w�i�ǂݍ���
	auto back = Back::Create((std::string)"back.png", 1440, 810);

	// ���S�I�u�W�F�N�g����
	logo.Create((std::string)"on_editing.png");

	// �J�����ʒu�̈ړ��A����ȏ�̐������K�v�؎��H
	OGge->camera->SetPos(Vec2(0, 200));
	OGge->camera->SetSize(Vec2(1440, 810));

	// �}�b�v�𐶐��i�n�ʗp�j
	auto map = Map::Create((std::string)"title.csv");

	// ���^�p�v���C���[����
	auto player = Chara::Create((std::string)"player2.png", Vec2(790.f, 638.f));
	player->SetRecordEnable();
	
	//�@BGM����
	bgm = new Sound();
	bgm->create((std::string)"editTitle.wav", true);
	bgm->setVolume(1.f);
	rm->SetSoundData((std::string)"editTitleBGM", bgm);
	bgm->play();
	
	__super::Init((std::string)"titlemovement");
	__super::SetDrawOrder(0.5f);
	return true;
}

void TitleMovement::UpDate() {
}

void TitleMovement::Render2D() {
	//���S�\��
	{
		Box2D draw(Vec2(400, 250), logo.GetTextureSize());
		draw.OffsetSize();
		Box2D src(0.f, 0.f, draw.w, draw.h);
		this->logo.Draw(draw, src);
	}
}

bool TitleMovement::Finalize() {
	bgm->stop();
	rm->DeleteSound((std::string)"editTitleBGM");
	delete bgm;

	logo.Finalize();

	auto map = OGge->GetTask<Map>("map");
	if (map)
	{
		(*map).Kill();
	}
	auto Npc = OGge->GetTask<Chara>("Chara");
	if (Npc)
	{
		Npc->Kill();
	}
	return true;
}

TitleMovement::SP TitleMovement::Create(bool flag_) {
	auto to = TitleMovement::SP(new TitleMovement());
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