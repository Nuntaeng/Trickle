#pragma once
//�K�v�ǂݍ��݃t�@�C��
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

#include "Switch.h"
class Seihyouki : public GameObject, public TaskObject
{
	//-------------------------------------------
	//�e���Ő��삷��Ƃ��Ɏg�p������̂͂����ɋL�q����
	//-------------------------------------------
private:
	void toIce();							//�X�ɂ���
	void SetSwitchFlag(std::shared_ptr<Switch>&);
	void GetFlag();
	bool GetSwitchFlag();
private:
	GameObject hitBace;
	bool switchflag;
	//------------------
	//�Œ艻����Ă��鏈��
	//------------------
public:
	std::string taskName;
	std::shared_ptr<Switch> target;
	virtual ~Seihyouki();
	typedef std::shared_ptr<Seihyouki> SP;
	static Seihyouki::SP Create(Vec2& pos, bool = true);
	static Seihyouki::SP Create(Vec2& pos,std::shared_ptr<Switch>& target,bool = true);
	Seihyouki();
	//-------------
	//�ύX���Ȃ�����
	//-------------
	bool Initialize(Vec2&);		//����������
	bool Initialize(Vec2&,std::shared_ptr<Switch>& target);		//����������
	void UpDate();			//�X�V����
	void Render2D();		//�`�揈��
	bool Finalize();		//�������

private:
	int movetime;					//�X�ɂ���܂ł̊i�[����t���[����
	const int movetime_ice = 20;	//�X�ɂ���܂ŁE�E�E
};