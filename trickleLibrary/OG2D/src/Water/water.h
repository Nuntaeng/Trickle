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
/**
*��ԑJ�ڂ���I�u�W�F�N�g�Ǘ�class
*/
class Water : public GameObject,public TaskObject {

public:
	/**
	*enum State
	* ��Ԃ̒l
	*/
	enum class State : int {
		LIQUID = 0,			//�@�t��
		SOLID,				//�@��
		GAS					//�@�C��
	};
	/**
	*enum Situation
	* ������
	*/
	enum class Situation : int
	{
		Newfrom,			//�o����
		Normal,				//�ʏ�
		Deleteform,			//�폜��
		CreaDelete,			//�폜
		Rainfrom			//�J���
	};
private:
	//! �����ő呬�x
	const float maxFall;
	//! �d�͉����x
	const float gravity;
	//! ���C
	float finSpeed;
	//! �J��������
	const unsigned __int8 rainTime;
	//! �摜���
	Texture* tex;
	//! ���݂̏��
	State currentState;
	//! �O�̏��
	State preState;
	//! ���݂̏��
	Situation nowSituation;
	//! �Œ�T�C�Y
	Vec2 minSize;
	//! �ő�T�C�Y
	Vec2 maxSize;
	//! �ړ��l
	Vec2 move;
	//! 1�t���[���ł̈ړ��l
	Vec2 nowMove;
	//! �����̓����蔻��
	GameObject* left;
	//! �E���̓����蔻��
	GameObject* right;
	//! �����̐F���
	Paint::PaintColor color;
	//! ��Ԃ̕ω��^�C��
	int setTime;
	//! �����̏������
	bool hold;
	//! ��ID
	unsigned int id;
	//! �T�E���h�̃t�@�C�����i�[
	std::string soundname; 
	//! �`��p�J���[�l
	Color color_a;
	//! ���ɓ������Ă���^�C��
	unsigned int fireCnt;
	//! �X�ɓ������Ă���^�C��
	unsigned int iceCnt;
	//! �X�}�[�g�|�C���^
	typedef std::shared_ptr<Water> SP;
public:
	//! ����
	float volume;
	//! ���G����
	int invi;
	//! �J�E���g����
	int nowTime;
	//! �T�E���h�̐���
	bool soundplay;
	Sound sound;
	VolumeControl volControl;
private:
	/**
	*@brief	:����������
	*@return:Situation ���̏��
	*/
	Situation UpNewform();
	/**
	*@brief	:�폜������
	*@return:Situation ���̏��
	*/
	Situation UpDeleteform();
	/**
	*@brief	:�X�V����
	*@return:Situation ���̏��
	*/
	Situation UpNormal();
	/**
	*@brief	:�d�͏���
	*/
	void Friction();
	/**
	*@brief	:��������
	*@param	:string name ������s�������I�u�W�F�N�g��
	*@param	:int id ����̓����蔻��ID
	*@return:bool �������Ă����true
	*/
	bool FootCheck(const std::string& name, const int id = 0);
	/**
	*@brief	:���㏈��
	*@param	:string name ������s�������I�u�W�F�N�g��
	*@param	:int id ����̓����蔻��ID
	*@return:bool �������Ă����true
	*/
	bool HeadCheck(const std::string& name, const int id = 0);
	/**
	*@brief	:�����X���菈��
	*@return:bool �������Ă����true
	*/
	bool FootSolidCheck();
	/**
	*@brief	:����X���菈��
	*@return:bool �������Ă����true
	*/
	bool HeadSolidCheck();
	/**
	*@brief	:���̈ړ�����
	*@param	:Vec2 move �ړ��l
	*/
	void MoveWATERCheck(Vec2& move);
	/**
	*@brief	:�_�̈ړ�����
	*@param	:Vec2 move �ړ��l
	*/
	void MoveGASCheck(Vec2& move);
	/**
	*@brief	:�X�̈ړ�����
	*@param	:Vec2 move �ړ��l
	*/
	void MoveSOILDCheck(Vec2& move);
	/**
	*@brief	:��Ԋm�F
	*/
	void CheckState();
	/**
	*@brief	:�X�̉����o������
	*@return:bool �����o�����s�����ꍇtrue
	*/
	bool SolidExtrusion();
	/**
	*@brief	:����������
	*@return:bool ����true
	*/
	bool Initialize();
	/**
	*@brief	:�X�V����
	*/
	void UpDate() override;
	/**
	*@brief	:�`�揈��
	*/
	void Render2D() override;
	/**
	*@brief	:�������
	*@return:bool ����true
	*/
	bool Finalize();
	/**
	*@brief	:constructor
	*@param	:Vec2 pos �����ʒu
	*/
	explicit Water(const Vec2& pos);
public:
	/**
	*@brief	:destructor
	*/
	virtual ~Water();
	/**
	*@brief	:�摜��o�^����
	*@param	:Texture* texture �摜�f�[�^�̃|�C���^
	*/
	void SetTexture(Texture* texture);
	/**
	 * @brief	��ԓ]�ڂ��܂��B
	 * @see	�O�Ŏg���Ƃ��ɂ�Water::State::Liquid ����Ȍ`��
	 */
	void SetState(const State&);
	/**
	*@brief	:���݂̏�Ԃ�Ԃ�
	*@return:State ���ݏ��
	*/
	State GetState() const;
	/**
	*@brief	:�I�u�W�F�N�g�̈ړ�����
	*@param	:Vec2 move �ړ��l
	*/
	void MovePos(const Vec2& move);
	/**
	*@brief	:�I�u�W�F�N�g��X�ړ��l
	*@param	:float move �ړ��l
	*/
	void MovePos_x(const float move);
	/**
	*@brief	:�ړ��l�̎擾
	*@return:Vec2 �ړ��l
	*/
	Vec2 GetMove() const;
	/**
	*@brief	:��Ԃ��X�V����
	*@param	:Situation s ���
	*/
	void SetSituation(const Situation& s);
	/**
	*@brief	:��Ԃ��擾����
	*@return:Situation ���ݏ��
	*/
	Situation GetSituation() const;
	/**
	*@brief	:�����o���ꂽ�ړ�����
	*@param	:Vec2 move �ړ���
	*@return:Vec2 �ړ��ł��Ȃ������l
	*/
	Vec2 MoveSolid(const Vec2& move);
	/**
	*@brief	:���ʂ��ړ�����
	*@return:float ����
	*/
	float waterMove();
	/**
	*@brief	:���ʂ��O������㏑������
	*@param	:float value ����
	*/
	void SetWaterVolume(const float value);
	/**
	*@brief	:���ʂ��擾
	*@return:float ����
	*/
	float GetWaterVolume() const;
	/**
	*@brief	:�o�P�c�Ƃ̔�����s�����ǂ���
	*@return:bool �s���ꍇtrue
	*/
	bool IsBucket();
	/**
	*@brief	:�F�̐ݒ�
	*@param :Paint::PaintColor color �F���
	*@return:bool ������true
	*/
	bool SetColor(const Paint::PaintColor& color);
	/**
	*@brief	:�F�̎擾
	*@return:Paint::PaintColor �F���
	*/
	Paint::PaintColor GetColor() const;
	/**
	*@brief	:�^�X�N����
	*@param	:Vec2 pos �ʒu���
	*@return:Water �����Ɏ��s������nullptr
	*/
	static SP Create(const Vec2& pos);
	/**
	*@brief	:�ő�T�C�Y��o�^
	*@param	:Vec2 maxSize �T�C�Y
	*/
	void SetMaxSize(const Vec2& maxSize);
	/**
	*@brief	:���g��������Ă��邩�Ԃ�
	*@return:bool �������
	*/
	bool GetHold() const;
	/**
	*@brief :������Ԃ��w�肷��
	*@param :bool flag �������
	*/
	void HoldCheck(const bool flag);
	/**
	*@brief	:�ړ��l�����Z�b�g����
	*/
	void ResetMove();
	/**
	*@brief	:���g���n�������̏���
	*/
	void SolidMelt();
	/**
	*@brief	:���g�̃T�C�Y�̕ύX���s��
	*@param :Vec2 scale �T�C�Y
	*/
	void SetScale(const Vec2& scale);
	/**
	*@brief	:��ID��Ԃ�
	*@return:unsigned int ��ID
	*/
	unsigned int GetID() const;
	/**
	*@brief	:���J�E���g��ݒ肷��
	*@param	:unsigned int cnt �J�E���g
	*/
	void SetFireCnt(const unsigned int& cnt);
	/**
	*@brief	:���J�E���g��Ԃ�
	*@return:unsigned int ���݃J�E���g
	*/
	unsigned int GetFireCnt() const;
	/**
	*@brief	:�X�J�E���g��ݒ肷��
	*@param	:unsigned int cnt �J�E���g
	*/
	void SetIceCnt(const unsigned int& cnt);
	/**
	*@brief	:�X�J�E���g��Ԃ�
	*@return:unsigned int ���݃J�E���g
	*/
	unsigned int GetIceCnt() const;
};