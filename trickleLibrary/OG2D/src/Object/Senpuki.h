//______________________________//
//|�����M�~�b�N  ��@        |//
//|�����F2018/03/29 ����       |//
//|�����F2018/03/30 �����@     |//
//|�����F2018/03/31 ����       |//
//|�����F2018/04/01 ����       |//
//|����: 2018/04/02 ����       |//
//|����: 2018/04/03 ����       |//
//|�����F2018/04/06 ����       |//
//|�����F2018/04/07 ����       |//
//|____________________________|//

#pragma once
#include "Object\Object.h"
#include <vector>                                        //�X�e�[�W�ɂ���ĕω������@�̍��W���i�[���邽��
//��������//
///������������M�~�b�N��ǉ�����ꍇ�͂����ɋL�q����///
//��������//

#include "Water\water.h"                                 //���Ƃ̓����蔻��
#include "Switch.h"                                      //�X�C�b�`�Ƃ̓����蔻��ESwitch�̐؂�ւ��t���O
#include "Map\Map.h"                                     //Map�Ƃ̔���

class Map;
class Switch;

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
	explicit Senpuki(Vec2);



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
	Swtich* �����蔻��ɕK�v�ȃN���X�̃A�h���X�l�������܂��B
	�� ����   : Switch* �����蔻��ɕK�v�ȃN���X�̃A�h���X�l  int �X�C�b�`�̔z��v�f�l
	�� �߂�l : �Ȃ�
	*/
	void SetParent(Switch*,int);


	/*
	Object* �����蔻��ɕK�v�ȃN���X�̃A�h���X�l�������܂��B
	�� ����   : Object* �����蔻��ɕK�v�ȃN���X�̃A�h���X�l
	�� �߂�l : �Ȃ�
	*/
	void SetParent(Object*);


	/*
	Map* �����蔻��ɕK�v�ȃN���X�̃A�h���X�l�������܂��B
	�� ����   : Map* �����蔻��ɕK�v�ȃN���X�̃A�h���X�l 
	�� �߂�l : �Ȃ�
	*/
	void SetParent(Map*);


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
	�� ����   : Switch& S�L�[�i�؂�ւ��{�^���j�������ꂽ�瑦���ɂ���Switch�̐؂�ւ��t���O�����Đ�@�̉ғ�����I�u�W�F�N�g��ύX���܂��B
	�� �߂�l : �Ȃ�
	*/
	void Switch_Swap(Switch&);

	/*
	�����C��ԂɂȂ����Ƃ��ɐ�@�ɂ���Ĉړ������܂��B
	�� ����   : Object& �����C��ԂɂȂ������̃A�h���X�l
	�� �߂�l : Vec2 �ړ�����ׂ��ړ���
	*/
	Vec2 Water_Move(Object&);

	/*
	���Ƃ̓����蔻����`���b�N���܂�
	�� ����   : const Object& ���̃A�h���X�l
	�� �߂�l : bool ����͈͂Ɠ������Ă��邩��Ԃ�
	*/
	bool Cheak_Water(const Object&);

private:
	bool Water_flag;                                     //�����蔻��i�[�ϐ�
	bool Switch_ON_OFF;                                  //OFF(false) ��̐�@�@ON(true)�@���̐�@
	bool Wall_flag;                                      //�ǂƂ̓����蔻��t���O�i�[����ϐ�
	bool Range_Flag;                                     //����͈͂Ƃ̓����蔻����i�[����
	Map* parent_Wall;                                    //nullptrCheak�֐�(����͕�)
	std::vector<Vec2> Pos;                               //�R���X�g���N�^�ő���ꂽ�������W�l��ۑ�����i�[�q��
	Switch* switch_pointa[2];                            //switch�̃A�h���X�l���i�[����ϐ�
public:
	Object range;                                        //����͈́i���݂͎g�p���Ă��܂���j
};