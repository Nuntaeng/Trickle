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
	void Update(Map &map, Block &block);
	void Render();
	void Finalize();

	void SetParent(Object*);
	bool HasParent() const;


	//�}�b�v�Ƃ̓����蔻��Ɏg�p
	void CreateFoot();
	void CreateHead();
	void CreateLeft();
	void CreateRight();

	//�v���C���Ƃ̓����蔻��Ɏg�p
	void PlCheckHitR(Object &p);
	void PlCheckHitL(Object &p);
	void PlCheckHitH(Object &p);
	void PlCheckHitF(Object &p);

	//�v���C���Ƃ̓����蔻��p�t���b�O
	bool plhitR;
	bool plhitL;
	bool plhitH;
	bool plhitF;
	//�}�b�v�Ƃ̓����蔻��p�t���b�O
	bool maphitR;
	bool maphitL;
	bool maphitH;
	bool maphitF;

	//�߂荞�܂Ȃ�����
	void CheckMove(Vec2 &e_, Map &map , Block &bock);

	//�I�u�W�F�N�g�𐶐����邽��
	Object footBase;
	Object headBase;
	Object leftBase;
	Object rightBase;

private:
	Object * parent;
	Texture tex;
};

#endif