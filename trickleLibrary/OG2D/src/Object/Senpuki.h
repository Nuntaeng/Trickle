//______________________________//
//|�����M�~�b�N  ��@        |//
//|�����F2018/03/29 ����       |//
//|�����F2018/03/30 �����@     |//
//|�����F2018/03/31 ����       |//
//|�����F2018/04/01 ����       |//
//|____________________________|//

#pragma once
#include "Object\Object.h"
#include <vector>                                        //�X�e�[�W�ɂ���ĕω������@�̍��W���i�[���邽��
//��������//
///������������M�~�b�N��ǉ�����ꍇ�͂����ɋL�q����///
//��������//

#include "Water\water.h"                                 //���Ƃ̓����蔻��
#include "Switch.h"                                      //�X�C�b�`�Ƃ̓����蔻��ESwitch�̐؂�ւ��t���O

class Senpuki : public Object
{
public:
	/*
	�������W�ɂ���ē����蔻���`�̐����E�t���O�̏������E�����_���̓����蔻����s���܂��B
	�� ����   : Vec2 ���������W�l
	�� �߂�l : bool ������������������Ԃ��܂��B�i����true��������܂���j
	*/
	bool Initialize(Vec2);


	
	/*
	��@�̍X�V����
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	void UpDate();



	/*
	��@�̉������
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	void Finalize();



	/*
	��@�̕`�揈���iMap�ŕ\������̂ł��܂�Ӗ����Ȃ��j
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	void Render();                                       



	/*
	�R���X�g���N�^�@���������邱�Ƃ���܂���
    �� ����   : �Ȃ�
    �� �߂�l : �Ȃ�
	*/
	explicit Senpuki();  



	/*
	�R���X�g���N�^�iVec2�@�������W)
	�� ����   : Vec2 ��@�̏������W�ɐݒ肷����W�l
	�� �߂�l : �Ȃ�
	*/
	explicit Senpuki(Vec2 pos);



	/*
	�f�X�g���N�^�@Object*��delete�ō폜���܂��B
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	virtual ~Senpuki();



	/*
	Object* parent �̎w���Ă���ꏊ��nullptr�ł͂Ȃ�����bool�^�ŕԂ��܂��B
	�� ����   : �Ȃ�
	�� �߂�l : bool
	*/
	bool HasParent() const;                              
				
	
	/*
	Swtich* parent �ɓ����蔻��ɕK�v�ȃN���X�̃A�h���X�l�������܂��B
	�� ����   : Switch* �����蔻��ɕK�v�ȃN���X�̃A�h���X�l
	�� �߂�l : �Ȃ�
	*/
	void SetParent(Switch* obj);


	/*
	Object* parent �ɓ����蔻��ɕK�v�ȃN���X�̃A�h���X�l�������܂��B
	�� ����   : Object* �����蔻��ɕK�v�ȃN���X�̃A�h���X�l
	�� �߂�l : �Ȃ�
	*/
	void SetParent(Object* obj);


	/*
	�����蔻����܂Ƃ߂��֐��ł��B�i����������->�����_���̓����蔻��̏ꏊ�ō̗p�j
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	void CheakHit();


	/*
	�X�C�b�`�̐؂�ւ��t���O���������ꍇ�ɐ�@�̍��W��؂�ւ��܂��B
	�� ����   : const Vec2 �؂�ւ��ꏊ�̍��W�l
	�� �߂�l : Vec2
	*/
	Vec2 Switch_On_or_Off_pos(const Vec2);


	/*
	vector�ɍ��W�l��������֐��ł��B
	�� ����   : const Vec2 vector�ɃZ�b�g�ǉ������������蔻����W�l
	�� �߂�l : �Ȃ�
	*/
	void Set_Pos(const Vec2);


	/*
	�X�C�b�`�̐؂�ւ��t���O�ɂ���č��W�l�̍Đݒ�����܂��B
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	void Switch_Swap();

	/*
	�����C��ԂɂȂ����Ƃ��ɐ�@�ɂ���Ĉړ������܂��B
	�� ����   : Water& �����C��ԂɂȂ������̃A�h���X�l
	�� �߂�l : Vec2 �ړ�����ׂ��ړ���
	*/
	Vec2 Water_Move(Water& o_);

	/*
	const���O���֐�
	�� ����   : typename T& const���O�������N���X
	�� �߂�l : typaname T& const�Ȃ�
	*/
	template<typename T>
	T& const_off(T& obj);
private:
	bool Water_flag;                                     //�����蔻��i�[�ϐ�
	bool Switch_ON_OFF;                                  //OFF(false) ��̐�@�@ON(true)�@���̐�@
	CollisionBox range;                                  //����͈́i���݂͎g�p���Ă��܂���j
	Object* parent;                                      //nullptrCheak�֐�
	std::vector<Vec2> Pos;                               //�R���X�g���N�^�ő���ꂽ�������W�l��ۑ�����i�[�q��
	Switch* switch_pointa;                               //switch�̃A�h���X�l���i�[����ϐ�
};