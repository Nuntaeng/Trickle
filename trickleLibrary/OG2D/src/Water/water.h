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
	 
public:
	explicit Water();
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

	bool active;

private:
	Texture tex;
	std::map<State, Box2D> drawRange;
	State currentState;
};
#endif