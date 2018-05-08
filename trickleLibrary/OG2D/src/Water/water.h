#ifndef __WATER_H__
#define __WATER_H__


/**
 * @brief	���֘A�����ł�
 * @date	2018-03-24
 * @author	Heewon Kim
 */

#include <map>
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include <algorithm>

class Water : public Object {

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
	void Update();
	void Render();
	void Finalize();

	void SetTexture(Texture* texture);

	/**
	 * @brief	��ԓ]�ڂ��܂��B
	 * @see	�O�Ŏg���Ƃ��ɂ�Water::State::Liquid ����Ȍ`��
	 */
	void SetState(const State&);
	State GetState() const;

	void SetSituation(const Situation&);
	Situation GetSituation() const;

	//���ʂ̈ړ�
	float waterMove();
	//���ʂ̃`�F�b�N
	float GetWaterVolume() const;
	void AddObject(Object* obj_);								//�I�u�W�F�N�g��o�^����
	bool DeleteObject(Object* obj_);							//�w��I�u�W�F�N�g��o�^����폜����
	void AllDelete();											//�S�o�^�I�u�W�F�N�g�̍폜
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
private:
	const float MOVE_SPEED = 15.f;								//�ړ��X�s�[�h
	const float JUMP_POWER = -20.f;								//�W�����v�p���[
	const float MAX_FALL = 30.f;								//�����ő呬�x
	const float GRAVITY = (9.8f / 60.f / 60.f * 32) * 50;		//�d�͉����x
	const float FIN_SPEED = 0.5f;								//���C
	const int RAIN_TIME = 180;
	Texture* tex;
	std::vector<Object*> mapObj;
	std::map<State, Box2D> drawRange;
	State currentState;
	Situation nowSituation;
	Vec2 minSize;
	Vec2 maxSize;
	Vec2 move;
	Color color;
	int setTime;
	Situation UpNewform();
	Situation UpDeleteform();
	Situation UpNormal();
	void SetMapObject(Object* mapobj);
	std::vector<Object*> objects;
	void Friction();
	bool FootCheck(std::string&,int = 0);
	void MoveWATERCheck(Vec2&);
	void MoveGASCheck(Vec2&);
	void MoveSOILDCheck(Vec2&);
	bool HeadCheck(std::string&,int = 0);
};
#endif