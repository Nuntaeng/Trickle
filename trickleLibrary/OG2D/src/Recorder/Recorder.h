#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "OGSystem\Timer\glTimer.h"

/**
 *	@brief  �v���C���[�̍s�����t�@�C���Ƃ��ċL�^���܂�
 *	@author	Heewon Kim (nabicore@icloud.com)
 */
class Recorder {
	explicit Recorder() {}
	virtual ~Recorder() {}
	bool Initialize(const std::string&);
	void printLog(const std::string&);
	void Recorde();

public:
	/**
	*	@brief	Recorder����������ɍ��܂�
	*	@param	�L�^�Ɏg���t�@�C����
	*	@param	�f�o�b�O�p���O���o�����ǂ��� �i�f�t�H���g�FFalse)
	*	@return	�������A�h���X�A�g���I�������K���폜���邱�ƁI
	*/
	static Recorder* Create(const std::string&, const bool&);

	/**
	 *	@brief	�N���X���폜���܂�
	 */
	void Destroy();

private:
	bool				isLogging = false;
	Time				gameTimer;
	std::string			fileName = "save.txt";
	std::ofstream		fileWriter;
	std::thread			recThread;
};