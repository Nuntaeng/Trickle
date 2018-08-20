#pragma once
#include "OGSystem\OGSystem.h"
/**
*@brief	:�^�X�N�ύX���ɍs�����[�h�p�̃^�X�N
*/
class Load : public TaskObject
{
public:
	/**
	*enum Fead
	*�C���ƃA�E�g�𕪂��邽��
	*/
	enum Fead
	{
		//!	�t�F�[�h�C��
		In,
		//!	�t�F�[�h�A�E�g
		Out
	};
private:
	//!	�摜�f�[�^
	Texture image;
	//! �`��ʒu
	Box2D draw;
	//!	�`��摜�ʒu
	Box2D src;
	//! �摜�̐F�f�[�^
	Color* color;
	//! ���݂̃��[�h
	Fead mode;
	//!	�폜���s���^�X�N�̕�����
	std::vector<std::string> deleteObjectName;
	//!	�X�}�[�g�|�C���^
	typedef std::shared_ptr<Load> SP;
	/**
	*@brief	:�`�揈��
	*/
	void Render2D() override;
	/**
	*@brief	:�|�[�Y����
	*/
	void PauseUpDate() override;
	/**
	*@brief	:�X�V����
	*/
	void UpDate() override;
	/**
	*@brief	:constructor
	*/
	Load();
	/**
	*@brief	:�t�F�[�h�A�E�g����
	*/
	void FeadOutUpDate();
	/**
	*@brief	:�t�F�[�h�C������
	*/
	void FeadInUpDate();
public:
	/**
	*@brief	:destructor
	*/
	virtual ~Load();
	/**
	*@brief	:�^�X�N����
	*/
	static SP Create();
	/**
	*@brief	:�o�^����Ă���摜�������I�ɕ`�悳����
	*/
	void Draw();
	/**
	*@brief	:�s���t�F�[�h���w�肷��
	*/
	void SetFead(const Fead&);
	/**
	*@brief	:�S�Ẵ^�X�N�̍X�V���~�߂�
	*@param	:bool flag �~�߂�true,����false
	*/
	void ALLTaskUpDateStop(const bool flag = true);
	/**
	*@brief	:���݂̃t�F�[�h���擾����
	*@return:Fead ���݂̃t�F�[�h
	*/
	Fead Get() const;
	/**
	*@brief	:�폜�������I�u�W�F�N�g�̕������o�^����
	*@param	:string name �I�u�W�F�N�g�̕�����
	*/
	void AddDeleteObjectName(const std::string& name);
};