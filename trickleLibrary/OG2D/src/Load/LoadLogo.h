#pragma once

#include "OGSystem\OGSystem.h"

class Load : public TaskObject
{
	class Param
	{
	public:
		std::mutex mutex;
		bool on;
		unsigned int animCnt;
	};
	std::shared_ptr<Param> param;
	Texture image;	//�摜
	Box2D draw;		//����錾�����肱���ɏ����Ă�������������y���Ȃ�̂ł͂̌��؂����Ă��܂��B
	Box2D src;		//
	Texture tex;
public:
private:
	void UpDate();
	static void Render(Texture* ,std::shared_ptr<Param>& param);
public:
	Load();
	virtual ~Load();
	typedef std::shared_ptr<Load> SP;
	static SP Create(bool = true);
	void Draw();		//�����`����s��
	void Delete();
};