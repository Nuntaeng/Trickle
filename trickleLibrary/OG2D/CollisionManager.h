#ifndef __COLLISIONMANAGER_H__
#define __COLLISIONMANAGER_H__


/**
 * @brief �����蔻��S�ʊǗ�
 * @date 2018-03-27
 * @author Heewon Kim
 */

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

	/**
	 * @brief �����蔻������ۂɍs������
	 * @note Update�ŌĂԂ���
	 */
	void Run();

private:
	std::vector<Object*> objs;
};

#endif