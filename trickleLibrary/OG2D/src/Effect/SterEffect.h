//#pragma once
//#include "OGSystem\OGsystem.h"
//#include "OGSystem\_OGsystem.h"
//#include "Object\Object.h"
//class SterEffect : public  GameObject , public  TaskObject
//{
//public:
//	//�X�e�[�g���
//	enum State
//	{
//		NON,
//		Motion,
//	};
//private:
//	typedef std::shared_ptr<SterEffect> SP;
//
//	//�摜�֘A
//	const Box2D Src = { 0,0,78,79 };
//	Texture image;
//	
//
//	//�A�j���[�V����
//	struct Animetion
//	{
//		State motion;
//		void StateChenge(State);
//	};
//	Animetion animetion;
//
//	//Update��
//	void MotionActive();
//	void Think();
//
//	//Easing�֘A
//	Easing easingX;
//	Easing easingY;
//	std::shared_ptr<GameObject> target;
//	std::shared_ptr<SterEffect> effect;
//	void ResetEasing(Easing&);
//	void MoveEasing();
//	bool isPlayed;
//
//	//�^�X�N�֘A
//	std::string taskName;
//	void UpDate();
//	void Render2D();
//	bool Finalize();
//public:
//	SterEffect();
//	virtual ~SterEffect();
//	static SterEffect::SP Create(std::shared_ptr<GameObject>,bool = true);
//	//�^�C�~���O�����炷�ꍇ�Ɏg�p����
//	static SterEffect::SP Create(std::shared_ptr<GameObject>, std::shared_ptr<SterEffect> Targeteffect ,bool = true);
//	bool Initialize(std::shared_ptr<GameObject>);
//	//�^�C�~���O�����炷�ꍇ�Ɏg�p����
//	bool Initialize(std::shared_ptr<GameObject>, std::shared_ptr<SterEffect> Targeteffect);
//	///���U���g���E��ԃ��[�V�����ɂ���Ƃ��Ɏg�p���܂��B
//	bool EasingIsPlay();
//};