//#pragma once
//#include "OGSystem\OGsystem.h"
//#include "Object\Object.h"
//#include "OGSystem/_OGsystem.h"
//
//class ClearUI : public GameObject, public TaskObject
//{
//private:
//	//�^�X�N�֘A
//	std::string taskName;
//
//	//�摜�֘A
//	Texture image;
//	const Box2D Src = {0,0,269,85};
//
//	//�g��@�\
//	Vec2  Center;			//�`�撆���Œ���W
//	Vec2  ReSize;			//�V�������T�C�Y����Scale
//	Vec2  ScaleVolume;		//�g�嗦
//	Vec2  PreSize;			//�O��̃f�[�^������Ă���
//	bool  Volumefinish;
//
//private:
//	//�^�X�N�֘A
//	bool Initialize(Vec2&);
//	bool Finalize();
//	void UpDate();
//	void Render2D();
//	ClearUI();
//
//	//�g��@�\
//	void MoveVolume();		  //�g�嗦���������㏸�����Ă����܂�
//	void ResetVolume();	      //�g�嗦���グ�邽�߂̏��������s��
//	void ResetCenter();		  //�����l�̍Čv�Z�����܂��i1�t���[���Ōv�Z�����ďI���������邱�Ɓj
//	void SetVolumeFlag(bool);
//public:
//	virtual ~ClearUI();
//	typedef std::shared_ptr<ClearUI> SP;
//	static ClearUI::SP Create(Vec2& pos, bool = true);
//
//	//���U���g�Ŏg�p����֐�
//	bool GetVolumeFlag();
//};