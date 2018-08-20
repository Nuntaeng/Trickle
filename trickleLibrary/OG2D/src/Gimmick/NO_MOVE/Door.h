///Game���p��switch�ɘA�������J���s��class
///constructor	pos = �ʒu,size = �傫��,isOpen = �J���Ă��邩(true = �J���Ă���,false = ���Ă���)
///ToOpen�ŊJ(����true,���sfalse)�AToClose�ŕ�(����true,���sfalse)�AIsOpen(�Jtrue,��false)�ŊJ���Ă��邩��Ԃ�
///GetID��Door�ɐݒ肳��Ă���ID��Ԃ��AID�͐������Ɍ��肳���
#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
/**
*@brief	:�Q�[�����̔��I�u�W�F�N�g
*/
class Door :public GameObject, public TaskObject
{
public:
	/**
	*@enum Direction
	*���̌���
	*/
	enum Direction
	{
		//!	��
		WIDTH,
		//!	�c
		HEIGHT,
	};
private:
	//!	��ID
	unsigned __int8 id;
	//! �J���Ă��邩�ǂ���
	bool isOpen;
	//! �ړ������ǂ���
	bool isMove;
	//! �O��̊J�����
	bool preIsOpen;
	//! �o�ߎ���
	float timeCnt;
	//!	���_�ʒu
	Vec2 originPos;
	//! �g�p�摜�̃|�C���^
	Texture* image;
	//! �`��ʒu
	Box2D draw;
	//! �`��摜�ʒu
	Box2D src;
	//! ����
	Direction direction;
	//!	�I�u�W�F�N�g�̈ʒu���v�Z����̂ɕK�v�ƂȂ�l�̃A�h���X��ۊ�
	float* ch_Value[3];
	//! �`��p��]�l
	float rotate;
	//! �X�}�[�g�|�C���^
	typedef std::shared_ptr<Door> SP;
	/**
	*@brief	:�X�V����
	*/
	void UpDate() override;
	/**
	*@brief	:�`�揈��
	*/
	void Render2D() override;
	/**
	*@brief	:constructor
	*@param	:Vec2 pos	�ʒu
	*@param	:Vec2 size	�傫��
	*@param	:bool isOpen	�J���
	*@param	:Direction dire	����
	*/
	Door(const Vec2& pos, const Vec2& size, const bool isOpen, const Direction& dire);
public:
	/**
	*@brief	:destructor
	*/
	virtual ~Door();
	/**
	*@brief	:�^�X�N����
	*@param	:Vec2 pos	�ʒu
	*@param	:Vec2 size	�傫��
	*@param	:bool isOpen	�J���
	*@param	:Direction dire	����
	*@return:Door �����Ɏ��s�����ꍇnullptr
	*/
	static SP Create(const Vec2& pos,const Vec2& size,const bool isOpen,const Direction& dire);
	/**
	*@brief	:�����J����
	*@return:bool ���������ꍇtrue
	*/
	bool ToOpen();
	/**
	*@brief	:����߂�
	*@return:bool ���������ꍇtrue
	*/
	bool ToClose();
	/**
	*@brief	:���̏�Ԃ𔽓]�ɂ���
	*@return:bool �ύX��̏��
	*/
	bool changeIsOpen();
	/**
	*@brief	:���݂̊J��Ԃ�Ԃ�
	*@return:bool �J���
	*/
	bool IsOpen() const;
	/**
	*@brief	:���ݓ����Ă��邩��Ԃ�
	*@return:bool �����Ă���ꍇtrue
	*/
	bool IsMove() const;
	/**
	*@brief	:�g�p�摜��o�^����
	*@param	:Texture* tex	�摜�̃|�C���^
	*/
	void SetTexture(Texture* tex);
	/**
	*@brief	:��ID��Ԃ�
	*@return:unsgined __int8 ��ID
	*/
	unsigned __int8 GetID() const;
};