#pragma once
//�K�v�ǂݍ��݃t�@�C��
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"


class Seihyouki : public GameObject, public TaskObject
{
	std::string taskName;
	int changeStateCnt;			//����X�ɂ���܂ł̎��ԃJ�E���^
	const int maxChangeTime;	//�����X�ɂȂ�t���[����
	GameObject hitBase;			//���Ƃ̓����蔻��p	�Ȃ����M��͂Ȃ��̂ɐ��X�@�ɂ͂���̂��c�c��ɕ`������̃N���X�ōs�����Ƃ��l���Ĉꉞ�c��
	bool active;				//�ғ������ǂ���
	Texture* coldImg;			//�摜�f�[�^
	int animCnt;				//�A�j���[�V�����J�E���g
	int coldNum;				//�����ɂ���đ�����摜�̐�
	std::vector<Box2D> draw;	//�X�̉摜


	bool Initialize(Vec2& , Vec2 range);		//����������
	void UpDate();				//�X�V����
	void Render2D();			//�`�揈��
	bool Finalize();			//�������
	void toIce();				//�X�ɂ���

	Seihyouki();

public:
	typedef std::shared_ptr<Seihyouki> SP;
	static Seihyouki::SP Create(Vec2& pos, Vec2 range, bool flag = true);
	void SetTexture(Texture*);

	void changeActive();				//���g�̉ғ���Ԃ𔽓]������
};




//class Seihyouki : public GameObject, public TaskObject
//{
//	//-------------------------------------------
//	//�e���Ő��삷��Ƃ��Ɏg�p������̂͂����ɋL�q����
//	//-------------------------------------------
//private:
//	void toIce();							//�X�ɂ���
//	void SetSwitchFlag(std::shared_ptr<Switch>&);
//	void GetFlag();
//	bool GetSwitchFlag();
//private:
//	GameObject hitBace;
//	bool switchflag;
//	//------------------
//	//�Œ艻����Ă��鏈��
//	//------------------
//public:
//	std::string taskName;
//	std::shared_ptr<Switch> target;
//	virtual ~Seihyouki();
//	typedef std::shared_ptr<Seihyouki> SP;
//	static Seihyouki::SP Create(Vec2& pos, bool = true);
//	static Seihyouki::SP Create(Vec2& pos,std::shared_ptr<Switch>& target,bool = true);
//	Seihyouki();
//	//-------------
//	//�ύX���Ȃ�����
//	//-------------
//	bool Initialize(Vec2&);		//����������
//	bool Initialize(Vec2&,std::shared_ptr<Switch>& target);		//����������
//	void UpDate();			//�X�V����
//	void Render2D();		//�`�揈��
//	bool Finalize();		//�������
//
//private:
//	int movetime;					//�X�ɂ���܂ł̊i�[����t���[����
//	const int movetime_ice = 20;	//�X�ɂ���܂ŁE�E�E
//};