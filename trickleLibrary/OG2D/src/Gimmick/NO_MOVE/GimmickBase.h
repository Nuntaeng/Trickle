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
class GimmickBase : public GameObject, public TaskObject
{
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

private:
	//! @brief �o�^����^�X�N��
	std::string taskName_;
	//! @brief ���Ɠ����蔻����s����`
	GameObject hitBase_;
	//! @brief ���g�̋쓮���
	bool active_;
	//! @brief �{�̂̌���
	Dir dir_;
	//! @brief �����蔻��̕�
	Vec2 range_;


public:
	GimmickBase(Vec2 pos, Vec2 range, Dir dir, bool active);
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
	* @brief ����������
	*/
	virtual bool Initialize(Vec2 pos, Vec2 range, Dir dir, bool active);

	/**
	* @brief �^�X�N����o�^����
	*/
	void setTaskName(const std::string& name);

	/**
	* @brief �����蔻���`��ݒ肷��
	*/
	void setHitBase(Vec2 pos, Vec2 range);
	/**
	* @brief �����蔻���`��Ԃ�
	*/
	GameObject getHitBase();

	/**
	* @brief ���g�̉ғ���Ԃ𔽓]������
	*/
	void changeActive();

	/**
	* @brief �����Ԃ̐��Ɍ��ʂ�^����
	* @details Fan�F�����C�����ɓ������AHeater�F�X����,���������C�AIcemachine�F�����X
	*/
	virtual void affectWater();

	/**
	* @brief ������ݒ肷��
	*/
	void setDirection(Dir d);
	/**
	* @brief ������Ԃ�
	*/
	Dir getDirection();

	/**
	* @brief �쓮��Ԃ�ݒ肷��
	*/
	void setActive(bool a);

	/**
	* @brief �쓮��Ԃ�Ԃ�
	*/
	bool isActive();
};

