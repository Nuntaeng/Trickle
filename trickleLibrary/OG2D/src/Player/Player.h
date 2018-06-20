#pragma once
//______________________________//
//|�v���C��                    |//
//|�����F2018/03/23���c	       |//
//|�����F2018/03/26����N�@    |//
//|�����F2018/03/29����N�@    |//
//|�����F2018/03/30�ؖ��@    |//
//|____________________________|//
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

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
public:
	enum State
	{
		NORMAL,		//�ʏ�
		BUCKET,		//�o�P�c����
		ANIMATION,	//�A�j���[�V������
	};
	enum Motion
	{
		Normal,		//�ʏ�
		Walk,		//������
		Jump,		//�W�����v
		Ladder,		//�͂���
		Fall,		//����
		Switch_M,	//�X�C�b�`����
		Block_M,	//�u���b�N����
		Lift,		//����������
		Lower,		//�������낷
		Spill,		//�삷
	};
private:
	class Animation
	{
	public:
		Vec2 animationVec;										//�ړ���
		Vec2 startVec;											//�J�n�ʒu
		Vec2 endVec;											//�I���ʒu
		int timeCnt;											//�A�j���[�V�����o�ߎ���
		int animCnt;											//���Z�b�g�����A�j���[�V�����̃J�E���g�i�X�C�b�`�A��q�A����������j
		Motion animMo;											//�ړ�����animation�֐����X�C�b�`�ƒ�q�����Ŏg���Ă��č�����ϐ�, �A�j���[�V�������ɓ����Ȃ��悤�ɂ��邱�Ƃ�����Ă�
		int same_flag;											//�ړ�������W�ƃv���C���̍��W�������Ƃ�true��Ԃ�

		int idle[10] = { 0,0,0,0,0,0,0,1,1,1 };					//Normal��Ԃ̃A�j���[�V����
		int walk[9] = { 0,1,2,3,4,5,6,7,8 };					//Walk��Ԃ̃A�j���[�V����
		int ladder[2] = { 0,1 };								//ladder_ani��Ԃ̃A�j���[�V����
		int switch_1[6] = { 0,1,2,3,4 };
		int switch_2[6] = { 4,3,2,1,0 };
		int lift[2] = { 2,3 }; 
		int lower[2] = { 3,2 };
		int spill[3] = { 0, 1, 0 };
	public:
		void SetAnimaVec(Vec2& start_, Vec2& end_);				//�J�n�ʒu�ƏI���ʒu��o�^
		bool Initialize();										//������
		Vec2 Move(Motion motion_);								//�ړ��������s���ړ��l��Ԃ�
		bool isMove();											//�ړ����������ǂ�����Ԃ�
		Box2D returnSrc(Motion motion, State state, Direction dir);			//motion�ɂ����src��Ԃ�
	private:
		int srcX = 586, srcY = 575;									//�v���C���摜�̌��X�̃T�C�Y
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
	Animation animation;										//�A�j���[�V�����̈ړ�����
	int inv;													//���G����
	std::string taskName;
	bool hold;
	bool isInputAuto;
private:
	bool HeadCheck();											//���̓����蔻��
	bool FootCheck();											//�����̓����蔻��
	bool HeadCheck(std::string& objname_, int n = 0);			//���̕ʃI�u�W�F�N�g�ւ̔���,0 = ���̃I�u�W�F�N�g,1 = ����ȊO�̃I�u�W�F�N�g
	bool FootCheck(std::string& objname_, int n = 0);			//�����̕ʃI�u�W�F�N�g�ւ̔���
	bool SolidFootCheck();
	void MoveCheck(Vec2 est);									//�ړ����菈��
	void MoveCheck(Vec2& est, std::string& objname_);			//��q��ԂŎg�p����ړ�����
	void Friction();											//�d�͂▀�C�̌v�Z
	bool BucketHit();											//�o�P�c�Ƃ̓����蔻��
	void BucketMove();											//�������Ă���o�P�c�̈ʒu��ς���
	bool TohaveObjectHit();											//�u���b�N�Ƃ̓����蔻��
	bool ObjectHit(std::string& objname_);						//�w�肵���I�u�W�F�N�g�^�O�̃I�u�W�F�N�g�̓����蔻��
	void SwitchCheck();											//�X�C�b�`�Ƃ̓����蔻��
	bool LadderJumpCheck();										//��q���ɃW�����v���s���ۂ̓����蔻��
	bool PutCheck();											//�u��������s���邩�̔���
	bool HeadSolidCheck();										//����X����
public:
	typedef std::shared_ptr<Player> SP;
	static SP Create(Vec2&, bool = true);
	Player();													//�R���X�g���N�^
	virtual ~Player();											//�f�X�g���N�^
	bool Initialize();											//������
	bool Initialize(Vec2&);										//�ʒu�ݒ菉����
	void UpDate();												//�X�V����
	void Render2D();											//�`�揈��
	bool Finalize();											//�������
	Vec2 GetEst() const;										//���݈ړ��l��Ԃ�
	void SetTexture(Texture* texture);							//�e�N�X�`����o�^
	State NowState() const;										//���݂�State��Ԃ�
	void SetPos(Vec2&);											//�v���C���[�̈ʒu��ݒ肷��
	Vec2 GetPos() const;										//�v���C���[�̈ʒu��Ԃ�
	void SetInputAuto(bool);
	bool GetInputAuto() const;
	bool ReleaseHold();
	void SetMotion(Motion motion_);
	//���͏����ȗ���
	bool InputLeft();
	bool InputRight();
	bool InputDown();
	bool InputUp();
	bool InputB1down();
	bool InputB2down();
	bool InputB1on();
	bool InputB2on();
	float AxisLX();
	float AxisLY();
	float AxisRX();
	float AxisRY();
};