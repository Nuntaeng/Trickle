#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

#include "Task\Task_Result.h"
class FlagUI : public GameObject, public TaskObject
{
public:

public:
	void FalgJudge(int);
private:
	Texture image[2];
	int Resultflag;
	int targetflag;
	bool flagactive;
	void SetResultflag();
	const Box2D Src = Box2D(0, 0, 322, 322);
public:
	std::string taskName;
	virtual ~FlagUI();
	typedef std::shared_ptr<FlagUI> SP;
	static FlagUI::SP Create(Vec2& pos,int targetflag,bool = true);
	FlagUI();
	//-------------
	//�ύX���Ȃ�����
	//-------------
	bool Initialize(Vec2& pos,int&);//����������
	void UpDate();					//�X�V����
	void Render2D();				//�`�揈��
	bool Finalize();				//�������
};