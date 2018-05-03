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
#include "Senpuki.h"


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
	//�I�u�W�F�N�g�Ȃ̂ŃI�u�W�F�N�g���p�����Ă������̓X�C�b�`���؂�ւ���
	std::vector<Object*> targets;
	Texture image;
	std::string path;
	bool is_on;

};