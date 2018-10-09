/**
* @file GimmickBase.h
* @brief Fan,Heater,Icemachine�̊��N���X���`����
* @author yokota0717
* @date 2018.10.9
*/

#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

/**
* @brief Fan,Heater,Icemachine�̊��N���X
* @details �X�C�b�`�ŃI���I�t��؂�ւ���M�~�b�N�͂��̃N���X���p�����邱��
*/
class GimmickBase
{
	std::string taskName;
	GameObject hitBase;
	bool active;

public:
	/**
	* @brief �M�~�b�N�̌���
	*/
	enum Dir {
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};
	GimmickBase();
	~GimmickBase();

	/**
	* @brief �^�X�N�I�u�W�F�N�g��������
	* @param pos �M�~�b�N�̖{�̂�\��������W(�摜����)
	* @param range �����蔻���`�̑傫��
	* @param dir �{�̂̌���
	* @param active �����������_�œ����Ă��邩�ǂ���
	*/
	std::shared_ptr<GimmickBase> Create(Vec2 pos, Vec2 range, Dir dir, bool active);

	/**
	* @brief ���g�̉ғ���Ԃ𔽓]������
	*/
	void changeActive();

	/**
	* @brief �����Ԃ̐��Ɍ��ʂ�^����
	* @details Fan�F�����C�����ɓ������AHeater�F�X����,���������C�AIcemachine�F�����X
	*/
	void affectWater();
};

