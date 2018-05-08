#include "OGsystem.h"
//--------------------------------------------------
//@:GameEngineclass									
//--------------------------------------------------
EngineSystem::EngineSystem()
{
	//Window��񂪃Z�b�g����Ȃ��������̂��߂̏����ݒ�
	this->w_wi = 960;
	this->w_he = 540;
	this->w_na = "NoName";
	this->w_sc = false;
	this->Cursor_on = true;
	this->file = "testicon.png";
	this->w_pos = { 1920 - this->w_wi, 50 };
	this->DeleteEngine = false;
}
EngineSystem::EngineSystem(int widht, int height, char* name, bool screen)
{
	this->w_he = widht;
	this->w_he = height;
	this->w_na = name;
	this->w_sc = screen;
}
void EngineSystem::Initialize()
{
	//����������
	//�J����2D�̐���
	this->camera = Camera2D::Create(Box2D(0, 0, 960, 540));
	//Window�̐���
	this->window = Window::Create(w_wi, w_he, w_na, w_sc, w_pos);
	//Window�ݒ�
	this->window->LimitsWindow();
	this->window->InMouseMode(this->Cursor_on);
	this->window->setIcon(this->path + this->file);
	//fps�̐ݒ�
	//���f�o�b�O���̂ݎg�p����
#if(_DEBUG)
	this->fps = FPS::Create();
#endif
	//���͊֘A�̏�����
	this->in.Inputinit(this->window->window);
	//�T�E���h�Ǘ��̏�����
	this->soundManager = SoundManager::Create();
	//�I�[�f�B�I�f�o�C�X�̏������Ɛݒ�
	this->audiodevice = Audio::Create();
	//�e�l�̏�����
	DebugFunction = false;
	this->isPause = false;
	this->end = false;
}
void EngineSystem::SetWindow(int width, int height, char* name, bool screen)
{
	//Window����o�^����
	this->w_wi = width;
	this->w_he = height;
	this->w_na = name;
	this->w_sc = screen;
}
void EngineSystem::SetCursorOn(const bool on)
{
	//�J�[�\���̉����L��
	this->Cursor_on = on;
}
void EngineSystem::SetIcon(std::string& filepath_)
{
	//�A�C�R���Ɏg�p����摜�̐ݒ�
	this->file = filepath_;
}
void EngineSystem::Update()
{
	//�J�����Ɠ��͏󋵂̍X�V
	this->camera->CameraUpdate();
	this->in.upDate();
#if(_DEBUG)
	this->fps->Update();
#endif
}
void EngineSystem::SetPause(const bool ispause_)
{
	//�|�[�Y�ݒ�
	this->isPause = ispause_;
}
bool EngineSystem::GetPause() const
{
	//�|�[�Y�󋵂�Ԃ�
	return this->isPause;
}
void EngineSystem::GameEnd()
{
	//�A�v���P�[�V�����̏I���\��ݒ�
	this->end = true;
}
bool EngineSystem::GetEnd() const
{
	//�A�v���P�[�V�������I���̗L����Ԃ�
	return this->end;
}
void EngineSystem::ChengeTask()
{
	//�^�X�N��ύX����ۂɌ��ɖ߂���������
	this->camera->SetPos(Vec2(0.f, 0.f));
	this->camera->SetSize(Vec2(this->window->_widht, this->window->_height));
	this->SetPause(false);
	this->soundManager->AllDelete();
}
void EngineSystem::SetWindowPos(Vec2& pos)
{
	//Window�̈ʒu��Ԃ�
	this->w_pos = pos;
}
void EngineSystem::SetDeleteEngine(bool flag)
{
	//�G���W���̏I����o�^
	this->DeleteEngine = flag;
}
bool EngineSystem::GetDeleteEngine()
{
	//�G���W���I����Ԃ�
	return this->DeleteEngine;
}
EngineSystem::~EngineSystem()
{

}
EngineSystem* gameEngine;