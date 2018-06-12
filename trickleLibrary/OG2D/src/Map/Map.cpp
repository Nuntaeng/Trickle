#include "Map.h"
#include "Player\Player.h"
#include "Bucket\bucket.h"
#include "Gimmick\NO_MOVE\Switch.h"
#include "Goal\Goal.h"
#include "Paint\Paint.h"
Map::Map()
{
	this->chip.resize(45);
	this->chipimgname = "mapchip2.png";
	this->chipsize = { 256,256 };
	this->DrawSize = { 64,64 };
	__super::Init((std::string)"map");
}

Map::~Map()
{
	this->Finalize();
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{

	}
}

bool Map::LoadMap(std::string& path_, Format format)
{
	if (Format::csv != format)
	{
		std::cout << "ファイル形式が読み込みに対応していません" << std::endl;
		return false;
	}
	//ファイルの読み込み(入力用式、バイナリデータでの読み込み)
	std::ifstream ifs(this->_FilePath + path_, std::ios::in | std::ios::binary);
	//読み込めなかった時のエラー処理
	if (!ifs)
	{
		std::cout << "マップ読み込みエラー" << std::endl;
		return false;
	}
	//読み込んだデータを入れておく変数
	std::string line;
	//改行か終了地点までの文字の文字列をlineにいれる
	std::getline(ifs, line);
	//文字列を操作するための入力class、直接アクセスできる
	std::istringstream _is(line);
	//一字書き込み変数
	std::string text;
	//_isに入っている文字列から','までの文字をtextにいれる
	std::getline(_is, text, ',');
	//textのデータを変数にいれる
	(std::stringstream)text >> this->mapSize.x;
	std::getline(_is, text, ',');
	(std::stringstream)text >> this->mapSize.y;
	//_arrをmapyのサイズ分にサイズを変更する(配列化)
	this->_arr.resize((int)this->mapSize.y);
	this->ID.resize((int)this->mapSize.y);
	this->hitBase.resize((int)this->mapSize.y);
	//_arr[]をmapxのサイズ分にサイズを変更する(二次配列化)
	for (int i = 0; i < this->mapSize.y; ++i)
	{
		this->_arr[i].resize((int)this->mapSize.x);
		this->ID.resize((int)this->mapSize.x);
		this->hitBase[i].resize((int)this->mapSize.x);
	}
	for (int y = 0; y < this->mapSize.y; ++y) {
		std::string lineText;
		std::getline(ifs, lineText);
		std::istringstream  ss_lt(lineText);
		for (int x = 0; x < this->mapSize.x; ++x) {
			std::string  text;
			std::getline(ss_lt, text, ',');
			if (text == "\r")
			{
				continue;
			}
			if (text.find("\r") != std::string::npos)
			{
				text.erase(text.find("\r"));
			}
			//文字列が数字のみかを検索
			if (std::all_of(text.cbegin(), text.cend(), isdigit))
			{
				//番号をそのまま格納
				int num = 0;
				(std::stringstream)text >> this->_arr[y][x];
				(std::stringstream)text >> num;
				//this->hitBase[y][x].Setarr(num);
			}
			else
			{
				//文字列に応じたオブジェクトを生成する
				this->ObjectCreateCheck(text, x, y);
				//その場所の番号は0としておく。
				this->_arr[y][x] = 0;
				//this->hitBase[y][x].Setarr(0);
			}
		}
	}
	ifs.close();
	//画像読み込み
	this->mapimg.Create(chipimgname);
	for (int i = 0; i < chip.size(); ++i)
	{
		//元画像チップの描画範囲の指定
		int x = (i % 20);
		int y = (i / 20);
		this->chip[i] = Box2D(x*chipsize.x, y * chipsize.y, chipsize.x, chipsize.y);
		this->chip[i].OffsetSize();
	}
	for (int y = 0; y < this->mapSize.y; ++y)
	{
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			//オブジェクトの生成
			if (_arr[y][x] != 0)
			{
				this->hitBase[y][x].CreateObject(Objform::Cube, Vec2(this->DrawSize.x * x, this->DrawSize.y * y), DrawSize, 0.f);
			}
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
				//床
				this->hitBase[y][x].objectTag = "Floor";
				//*this->ID[y][x] = new int(0);
				break;
			case 14:
				this->hitBase[y][x].Scale.y = 20.0f;		//仮処理、上方向金網のみ当たり判定の高さを20に制限
			case 15:
			case 16:
			case 17:
				//this->ID[y][x] = new int(1);
				this->hitBase[y][x].objectTag = "Net";
				break;
			case 18:
			case 19:
			case 20:
			case 21:
				//this->ID[y][x] = new int(0);
				this->hitBase[y][x].objectTag = "Soil";
				break;
			case 22:
				this->hitBase[y][x].objectTag = "LadderTop";
				break;
			case 23:
				this->hitBase[y][x].objectTag = "Ladder";
			case 24:
				this->hitBase[y][x].objectTag = "Ladder";
				//this->ID[y][x] = new int(0);
				break;
			default:
				break;
			}

			/*if (this->ID[y][x])
			{
				this->hitBase[y][x].CreateObject(Cube, Vec2(this->DrawSize.x * x, this->DrawSize.y * y), this->DrawSize, 0.0f);
			}*/
			//switch (this->hitBase[y][x].Getarr())
			//{
			//case 1:
			//case 2:
			//case 3:
			//case 4:
			//case 5:
			//case 6:
			//case 7:
			//case 8:
			//case 9:
			//	//床
			//	this->hitBase[y][x].objectTag = "Floor";
			//	this->hitBase[y][x].SetID(0);
			//	break;
			//case 14:
			//	this->hitBase[y][x].Scale.y = 20.0f;		//仮処理、上方向金網のみ当たり判定の高さを20に制限
			//case 15:
			//case 16:
			//case 17:
			//	this->hitBase[y][x].SetID(1);
			//	this->hitBase[y][x].objectTag = "Net";
			//	break;
			//case 18:
			//case 19:
			//case 20:
			//case 21:
			//	this->hitBase[y][x].SetID(0);
			//	this->hitBase[y][x].objectTag = "Soil";
			//	break;
			//case 22:
			//	this->hitBase[y][x].objectTag = "LadderTop";
			//	break;
			//case 23:
			//	this->hitBase[y][x].objectTag = "Ladder";
			//case 24:
			//	this->hitBase[y][x].objectTag = "Ladder";
			//	this->hitBase[y][x].SetID(0);
			//	break;
			//default:
			//	break;
			//}
			/*if (this->hitBase[y][x].GetID())
			{
				this->hitBase[y][x].CreateObject(Cube, Vec2(this->DrawSize.x * x, this->DrawSize.y * y), this->DrawSize, 0.0f);
			}*/
		}
	}

	return true;
}

