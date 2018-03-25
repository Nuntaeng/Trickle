#include "Player.h"


void Player::Initialize()
{
	std::cout << "Player������" << std::endl;
	this->playerimg.TextureCreate(this->fileName);
	CreateObject(Cube, Vec2(10.0f, 300.0f), Vec2(128.0f, 128.0f), 0.0f);
	this->hitcheck = false;

	//�W�����v���
	jumpFlag = false;
}

void Player::UpDate()
{
	est.x = 0;
	if (Input::KeyInputOn(Input::LEFT)) {
		est.x = -Player::MOVE_SPEED;
	}
	if (Input::KeyInputOn(Input::RIGHT)) {
		est.x = Player::MOVE_SPEED;
	}

	//y�����̑��x�ɉ����x��������
	est.y += Player::GRAVITY;

	//�W�����v�̏���
	JumpMove();
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
void Player::JumpMove()
{
	//true�̎��̓W�����v��ԁA����Ȃ���Βʏ���
	if (!jumpFlag) {
		est.y = 0.f;
		//Z�{�^������������A�W�����v��ԂɈڍs����
		if (Input::KeyInputOn(Input::Z)) {
			jumpFlag = true;
			est.y = Player::JUMP_POWER;
		}
	}
	//�W�����v��Ԃ̏���
	else {
		//���n����(�������AMAP�̓����蔻������s������)
		if (position.y >= 700) {
			jumpFlag = false;
		}
	}
}