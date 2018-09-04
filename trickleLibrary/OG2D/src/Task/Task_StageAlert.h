#pragma once
#include "OGSystem\OGsystem.h"
#include "MapPreviewer.h"
#include "StageInfoRes.h"
#include <queue>
#include <functional>


/**
 @brief		�X�e�[�W�I���^�X�N�őI�������X�e�[�W�̊T�v��\������
 @author	Heewon Kim (nabicore@icloud.com)
 @date		2018-06-05
 */

class StageAlert : public TaskObject {
private:

	bool Initialize(const Box2D&);
	virtual void UpDate() override;
	virtual void Render2D() override;
	void Finalize();

	Box2D getSrcOriginal(Texture*) const;
	bool preloadResource(const std::string&);
	inline Box2D GetFixedCameraCoord(const Box2D&) const;
	Box2D OptimizeForWindowSize(const Box2D&) const;
	void positioning();

public:
	explicit StageAlert() {}
	virtual ~StageAlert();

	/**
	 @brief			�X�e�[�W�̏ڍׂ��t�@�C������ǂݍ��݂܂�
	 @param			�t�@�C���̃p�X
	 */
	void SetStageData(const std::string&);

	/**
	 @brief			�X�e�[�W���ƂɌ�������f�[�^��\��Init���܂�
	 @param			�֘A��񂪓����Ă�e�L�X�g�t�@�C���̃p�X
	 @return true	�ǂݍ��ݐ���
	 @return false	�ǂݍ��ݎ��s�A�e�L�X�g�t�@�C���̖��O�A�p�X�Ȃǂ���������������x�m�F���Ă݂邱�ƁI
	 */
	bool operator<<(const std::string&);

	/**
	 @param			�X�e�[�W��
	 @return		�X�e�[�W��񂪃��[�h����Ă��邩�ǂ���
	 */
	bool isExist(const std::string&);

	void SelectFirstElement();

	void setActive(const bool&);
	bool isActive() const;

	void setPosition(const Vec2&);
	Vec2 getPosition() const;

	typedef std::shared_ptr<StageAlert> SP;
	static SP Create(bool, const Box2D&);

private:
	bool													active = false;

	Vec2													position;
	Box2D													titleDraw;
	std::array<Box2D, StageInfoRes::MAX_ACHIEVEMENT>		starFixedDraw;
	std::array<Box2D, StageInfoRes::MAX_ACHIEVEMENT>		achievementFixedDraw;
	std::map<Texture*, Box2D>								draws;
	std::map<Texture*, Box2D>								srcs;
	Box2D													clearFlagDraw;
	Box2D													windowSize;
	Box2D													missionDraw;
	Box2D													missionSrc;

	std::map<std::string, StageInfoRes*>					infoRes;
	StageInfoRes*											currentRes;

	Texture													background;
	Texture													clearFlag;
	Texture*												clearStarTex;
	Texture*												normalStarTex;
	MapPreviewer::SP										previewer;
};