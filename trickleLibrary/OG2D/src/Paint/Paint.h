#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
/**
*@brief	:�G��I�u�W�F�N�g
*/
class Paint final: public GameObject, public TaskObject
{
public:
	/**
	*enum PaintColor
	*�G��p�̃J���[�F
	*/
	enum PaintColor
	{
		//!	��
		Red,
		//!	��
		Blue,
		//!	��
		Purple,
		//! ���n
		Normal,
	};
private:
	//!	�F���
	PaintColor* color;
	//!	�摜�̏��
	Texture* image;
	//! �`��ʒu
	Box2D draw;
	//!	�`��摜�ʒu
	Box2D src;
	//!	�X�}�[�g�|�C���^
	typedef std::shared_ptr<Paint> SP;
	/**
	*@brief	:�`��ʒu���w�肷��
	*/
	void Setsrc();
	/**
	*@brief	:���Ƃ̓����蔻��
	*@return:�������Ă����true
	*/
	bool WaterHit();
	/**
	*@brief	:�X�V����
	*/
	void UpDate() override;
	/**
	*@bried	:�`�揈��
	*/
	void Render2D() override;
	/**
	*@brief	:constructor
	*@param	:Vec2 pos �����ʒu
	*@param	:Vec2 size �傫��
	*@param	:PaintColor color_ �F���
	*/
	explicit Paint(const Vec2 & pos, const Vec2 & size, const PaintColor & color_);
public:
	/**
	*@brief	:destructor
	*/
	virtual ~Paint();
	/**
	*@brief	:�^�X�N����
	*@param	:Vec2 pos �����ʒu
	*@param	:Vec2 size �傫��
	*@param	:PaintColor color_ �F���
	*@return:�����Ɏ��s�����ꍇnullptr
	*/
	static SP Create(const Vec2& pos, const Vec2& size, const PaintColor& color_);
	/**
	*@brief	:�g�p�摜��o�^����
	*@param	:Texture* tex �摜���
	*/
	void SetTexture(Texture* tex);
};