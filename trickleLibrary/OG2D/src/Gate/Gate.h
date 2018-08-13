#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
/**
*@brief	:�X�e�[�W�Z���N�g�Ŏg�p������I�u�W�F�N�g
*/
class Gate : public GameObject, public TaskObject
{
	//!	�g�p�摜�|�C���^
	Texture* image;
	//!	�`��ʒu
	Box2D draw;
	//!	�e�N�X�`���ʒu
	Box2D src;
	//!	��ID
	unsigned __int8 ID;
	//!	�J���Ă��邩�ǂ���
	bool isOpen;
	//!	�O��̊J����
	bool preIsOpen;
	//!	�A�j���[�V�����p�J�E���g
	int AnimCnt;
	//!	�A�j���[�V�������ς��Ԋu
	int Sense;
	//!	�`���؂�͈͂�X���W
	float door_x;
	//!	�`���؂�͈͂�W���W
	float door_w;
	//!	�X�}�[�g�|�C���^
	typedef std::shared_ptr<Gate> SP;
	std::string soundclosename;     //�T�E���h�̃t�@�C�����i�[
	std::string soundopenname;
	/**
	*@brief	:constructor	�l�̏�����
	*/
	Gate(const Vec2&);
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
	*@brief	:�������
	*/
	virtual ~Gate();
	/**
	*@brief	:�^�X�N����
	*@param	:Vec2 pos	�����ʒu
	*@return:Gate �����Ɏ��s�����ꍇnullptr
	*/
	static SP Create(const Vec2& pos, bool = true);
	/**
	*@brief	:�^�X�N����
	*@param	:float pos_x	����X�ʒu
	*@param	:float pos_y	����Y�ʒu
	*@return:Gate �����Ɏ��s�����ꍇnullptr
	*/
	static SP Create(const float pos_x, const float pos_y, bool = true);
	/**
	*@brief	:�g�p�摜��o�^
	*@param	:Texture* texture	�g�p�摜�̃|�C���^
	*/
	void SetTexture(Texture* texture);
	/**
	*@brief	:��ID���擾
	*@return:unsigned __int8 ��ID
	*/
	unsigned __int8 GetID() const;
	/**
	*@brief	:�Q�[�g���J������
	*@return:bool �J���������J�n���ꂽ�ꍇtrue
	*/
	bool ToOpen();
	/**
	*@brief	:�Q�[�g�������
	*@return:bool ���������J�n���ꂽ�ꍇtrue
	*/
	bool ToClose();
	/**
	*@brief	:�o�^����Ă���`���؂�X�ʒu��Ԃ�
	*@return:float �ʒu��X���W
	*/
	float Get_Door_x() const;
	/**
	*@brief	:�o�^����Ă���`���؂�W���W��Ԃ�
	*@return:float �ʒu��W���W
	*/
	float Get_Door_w() const;

	Sound soundOpen;
	Sound soundClose;
};