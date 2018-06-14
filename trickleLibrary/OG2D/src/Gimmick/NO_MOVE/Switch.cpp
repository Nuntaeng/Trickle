#include "Switch.h"
using namespace std;

Switch::Switch()
{
	cout << "�X�C�b�`�@����" << endl;
	soundname = "switch.wav";
	this->taskName = "Switch";
	this->objectTag = "Switch";
	//�^�O���������m�\�ɂ���
	this->Init(taskName);
}

Switch::~Switch()
{
	this->Finalize();
	cout << "�X�C�b�`�@���" << endl;
}

bool Switch::Initialize(Vec2& pos, std::vector<std::shared_ptr<GameObject>> targets, TargetType ttype) {
	//�����蔻��̎���
	this->CreateObject(Cube, pos, Vec2(64, 64), 0.0f);
	image.Create((std::string)"switch.png");
	//�T�E���h����
	sound.create(soundname, false);
	sound.volume(1.0f);
	OGge->soundManager->SetSound(&sound);
	//�`��֘A
	draw = Box2D(pos.x, pos.y, 64.0f, 64.0f);
	draw.OffsetSize();
	animCnt = 24;
	play_switch = false;
	//�^�[�Q�b�g�֘A
	this->ttype = ttype;
	this->targets_ = targets;

	cout << "�ʏ�X�C�b�`�@������" << endl;
	return true;

}
void Switch::Update() {

}
void Switch::Render2D() {

	//�v���C�����X�C�b�`�܂ňړ��I�������Ƃ�
	if (this->play_switch)
	{
		if (this->isON_) {
			//�X�C�b�`��ON�Ȃ�A�j���[�V������PLUS������
			if (this->animCnt < 24) { ++this->animCnt; }
			else { this->play_switch = false; }
		}
		else {
			//�X�C�b�`��OFF�Ȃ�A�j���[�V������MINUS������
			if (this->animCnt > 0) { --this->animCnt; }
			else { this->play_switch = false; }
		}
	}
	Box2D src;
	int switchM[5] = { 0,1,2,3,4 };
	switch (this->ttype)
	{
	case TargetType::Heater:
		src = Box2D(switchM[this->animCnt / 5 % 5] * 256, 256 * 0, 256, 256);
		break;
	case TargetType::IceMachine:
		src = Box2D(switchM[this->animCnt / 5 % 5] * 256, 256 * 1, 256, 256);
		break;
	case TargetType::Fan:
		src = Box2D(switchM[this->animCnt / 5 % 5] * 256, 256 * 2, 256, 256);
		break;
	}

	src.OffsetSize();
	image.Draw(draw, src);

}
bool Switch::Finalize() {
	return image.Finalize();
}
void Switch::ChangeON_OFF() {
	//�؂�ւ����T�E���h�𐶐�
	sound.play();
	for (auto target : targets_) {
		PostMsg(target);
	}
	this->isON_ = !this->isON_;
}
bool Switch::isON() {
	return this->isON_;
}
void Switch::setSwitch(bool play)
{
	//�v���C�����X�C�b�`�܂ňړ��I�������Ƃ�
	if (play == true)
	{
		this->play_switch = true;
	}
}

Switch::TargetType Switch::getTargetType() {
	return this->ttype;
}
bool Switch::PostMsg(std::shared_ptr<GameObject> target) {
	switch (ttype) {
	case TargetType::Fan:
		(std::static_pointer_cast<Fan>(target))->changeActive();
		break;
	case TargetType::Heater:
		(std::static_pointer_cast<Kanetuki>(target))->changeActive();
		break;
	case TargetType::IceMachine:
		(std::static_pointer_cast<Seihyouki>(target))->changeActive();
		break;
	default:
		return false;
	}
	return true;
}
Switch::SP Switch::Create(Vec2& pos, std::vector<std::shared_ptr<GameObject>> targets, TargetType ttype, bool flag) {
	Switch::SP to = Switch::SP(new Switch());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos, targets, ttype))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}





