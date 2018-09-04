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
		//!	���S�̃t�F�[�h�C��
		LogoIn,
		//!	���S�̃t�F�[�h�A�E�g
		LogoOut,
		//! �w�i�̃t�F�[�h�C��
		BackIn,
		//! �w�i�̃t�F�[�h�A�E�g
		BackOut,
	};
private:
	//!	���S�f�[�^
	Texture* logoimage;
	//! �w�i�f�[�^
	Texture* backimage;
	//! �`��ʒu
	Box2D draw;
	//!	�`��摜�ʒu
	Box2D src;
	//! �w�i�̐F�f�[�^
	Color* backcolor;
	//! ���S�̐F�f�[�^
	Color* logocolor;
	//! ���݂̃��[�h
	Fead mode;
	//! �t�F�[�h�A�E�g�̃^�C��
	const float feadOutTime;
	//! �t�F�[�h�C���̃^�C��
	const float feadInTime;
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
	*@brief	:���S�t�F�[�h�A�E�g����
	*/
	void FeadLogoOutUpDate();
	/**
	*@brief	:���S�t�F�[�h�C������
	*/
	void FeadLogoInUpDate();
	/**
	*@brief	:�w�i�t�F�[�h�A�E�g����
	*/
	void FeadBackOutUpDate();
	/**
	*@brief	:�w�i�t�F�[�h�C������
	*/
	void FeadBackInUpDate();
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