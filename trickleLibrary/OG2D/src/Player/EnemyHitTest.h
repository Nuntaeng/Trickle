#pragma once
#include "Object\Object.h"
#include "Win\WinMain.h"
#include "Task\Task_GIMMICK_Control.h"

class GIMMICK_Control;

enum State
{
	Normal,//��
	Hot,   //�����C
	Frieze,//�X
};
class EnemyHitTest : public Object
{
public:
	State state;
	void Initialize();
	void Finalize();
	void UpDate();
	void Render();

	EnemyHitTest();
	~EnemyHitTest();
private:
	void Move();
	Texture image;						//�摜�C���[�W
	std::string	 _filePath;				//�摜�p�X
};