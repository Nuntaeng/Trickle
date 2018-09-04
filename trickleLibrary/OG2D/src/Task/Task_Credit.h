#pragma once
#include "OGSystem/OGSystem.h"

class Credit : public TaskObject
{
	class Animation
	{
		Easing easing_x;
		Easing easing_y;
		Vec2 StartPos;
		Vec2 EndPos;
	public:
		Vec2 Move();
		Vec2 Move(const float time);
		Vec2 Move(const Easing::Name = Easing::Name::Linear, const Easing::Mode = Easing::Mode::InOut, const float = 10.f);
		Animation();
		void Set(Vec2&, Vec2&);
		bool isPlay() const;
	};
	Animation camera_anim;

public:
	std::string taskName;
	//�V�F�A�|�C���^�錾
	typedef std::shared_ptr<Credit> SP;
	static Credit::SP Create(bool flag = true);
	//�R���X�g���N�^
	Credit();
	//�f�X�g���N�^
	virtual ~Credit();
	//��������
	bool Initialize();
	//�X�V����
	void UpDate();
	//�`�揈��
	void Render2D();
	void Finalize(); 

	void Next();		//���̃��[�h�Ɉڂ�
	bool LoadSize();	//�e�L�X�g�t�@�C���ɏ����Ă���T�C�Y��ǂݍ���
	void SetSize();		//�ǂݍ��񂾃T�C�Y���w�肷��
	void CreditJump(int start, int time);	//
	bool CheckTime(int);					//

private:
	const int NON = 0;
	const int MODE1 = 1;
	const int MODE2 = 2;
	const int MODE3 = 3;
	const int MODE4 = 4;
	const int MODE5 = 5;
	const int MODE6 = 6;
	const int MODE7 = 7;
	const int MODE8 = 8;
	const int MODE9 = 9;
	int nowMode;


	Texture LadderTex;

	struct IMAGE {
		const int DRAW_X = 0;
		const int DRAW_Y = 1;
		const int DRAW_W = 2;
		const int DRAW_H = 3;
		int imageSize[4];

		Box2D draw;
		Box2D src;
		Texture tex;
	};

	int FRAME_NUM = 8;
	IMAGE frame[9];

	int timeCnt;
	int jumpTimeCnt;
	int WAITTIME;

	//�G�t�F�N�g�̃J�E���g
	int effCounter;
	//�Ԃт�̃G�t�F�N�g
	Texture petalTex1;
	Texture petalTex2;
	Texture petalTex3;
	Texture petalTex4;
	Texture petalTex5;
};