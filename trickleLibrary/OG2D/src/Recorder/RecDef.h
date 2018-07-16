#pragma once
#include <iostream>
#include "OGSystem\Input\Input.h"

/**
 *	@brief	�Z�[�u�t�@�C���֘A�f�[�^�^�C�v��`
 *	@author	Heewon Kim (nabicore@icloud.com)
 */

namespace RecDef {
	enum KeyState {
		Idle,
		PRESS,
		RELEASE
	};
	typedef std::pair<Input::in, KeyState> WatchKey;
	typedef std::pair<In::AXIS, KeyState> WatchStick;
}