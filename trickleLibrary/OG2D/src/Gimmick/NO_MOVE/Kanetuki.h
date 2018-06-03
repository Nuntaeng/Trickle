#pragma once
//�K�v�ǂݍ��݃t�@�C��
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"


class Kanetuki : public GameObject, public TaskObject {
	std::string taskName;
	int changeStateCnt;				//���𐅏��C�ɂ���܂ł̎��ԃJ�E���^
	const int maxChangeTimeLiquid;	//���������C�ɂȂ�t���[����
	const int maxChangeTimeSolid;	//�X�����ɂȂ�t���[����
	GameObject hitBase;				//���Ƃ̓����蔻��p
	bool active;					//�ғ������ǂ���
	std::string startsoundname;
	std::string soundname;


	bool Initialize(Vec2&, Vec2 range, bool active);		//����������
	void UpDate();				//�X�V����
	void Render2D();			//�`�揈��
	bool Finalize();			//�������
	void toSteam();				//�����C�ɂ���

	Kanetuki();

public:
	~Kanetuki();
	typedef std::shared_ptr<Kanetuki> SP;
	static Kanetuki::SP Create(Vec2& pos, Vec2 range, bool active, bool flag = true);

	void changeActive();				//���g�̉ғ���Ԃ𔽓]������

	Sound soundstart;
	Sound sound;
	bool startflag;       //�T�E���h���Đ����Ă������̃t���b�O
	bool nowplay;

};





//class Kanetuki : public GameObject, public TaskObject
//{
//	//-------------------------------------------
//	//�e���Ő��삷��Ƃ��Ɏg�p������̂͂����ɋL�q����
//	//-------------------------------------------
//public:
//	std::shared_ptr<Switch> target;
//private:
//	bool switchflag;
//	//------------------
//	//�Œ艻����Ă��鏈��
//	//-----------------
//	std::string taskName;
//	typedef std::shared_ptr<Kanetuki> SP;
//	Kanetuki();
//	//-------------
//	//�ύX���Ȃ�����
//	//-------------
//	bool Initialize(Vec2&);
//	bool Initialize(Vec2&, std::shared_ptr<Switch>&);
//	//����������
//	void UpDate();			//�X�V����
//	void Render2D();		//�`�揈��
//	bool Finalize();		//�������
//	void GetFlag();
//private:
//	const int Fire_time_LIQUID = 10;	//���M���鎞�� �t��
//	const int Fire_time_SOLID = 5;	    //���M���鎞�� ��
//	int Fire_movetime;					//�R�₷���Ԃ��i�[����
//										//�T�E���h�t�@�C�����̊i�[
//	std::string startsoundname;
//	std::string soundname;
//
//	//��ԑJ��
//	void toSteam();						//�����琅���C�ɂ���
//										//�w��X�C�b�`�̃t���O��������
//	void SetSwitchFlag(std::shared_ptr<Switch>&);
//	bool GetSwitchFlag();
//	void Fire_MovetimeReset();
//public:
//	virtual ~Kanetuki();
//	static Kanetuki::SP Create(Vec2& pos, bool = true);
//	static Kanetuki::SP Create(Vec2& pos, std::shared_ptr<Switch>& swith, bool = true);
//
//	Sound soundstart;
//	Sound sound;
//	bool startflag;       //�T�E���h���Đ����Ă������̃t���b�O
//	bool nowplay;
//public:
//};