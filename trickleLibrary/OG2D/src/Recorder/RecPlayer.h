#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <functional>
#include "RecDef.h"
#include "OGSystem\Timer\glTimer.h"

/**
 *	@brief	Recorder�Ŏ�����f�[�^���Đ�����
 *	@author Heewon Kim (nabicore@icloud.com)
 */

class RecPlayer {
private:

	typedef RecDef::WatchKey KeyState;
	typedef std::pair<float, RecDef::WatchKey> KeyEventTimeline;
	typedef std::pair<In::AXIS, float> StickState;
	typedef std::pair<float, StickState> StickEventTimeline;

	explicit RecPlayer() {}
	virtual ~RecPlayer() {}
	inline void printLog(const std::string&);
	bool Initialize(const std::string&);
	bool isPlayable() const;
	bool isEventExist(const KeyState&);
	void Reset();
	std::vector<std::string> Split(const std::string&, const char&);

public:
	/**
	 *	@brief	�����֐�
	 *	@param	�t�@�C����
	 *	@param	�f�o�b�O���[�h�t���O�i��{�l�FOff�j
	 *	@return	�I�u�W�F�N�g
	 *	@return nullptr �I�u�W�F�N�g�������s�i�����p�X�w����j
	 */
	static RecPlayer* Create(const std::string&, const bool&);

	/**
	 *	@brief	�N���X����
	 */
	void Destroy();

	/**
	 *	@brief	�^�X�N��Update�ŌĂԂƓǂݍ��񂾃Z�[�u�f�[�^�̒ʂ蓮��
	 */
	void Play();

	/**
	 *	@brief	�L�[�������΂��s�����w�肵�܂�
	 *	@param	�L�[
	 *	@param	�L�[���������̂��������̂�
	 *	@param	���̃L�[���������Ƃ��s�����铮����L�q����void�^�֐�
	 */
	void AddKeyEvent(const Input::in&, const RecDef::KeyState& state, const std::function<void()>&);

	/**
	 *	@brief	�܂��v���C����L�^���c���Ă��邩
	 *	@return true �c���Ă���
	 */
	bool isEnded() const;

	/**
	 *	@brief	�܂��v���C����X�e�B�b�N�L�^���c���Ă��邩
	 *	@return	true �c���Ă���
	 */
	bool isAxisEnded() const;

	/**
	 *	@brief	���v���C�𔽕����邩��I��
	 *	@param	bool�l
	 */
	void SetRepeat(const bool&);

	/**
	 @brief		�Đ����P��I���Ɗ֐����Ă�
	 @param		�Ă΂��bool�^��Ԃ��֐��Atrue���Ă΂��O�܂ŌJ��Ԃ�
	 */
	void SetEndCallback(const std::function<bool()>&);

	/**
	 @return	�X�e�B�b�N�̌X��(�f�[�^���Ȃ��ꍇ�ɂ�0��Ԃ�)
	 */
	float GetCurrentStickTilt(const In::AXIS&);

	void SetPause();
	void SetPlay();

private:
	bool											isDbgMode = false;
	bool											isRepeat = false;
	bool											isPlaying = true;
	Time											timer;
	std::string										fileName;
	std::queue<KeyEventTimeline>					recData;
	std::queue<KeyEventTimeline>					backupData;
	std::queue<StickEventTimeline>					recStick;
	std::queue<StickEventTimeline>					backupStick;
	std::map<KeyState, std::function<void()>>		events;
	std::map<Input::in, RecDef::KeyState>			playerKeyState;
	std::function<bool()>							endCallback;
};