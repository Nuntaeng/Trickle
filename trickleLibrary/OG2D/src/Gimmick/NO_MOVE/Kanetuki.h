#pragma once
//�K�v�ǂݍ��݃t�@�C��
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

#include "Gimmick\NO_MOVE\Switch.h"

class Kanetuki : public GameObject, public TaskObject
{
	//-------------------------------------------
	//�e���Ő��삷��Ƃ��Ɏg�p������̂͂����ɋL�q����
	//-------------------------------------------
public:
	std::shared_ptr<Switch> target;
private:
	bool switchflag;
	//------------------
	//�Œ艻����Ă��鏈��
	//-----------------
	std::string taskName;
	typedef std::shared_ptr<Kanetuki> SP;
	Kanetuki();
	//-------------
	//�ύX���Ȃ�����
	//-------------
	bool Initialize(Vec2&);
	bool Initialize(Vec2&,std::shared_ptr<Switch>&);
	//����������
	void UpDate();			//�X�V����
	void Render2D();		//�`�揈��
	bool Finalize();		//�������
	void GetFlag();
private:
	const int Fire_time_LIQUID = 30;	//���M���鎞�� �t��
	const int Fire_time_SOLID = 20;	    //���M���鎞�� ��
	int Fire_movetime;					//�R�₷���Ԃ��i�[����

	//��ԑJ��
	void toSteam();						//�����琅���C�ɂ���
	//�w��X�C�b�`�̃t���O��������
	void SetSwitchFlag(std::shared_ptr<Switch>&);
	bool GetSwitchFlag();
	void Fire_MovetimeReset();
public:
	virtual ~Kanetuki();
	static Kanetuki::SP Create(Vec2& pos, bool = true);
	static Kanetuki::SP Create(Vec2& pos, std::shared_ptr<Switch>& swith, bool = true);
public:
};