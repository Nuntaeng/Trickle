/**
* @file Fan.h
* @brief ��@�N���X���`����
* @author yokota0717
* @date 2018.10.11
*/

#pragma once

#include "GimmickBase.h"
#include "VolumeControl\volumeControl.h"
#include "Effect\Effect.h"

/**
* @brief ��@�N���X
* @details �����C��Ԃ̐����������Ɉړ�������
*/
class Fan : GimmickBase {
	Texture* image;
	Texture* windimage;      //���̉摜
	Texture* windimage2;     //���̉摜2
	Texture* windimage3;      //���̉摜
	Texture* windimage4;      //���̉摜
	Texture* windimage5;      //���̉摜

	const Box2D Src = { 0,0,768 / 3,256 };
	float range;
	float movePos;
	int strength;
	float endpos;
	std::string soundname;      //�T�E���h�̃t�@�C�����i�[
	std::string taskName;		//�����p

	struct Animetion
	{
		int animetionframe;
		int speed;
		void AnimetionMove(bool flag);				//�A�j���[�V�����t���[���𓮂���
		void AnimetionReset();						//�A�j���[�V�����̐��l�����Z�b�g����
		void AnimetionSrc(Box2D& src, bool flag);	//�A�j���[�V�����t���[����`��ɉe��������
	};
	Animetion animetion;

	virtual bool Initialize(Vec2 pos, Vec2 range, Dir dir, bool active) override;
public:
	Fan(Vec2 pos, Vec2 range, Dir dir, bool active);
	~Fan();

	//�T�E���h����̏��
	bool startflag;
	Sound sound;
	VolumeControl volControl;
	//�G�t�F�N�g����̏��
	int effectCnt;
	int effectnum;       //�G�t�F�N�g�̉摜�������_���Ō���
	//! �G�t�F�N�g�̒�����ݒ肷��(����������Ƃǂ��ɂ�������)
	void setEffectDist(float dist);

	void UpDate() override;			//�X�V����
	void Render2D() override;		//�`�揈��
	bool Finalize();				//�������

	virtual void affectWater() override;
};
