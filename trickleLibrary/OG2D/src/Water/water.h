#pragma once


/**
 * @brief	���֘A�����ł�
 * @date	2018-03-24
 * @author	Heewon Kim
 */

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include <algorithm>
#include "VolumeControl\volumeControl.h"
#include "Paint\Paint.h"

class Water : public GameObject,public TaskObject {

public:
	enum class State : int {
		LIQUID = 0,			//�@�t��
		SOLID,				//�@��
		GAS					//�@�C��
	};
	
	enum class Situation : int
	{
		Newfrom,			//�o����
		Normal,				//�ʏ�
		Deleteform,			//�폜��
		CreaDelete,			//�폜
		Rainfrom			//�J���
	};
private:
	const float MAX_FALL;								//�����ő呬�x
	const float GRAVITY;		//�d�͉����x
	float FIN_SPEED;								//���C
	const unsigned __int8 RAIN_TIME;
	Texture* tex;
	State currentState;
	State preState;
	Situation nowSituation;
	Vec2 minSize;
	Vec2 maxSize;
	Vec2 move;
	Vec2 nowMove;
	Paint::PaintColor color;
	int setTime;
	bool hold;
	unsigned int id;
	std::string soundname;      //�T�E���h�̃t�@�C�����i�[
	Color color_a;
public:
	bool active;
	//����
	float volume;
	//���G����
	int invi;
	//�J�E���g����
	int nowTime;
	//�T�E���h�̐���
	bool soundplay;
	Sound sound;
	VolumeControl volControl;
private:
	Situation UpNewform();
	Situation UpDeleteform();
	Situation UpNormal();
	void Friction();
	bool FootCheck(std::string&, int = 0);
	bool FootSolidCheck();
	bool HeadSolidCheck();
	void MoveWATERCheck(Vec2&);
	void MoveGASCheck(Vec2&);
	void MoveSOILDCheck(Vec2&);
	bool HeadCheck(std::string&, int = 0);
	void CheckState();
public:
	explicit Water(Vec2 pos);
	virtual ~Water();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();
	void SetTexture(Texture* texture);
	/**
	 * @brief	��ԓ]�ڂ��܂��B
	 * @see	�O�Ŏg���Ƃ��ɂ�Water::State::Liquid ����Ȍ`��
	 */
	void SetState(const State&);
	State GetState() const;
	void MovePos(Vec2&);
	void MovePos_x(float);
	Vec2 GetMove() const;
	void SetSituation(const Situation&);
	Situation GetSituation() const;
	Vec2 MoveSolid(const Vec2&);									//�X�������o������(������)
	//���ʂ̈ړ�
	float waterMove();
	//���ʂ��O������㏑������
	void SetWaterVolume(float);
	//���ʂ̃`�F�b�N
	float GetWaterVolume() const;
	bool IsBucket();
	//�F�֘A
	bool SetColor(const Paint::PaintColor&);
	Paint::PaintColor GetColor() const;
	typedef std::shared_ptr<Water> SP;
	static SP Create(Vec2&, bool = true);
	void SetMaxSize(Vec2&);
	bool GetHold() const;
	void HoldCheck(bool);
	void ResetMove();
	bool SolidMelt();
};