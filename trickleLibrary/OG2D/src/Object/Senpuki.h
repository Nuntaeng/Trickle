//______________________________//
//|�����M�~�b�N  ��@        |//
//|�����F2018/03/29 ����       |//
//|�����F2018/03/30 �����@     |//
//|�����F2018/03/31 ����       |//
//|____________________________|//

#pragma once
#include "Object\Object.h"

//��������//
//������������M�~�b�N��ǉ�����ꍇ�͂����ɋL�q����//
//��������//

#include "Water\water.h"                                 //���Ƃ̓����蔻��

class Senpuki : public Object
{
public:
	bool Initialize(Vec2);                               //������������Ƃ���(Vec2 �������W)
	void UpDate();                                       //��@�̍X�V����
	void Finalize();                                     //��@�̉������
	void Render();                                       //��@�̕`�揈���iMap�ŕ\������̂ł��܂�Ӗ����Ȃ��j
	explicit Senpuki();                                  //�R���X�g���N�^�i�����@�Ȃ��j
	explicit Senpuki(Vec2 pos);                          //�R���X�g���N�^�iVec2�@�������W)
	virtual ~Senpuki();                                  //�f�X�g���N�^�@�������邱�ƂȂ�
	bool HasParent() const;                              //nullptr�łȂ������ׂ�֐�
	void SetParent(Object* obj);                         //�����o�ϐ� parent�Ɉ�����Object*�𓖂Ă�iObject* �������Object*)
	void CheakHit();                                     //�����蔻��̏������܂Ƃ߂��֐��i���݂�Player�j���ۂ͐��ŏ��������܂��B
private:
	bool flag;                                           //�����蔻��i�[�ϐ�
	CollisionBox range;                                  //����͈́i���݂͎g�p���Ă��܂���j
	Object* parent;                                      //nullptrCheak�֐�
};