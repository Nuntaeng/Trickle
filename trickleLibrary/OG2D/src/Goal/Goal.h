#ifndef __GOAL_H__
#define __GOAL_H__

//�K�v�ǂݍ��݃t�@�C��
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Goal : public GameObject, public TaskObject
{
	//-------------------------------------------
	//�e���Ő��삷��Ƃ��Ɏg�p������̂͂����ɋL�q����
	//-------------------------------------------
public:
	bool Initialize(Vec2&);
	bool cleared;
	
	//void AddWater();
	//bool DeleteWater();
	bool ClearCheck();
private:
	Texture tex;

	//------------------
	//�Œ艻����Ă��鏈��
	//------------------
public:
	std::string taskName;
	virtual ~Goal();
	typedef std::shared_ptr<Goal> SP;
	static Goal::SP Create(bool);
	static Goal::SP Create(bool,Vec2&);
	Goal();
	//-------------
	//�ύX���Ȃ�����
	//-------------
	bool Initialize();		//����������
	void UpDate();			//�X�V����
	void Render2D();		//�`�揈��
	bool Finalize();		//�������
};

#endif