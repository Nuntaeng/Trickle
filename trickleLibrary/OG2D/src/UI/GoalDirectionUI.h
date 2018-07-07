#pragma once
#include "OGSystem/OGsystem.h"
#include "Object/Object.h"

/*
*  �S�[���̐i�s����������UI�N���X�ł�
*/
class GoalDirection : public GameObject , public TaskObject
{
	enum DrawPattrn
	{
		ULeft,
		URight,
		UCenter,
		CLeft,
		CRight,
		CCenter,
		DLeft,
		DRight,
		DCenter,
	};
public:
	//�����o�ϐ�

	typedef std::shared_ptr<GoalDirection> SP;
	DrawPattrn drawPattrn;

	//�����o�֐�
	GoalDirection();
	virtual ~GoalDirection();
	static GoalDirection::SP Create(std::vector<std::shared_ptr<GameObject>>, bool = true);
	bool Initialize(std::vector<std::shared_ptr<GameObject>>);
	
private:
	std::string taskName;
	std::vector<std::shared_ptr<GameObject>> targets;
	Texture image;
	const Box2D srcbase = {0,0,256,256};

	bool Finalize();
	void UpDate()override;
	void Render2D()override;

	void SetPos(Vec2&);
	bool WindowOuterCheck();
	void TargetDirecition();
	void CameraPosUpDate();
	float ToDeg(float radian);
};
