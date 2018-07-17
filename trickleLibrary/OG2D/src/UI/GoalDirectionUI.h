#pragma once
#include "OGSystem/OGsystem.h"
#include "Object/Object.h"
#include "Paint/Paint.h"

/*
*  �S�[���̐i�s����������UI�N���X�ł�
*/
class GoalDirection : public GameObject , public TaskObject
{
public:
	//�����o�ϐ�

	typedef std::shared_ptr<GoalDirection> SP;

	//�����o�֐�
	GoalDirection();
	virtual ~GoalDirection();
	static GoalDirection::SP Create(std::shared_ptr<GameObject>, bool = true);
	bool Initialize(std::shared_ptr<GameObject>);

	void SetTextrue(Texture*,Texture*);
private:
	//�����o�ϐ�
	std::string taskName;

	std::shared_ptr<GameObject> target;

	Texture* image;
	Texture* flower;
	const Box2D srcbase = {0,0,256,256};
	const Box2D srcflower = {0,0,256,256};

	//�����o�֐�

	bool Finalize();
	void UpDate()override;
	void Render2D()override;

	void SetPos(Vec2&);
	
	bool WindowOuterCheck();
	void TargetDirecition();
	Vec2 CameraPosUpDate();
	float ToDeg(float radian);
};
