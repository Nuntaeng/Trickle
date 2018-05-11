#pragma once
//______________________________//
//|�v���C��                    |//
//|�����F2018/03/23���c	       |//
//|�����F2018/03/26����N�@    |//
//|�����F2018/03/29����N�@    |//
//|�����F2018/03/30�ؖ��@    |//
//|____________________________|//
#include "Bucket\bucket.h"
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Gimmick\NO_MOVE\Switch.h"
#include "Block\block.h"

class Player :public GameObject ,public TaskObject
{
	enum Direction						//�������Ǘ�
	{
		LEFT,
		RIGHT,
	};
	/*const std::array<std::string, 3> WALKABLE_CHIPS{
		"Floor",
		"Soil",
		"Net"
	};*/
	enum State
	{
		NORMAL,		//�ʏ�
		LADDER,		//�͂�����
		BUCKET,		//�o�P�c����
		ANIMATION,	//�A�j���[�V������
	};
	enum Motion
	{
		Normal,		//�ʏ�
		Walk,
		Jump,		//�W�����v
		Ladder,		//�͂���
		Fall,		//����
	};
	class Animation
	{
	public:
		Vec2 animationVec;										//�ړ���
		Vec2 startVec;											//�J�n�ʒu
		Vec2 endVec;											//�I���ʒu
		int timeCnt;											//�A�j���[�V�����o�ߎ���
		//int idle[10];											//Normal��Ԃ̃A�j���[�V����
	public:
		void SetAnimaVec(Vec2& start_, Vec2& end_);				//�J�n�ʒu�ƏI���ʒu��o�^
		bool Initialize();										//������
		Vec2 Move();											//�ړ��������s���ړ��l��Ԃ�
		bool isMove();											//�ړ����������ǂ�����Ԃ�
	};
private:
	const float MOVE_SPEED = 5.f;								//�ړ��X�s�[�h
	//const float JUMP_POWER = -30.f;							//�W�����v�p���[(test)
	const float JUMP_POWER = -13.f;								//�W�����v�p���[
	const float MAX_FALL = 15.f;								//�����ő呬�x
	const float GRAVITY = (9.8f / 60.f / 60.f * 32) * 10;		//�d�͉����x
	const float FIN_SPEED = 0.5f;								//���C
	bool CheckJump;												//�W�����v����
	bool CheckGravity;											//�d�͉����x����
	int moveCnt;												//�ړ��J�E���g
	Texture* playerimg;											//�摜�f�[�^
	Vec2 est;													//�ړ���
	Direction direction;										//�������i�[����ϐ�
	Motion motion;												//���󃂁[�V����
	State state;												//������
	std::vector<GameObject*> objects;								//�����蔻��I�u�W�F�N�g
	std::vector<Bucket*> buckets;								//�o�P�c����
	std::vector<Block*> blocks;									//�u���b�N����
	std::vector<GameObject*> waters;								//������
	Bucket* haveBucket;											//�����o�P�c���
	Animation animation;										//�A�j���[�V�����̈ړ�����
	int inv;													//���G����
	std::string taskName;
private:
	bool HeadCheck();											//���̓����蔻��
	bool FootCheck();											//�����̓����蔻��
	bool HeadCheck(std::string& objname_, int n = 0);			//���̕ʃI�u�W�F�N�g�ւ̔���,0 = ���̃I�u�W�F�N�g,1 = ����ȊO�̃I�u�W�F�N�g
	bool FootCheck(std::string& objname_, int n = 0);			//�����̕ʃI�u�W�F�N�g�ւ̔���
	void MoveCheck(Vec2& est);									//�ړ����菈��
	void MoveCheck(Vec2& est, std::string& objname_);				//��q��ԂŎg�p����ړ�����
	void Friction();											//�d�͂▀�C�̌v�Z
	bool BucketHit();											//�o�P�c�Ƃ̓����蔻��
	void BucketMove();											//�������Ă���o�P�c�̈ʒu��ς���
	bool BlockHit();											//�u���b�N�Ƃ̓����蔻��
	bool ObjectHit(std::string& objname_);						//�w�肵���I�u�W�F�N�g�^�O�̃I�u�W�F�N�g�̓����蔻��
public:
	typedef std::shared_ptr<Player> SP;
	static SP Create(Vec2&, bool = true);
	Player();													//�R���X�g���N�^
	virtual ~Player();													//�f�X�g���N�^
	bool Initialize();											//������
	bool Initialize(Vec2&);										//�ʒu�ݒ菉����
	void UpDate();												//�X�V����
	void Render2D();												//�`�揈��
	bool Finalize();											//�������
	void AddObject(GameObject* obj_);								//�I�u�W�F�N�g��o�^����
	void DeleteObject(GameObject* obj_);							//�w��I�u�W�F�N�g��o�^����폜����
	void AllDelete();											//�S�o�^�I�u�W�F�N�g�̍폜
	void AddBucket(Bucket* bucket);								//�o�P�c�I�u�W�F�N�g�̓o�^
	bool DeleteBucket(Bucket* bucket);							//�w��o�P�c�I�u�W�F�N�g���폜
	void AddBlock(Block* block);								//�u���b�N�I�u�W�F�N�g��o�^	
	bool DeleteBlock(Block* block);								//�w��u���b�N�I�u�W�F�N�g�̍폜
	void AddWater(GameObject*);										//���I�u�W�F�N�g��o�^
	bool DeleteWater(GameObject*);									//�w�萅�I�u�W�F�N�g�̍폜
	Vec2 GetEst() const;										//���݈ړ��l��Ԃ�
	void SetTexture(Texture* texture);							//�e�N�X�`����o�^
	State NowState() const;										//���݂�State��Ԃ�
	void SetPos(Vec2&);											//�v���C���[�̈ʒu��ݒ肷��
	Vec2 GetPos() const;										//�v���C���[�̈ʒu��Ԃ�
	//���͏����ȗ���
	bool InputLeft() {
		return OGge->in->on(Input::CL);
	}
	bool InputRight() {
		return OGge->in->on(Input::CR);
	}
	bool InputDown() {
		return OGge->in->on(Input::CD);
	}
	bool InputUp() {
		return OGge->in->on(Input::CU);
	}
};