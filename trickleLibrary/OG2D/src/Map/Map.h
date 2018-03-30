#pragma once
//______________________________//
//|�}�b�v�V�X�e��               |//
//|�����F2018/03/24���q��       |//
//|____________________________|//
#include "Object\Object.h"

class Map
{
public:
	Map();
	bool LoadMap(std::string _path);
	void MapRender();
	//void MapUpDate();
	void Finalize();
	//�`�悷��}�b�v�`�b�v�̐�
	//int mapX, mapY;
	Vec2 mapSize;
	//�`��}�b�v�z��
	std::vector<std::vector<int>> _arr;
	//���摜�̉摜�ʒu
	std::vector<Box2D> chip;
	//�I�u�W�F�N�g���
	std::vector<std::vector<Object>> hitBase;
	//std::vector<std::vector<Box2D>> hitBase;
	//�g�p�摜���
	Texture mapimg;
	//���摜�̏c���T�C�Y
	Vec2 chipsize;
	//�`��̏c���T�C�Y
	Vec2 DrawSize;
	//�}�b�v�Ƃ̓����蔻��
	bool MapHitCheck(Object &p);
private:
	//�t�@�C���p�X
	const std::string _FilePath = "./data/map/";
	std::string chipimgname;
};