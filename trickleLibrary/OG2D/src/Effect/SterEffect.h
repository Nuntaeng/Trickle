#pragma once
#include "OGSystem\OGsystem.h"
#include "OGSystem\_OGsystem.h"
#include "Object\Object.h"
class SterEffect : public  GameObject , public  TaskObject
{
public:
	//�X�e�[�g���
	enum State
	{
		NON,
		Motion,
	};
private:
	typedef std::shared_ptr<SterEffect> SP;

	//�摜�֘A
	const Box2D Src = { 0,0,322,322 };
	Texture image;
	

	//�A�j���[�V����
	struct Animetion
	{
		State motion;
		void StateChenge(State);
	};
	Animetion animetion;

	//Update��
	void MotionActive();
	void Think();

	//Easing�֘A
	Easing easingX;
	Easing easingY;
	std::shared_ptr<GameObject> target;
	void ResetEasing(Easing&);
	void MoveEasing();
	bool isPlay;

	//�^�X�N�֘A
	std::string taskName;
	void UpDate();
	void Render2D();
	bool Finalize();
public:
	SterEffect();
	virtual ~SterEffect();
	static SterEffect::SP Create(std::shared_ptr<GameObject>,bool = true);
	bool Initialize(std::shared_ptr<GameObject>);

	bool EasingIsPleyed();
};