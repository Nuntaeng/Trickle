#include "Map.h"
Map::Map()
{
	
}

bool Map::LoadMap(std::string _path)
{
	std::ifstream ifs(this->_FilePath + _path, std::ios::in | std::ios::binary);
	if (!ifs)
	{
		std::cout << "�}�b�v�ǂݍ��݃G���[" << std::endl;
		return false;
	}
	std::string _s;
	int _csize = 0;
	//�e�l���e�L�X�g����i�[
	while (std::getline(ifs, _s))
	{
		if (_s.substr(0, 2) == "X ")
		{
			std::istringstream _is(_s.substr(2));
			_is >> this->mapSize.x;
		}
		if (_s.substr(0, 2) == "Y ")
		{
			std::istringstream _is(_s.substr(2));
			_is >> this->mapSize.y;
		}
		if (_s.substr(0, 2) == "C ")
		{
			std::istringstream _is(_s.substr(2));
			_is >> _csize;
		}
		if (_s.substr(0, 2) == "N ")
		{
			std::istringstream _is(_s.substr(2));
			_is >> this->chipimgname;
		}
		if (_s.substr(0, 3) == "CX ")
		{
			std::istringstream _is(_s.substr(3));
			_is >> this->chipsize.x;
		}
		if (_s.substr(0, 3) == "CY ")
		{
			std::istringstream _is(_s.substr(3));
			_is >> this->chipsize.y;
		}
		if (_s.substr(0, 3) == "XS ")
		{
			std::istringstream _is(_s.substr(3));
			_is >> this->DrawSize.x;
		}
		if (_s.substr(0, 3) == "YS ")
		{
			std::istringstream _is(_s.substr(3));
			_is >> this->DrawSize.y;
		}
	}
	//�g�p����}�b�v�`�b�v�̐�
	this->chip.resize(_csize);
	//�}�b�v�z��̐���
	this->_arr.resize(this->mapSize.y);
	this->hitBase.resize(this->mapSize.y);
	for (int i = 0; i < this->mapSize.y; ++i)
	{
		this->_arr[i].resize(this->mapSize.x);
		this->hitBase[i].resize(this->mapSize.x);
	}
	ifs.close();
	//�摜�ǂݍ���
	mapimg.TextureCreate(chipimgname);
	int j = 0;
	std::ifstream ifs2(this->_FilePath + _path, std::ios::in | std::ios::binary);
	if (!ifs2)
	{
		std::cout << "�}�b�v�ǂݍ��݃G���[" << std::endl;
		return false;
	}
	while (std::getline(ifs2, _s))
	{
		if (_s.substr(0, 8) == "MapChip ")
		{
			std::istringstream _is(_s.substr(8));
			for (int i = 0; i < this->mapSize.x; ++i)
			{
				//�}�b�v�ԍ����i�[
				_is >> this->_arr[j][i];
			}
			++j;
		}
	}
	for (int i = 0; i < _csize; ++i)
	{
		//���摜�`�b�v�̕`��͈͂̎w��
		int x = (i % 10);
		int y = (i / 10);
		this->chip[i] = Box2D(x*32.f, y * 32.f, 32.f, 32.f);
		this->chip[i].OffsetSize();
	}
	for (int y = 0; y < this->mapSize.y; ++y)
	{
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			//�I�u�W�F�N�g�̐���
			this->hitBase[y][x].CreateObject(Cube, Vec2(this->DrawSize.x * x, this->DrawSize.y * y), DrawSize, 0.f);
		}

	}
	ifs2.close();
	return true;
}

void Map::MapRender()
{
	for (int y = 0; y < this->mapSize.y; ++y)
	{
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			Box2D draw(this->hitBase[y][x].position, this->DrawSize);
			draw.OffsetSize();
			mapimg.Draw(draw, this->chip[this->_arr[y][x]]);
		}
	}
}

void Map::Finalize()
{
	mapimg.Finalize();
}

bool Map::MapHitCheck(Object &p)
{
	for (int y = 0; y < this->mapSize.y; ++y)
	{
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			//�}�b�v�ԍ��O�ȊO�ɓ���������TRUE��Ԃ�
			if (this->_arr[y][x] != 0) {
				if (this->hitBase[y][x].hit(p))
				{
					return true;
				}
			}
		}
	}
	return false;
}