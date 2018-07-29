#pragma once
//______________________________//
//|�}�b�v�V�X�e��               |//
//|�����F2018/03/24���q��       |//
//|____________________________|//
#include "Object\Object.h"
#include "OGSystem\Texture\Texture.h"
#include "OGSystem\OGsystem.h"
#include <cctype>
#include <algorithm>
enum Format
{
	csv,
};

class Map : public TaskObject
{
	class Base : public GameObject
	{
		int arr;
		int* ID;
	public:
		Base();
		virtual ~Base();
		bool IDCheck(const int);
		bool ChipCheck(const int);
		void SetID(const int);
		void Setarr(const int);
		int Getarr() const;
		int* GetID() const;
	};
public:
	//�`�悷��}�b�v�`�b�v�̐�
	Vec2 mapSize;
	//�`��}�b�v�z��
	//���摜�̉摜�ʒu
	std::vector<Box2D> chip;
	//�I�u�W�F�N�g���
	std::vector<std::vector<Base>> hitBase;
	//�g�p�摜���
	Texture mapimg;
	//���摜�̏c���T�C�Y
	Vec2 chipsize;
	//�`��̏c���T�C�Y
	Vec2 DrawSize;
public:
	Map();
	virtual ~Map();
	typedef std::shared_ptr<Map> SP;
	static SP Create(std::string&, Format = csv, bool = true);
	bool LoadMap(std::string& _path, Format format);
	void UpDate();
	void Render2D();
	bool Finalize();
	//�}�b�v�Ƃ̓����蔻��
	bool HitCheck(GameObject &p, const int id);
	bool HitCheck(GameObject &p, const std::string name);
private:
	//�t�@�C���p�X
	const std::string _FilePath = "./data/map/";
	std::string chipimgname;
private:
	void ObjectCreateCheck(std::string&,int,int);
	
	Vec2 waterPos;		//���̐����ʒu�ۑ��p
public:
	Vec2 getWaterPos(); //���̐����ʒu��Ԃ�
};