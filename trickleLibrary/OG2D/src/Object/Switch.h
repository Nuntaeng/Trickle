//______________________________//
//|�����M�~�b�N  �X�C�b�`      |//
//|�����F2018/03/29 ����	   |//
//|�����F2018/03/31 �����@     |//
//|�����F2018/04/01 ����       |//
//|____________________________|//
#pragma once
#include "Object.h"
#include "Player\Player.h"
#include <vector>

class Player;

class Switch : public Object
{
public:
	/*
	�R���X�g���N�^�@�����݂͉�������������܂���
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	explicit Switch();


	/*
	�R���X�g���N�^�iVec2�@�������W�l�j
	�� ����   : Vec2 �X�C�b�`�̏������W�l�ݒ�
	�� �߂�l : �Ȃ�
	*/
	explicit Switch(Vec2);


	/*
	�f�X�g���N�^�@Player*��delete�ō폜���܂��B
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	virtual ~Switch();
	
	
	/*
	(����1 �������W)�����������@�����蔻��E��`�̐����E�t���O�̏�����
	�� ����   : Vec2 ���������W�l
	�� �߂�l : bool ������������������Ԃ��܂��B�i����true��������܂���j
	*/
	bool Initlaize(Vec2);
	

	/*
	�X�V����
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	void UpDate();
	

	/*
	�������
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	void Finalize();


	/*
	�`�揈���i���̂Ƃ���Ӗ����Ȃ��j
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	void Render();


	/*
	�����蔻��̏������������Ƃ���
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/

	void CheakHit();


	/*
	nullptr�łȂ������ׂ�֐�
	�� ����   : �Ȃ�
	�� �߂�l : bool
	*/
	bool HasParent() const;


	/*
	�����o�ϐ� parent�Ɉ�����Player*�𓖂Ă�iPlayer* �������Object*)
	�� ����   : Player* Player�̃N���X�̃A�h���X�l
	�� �߂�l : �Ȃ�
	*/
	void SetParent(Player* obj);
private:
	bool Hitflag;                                //�����蔻��
	bool switch_ON_OFF;                          //�X�C�b�`��ON��OFF�������� ON(true) OFF(false)
	std::vector<Vec2>Pos;                        //�R���X�g���N�^���Ɉ����ł������W�l��ۑ�����
	Player* player_pointa;                       //Player�̃A�h���X�l���擾���ē����蔻��������ɕK�v
};