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
public:
	//�`�悷��}�b�v�`�b�v�̐�
	Vec2 mapSize;
	//�`��}�b�v�z��
	std::vector<std::vector<int>> _arr;
	//���摜�̉摜�ʒu
	std::vector<Box2D> chip;
	//�I�u�W�F�N�g���
	std::vector<std::vector<GameObject>> hitBase;
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
	//void MapUpdate();
	bool Finalize();
	//�}�b�v�Ƃ̓����蔻��
	bool MapHitCheck(GameObject &p);
private:
	//�t�@�C���p�X
	const std::string _FilePath = "./data/map/";
	std::string chipimgname;
private:
	void ObjectCreateCheck(std::string&,int,int);
};