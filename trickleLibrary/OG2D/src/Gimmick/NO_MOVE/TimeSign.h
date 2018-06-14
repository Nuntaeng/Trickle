#pragma once
#include <map>
#include <array>
#include "OGSystem\OGsystem.h"

/**
 @brief		�}�b�v��Ō��ݎ��Ԃ������Ă����D
 @author	Heewon Kim (nabicore@icloud.com)
 @note		GameManager�^�X�N�������Ă��Ȃ��Ǝ��s����܂���
 @date		2018-06-11
 */

class TimeSign : public TaskObject {
private:
	bool Initialize(const std::string&, const Box2D&);
	virtual void UpDate() override;
	virtual void Render2D() override;
	void Finalize();

	void ClearNumberAtlas();
	inline bool isCommaDrawable(const int&) const;

public:
	explicit TimeSign() {}
	virtual ~TimeSign();

	/**
	 @brief		�����摜�t�@�C�������������Ă�t�H���_�p�X���Ďw�肵�܂�
	 @param		�摜�p�X
	 @param		1����������̃T�C�Y
	 @param		�w�i�ʒu����ǂ̂��炢����Ƃ���
	 */
	void setAtlas(const std::string&, const Box2D&, const Box2D&);

	/**
	 @brief		���v�̒��A�����̈ʒu���w�肵�܂�
	 @param		�ʒu�l
	 */
	void setDialogPos(const Vec2&);

	/**
	 @brief		���Ԃ�\�����鐔���̊p�x��ݒ肵�܂�
	 @param		�x�p�x
	 */
	void setAtlasAngle(const float&);

	/**
	 @brief		���ƕb�ԂɁu�F�v��ǉ����܂�
	 @param		Draw
	 @param		�����\�̒��ɂ���ꍇ�A���͈̔�
	 @param		�����P��
	 @note		setAtlas���Ă񂾂�A���̂��ƂɌĂ�ł�������
	 */
	void setComma(const Box2D&, const Box2D&, const Box2D&);

	void setPosition(const Vec2&);
	Vec2 getPosition() const;

	typedef std::shared_ptr<TimeSign> SP;
	static SP Create(const std::string&, const Box2D&, bool);

private:
	bool							activate = true;
	Box2D							originPos;
	
	Texture							base;
	Texture							numberAtlas;
	std::map<char, Box2D>			numberSrcs;
	std::array<Box2D, 5>			timerDraws;
	std::array<int, 5>				currentTime;
	float							rotateAngle = 0.f;
};
