#pragma once


/**
 * @brief	���֘A�����ł�
 * @date	2018-03-24
 * @author	Heewon Kim
 */

#include <map>
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include <algorithm>

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
	bool SetColor(Color&);
	Color GetColor() const;
	bool active;
	//����
	float volume;
	//���G����
	int invi;
	//�J�E���g����
	int nowTime;
	typedef std::shared_ptr<Water> SP;
	static SP Create(Vec2&, bool = true);

	void SetMaxSize(Vec2&);
	//�T�E���h�̐���
	Sound sound;
	bool soundplay;

	
	bool GetHold() const;
	void HoldCheck(bool);
	void ResetMove();
	bool SolidMelt();

private:
	const float MOVE_SPEED = 15.f;								//�ړ��X�s�[�h
	const float JUMP_POWER = -20.f;								//�W�����v�p���[
	const float MAX_FALL = 15.f;								//�����ő呬�x
	const float GRAVITY = (9.8f / 60.f / 60.f * 32) * 5;		//�d�͉����x
	const float FIN_SPEED = 5.0f;								//���C
	const int RAIN_TIME = 180;
	Texture* tex;
	State currentState;
	State preState;
	Situation nowSituation;
	Vec2 minSize;
	Vec2 maxSize;
	Vec2 move;
	Color color;
	int setTime;
	bool hold;
	Situation UpNewform();
	Situation UpDeleteform();
	Situation UpNormal();
	unsigned int id;
	void Friction();
	bool FootCheck(std::string&,int = 0);
	bool FootSolidCheck();
	bool HeadSolidCheck();
	void MoveWATERCheck(Vec2);
	void MoveGASCheck(Vec2);
	void MoveSOILDCheck(Vec2);
	bool HeadCheck(std::string&,int = 0);
	void CheckState();
	
	std::string soundname;      //�T�E���h�̃t�@�C�����i�[
};