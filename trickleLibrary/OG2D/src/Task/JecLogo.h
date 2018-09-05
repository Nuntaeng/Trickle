#pragma once
#include "OGSystem\OGSystem.h"

class LogoTask : public TaskObject
{
	/**
	*enum Mode
	*��ԊǗ�
	*/
	enum Mode
	{
		//! �w�iIN
		back_In,
		//! ���SIN
		logo_In,
		//! ���SOUT
		logo_Out,
		//! �w�iOUT
		back_Out,
		//! �I��
		end,
	};
	//! ���S�摜�̃|�C���^
	Texture* logo;
	//! ���S�̃��l
	float logo_a;
	//! �w�i�̐F
	Color back;
	//! ���
	Mode mode;
	//! �X�}�[�g�|�C���^
	typedef std::shared_ptr<LogoTask> SP;
	/**
	*@brief	:constructor
	*/
	LogoTask();
	/**
	*@brief	:�X�V����
	*/
	void UpDate() override;
	/**
	*@brief	:�`�揈��
	*/
	void Render2D() override;
public:
	/**
	*@brief	:�^�X�N����
	*@return:���s�����ꍇnullptr
	*/
	static SP Create();
	/**
	*@brief	:destructor
	*/
	virtual ~LogoTask();
};