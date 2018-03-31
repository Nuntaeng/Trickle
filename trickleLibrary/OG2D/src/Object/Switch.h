//______________________________//
//|�����M�~�b�N  �X�C�b�`      |//
//|�����F2018/03/29 ����	   |//
//|�����F2018/03/31 �����@     |//
//|____________________________|//
#pragma once
#include "Object.h"
#include "Player\Player.h"
#include <vector>

class Player;

class Switch : public Object
{
public:
	explicit Switch();                           //�R���X�g���N�^�i�����Ȃ��j
	explicit Switch(Vec2);                       //�R���X�g���N�^�iVec2�@�������W�l�j
	virtual ~Switch();                           //�f�X�g���N�^�@���݂͓��ɂȂ�
	bool Initlaize(Vec2);                        //(����1 �������W)�����������@�����蔻��E��`�̐����E�t���O�̏�����
	void UpDate();                               //�X�V����
	void Finalize();                             //�������
	void Render();                               //�`�揈���i���̂Ƃ���Ӗ����Ȃ��j

	void CheakHit();                             //�����蔻��̏������������Ƃ���
	bool HasParent() const;                      //nullptr�łȂ������ׂ�֐�
	void SetParent(Player* obj);                 //�����o�ϐ� parent�Ɉ�����Player*�𓖂Ă�iPlayer* �������Object*)
private:
	bool Hitflag;                                //�����蔻��
	bool switch_ON_OFF;                          //�X�C�b�`��ON��OFF�������� ON(true) OFF(false)
	std::vector<Vec2>Pos;                        //�R���X�g���N�^���Ɉ����ł������W�l��ۑ�����
	Player* player_pointa;                       //Player�̃A�h���X�l���擾���ē����蔻��������ɕK�v
};