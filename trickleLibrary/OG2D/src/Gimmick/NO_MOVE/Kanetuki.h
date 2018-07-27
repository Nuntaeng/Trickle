#pragma once
//�K�v�ǂݍ��݃t�@�C��
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include <vector>
#include "VolumeControl\volumeControl.h"


class Kanetuki : public GameObject, public TaskObject {
public:
	enum Angle {
		UP,
		LEFT,
		RIGHT,
		BOTTOM,
	};

private:
	std::string taskName;
	const unsigned int maxChangeTimeLiquid;	//���������C�ɂȂ�t���[����
	const unsigned int maxChangeTimeSolid;	//�X�����ɂȂ�t���[����
	GameObject hitBase;				//���Ƃ̓����蔻��p
	bool active;					//�ғ������ǂ���
	//�T�E���h�̃t�@�C�����i�[
	std::string startsoundname;
	std::string stopsoundname;
	std::string soundname;
	Texture* hotImg;			//�摜�f�[�^
	int animCnt;				//�A�j���[�V�����J�E���g
	int hotNum;				//�����ɂ���đ�����摜�̐�
	std::vector<Box2D> draw;
	Angle angle;
	float texRotaAng;

	bool Initialize(Vec2&, Vec2 range, Angle ang, bool active);		//����������
	void UpDate();				//�X�V����
	void Render2D();			//�`�揈��
	bool Finalize();			//�������
	void toSteam();				//�����C�ɂ���

	Kanetuki();

public:
	~Kanetuki();
	typedef std::shared_ptr<Kanetuki> SP;
	static Kanetuki::SP Create(Vec2& pos, Vec2 range, Angle ang, bool active, bool flag = true);

	void changeActive();				//���g�̉ғ���Ԃ𔽓]������

	//�T�E���h�̐���
	Sound soundstart;
	Sound sound;
	Sound soundstop;

	VolumeControl volControl;
	
	bool startflag;       //�T�E���h���Đ����Ă������̃t���b�O
	bool nowplay;
	void SetTexture(Texture*);
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