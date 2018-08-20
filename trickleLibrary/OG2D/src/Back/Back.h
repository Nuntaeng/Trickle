#pragma once

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

/**
* @brief �w�i�ɗ����_�N���X
* @author ���c
* @date 2018.8.10
*/
class Cloud : public GameObject, public TaskObject {
	//! �_�̃e�N�X�`��
	Texture cloudImg;
	//! �_�摜�̕\���ʒu
	Vec2 cloudPos[2];
	//! �ړ��X�s�[�h
	float speed;
public:
	Cloud(const std::string& path, float speed);
	~Cloud();
	static std::shared_ptr<Cloud> Create(const std::string& path, float speed);

	void Initialize(const std::string& path, float speed);
	void UpDate() override;
	void Render2D() override;
};


/**
*@brief	:�w�i�`��ƃX�N���[�����s��class
*/
class Back : public TaskObject
{
	//!	�w�i�摜�f�[�^
	Texture backImg;
	//!	�`�悷��T�C�Y
	Vec2 size;
	//!	�X�N���[�����s���w�i���ǂ���
	bool isScroll;
	//!	�}�b�v�T�C�Y�̏c���l
	Vec2* mapSize;
	//!	�`�悷��摜�̈ʒu
	Vec2* texPos;
	//!	�}�b�v�̒��S�l
	float* Center;
	//!	�}�b�v�̈ʒu�ƒ[�̈ʒu�̍�
	float* Xsize;
	//!	�[�̈ʒu�Ɖ摜�̈ʒu�̍�
	float* Tsize;
	//!	�X�}�|�錾
	typedef std::shared_ptr<Back> SP;
	/**
	*@brief	:�摜�̓ǂݍ��݂ƕϐ��̏�����
	*/
	void Init(const std::string&);
	/**
	*@brife	:constructor
	*@param	:string	�t�@�C����
	*@param	:Vec2	�`�掞�̏c�T�C�Y�Ɖ��T�C�Y
	*/
	Back(const std::string&, const Vec2&);
	/**
	*@brife	:constructor
	*@param	:string	�t�@�C����
	*@param	:float size_x	�`�掞�̉��T�C�Y
	*@param :float size_y	�`�掞�̏c�T�C�Y
	*/
	Back(const std::string&, float, float);
	/**
	*@brife	:constructor
	*@param	:string	�t�@�C����
	*@param	:int size_x	�`�掞�̉��T�C�Y
	*@param :int size_y	�`�掞�̏c�T�C�Y
	*/
	Back(const std::string&, int, int);
	/**
	*@brief	:�X�V����
	*/
	void UpDate() override;
	/**
	*@brief	:�`�揈��
	*/
	void Render2D() override;
	/**
	*@brief	:�摜�̕`��ʒu�̐ݒ�
	*@return:bool	�ݒ�ɐ���������true
	*/
	bool TexturePositionConfig();
public:
	/**
	*@brief	:destructor
	*/
	virtual ~Back();
	/**
	*@brief	:�^�X�N����
	*@param	:string path	�t�@�C����
	*@param	:Vec2 size	�`�掞�̏c�T�C�Y�Ɖ��T�C�Y
	*@reutrn:Back	�����Ɏ��s�����ꍇ��nullptr
	*/
	static SP Create(const std::string& path, const Vec2& size);
	/**
	*@brief	:�^�X�N����
	*@param	:string path	�t�@�C����
	*@param	:float size_x	�`�掞�̉��T�C�Y
	*@param :float size_y	�`�掞�̏c�T�C�Y
	*@reutrn:Back	�����Ɏ��s�����ꍇ��nullptr
	*/
	static SP Create(const std::string& path, float size_x, float size_y);
	/**
	*@brief	:�^�X�N����
	*@param	:string path	�t�@�C����
	*@param	:int size_x	�`�掞�̉��T�C�Y
	*@param :int size_y	�`�掞�̏c�T�C�Y
	*@reutrn:Back	�����Ɏ��s�����ꍇ��nullptr
	*/
	static SP Create(const std::string& path, int size_x, int size_y);
	/**
	*@brief	:�X�N���[�����s���w�i����ݒ肷��
	*@param	:bool flag	�X�N���[�����s���L��
	*/
	void SetScroll(bool flag = true);
};