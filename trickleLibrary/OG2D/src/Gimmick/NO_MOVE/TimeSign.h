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
	bool Initialize(const std::string&, const Vec2&);
	virtual void UpDate() override;
	virtual void Render2D() override;
	void Finalize();

	void ClearNumberAtlas();
	void setAtlasAngle(const float&);

public:
	explicit TimeSign() {}
	virtual ~TimeSign();

	/**
	 @brief		�����摜�t�@�C�������������Ă�t�H���_�p�X���Ďw�肵�܂�
	 @param		�摜�p�X
	 @param		1����������̃T�C�Y
	 @param		�w�i�ʒu����ǂ̂��炢����Ƃ���
	 */
	void setAtlas(const std::string&, const Box2D&, const Vec2&);

	/**
	 @brief		���v�̒��A�����̈ʒu���w�肵�܂�
	 @param		�ʒu�l
	 */
	void setDialogPos(const Vec2&);

	void setPosition(const Vec2&);
	Vec2& getPosition() const;

	typedef std::shared_ptr<TimeSign> SP;
	static SP Create(const std::string&, const Vec2&, bool);

private:
	bool							activate = true;
	std::array<Box2D, 4>			timeNumberDraw;
	Box2D							originPos;
	
	Texture							base;
	Texture							numberAtlas;
	std::map<int, Box2D>			numberSrcs;
	std::array<Box2D, 4>			timerDraws;
	std::array<int, 4>				currentTime;
	float							rotateAngle = 0.f;
};
