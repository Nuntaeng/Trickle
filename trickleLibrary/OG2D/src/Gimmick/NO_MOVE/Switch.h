//______________________________//
//|�����M�~�b�N  �X�C�b�`      |//
//|�����F2018/03/29 ����	   |//
//|�����F2018/03/31 �����@     |//
//|�����F2018/04/01 ����       |//
//|����: 2018/04/02 ����       |//
//|����: 2018/04/03 ����       |//
//|�����F2018/04/07 ����       |//
//|____________________________|//
#pragma once
#include "Object\Object.h"
#include "Player\Player.h"
#include "Senpuki.h"
#include <vector>

//class Player;
//class Senpuki;
//
//class Switch : public Object
//{
//public:
//	/*
//	�R���X�g���N�^�@�����݂͉�������������܂���
//	�� ����   : �Ȃ�
//	�� �߂�l : �Ȃ�
//	*/
//	explicit Switch();
//
//
//	/*
//	�R���X�g���N�^�iVec2�@�������W�l�j
//	�� ����   : Vec2 �X�C�b�`�̏������W�l�ݒ�
//	�� �߂�l : �Ȃ�
//	*/
//	explicit Switch(Vec2);
//
//
//	/*
//	�f�X�g���N�^�@�Ȃ�
//	�� ����   : �Ȃ�
//	�� �߂�l : �Ȃ�
//	*/
//	virtual ~Switch();
//
//
//	/*
//	(����1 �������W)�����������@�����蔻��E��`�̐����E�t���O�̏�����
//	�� ����   : �Ȃ�
//	�� �߂�l : �Ȃ�
//	*/
//	void Initlaize();
//
//
//	/*
//	�X�V����
//	�� ����   : �Ȃ�
//	�� �߂�l : �Ȃ�
//	*/
//	void UpDate();
//
//
//	/*
//	�������
//	�� ����   : �Ȃ�
//	�� �߂�l : �Ȃ�
//	*/
//	void Finalize();
//
//
//	/*
//	�`�揈���i���̂Ƃ���Ӗ����Ȃ��j
//	�� ����   : �Ȃ�
//	�� �߂�l : �Ȃ�
//	*/
//	void Render();
//
//
//	/*
//	�����蔻��̏������������Ƃ���
//	�� ����   : �Ȃ�
//	�� �߂�l : �Ȃ�
//	*/
//
//	void CheakHit();
//
//
//	/*
//	�X�C�b�`�̓����蔻����W�l��vector�ŕۑ�����֐�
//	�� ����   : const Vec2 �����蔻��ɕK�v�ȍ��W�l
//	�� �߂�l : �Ȃ�
//	*/
//	void Set_Pos(const Vec2);
//
//public:
//
//	bool switch_ON_OFF[2];                       //�X�C�b�`��ON��OFF�������� ON(true) OFF(false)
//	Object hitBace[2];                           //�X�C�b�`�̓����蔻���`
//private:
//
//	bool Hitflag;                                //�����蔻��
//	std::vector<Vec2>Pos;                        //�R���X�g���N�^���Ɉ����ł������W�l��ۑ�����
//};


//���c����

//���ӁI�I�I�I
//�v���C������ȏ�̃X�C�b�`�ɓ����ɐڐG����ƃG���[�f���܂�
//�K���X�C�b�`�𕡐��u���Ƃ��͂P�}�X�ȏ㗣���Ĕz�u
class Switch :public Object {
public:	
	void Initialize(Vec2 pos);
	void Update();
	void Finalize();
	void Render();
	bool isON();
	void ON_OFF();
	void SetTarget(Object* t);
private:
	std::vector<Object*> targets;
	Texture image;
	std::string path;
	bool is_on;

};