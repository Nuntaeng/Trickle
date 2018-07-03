#pragma once
#include "OGSystem/OGSystem.h"

class Credit : public TaskObject
{
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

private:
	enum Mode {
		Non,
		Mode1,
	};
	Mode nowMode;


	Texture backTex;
	Texture frameTex;
	Texture nameTex;

	struct creditUI {
		Vec2 pos;
		float alpha;
	};
	creditUI frame;

	int cnt;

};
