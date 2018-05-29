#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "OGSystem\Timer\glTimer.h"
#include "OGSystem\Input\Input.h"

/**
 *	@brief	Recorder�Ŏ�����f�[�^���Đ�����
 *	@author Heewon Kim (nabicore@icloud.com)
 */

class RecPlayer {

private:
	explicit RecPlayer() {}
	virtual ~RecPlayer() {}
	bool Initialize(const std::string&);

public:
	/**
	 *	@brief	�����֐�
	 *	@param	�t�@�C����
	 *	@param	�f�o�b�O���[�h�t���O�i��{�l�FOff�j
	 *	@return	�I�u�W�F�N�g
	 */
	static RecPlayer* Create(const std::string&, const bool&);

	/**
	 *	@brief	�N���X����
	 */
	void Destroy();

private:
	std::string					fileName;
	std::istream				fileReader;
};