//bool Switch::Initialize(Vec2& pos)
//{
//	taskName = "Switch";
//	//�^�O���������m�\�ɂ���
//	this->Init(taskName);			//TaskObject���̏������s��
//									//�����蔻��̎���
//	CreateObject(Cube, pos, Vec2(64, 64), 0.0f);
//	image.Create((std::string)"switch.png");
//	//�T�E���h����
//	sound.create(soundname, false);
//	sound.volume(1.0f);
//	OGge->soundManager->SetSound(&sound);
//
//	cout << "�ʏ�X�C�b�`�@������" << endl;
//	return true;
//}
//bool Switch::Initialize(Vec2& pos, Switch::SP target)
//{
//	taskName = "Switch";
//	if (target)
//	{
//		cout << "�X�C�b�`�����m" << endl;
//	}
//	else
//	{
//		cout << "�X�C�b�`������s" << endl;
//	}
//
//	//�^�O���������m�\�ɂ���
//	this->Init(taskName);			//TaskObject���̏������s��
//	//�����蔻��̎���
//	CreateObject(Cube, pos, Vec2(64, 64), 0.0f);
//	//�^�[�Q�b�g��������
//	SetTarget(target);
//	image.Create((std::string)"switch.png");
//	//�T�E���h����
//	sound.create(soundname, false);
//	sound.volume(1.0f);
//	OGge->soundManager->SetSound(&sound);
//
//	cout << "�^�[�Q�b�g�X�C�b�`�@������" << endl;
//	return true;
//}
//void Switch::UpDate()
//{
//	//--------------------
//	//�X�V���ɍs���������L�q
//	//--------------------
//	//���̃X�C�b�`�̃t���O�ƑΏۂɔ��]������
//	if (targetswitch != nullptr)
//	{
//		this->TargetSwitchChenge();
//	}
//}
//void Switch::Render2D()
//{
//	//--------------------
//	//�`�掞�ɍs���������L�q
//	//--------------------
//	Box2D draw(position, Scale);
//	draw.OffsetSize();
//	Box2D src = this->Src;
//	src.OffsetSize();
//	if (this->GetisON())
//	{
//		int temp = src.x;
//		src.x = src.w;
//		src.w = temp;
//	}
//	image.Draw(draw, src);
//}
//
//bool Switch::Finalize()
//{
//	//-----------------------------------------
//	//���̃I�u�W�F�N�g�����ł���Ƃ��ɍs���������L�q
//	//-----------------------------------------
//	
//	//���̃^�X�N����邩���A�v���P�[�V�������I���\�肩�ǂ���
//	if (this->GetNextTask() && !OGge->GetDeleteEngine())
//	{
//		
//	}
//	return true;
//}
//bool Switch::GetisON()
//{
//	//�؂�ւ��t���O��Ԃ�
//	return is_on;
//}
//void Switch::ON_OFF()
//{
//	//�؂�ւ����T�E���h�𐶐�
//	sound.play();
//	//true��false�̐؂�ւ��t���O��؂�ւ���
//	is_on = !is_on;
//}
//void Switch::SetTarget(Switch::SP target)
//{
//	if (target != nullptr)
//	{
//		this->targetswitch = target;
//		this->is_on = !this->targetswitch->GetisON();
//	}
//}
//void Switch::TargetSwitchChenge()
//{
//	if (targetswitch != nullptr)
//	{
//		this->is_on = !this->targetswitch->GetisON();
//	}		
//}
//Switch::Switch()
//{
//	cout << "�X�C�b�`�@����" << endl;
//	soundname = "switch.wav";
//}
//
//Switch::~Switch()
//{
//	this->Finalize();
//	cout << "�X�C�b�`�@���" << endl;
//}
//Switch::SP Switch::Create(Vec2& pos,bool flag)
//{
//	Switch::SP to = Switch::SP(new Switch());
//	if (to)
//	{
//		to->me = to;
//		if (flag)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}
//Switch::SP Switch::Create(Vec2& pos, Switch::SP target,bool flag)
//{
//	Switch::SP to = Switch::SP(new Switch());
//	if (to)
//	{
//		to->me = to;
//		if (flag)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos, target))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}