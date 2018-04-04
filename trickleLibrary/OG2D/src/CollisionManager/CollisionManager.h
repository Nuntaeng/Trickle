#ifndef __COLLISIONMANAGER_H__
#define __COLLISIONMANAGER_H__


/**
 * @brief �����蔻��S�ʊǗ�
 * @date 2018-03-27
 * @author Heewon Kim
 */

#include <array>
#include <vector>
#include "Object\Object.h"

class CollisionManager {

public:
	explicit CollisionManager();
	virtual ~CollisionManager();
	
	/**
	 * @brief �����蔻����s�������I�u�W�F�N�g��o�^���܂�
	 * @param Object* �I�u�W�F�N�g�̃A�h���X
	 */
	void AddChild(Object*);

	template <typename T>
	void AddCollisionFunction(void (T::*function_)(std::vector<Object*>*), Object* obj_) {
		std::function<void(std::vector<Object*>*)> obj = std::bind(function_, std::placeholders::_1);
		collisionFunctions.push_back(obj);
	}	

	/**
	 * @brief �����蔻������ۂɍs������
	 * @note Update�ŌĂԂ���
	 */
	void Run();

	void Destroy();

	bool operator-(const Object*);

	void operator+=(Object*);

private:
	std::vector<Object*> objs;
	std::vector <std::function<void(std::vector<Object*>*)>> collisionFunctions;
};

#endif