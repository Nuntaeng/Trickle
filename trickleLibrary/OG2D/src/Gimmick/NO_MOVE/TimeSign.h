#pragma once
#include <map>
#include <array>
#include "OGSystem\OGsystem.h"

/**
 @brief		�}�b�v��Ō��ݎ��Ԃ������Ă����D
 @author	Heewon Kim (nabicore@icloud.com)
 @date		2018-06-11
 */

class TimeSign : public TaskObject {
private:
	bool Initialize(const Vec2&);
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
	 @param		�t�@�C���g���q (�u.�v�܂ł��āj
	 @note		�t�H���_�̒��Ő����摜�t�@�C�������̖��O�͕K�����̐����Ɠ������ݒ肵�Ă��������@�i�Ⴆ�΂P��\���摜�Ȃ�1.png)
	 @note		���ׂẲ摜�͓����T�C�Y�ɂȂ�悤�ɐ��삵�Ă�������
	 @note		�^�C������؂�u�F�v�����������Ɠ����T�C�Y�Łuspace.png�v�I�Ȗ��O�œ���ĉ�����
	 */
	void setAtlasPath(const std::string&, const std::string&);

	void setPosition(const Vec2&);
	Vec2& getPosition() const;

	typedef std::shared_ptr<TimeSign> SP;
	static SP Create(const Vec2&, bool);

private:
	std::array<Box2D, 4>			timeNumberDraw;
	Box2D							originPos;
	
	Texture							spacer;
	std::map<int, Texture>			numberAtlas;
	std::string						atlasPath = "numbers/";
	std::string						extension = ".png";
};
