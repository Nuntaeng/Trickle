#pragma once
//______________________________//
//|�Q�[���I�u�W�F�N�g            |//
//|�����F2018/03/20���q��       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
enum Objform
{
	Non,
	Ball,
	Cube,
};
class Object
{
public:
	Objform objform;
	Vec2 position;
	Vec2 Scale;
	float angle;
	CollisionBox collisionCube;
	CollisionCircle collisionBall;
	bool Gravity;
	bool hit(Object o);
	Object();
	Object(Objform form, Vec2 _posi, Vec2 _Sca, float _ang);
	~Object();
	void CreateObject(Objform form, Vec2 _posi, Vec2 _Sca, float _ang);
	std::string objectTag;

protected:
	/**
	 * @brief �I�[�o�[���C�h���ē����蔻�菈���������Ă�������
	 * @param Object ���̃I�u�W�F�N�g�ɓ����������̃I�u�W�F�N�g
	 */
	void Collide(const Object&);

private:
};