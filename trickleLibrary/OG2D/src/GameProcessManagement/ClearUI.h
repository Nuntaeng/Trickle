#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "OGSystem/_OGsystem.h"

class ClearUI : public GameObject, public TaskObject
{
private:
	//�^�X�N�֘A
	std::string taskName;

	//�摜�֘A
	Texture image;
	const Box2D Src = {0,0,269,85};

	//��]
	Vec2 rotate;

	//�g��@�\�ϐ�
	float Volume;
	bool  Volumefinish;

private:
	//�^�X�N�֘A
	bool Initialize(Vec2&);
	bool Finalize();
	void UpDate();
	void Render2D();
	ClearUI();

	//�g��@�\
	void ResetVolume();
	void ResetVolumeFlag();
	void SetVolumeFlag(bool);
	void MoveVolume();
public:
	virtual ~ClearUI();
	typedef std::shared_ptr<ClearUI> SP;
	static ClearUI::SP Create(Vec2& pos, bool = true);

	//���U���g�Ŏg�p����֐�
	bool GetVolumeFlag();
};