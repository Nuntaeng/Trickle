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

	bool preloadResource(const std::string&);
	void changeTexture(Texture*, const std::string&, bool);
	inline Box2D GetFixedCameraCoord(const Box2D&) const;
	Box2D OptimizeForWindowSize(const Box2D&) const;

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

	typedef std::shared_ptr<StageAlert> SP;
	static SP Create(bool, const Box2D&);

private:
	std::map<Texture*, Box2D>								draws;
	std::map<Texture*, Box2D>								srcs;
	Box2D													windowSize;

	Texture													background;
	Texture													mission;
	Texture													clearFlag;
	std::array<Texture, StageInfoRes::MAX_ACHIEVEMENT>		starsTex;
	std::map<std::string, StageInfoRes*>					infoRes;
	StageInfoRes*											currentRes;
	MapPreviewer::SP										previewer;
};