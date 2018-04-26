#pragma once
#ifndef __BLOCK_H__          //����ȂɁH
#define __BLOCK_H__


#include "Water\water.h"
#include "Map\Map.h"
#include "CollisionManager\CollisionManager.h"
//#include "Object\Object.h"

class Block : public Object {

public:
	explicit Block();
	explicit Block(Vec2 pos);
	virtual ~Block();

	//bool HitMap;
	//float speed;
	Vec2 speed;
	Vec2 gravity;
	bool Initialize(Vec2);
	void Update(Map &map, Block &block, Object& p);
	void Render();
	void Finalize();

	void SetParent(Object*);
	bool HasParent() const;

	//�߂荞�܂Ȃ�����
	void CheckMove(Vec2 &e_, Map &map, Block &bock);
	//�v���C���[�ƃu���b�N�̓����������̏���
	void PlCheckHit(Object &p, Block &block);
	//�v���C���[�ƃu���b�N�̓����蔻��t���b�O
	bool plhit;
	//�v���C��������A�ړ�����ʂ������Ă���
	Vec2 GetMove(Vec2 move);
	//�v���C���[�Ɉړ��s���̒l��Ԃ�
	Vec2 BackMove();

	Vec2 backmove;

	//�v���C���Ƃ̓����蔻��Ɏg�p�@�@�g��Ȃ��Ȃ���
	void PlCheckHitR(Object &p);
	void PlCheckHitL(Object &p);
	void PlCheckHitH(Object &p);
	void PlCheckHitF(Object &p);
	//�v���C���Ƃ̓����蔻��p�t���b�O �g��Ȃ��Ȃ���
	bool plhitR;
	bool plhitL;
	bool plhitH;
	bool plhitF;
	//�I�u�W�F�N�g�𐶐����邽�� �g��Ȃ��Ȃ���
	Object footBase;
	Object headBase;
	Object leftBase;
	Object rightBase;

private:
	Object * parent;
	Texture tex;
};

#endif