#ifndef __WATER_H__
#define __WATER_H__


/**
 * @brief	���֘A�����ł�
 * @date	2018-03-24
 * @author	Heewon Kim
 */

#include <map>
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Water : public Object {

public:
	enum class State : int {
		LIQUID = 0,			//�@�t��
		SOLID,				//�@��
		GAS					//�@�C��
	};
	
	enum class Situation : int
	{
		Newfrom,			//�o����
		Normal,				//�ʏ�
		Deleteform,			//�폜��
		CreaDelete,			//�폜
	};

public:
	explicit Water(Vec2 pos);
	virtual ~Water();

	bool Initialize();
	void Update();
	void Render();
	void Finalize();

	/**
	 * @brief	��ԓ]�ڂ��܂��B
	 * @see	�O�Ŏg���Ƃ��ɂ�Water::State::Liquid ����Ȍ`��
	 */
	void SetState(const State&);
	State GetState() const;

	void SetSituation(const Situation&);
	Situation GetSituation() const;

	//���ʂ̈ړ�
	float waterMove();
	//���ʂ̃`�F�b�N
	float GetWaterVolume() const;

	bool active;
	//����
	float volume;
	//���G����
	int invi;
private:
	Texture tex;
	std::map<State, Box2D> drawRange;
	State currentState;
	Situation nowSituation;
	Vec2 minSize;
	Vec2 maxSize;
	int setTime;
	Situation UpNewform();
	Situation UpDeleteform();
	Situation UpNormal();
};
#endif