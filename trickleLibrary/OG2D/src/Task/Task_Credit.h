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
	void Next();
	bool LoadSize();

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
	int nowMode;


	Texture frameTex;
	Texture nameTex;

	struct IMAGE {
		Box2D draw;
		Box2D src;
		Texture tex;
		float angle;
	};
	IMAGE name[7];
	IMAGE frame[2];

	int timeCnt;
	int WAITTIME;
	float alpha;

	bool CheckTime(int);
};