void Map::ObjectCreateCheck(std::string& text, int x_index, int y_index)
{
	if (text == "p")
	{
		auto player = Player::Create(Vec2(this->DrawSize.x * x_index, this->DrawSize.y * y_index));
		player->SetTexture(rm->GetTextureData((std::string)"playerTex"));
		return;
	};
	if (text == "b")
	{
		auto bucket = Bucket::Create(Vec2(this->DrawSize.x * x_index, this->DrawSize.y * y_index));
		return;
	}
	if (text == "g")
	{
		auto goal = Goal::Create(Vec2(this->DrawSize.x * x_index, this->DrawSize.y * y_index));
		return;
	}
	if (text == "paintred")
	{
		auto paint = Paint::Create(Vec2(this->DrawSize.x * x_index, this->DrawSize.y * y_index), Vec2(64, 64), Paint::PaintColor::Red);
		paint->SetTexture(rm->GetTextureData((std::string)"paintTex"));
		return;
	}
	if (text == "paintblue")
	{
		auto paint = Paint::Create(Vec2(this->DrawSize.x * x_index, this->DrawSize.y * y_index), Vec2(64, 64), Paint::PaintColor::Blue);
		paint->SetTexture(rm->GetTextureData((std::string)"paintTex"));
		return;
	}
	if (text == "paintpurple")
	{
		auto paint = Paint::Create(Vec2(this->DrawSize.x * x_index, this->DrawSize.y * y_index), Vec2(64, 64), Paint::PaintColor::Purple);
		paint->SetTexture(rm->GetTextureData((std::string)"paintTex"));
		return;
	}
}

void Map::UpDate()
{

}

void Map::Render2D()
{
	for (int y = 0; y < this->mapSize.y; ++y)
	{
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			if (this->_arr[y][x] != 0)
			{
				Box2D draw(this->hitBase[y][x].position, this->DrawSize);
				draw.OffsetSize();
				this->mapimg.Draw(draw, this->chip[this->_arr[y][x]]);
			}
			/*if (this->hitBase[y][x].Getarr() != 0)
			{
				Box2D draw(this->hitBase[y][x].position, this->DrawSize);
				draw.OffsetSize();
				this->mapimg.Draw(draw, this->chip[this->hitBase[y][x].Getarr()]);
			}*/
		}
	}
}

bool Map::Finalize()
{
	this->_arr.clear();
	this->hitBase.clear();
	this->chip.clear();
	this->mapimg.Finalize();
	return true;
}

bool Map::MapHitCheck(GameObject &p)
{
	for (int y = 0; y < this->mapSize.y; ++y)
	{
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			//マップ番号０以外に当たったらTRUEを返す
			if (this->_arr[y][x] != 0 &&
				this->_arr[y][x] != 10 &&
				this->_arr[y][x] != 12 &&
				this->_arr[y][x] != 13 &&
				this->_arr[y][x] != 21 &&
				this->_arr[y][x] != 22 &&
				this->_arr[y][x] != 20 &&
				this->_arr[y][x] != 23) {
				if (this->hitBase[y][x].hit(p))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Map::HitCheck(GameObject &p, const int id)
{
	for (int y = 0; y < this->mapSize.y; ++y)
	{
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			/*	if (this->hitBase[y][x].IsObjectDistanceCheck(p.position, p.Scale))
				{
					if (this->hitBase[y][x].IDCheck(id))
					{
						if (this->hitBase[y][x].hit(p))
						{
							return true;
						}
					}
				}*/
		}
	}
	return false;
}

Map::SP Map::Create(std::string& path, Format format, bool flag_)
{
	auto to = Map::SP(new Map());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->LoadMap(path, format))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

Map::Base::Base()
{
	this->arr = 0;
	this->ID = nullptr;
}
Map::Base::~Base()
{
	if (this->ID)
	{
		delete this->ID;
		this->ID = nullptr;
	}
}

bool Map::Base::IDCheck(const int id)
{
	if (this->ID)
	{
		return *this->ID <= id ? true : false;
	}
	return false;
}

bool Map::Base::ChipCheck(const int chip)
{
	return this->arr == chip ? true : false;
}
void Map::Base::Setarr(const int _arr)
{
	this->arr = _arr;
}
void Map::Base::SetID(const int id)
{
	if (!this->ID)
	{
		this->ID = new int(id);
	}
	else
	{
		*this->ID = id;
	}
}
int Map::Base::Getarr() const
{
	return this->arr;
}
int* Map::Base::GetID() const
{
	return this->ID;
}