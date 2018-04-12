#pragma once
//______________________________//
//|�����M�~�b�N ���X�@         |//
//|�����F2018/04/07 ����       |//
//|____________________________|//


#include "Object\Object.h"
#include <vector>

#include "Water\water.h"

class Seihyouki : public Object
{
public:
	/*
	�R���X�g���N�^
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	Seihyouki();


	/*
	�R���X�g���N�^
	�� ����   : Vec2 �������W�l
	�� �߂�l : �Ȃ�
	*/
	Seihyouki(Vec2);


	/*
	�f�X�g���N�^
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	virtual ~Seihyouki();


	/*
	�I�u�W�F�N�g�^�O�̐ݒ�@�I�u�W�F�N�g�̐����@
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	void Initialize();



//�ǉ��ϐ�//
public:
	Object hitBace;                      //�����蔻���`�̐���
private:
	std::vector<Vec2> Pos;               //���W�l���i�[����ϐ�
	int coldCount;                       //�X�ɂȂ�܂ł̎��Ԃ��i�[����
//�ǉ��֐�//
public:
	/*
	�����蔻��̏��������܂�
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	void CheakHit();

	/*
	vector�Ɉ����̍��W�l��ǉ����܂�
	�� ����   : Vec2 �i�[������W�l 
	�� �߂�l : �Ȃ�
	*/
	void Input_Pos(Vec2);
};