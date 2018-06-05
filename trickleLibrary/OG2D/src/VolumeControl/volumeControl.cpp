#include "VolumeControl\volumeControl.h"
#include "Player\Player.h"
#include <math.h>

VolumeControl::VolumeControl()
{
	this->distance = 0.0f;
	this->playerPos = nullptr;
	this->soundPos = Vec2(0, 0);
	std::cout << "ボリューム調節クラス生成" << std::endl;
}
VolumeControl::~VolumeControl()
{
	std::cout << "ボリューム調節クラス解放" << std::endl;
	if (this->playerPos)
	{
		delete this->playerPos;
	}
}


//距離を求める
float VolumeControl::GetDistance(Vec2 soundpos)
{
	Vec2 hypotenuse;      //距離を求める為の数値を格納　hypotenuseは斜辺の意
	soundPos = soundpos;       //デバックで値を見やすくしたかった。不要なら削除予定
	if (this->playerPos)       //プレイヤが存在していたら
	{
		//x軸
		if (playerPos->x >= soundPos.x)
		{
			hypotenuse.x = playerPos->x - soundPos.x;
		}
		else
		{
			hypotenuse.x = soundPos.x - playerPos->x;
		}
		//y軸
		if (playerPos->y >= soundPos.y)
		{
			hypotenuse.y = playerPos->y - soundPos.y;
		}
		else
		{
			hypotenuse.y = soundPos.y - playerPos->y;
		}
	}
	else                      //プレイヤが存在していなかったら
	{
		hypotenuse = soundPos;
	}
	//デバック用
	//std::cout << sqrt(hypotenuse.x*hypotenuse.x + hypotenuse.y*hypotenuse.y) << std::endl;

	distance= sqrt(hypotenuse.x*hypotenuse.x + hypotenuse.y*hypotenuse.y);        //直線距離を求める
	return distance;
}

//距離に応じたボリュームを設定するための数値(0~1)を取得
float VolumeControl::VolSet()
{
	////距離が離れるほど音量を小さく
	//if (distance < 200)
	//{
	//	return 1.0f;     //最大音量	
	//}
	//else if (distance < 300)
	//{
	//	return 0.9f;
	//}
	//else if (distance < 400)
	//{
	//	return 0.8f;
	//}
	//else if (distance < 500)
	//{
	//	return 0.7f;
	//}
	//else if (distance < 600)
	//{
	//	return 0.6f;
	//}
	//else if (distance < 700)
	//{
	//	return 0.5f;
	//}
	//else if (distance < 800)
	//{
	//	return 0.4f;
	//}
	//else if (distance < 900)
	//{
	//	return 0.3f;
	//}
	//else if (distance < 1000)
	//{
	//	return 0.2f;
	//}
	////else if (distance < 1000)
	////{
	////	return 0.1f;
	////}
	//else
	//{
	//	return 0.0f;
	//}
	float changeVolDis;
	changeVolDis = this->maxdis / 10.0f;    //音量を十段階切り替え
	//距離が離れるほど音量を小さく
	if (distance < changeVolDis*2.0f)
	{
		return 1.0f*maxvol;     //最大音量	
	}
	else if (distance < changeVolDis*3.0f)
	{
		return 0.9f*maxvol;
	}
	else if (distance < changeVolDis*4.0f)
	{
		return 0.8f*maxvol;
	}
	else if (distance < changeVolDis*5.0f)
	{
		return 0.7f*maxvol;
	}
	else if (distance < changeVolDis*6.0f)
	{
		return 0.6f*maxvol;
	}
	else if (distance < changeVolDis*7.0f)
	{
		return 0.5f*maxvol;
	}
	else if (distance < changeVolDis*8.0f)
	{
		return 0.4f*maxvol;
	}
	else if (distance < changeVolDis*9.0f)
	{
		return 0.3f*maxvol;
	}
	else if (distance < maxdis)
	{
		return 0.1f*maxvol;
	}
	//else if (distance < 1000)
	//{
	//	return 0.1f;
	//}
	else
	{
		return 0.0f;
	}
}

void VolumeControl::GetPlPos()
{
	auto player = OGge->GetTask<Player>("Player");
	if (player)         //プレイヤが存在していたら	
	{
		this->playerPos = new Vec2(player->position);
	}
	//プレイヤが存在していなかったら初期値で入れたnullptrが返る
}


void VolumeControl::Play(Vec2 pos,float maxDis,float maxVol,Sound& sound)    //最大音量を指定
{
	maxdis = maxDis;
	maxvol = maxVol;
	//距離によって音量を変える
	this->GetPlPos();
	this->GetDistance(pos);
	sound.volume(this->VolSet());
}