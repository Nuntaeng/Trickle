#pragma once
//______________________________//
//|�}�b�v�V�X�e��               |//
//|�����F2018/03/24���q��       |//
//|____________________________|//
#include "Object\Object.h"

enum Format
{
	csv,
};

class Map
{
public:
	//�`�悷��}�b�v�`�b�v�̐�
	Vec2 mapSize;
	//�`��}�b�v�z��
	std::vector<std::vector<int>> _arr;
	//���摜�̉摜�ʒu
	std::vector<Box2D> chip;
	//�I�u�W�F�N�g���
	std::vector<std::vector<Object>> hitBase;
	//�g�p�摜���
	Texture mapimg;
	//���摜�̏c���T�C�Y
	Vec2 chipsize;
	//�`��̏c���T�C�Y
	Vec2 DrawSize;
public:
	Map();
	bool LoadMap(std::string _path);
	bool LoadMap(std::string _path, Format format);
	void MapRender();
	//void MapUpdate();
	void Finalize();
	//�}�b�v�Ƃ̓����蔻��
	bool MapHitCheck(Object &p);
private:
	//�t�@�C���p�X
	const std::string _FilePath = "./data/map/";
	std::string chipimgname;
};