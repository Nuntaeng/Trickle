#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <thread>
#include <queue>
#include "OGSystem\OGsystem.h"
#include "OGSystem\Timer\glTimer.h"
#include "OGSystem\Input\Input.h"

/**
 *	@brief  �v���C���[�̍s�����t�@�C���Ƃ��ċL�^���܂�
 *	@author	Heewon Kim (nabicore@icloud.com)
 */
class Recorder {
private:

	enum KeyState {
		Idle,
		PRESS,
		RELEASE
	};
	typedef std::pair<Input::in, KeyState> WatchKey;

	explicit Recorder() {}
	virtual ~Recorder() {}
	bool Initialize(const std::string&);
	bool isKeyListenable() const;
	bool isAlreadyRecorded(const WatchKey&, const KeyState&) const;
	void printLog(const std::string&);
	void Recorde();
	void RecordeButton();

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

	/**
	 *	@brief	�s�����L�^���܂�
	 *	@param	�L�^����郁�b�Z�[�W
	 */
	void WriteRecord(const std::string&);

	/**
	 *	@brief	�L�[���͋L�^�������܂�
	 *	@param	OGge->in
	 */
	void ActivateKeyRecord(Input*);

	/**
	 *	@brief	�L�[���͂��L�^����L�[�����Ă����܂��B
	 *	@param	�L�[
	 */
	void AddKeyInputWatchList(const Input::in&);
	void operator>>(const Input::in&);

private:
	bool							isLogging = false;
	Time*							gameTimer;
	Input*							inputListener;
	std::string						fileName = "save.txt";
	std::ofstream					fileWriter;
	std::thread						recThread;
	std::queue<std::string>			inputQueue;
	std::vector<WatchKey>			watchKeys;
};