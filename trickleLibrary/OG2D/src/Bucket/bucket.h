#pragma once


/**
 * @brief �f���́f�o�P�b�c
 * @author Heewon Kim
 * @date 2018-03-30
 */

#include "OGSystem\OGSystem.h"
#include "Object\Object.h"
#include "Block\block.h"

class Bucket : public GameObject,public TaskObject {

private:
	const Box2D BUCKET_NOTHING = Box2D(0, 0, 256, 256);
	const Box2D BUCKET_WATER = Box2D(256, 0, 256, 256);
	Box2D GetSpriteCrop() const;
	bool BucketWaterCreate();
	bool isObjectCollided();

public:
	explicit Bucket();
	explicit Bucket(Vec2& pos);
	virtual ~Bucket();

	typedef std::shared_ptr<Bucket> SP;
	static SP Create(Vec2&, bool = true);
	bool Initialize(Vec2& pos);
	void UpDate();
	void Render2D();
	bool Finalize();

	void CheckMove(Vec2 &);

	void HoldCheck(bool = true);
	bool GetHold() const;
	void WaterIsHitCheck();
	/**
	 * @brief	�o�P�b�c���琅�����ڂ��܂�
	 * @return	�o�P�b�c�̒��ɂ������ʂ����̐��̃A�h���X�n
	 * @note	new�g�����̂ŕK�������Ă�������
	 */
	float capacity;
	Vec2 gravity;			//�d��
	bool hold;				//�v���C�����o�P�c�������Ă��邩�̔��f
	int invi;				//���G����(���Ƃ̔�����s��Ȃ�����)
private:
	Texture tex;
};