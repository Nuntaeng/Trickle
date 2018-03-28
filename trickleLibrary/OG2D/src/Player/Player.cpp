#include "Player.h"

//��������//-----------------------------------------------------------------------------
void Player::Initialize()
{
	std::cout << "Player������" << std::endl;
	this->playerimg.TextureCreate(this->fileName);
	CreateObject(Cube, Vec2(10.0f, 200.0f), Vec2(64.0f, 64.0f), 0.0f);
	
	
	//������p
	footBase.CreateObject(Cube, Vec2(this->position.x, this->position.y + this->Scale.y), Vec2(this->Scale.x, 1.0f), 0.0f);
	footBase.objectTag = "PlayerFoot";
	footBase.CollisionProcess = [&](const Object& o_) {
		std::cout << o_.objectTag << std::endl;
		if (o_.objectTag == "Floor") {
			std::cout << "�������蒆" << std::endl;		//�\���Ȃ��H�H�H
			footBase.isCollided = true;
			/*jumpFlag = false;*/
		}
	};


	this->hitcheck = false;
	this->objectTag = "Player";
	//�����蔻�菉����
	this->isCollided = false;
	//������Ԃ̌��������Ă���
	direction = Direction::RIGHT;
	//�W�����v���
	jumpFlag = false;

	//�����蔻��
	Object::CollisionProcess = [&](const Object& o_) {
		if (o_.objectTag == "Floor") {
			/*std::cout << "���Ɠ����蔻�蒆�I" << std::endl;*/
			this->isCollided = true;
			jumpFlag = false;
		}
	};
}
//��������//-----------------------------------------------------------------------------
void Player::UpDate()
{
	//�L�����N�^�[�̈ړ�����
	est.x = 0;
	if (Input::KeyInputOn(Input::LEFT)) {
		est.x = -Player::MOVE_SPEED;
		//�L�����N�^�[�̌����ϊ�
		direction = Direction::LEFT;
	}
	if (Input::KeyInputOn(Input::RIGHT)) {
		est.x = Player::MOVE_SPEED;
		//������RIGHT��
		direction = Direction::RIGHT;
	}

	//y�����̑��x�ɉ����x��������
	est.y += Player::GRAVITY;

	//�W�����v�̏���
	JumpMove();
	//�����ڐG����
	//CheckFoot();

	position += est;
}
//��������//-----------------------------------------------------------------------------
void Player::Render()
{
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	//LEFT�����Ȃ�摜�𔽓]������
	if (direction == Direction::LEFT) {
		int k = src.w;
		src.w = src.x;
		src.x = k;
	}
	this->playerimg.Draw(draw, src);
}
//��������//-----------------------------------------------------------------------------
void Player::Finalize()
{
	std::cout << "Player���" << std::endl;
	this->playerimg.Finalize();

}
//��������//-----------------------------------------------------------------------------
//�֐�
//��������//-----------------------------------------------------------------------------
//�W�����v�̏���
void Player::JumpMove()
{
	footBase.position = Vec2(this->position.x, this->position.y + this->Scale.y);
	//true�̎��̓W�����v��ԁA����Ȃ���Βʏ���
	if (footBase.isCollided) {
		est.y = 0.f;
		//Z�{�^������������A�W�����v��ԂɈڍs����
		if (Input::KeyInputOn(Input::Z)) {
			est.y = Player::JUMP_POWER;
		}
	}
}
//��������//-----------------------------------------------------------------------------
//�����ڐG����
void Player::CheckFoot()
{
	footBase.CreateObject(Cube, Vec2(this->position.x, this->position.y + this->Scale.y), Vec2(this->Scale.x, 1.0f), 0.0f);
	footBase.objectTag = "PlayerFoot";
	footBase.CollisionProcess = [&](const Object& o_) {
		std::cout << "�������蒆" << std::endl;
		this->isCollided = true;
	};
}