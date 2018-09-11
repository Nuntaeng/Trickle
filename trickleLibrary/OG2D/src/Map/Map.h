#pragma once
//______________________________//
//|�}�b�v�V�X�e��               |//
//|�����F2018/03/24���q��       |//
//|____________________________|//
#include "Object\Object.h"
#include "OGSystem\Texture\Texture.h"
#include "OGSystem\OGsystem.h"
#include <cctype>
#include <algorithm>
/**
*enum Format
*�t�@�C���`��
*/
enum Format
{
	//!	csv
	csv,
};
/**
*@brief	:�Q�[���Ɏg�p����}�b�vclass
*/
class Map : public TaskObject
{
	class Base : public GameObject
	{
		//!	�}�b�v�ԍ�
		int arr;
		//!	����pID
		int* ID;
	public:
		/**
		*@brief	:constructor
		*/
		Base();
		/**
		*@brief	:destructor
		*/
		virtual ~Base();
		/**
		*@brief	:�o�^ID���w��ԍ��ȉ������ׂ�
		*@param	:int id �w��ԍ�
		*@return:�ȉ��ł����true
		*/
		bool IDCheck(const int id);
		/**
		*@brief	:�o�^�ԍ����w��l�Ɠ����������ׂ�
		*@param	:int chip �w��l
		*@return:�����Ȃ�true
		*/
		bool ChipCheck(const int chip);
		/**
		*@brief	:ID��o�^����
		*@param	:int id ID�̒l
		*/
		void SetID(const int id);
		/**
		*@brief	:�}�b�v�ԍ����w�肷��
		*@param	:int arr �w��l
		*/
		void Setarr(const int arr);
		/**
		*@brief	:�o�^����Ă���}�b�v�ԍ���Ԃ�
		*@return:int �}�b�v�ԍ��̒l
		*/
		int Getarr() const;
		/**
		*@brief	:�o�^����Ă���ID��Ԃ�
		*@return:int* ���o�^�Ȃ��nullptr
		*/
		int* GetID() const;
	};
private:
	//! �t�@�C���p�X
	const std::string _FilePath;
	//! �摜�̃t�@�C����
	std::string chipimgname;
	//!	�`��}�b�v�z��
	std::vector<Box2D> chip;
	//!	�g�p�摜���
	Texture* mapimg;
	//!	���摜�̏c���T�C�Y
	Vec2 chipsize;
	//!	�X�}�[�g�|�C���^
	typedef std::shared_ptr<Map> SP;
public:
	//!	�`�悷��}�b�v�`�b�v�̐�
	Vec2 mapSize;
	//!	�I�u�W�F�N�g���
	std::vector<std::vector<Base>> hitBase;
	//!	�`��̏c���T�C�Y
	Vec2 DrawSize;
	/**
	*@brief	:constructor
	*/
	Map();
	/**
	*@brief	:�X�V����
	*/
	void UpDate() override;
	/**
	*@brief	:�`�揈��
	*/
	void Render2D() override;
	/**
	*@brief	:�������
	*/
	bool Finalize();
	/**
	*@brief	:�}�b�v���O���t�@�C������ǂݍ���
	*@param	:string _path �t�@�C����
	*@param	:Format	format �t�@�C���`��
	*@return:�ǂݍ��݂ɐ��������true
	*/
	bool LoadMap(const std::string& _path, const Format& format);
public:
	/**
	*@brief	:destructor
	*/
	virtual ~Map();
	/**
	*@brief	:�^�X�N����
	*@param	:string path �t�@�C����
	*@param	:Format format �t�@�C���t�H�[�}�b�g
	*/
	static SP Create(const std::string& path, const Format& format = csv);
	/**
	*@brief	:�}�b�v�Ƃ̓����蔻��
	*@param	:GameObject p ���肵�����I�u�W�F�N�g
	*@param	:int id �w��ID�ȉ��̂��̂̂ݔ�����s��
	*@return:�������Ă����true
	*/
	bool HitCheck(GameObject &p, const int id);
	/**
	*@brief	:�}�b�v�Ƃ̓����蔻��
	*@param	:GameObject p ���肵�����I�u�W�F�N�g
	*@param	:string name �w�薼�̂ݔ�����s��
	*@return:�������Ă����true
	*/
	bool HitCheck(GameObject &p, const std::string& name);
private:
	/**
	*@brief	:�ǂݍ��݂ɉ������I�u�W�F�N�g�̐������s��
	*@param	:string name �ǂݍ��ݖ�
	*@param	:int x ����X���W
	*@param	:int y ����Y���W
	*/
	void ObjectCreateCheck(const std::string& name,int x,int y);
	
	Vec2 waterPos;		//���̐����ʒu�ۑ��p
public:
	Vec2 getWaterPos(); //���̐����ʒu��Ԃ�
};