#include "Player.h"


void Player::Initialize()
{
	std::cout << "Player������" << std::endl;
	this->playerimg.TextureCreate(this->fileName);
	CreateObject(Cube, Vec2(10.0f, 600.0f), Vec2(128.0f, 128.0f), 0.0f);
	this->hitcheck = false;

	//�W�����v���
	jumpFlag = false;
	//�ړ��X�s�[�h
	speed = 0.15f;
}

void Player::UpDate()
{
	Vec2 est;
	//if (Input::KeyInputOn(Input::LEFT)) {
	//	est.x -= 1;
	//}
	//if (Input::KeyInputOn(Input::RIGHT)) {
	//	est.x += 1;
	//}
	//if (Input::KeyInputOn(Input::UP)) {
	//	est.y -= 1;
	//}
	//if (Input::KeyInputOn(Input::DOWN)) {
	//	est.y += 1;
	//}
	position.y += 1;

	//�W�����v�̏���
	JumpMove(est);



	est.Normalize();
	//est *= speed;
	position += est;
}

void Player::Render()
{
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	this->playerimg.Draw(draw, src);
}

void Player::Finalize()
{
	std::cout << "Player���" << std::endl;
	this->playerimg.Finalize();

}
//�W�����v�̏���
void Player::JumpMove(Vec2& e_)
{
	e_.x = 0;
	if (Input::KeyInputOn(Input::LEFT)) {
		e_.x = -speed;
	}
	if (Input::KeyInputOn(Input::RIGHT)) {
		e_.x = speed;
	}

	//true�̎��̓W�����v��ԁA����Ȃ���Βʏ���
	if (!jumpFlag) {
		//Z�{�^������������A�W�����v��ԂɈڍs����
		if (Input::KeyInputOn(Input::Z)) {
			jumpFlag = true;
			e_.y = Player::JUMP_POWER;
		}
	}
	//�W�����v��Ԃ̏���
	else {
		//y�����̑��x�ɉ����x��������
		e_.y += Player::GRAVITY;
		//y���W�̍X�V
		position.y += e_.y;
		//���n����(�������AMAP�̓����蔻������s������)
		if (e_.y>0 /*&& position.y >= ground_y*/) {
			jumpFlag = false;
			e_.y = 0.f;
		}
	}
}