#pragma once
//______________________________//
//|�Q�[���I�u�W�F�N�g            |//
//|�����F2018/03/20���q��       |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include <functional>
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
	float mass;
	float fricition = 0.f;
	float fricition_current = 0.f;
	bool hit(Object o);
	Object();
	Object(Objform form, Vec2 _posi, Vec2 _Sca, float _ang);
	~Object();
	void CreateObject(Objform form, Vec2 _posi, Vec2 _Sca, float _ang);
	std::string objectTag;
	bool isCollided;
	bool isCollidedGlobal = false;

	void LineDraw();

	void SetFricition(float);
	Vec2 UseFricition() const;


	/**
	 * @note �����������g���I�u�W�F�N�g�̂Ȃ��ł��̊֐���ǂ�ŉ�����
	 * @code void Update() { Object::updatePhysics(); .... }
	 */
	void UpdatePhysics();

	/**
	 * @brief �I�[�o�[���C�h���ē����蔻�菈���������Ă�������
	 * @param Object ���̃I�u�W�F�N�g�ɓ����������̃I�u�W�F�N�g
	 */
	std::function<void(const Object&)> CollisionProcess;

	/**
	 * @brief �����蔻�肪�I�������Ƃ��̍Ō�̂P�t���[�������Ăяo����܂��B
	 * @param ���������I�u�W�F�N�g
	 */
	std::function<void(const Object&)> CollisionOut;

	/**
	* @brief �����蔻�肪�n�܂�Ƃ��̍Ō�̂P�t���[�������Ăяo����܂��B
	* @param ���������I�u�W�F�N�g
	*/
	std::function<void(Object&)> CollisionIn;

private:
};