#pragma once

/*�d���ŋ쓮����X�C�b�`�̍쐬*/
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class WeightSwitch :public GameObject, public TaskObject
{
	float totalmass;        //�X�C�b�`�ɏ���Ă��镨�̍��v���ʂ��i�[
	float maxmass;          //�����J���d��
	Texture* image;
	std::string taskName;
	Box2D draw;
	Box2D src;
	bool nowActive;          //�������J���邩�ǂ���
	bool canPlhitCheck;         //�v���C���Ɠ����蔻������ėǂ���
	bool canIcehitCheck;        //�X�Ɠ����蔻������Ă悢��
	bool canBlockhitCheck;      //�u���b�N�Ɠ����蔻������Ă悢��
	bool canBuckethitCheck;     //�o�P�c�Ɠ����蔻������Ă悢��

public:
	typedef std::shared_ptr<WeightSwitch> SP;

	explicit WeightSwitch(const Vec2& pos_, const Vec2& size_, const float mass_);
	virtual ~WeightSwitch();

	//��������Ă��邩�ǂ����̏�Ԕ��f�Ɏg��
	enum State
	{
		Nomal,         //����Ă��Ȃ����
		Riding         //����Ă�����
	};
	State state;

	void UpDate();
	void Render2D();

	void Getmass();
	bool SetnowState();             //���̃X�C�b�`�̏�Ԃ�Ԃ�
	void SetTexture(Texture*);      //�摜�̃Z�b�g
	static SP Create(const Vec2& pos, const Vec2& size, const float mass);
};
