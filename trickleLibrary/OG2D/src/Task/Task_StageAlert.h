#pragma once
#include "OGSystem\OGsystem.h"


/**
 @brief		�X�e�[�W�I���^�X�N�őI�������X�e�[�W�̊T�v��\������
 @author	Heewon Kim (nabicore@icloud.com)
 @date		2018-06-05
 */

class StageAlert : public TaskObject {
private:
	typedef std::pair<std::string, bool> Achievement;

	bool Initialize();
	virtual void UpDate() override;
	virtual void Render2D() override;
	void Finalize();

public:
	explicit StageAlert() {}
	virtual ~StageAlert();

	/**
	 @brief			�X�e�[�W�̏ڍׂ��t�@�C������ǂݍ��݂܂�
	 @param			�t�@�C���̃p�X
	 @return true	�ǂݍ��݂ɐ�������
	 @note			�X�e�[�W���N���A�������A�ǂ�ȕ]��������������Ȃǂ��u�X�e�[�W���O_save.txt�v�`�ŕۑ�����܂�
	 */
	bool SetStageData(const std::string&);

	typedef std::shared_ptr<StageAlert> SP;
	static SP Create(bool = true);

private:
	const static int MAX_ACHIEVEMENT = 3;

private:
	std::string					stageName;
	bool						isClear = false;
	Achievement					achievements[MAX_ACHIEVEMENT];

	Texture						background;
	Texture						star;
	Texture						mission;
	Texture						clearFlag;
};