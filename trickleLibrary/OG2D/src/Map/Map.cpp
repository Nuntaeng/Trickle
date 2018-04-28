#include "Map.h"
Map::Map()
{
	this->chip.resize(30);
	this->chipimgname = "mapchip2.png";
	this->chipsize = { 256,256 };
	this->DrawSize = { 64,64 };
}

bool Map::LoadMap(std::string path_, Format format)
{
	if (Format::csv != format)
	{
		std::cout << "�t�@�C���`�����ǂݍ��݂ɑΉ����Ă��܂���" << std::endl;
		return false;
	}
	//�t�@�C���̓ǂݍ���(���͗p���A�o�C�i���f�[�^�ł̓ǂݍ���)
	std::ifstream ifs(this->_FilePath + path_, std::ios::in | std::ios::binary);
	//�ǂݍ��߂Ȃ��������̃G���[����
	if (!ifs) 
	{
		std::cout << "�}�b�v�ǂݍ��݃G���[" << std::endl;
		return false; 
	}
	//�ǂݍ��񂾃f�[�^�����Ă����ϐ�
	std::string line;
	//���s���I���n�_�܂ł̕����̕������line�ɂ����
	std::getline(ifs, line);
	//������𑀍삷�邽�߂̓���class�A���ڃA�N�Z�X�ł���
	std::istringstream _is(line);
	//�ꎚ�������ݕϐ�
	std::string text;
	//_is�ɓ����Ă��镶���񂩂�','�܂ł̕�����text�ɂ����
	std::getline(_is, text, ',');
	//text�̃f�[�^��ϐ��ɂ����
 	(std::stringstream)text >> this->mapSize.x;
	std::getline(_is, text, ',');
	(std::stringstream)text >> this->mapSize.y;
	//_arr��mapy�̃T�C�Y���ɃT�C�Y��ύX����(�z��)
	this->_arr.resize(this->mapSize.y);
	this->hitBase.resize(this->mapSize.y);
	//_arr[]��mapx�̃T�C�Y���ɃT�C�Y��ύX����(�񎟔z��)
	for (int i = 0; i < this->mapSize.y; ++i)
	{
		this->_arr[i].resize(this->mapSize.x);
		this->hitBase[i].resize(this->mapSize.x);
	}
	for (int y = 0; y < this->mapSize.y; ++y) {
		std::string lineText;
		std::getline(ifs, lineText);
		std::istringstream  ss_lt(lineText);
		for (int x = 0; x < this->mapSize.x; ++x) {
			std::string  text;
			std::getline(ss_lt, text, ',');
			(std::stringstream)text >> this->_arr[y][x];
		}
	}
	ifs.close();
	//�摜�ǂݍ���
	this->mapimg.TextureCreate(chipimgname);
	for (int i = 0; i < chip.size(); ++i)
	{
		//���摜�`�b�v�̕`��͈͂̎w��
		int x = (i % 20);
		int y = (i / 20);
		this->chip[i] = Box2D(x*chipsize.x, y * chipsize.y, chipsize.x, chipsize.y);
		this->chip[i].OffsetSize();
	}
	for (int y = 0; y < this->mapSize.y; ++y)
	{
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			//�I�u�W�F�N�g�̐���
			this->hitBase[y][x].CreateObject(Cube, Vec2(this->DrawSize.x * x, this->DrawSize.y * y), DrawSize, 0.f);
			switch (this->_arr[y][x])
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				//��
				this->hitBase[y][x].objectTag = "Floor";
				break;
			case 14:
			case 15:
			case 16:
			case 17:
				this->hitBase[y][x].objectTag = "Net";
				break;
				//case 3:
				//	this->hitBase[y][x].objectTag = "Net";
				//	break;
				//case 4:
				//	this->hitBase[y][x].objectTag = "Net";
				//	break;
			case 18:
			case 19:
				this->hitBase[y][x].objectTag = "Soil";
				break;
			case 21:
			case 22:
				this->hitBase[y][x].objectTag = "Ladder";
				break;
				//case 8:
				//	this->hitBase[y][x].objectTag = "Ladder";
				//	break;
				//case 9:
				//this->hitBase[y][x].objectTag = "Switch";
				//break;
			default:
				break;
			}
		}
	}
	return true;
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
		int x = (i % 20);
		int y = (i / 20);
		this->chip[i] = Box2D(x*32.f, y * 32.f, 32.f, 32.f);
		this->chip[i].OffsetSize();
	}
	for (int y = 0; y < this->mapSize.y; ++y)
	{
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			//�I�u�W�F�N�g�̐���
			this->hitBase[y][x].CreateObject(Cube, Vec2(this->DrawSize.x * x, this->DrawSize.y * y), DrawSize, 0.f);
			switch (this->_arr[y][x])
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				//��
				this->hitBase[y][x].objectTag = "Floor";
				break;
			case 14:
			case 15:
			case 16:
			case 17:
				this->hitBase[y][x].objectTag = "Net";
				break;
			//case 3:
			//	this->hitBase[y][x].objectTag = "Net";
			//	break;
			//case 4:
			//	this->hitBase[y][x].objectTag = "Net";
			//	break;
			case 18:
			case 19:
				this->hitBase[y][x].objectTag = "Soil";
				break;
			case 21:
			case 22:
				this->hitBase[y][x].objectTag = "Ladder";
				break;
			//case 8:
			//	this->hitBase[y][x].objectTag = "Ladder";
			//	break;
			//case 9:
				//this->hitBase[y][x].objectTag = "Switch";
				//break;
			default:
				break;
			}
		}

	}
	ifs2.close();
	return true;
}

void Map::MapRender()
{
 	for  (int y = 0; y < this->mapSize.y; ++y)
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
	this->_arr.clear();
	this->hitBase.clear();
	this->chip.clear();
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