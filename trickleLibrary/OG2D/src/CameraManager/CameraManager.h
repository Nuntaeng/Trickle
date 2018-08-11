
#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
/**
*@brief	:�^�C�g���Ŏg�p����J�����̈ړ����s��class
*/
class CameraManager
{
	//!	�J�������ړ�������͈�
	Box2D Range;
	//!	���݂̐��E�̑傫��
	Box2D Size;
	//!	�J�����̎��ےl
	Box2D RealRange;
	//!	�ړ��l
	Vec2 est;
	//!	�^�[�Q�b�g�̈ʒu�ƃT�C�Y
	Box2D pretarget;
	//!	�J�������X�N���[��������Ώ�
	GameObject* target;
	/**
	*@brief	:�X�N���[������͈͂��w�肷��
	*@param	:Box2D range	�͈͂̈ʒu�ƃT�C�Y
	*/
	void SetRange(const Box2D& range);

public:
	/**
	*@brief	:�����l������
	*/
	CameraManager();
	/**
	*@brief	:�����l���
	*/
	~CameraManager();
	/**
	*@brief	:�^�[�Q�b�g��o�^
	*@param	:GameObject* taget	�^�[�Q�b�g�̃I�u�W�F�N�g�̃|�C���^
	*/
	void SetObject(GameObject* target);
	/**
	*@brief	:���݂̐��E�̃T�C�Y���w�肷��
	*@param	:Box2D size	���E�̑傫��
	*/
	void SetSize(const Box2D& size);
	/**
	*@brief	:�J�������^�[�Q�b�g�ɍ��킹��
	*/
	void move();
	/**
	*@brief	:�^�[�Q�b�g����������
	*/
	void DeleteObject();
};
/**
*@brief	:�J�����̑��ړ��h�~�̂��߂̊g���@�\
*/
class CameraEasing
{
	//!	�C�[�W���O��X�p
	Easing easing_x;
	//! �C�[�W���O��Y�p
	Easing easing_y;
	//!	�J�n�ʒu�̃|�C���^
	Vec2* start;
	//!	�I���ʒu�̃|�C���^
	Vec2* end;
public:
	/**
	*@brief	:�����l������
	*/
	CameraEasing();
	/**
	*@brief	:�����l���
	*/
	~CameraEasing();
	/**
	*@brief	:�J�����̈ړ��̏I���ʒu�̓o�^
	*@param	:Vec2 end	�I���ʒu
	*/
	void SetEndPos(const Vec2& end);
	/**
	*@brief	:�J�����̈ړ�
	*/
	void CameraMove();
	/**
	*@brief	:�J�������ړ������Ă��邩�ǂ���
	*@return:�����Ă���Œ��ł����true
	*/
	bool IsPlay();
	/**
	*@brief	:�J�����̈ړ����~�߂�
	*/
	void MoveEnd();
};