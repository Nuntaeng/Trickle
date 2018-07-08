///Game���p��switch�ɘA�������J���s��class
///constructor	pos = �ʒu,size = �傫��,isOpen = �J���Ă��邩(true = �J���Ă���,false = ���Ă���)
///ToOpen�ŊJ(����true,���sfalse)�AToClose�ŕ�(����true,���sfalse)�AIsOpen(�Jtrue,��false)�ŊJ���Ă��邩��Ԃ�
///GetID��Door�ɐݒ肳��Ă���ID��Ԃ��AID�͐������Ɍ��肳���
///
#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
class Door :public GameObject, public TaskObject
{
	unsigned __int8 id;
	bool isOpen;
	bool isMove;
	bool preIsOpen;
	float timeCnt;
	Vec2 originPos;
	Texture* image;
	Box2D draw;
	Box2D src;
public:
	Door(const Vec2& pos,const Vec2& size,const bool isOpen);
	virtual ~Door();
	typedef std::shared_ptr<Door> SP;
	static SP Create(const Vec2& pos,const Vec2& size,const bool isOpen);
	void UpDate() override;
	void Render2D() override;
	bool ToOpen();	
	bool ToClose();
	bool IsOpen() const;
	bool IsMove() const;
	void SetTexture(Texture*);
	unsigned __int8 GetID() const;
};