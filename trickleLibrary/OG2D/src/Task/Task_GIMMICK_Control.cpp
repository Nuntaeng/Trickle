#include "Task_GIMMICK_Control.h"
//��������//-----------------------------------------------------------------------------
GIMMICK_Control::GIMMICK_Control()
{
	//
}
//��������//-----------------------------------------------------------------------------
GIMMICK_Control::~GIMMICK_Control()
{
	//delete _e_pointa;
	delete _sen_pointa;
	delete _ka_pointa;
	delete _swi_pointa;
}
//��������//-----------------------------------------------------------------------------
void GIMMICK_Control::Initialize()
{
	//�M�~�b�N�̂��ꂼ��̏���������������

	//_e_pointa = new EnemyHitTest();

	_sen_pointa = new Senpuki();
	_ka_pointa = new Kanetuki();
	_swi_pointa = new Switch();

	//_e_pointa->Initialize();
	_sen_pointa->Initialize();
	_ka_pointa->Initialize();
	_swi_pointa->Initlaize();
}
//��������//-----------------------------------------------------------------------------
void GIMMICK_Control::Finalize()
{
	//�M�~�b�N���ꂼ��̉������

	//_e_pointa->Finalize();
	_sen_pointa->Finalize();
	_ka_pointa->Finalize();
	_swi_pointa->Finalize();
}
//��������//-----------------------------------------------------------------------------
TaskFlag GIMMICK_Control::UpDate()
{
	//�M�~�b�N���ꂼ��̍X�V����
	TaskFlag nextTask = Task_Sample;

	//_e_pointa->UpDate();

	_sen_pointa->UpDate();
	_ka_pointa->UpDate();
	_swi_pointa->UpDate();
	return nextTask;
}
//��������//-----------------------------------------------------------------------------
void GIMMICK_Control::Render2D()
{
	//�M�~�b�N���ꂼ��̕`�揈��

	//_e_pointa->Render();

	_sen_pointa->Render();
	_ka_pointa->Render();
	_swi_pointa->Render();
}
