#include "Ladder.h"
const Vec2 IMAGE_SIZE(32, 32);			//�摜�T�C�Y
const Vec2 POS(100, 100);				//�������W

Ladder::Ladder()
{
	objectTag = "Ladder";
	flag = false;
}
Ladder::~Ladder()
{

}
bool Ladder::Initialize()
{
	CreateObject(Objform::Cube, POS, IMAGE_SIZE, 0);
	return true;
}
void Ladder::Update()
{
	flag = CheakHit();
	if (flag)
	{
		std::cout << "��q��n���悤�ɂ��܂�" << std::endl;
	}
}
void Ladder::Render()
{
	//map���ł̏����Ȃ̂ł��܂�Ӗ����Ȃ�
}
void Ladder::Finalize()
{

}
bool Ladder::CheakHit()
{
	Object::CollisionProcess = [&](const Object& o_)
	{
		if (o_.objectTag == "Player")
		{
			return true;
		}
		return false;
	};
	return false;
}