#pragma once
//�K�v�ǂݍ��݃t�@�C��
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Kanetuki : public GameObject, public TaskObject
{
	//-------------------------------------------
	//�e���Ő��삷��Ƃ��Ɏg�p������̂͂����ɋL�q����
	//-------------------------------------------
public:

private:
	GameObject hitBace;
	//------------------
	//�Œ艻����Ă��鏈��
	//------------------
public:
	std::string taskName;
	virtual ~Kanetuki();
	typedef std::shared_ptr<Kanetuki> SP;
	static Kanetuki::SP Create(bool = true);
	Kanetuki();
	//-------------
	//�ύX���Ȃ�����
	//-------------
	bool Initialize();		//����������
	void UpDate();			//�X�V����
	void Render2D();		//�`�揈��
	bool Finalize();		//�������
private:
	const int Fire_time_LIQUID = 70;	//���M���鎞�� �t��
	const int Fire_time_SOLID = 40;	    //���M���鎞�� ��
	int Fire_movetime;					//�R�₷���Ԃ��i�[����

	//��ԑJ��
	void toSteam();		//�����琅���C�ɂ���
public:
	void Create(Vec2, Vec2);	//���W�l�@�����蔻��T�C�Y
	//void SetWaterPool(std::vector<Water*> *);
};