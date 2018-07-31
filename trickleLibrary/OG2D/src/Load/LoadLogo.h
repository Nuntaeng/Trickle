#pragma once

#include "OGSystem\OGSystem.h"

class Load : public TaskObject
{
public:
	enum Fead
	{
		In, Out
	};
private:
	Texture image;	//�摜
	Box2D draw;		//����錾�����肱���ɏ����Ă�������������y���Ȃ�̂ł͂̌��؂����Ă��܂��B
	Box2D src;		//
	Texture tex;
	Color* color;
	Fead mode;
	std::vector<std::string> deleteObject;
public:
	Load();
	virtual ~Load();
	typedef std::shared_ptr<Load> SP;
	static SP Create(bool = true);
	void Draw();		//�����`����s��
	void Render2D() override;
	void PauseUpDate() override;
	void UpDate() override;
	void Set(const Fead&);
	Fead Get() const;
	void AddObject(const std::string&);
};