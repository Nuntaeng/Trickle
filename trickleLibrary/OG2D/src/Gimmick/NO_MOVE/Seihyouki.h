#pragma once
//�K�v�ǂݍ��݃t�@�C��
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Seihyouki : public GameObject, public TaskObject
{
	//-------------------------------------------
	//�e���Ő��삷��Ƃ��Ɏg�p������̂͂����ɋL�q����
	//-------------------------------------------
public:
	void HitGeneration(Vec2&, Vec2&);		//���W�l�@�����蔻��T�C�Y
	
	void toIce();							//�X�ɂ���
private:
	Texture sampleImage;
	GameObject hitBace;
	//------------------
	//�Œ艻����Ă��鏈��
	//------------------
public:
	std::string taskName;
	virtual ~Seihyouki();
	typedef std::shared_ptr<Seihyouki> SP;
	static Seihyouki::SP Create(Vec2& pos, Vec2& scale,bool = true);
	Seihyouki();
	//-------------
	//�ύX���Ȃ�����
	//-------------
	bool Initialize(Vec2&,Vec2&);		//����������
	void UpDate();			//�X�V����
	void Render2D();		//�`�揈��
	bool Finalize();		//�������

private:
	int movetime;					//�X�ɂ���܂ł̊i�[����t���[����
	const int movetime_ice = 20;	//�X�ɂ���܂ŁE�E�E
};