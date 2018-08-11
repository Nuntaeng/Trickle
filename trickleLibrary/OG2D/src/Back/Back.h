#pragma once

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

/**
* @brief �w�i�ɗ����_�N���X
* @author ���c
* @date 2018.8.10
*/
class Cloud : public GameObject, public TaskObject {
	//! �_�̃e�N�X�`��
	Texture cloudImg;
	//! �_�摜�̕\���ʒu
	Vec2 cloudPos[2];
	//! �ړ��X�s�[�h
	float speed;
public:
	Cloud(const std::string& path, float speed);
	~Cloud();
	static std::shared_ptr<Cloud> Create(const std::string& path, float speed);

	void Initialize(const std::string& path, float speed);
	void UpDate() override;
	void Render2D() override;
};


class Back : public TaskObject
{
	Texture backImg;
	Vec2 size;
	bool isScroll;
	Vec2* mapSize;
	void Init(const std::string&);
	Vec2* texPos;
	float* Center;
	float* Xsize;
	float* Tsize;
public:
	Back(const std::string&,Vec2&);
	Back(const std::string&, float, float);
	Back(const std::string&, int, int);
	void UpDate() override;
	void Render2D() override;
	typedef std::shared_ptr<Back> SP;
	static SP Create(const std::string&, Vec2&, bool = true);
	static SP Create(const std::string&, float, float, bool = true);
	static SP Create(const std::string&, int, int, bool = true);
	void SetScroll(bool = true);
	virtual ~Back();
};

