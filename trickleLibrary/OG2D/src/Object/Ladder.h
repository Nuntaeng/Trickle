#pragma once
//______________________________//
//|�����Ȃ��M�~�b�N ��q       |//
//|�����F2018/03/29 ����	   |//
//|�@                          |//
//|____________________________|//
#include "Object.h"
class Ladder : public Object
{
public:
	bool Initialize();
	void UpDate();
	void Render();			//map�ŕ`����s���̂ł��܂�Ӗ����Ȃ�
	void Finalize();
	Ladder();
	~Ladder();
	//��������//
	//�ǉ��ϐ�//
	//��������//
private:
	bool flag;				//Player�ƐڐG�����Ă��邩�̃t���O
	bool CheakHit();		//Player�Ƃ̐ڐG������s��
};