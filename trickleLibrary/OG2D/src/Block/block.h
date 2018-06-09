#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Bucket\bucket.h"

class Block : public GameObject ,public TaskObject{

private:
	/**
	 @author Heewon Kim
	 @brief �����蔻��֘A�S�̓I�Ȕ�����s���܂�
	 @return �����ɂԂ������̂��̔���
	*/
	bool isCollideSomething();
	bool footCheck();
public:
	explicit Block();
	explicit Block(Vec2& pos);
	virtual ~Block();

	typedef std::shared_ptr<Block> SP;
	static SP Create(Vec2&,bool = true);

	//bool HitMap;
	//float speed;
	Vec2 speed;
	Vec2 gravity;
	GameObject foot;
	unsigned __int8 Cnt;
	bool Initialize(Vec2&);
	void UpDate();
	void Render2D();
	bool Finalize();

	//�߂荞�܂Ȃ�����
	void CheckMove(Vec2 &e_);
	//�v���C���[�ƃu���b�N�̓����������̏���
	void PlCheckHit(GameObject &p);
	//�v���C���[�ƃu���b�N�̓����蔻��t���b�O
	bool plhit;
	//�v���C��������A�ړ�����ʂ������Ă���
	Vec2 GetMove(Vec2& move);
	//�v���C���[�Ɉړ��s���̒l��Ԃ�
	Vec2 BackMove();

	Vec2 backmove;

	//�v���C���Ƃ̓����蔻��Ɏg�p�@�@�g��Ȃ��Ȃ���
	void PlCheckHitR(GameObject &p);
	void PlCheckHitL(GameObject &p);
	void PlCheckHitH(GameObject &p);
	void PlCheckHitF(GameObject &p);
	//�v���C���Ƃ̓����蔻��p�t���b�O �g��Ȃ��Ȃ���
	bool plhitR;
	bool plhitL;
	bool plhitH;
	bool plhitF;
	//�I�u�W�F�N�g�𐶐����邽�� �g��Ȃ��Ȃ���
	GameObject footBase;
	GameObject headBase;
	GameObject leftBase;
	GameObject rightBase;

private:
	Texture tex;
};