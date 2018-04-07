//______________________________//
//|�����M�~�b�N  ���M�@        |//
//|�����F2018/03/27 ����	   |//
//|�����F2018/04/07 ����       |//
//|____________________________|//
#pragma once
#include "Object.h"
#include "Water\water.h"
#include <vector>

class Kanetuki : public Object
{
public:
	/*
	�R���X�g���N�^���Ăяo��
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	explicit Kanetuki();


	/*
	�R���X�g���N�^���Ăяo��
	�� ����   : Vec2 �������W�l
	�� �߂�l : �Ȃ�
	*/
	explicit Kanetuki(Vec2);

	/*
	�f�X�g���N�^
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	~Kanetuki();


	/*
	�����蔻���`�̐�����t���O�̏����������܂��B�����_���̓����蔻����Ăяo���܂��B
	�� ����   :
	�� �߂�l :
	*/
	void Initialize();


	/*
	����͂�邱�Ƃ��Ȃ��@������
	�� ����   :
	�� �߂�l :
	*/
	void UpDate();


	/*
	��邱�ƂȂ�
	�� ����   :
	�� �߂�l :
	*/
	void Finalize();

//�ǉ��ϐ�
public:
	Object hitBace[2];                    //�����蔻���`�𐶐�����
private:
	bool hitflag[2];                      //�����蔻����i�[����
	std::vector<Vec2>Pos;                 //�����Ŗ���Ă������W�f�[�^��ۑ�����
	int HotCount[2];                      //�����C�ɂȂ�܂ł̎��Ԋi�[
//�ǉ��֐�
public:
	/*
	Vector�ɍ��W��ۑ����܂��B
	�� ����   : Vec2 �ۑ����������W�l
	�� �߂�l : �Ȃ�
	*/
	void Input_Pos(Vec2);

private:
	/*
	�����̂������琅���C�ɕύX���܂��B
	�� ����   : �Ȃ�
	�� �߂�l : �Ȃ�
	*/
	void CheakHit();
};