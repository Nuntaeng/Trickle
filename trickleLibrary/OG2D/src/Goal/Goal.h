#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Paint\Paint.h"
/**
*@brief	:�S�[���I�u�W�F�N�g
*/
class Goal : public GameObject, public TaskObject
{
	/**
	*@class	CameraAnim
	*�J����������s��class
	*/
	class CameraAnim
	{
		//!	�J�n�ʒu
		Vec2 startPos;
		//!	�I���ʒu
		Vec2 endPos;
		//!	�ړ���v����
		unsigned int time;
		//!	X���W�pEasing
		Easing easing_x;
		//!	Y���W�pEasing
		Easing easing_y;
	public:
		/**
		*@brief	:�C�[�W���O��o�^����
		*@param	:Vec2 start	�J�n�ʒu
		*@param	:Vec2 end	�I���ʒu
		*@param	:unsigned int time	���v����
		*/
		void SetEasing(const Vec2& start, const Vec2& end, const unsigned int time);
		/**
		*@brief	:�ړ��l��Ԃ�
		*@return:�ړ���̒l
		*/
		Vec2 Move();
		/**
		*@brief	:�ړ������ǂ�����Ԃ�
		*@return:�ړ����Ȃ�true
		*/
		bool isPlay();
	};
	/**
	*enum Mode
	*���݂̏�Ԃ��Ǘ�����
	*/
	enum Mode
	{
		//!	����
		Non,
		//!	�J�����ړ�
		Form1,
		//!	�ԍ炫
		Form2,
		//!	�J������߂�
		Form3,
		//!	�I��
		End,
	};
	//!	�N���A���
	bool isClear;
	//!	���͂𐧌������邩�ǂ���
	bool isCheck;
	//!	���i�̃Q�[���p�J�����̃��b�N��ݒ����
	bool cameraLock;
	//!	�A�j���[�V�����p�J�E���g
	unsigned int animCnt;
	//!	��ID
	unsigned int ID;
	//!	�g�p�摜
	Texture* image;
	//!	���p�摜
	Texture lightTex;
	//!	���p�����蔻��
	GameObject foot;
	//!	�`��ʒu
	Box2D draw;
	//! �`��摜�ʒu
	Box2D src;
	//!	�������Ă����F�̏��
	Paint::PaintColor color;
	//!	�J���[���
	Paint::PaintColor termsColor;
	//!	���݂̏�
	Mode mode;
	//!	�J�����̈ʒuEasing�Ǘ�
	CameraAnim cm_Pos;
	//!	�J�����̃T�C�YEasing�Ǘ�
	CameraAnim cm_Size;
	//!	�ړ��O�J�����ʒu
	Vec2* precmPos;
	//!	�ړ��O�J�����T�C�Y
	Vec2* precmSize;
	//!	�T�E���h�̃t�@�C�����i�[
	std::string soundname;
	/**
	*@brief	:���̃S�[���̏�Ԃ��m�F����
	*@return:bool �S�ăS�[�����Ă����true
	*/
	bool isGoalCheck();
	/**
	*@brief	:constructor
	*@param	:Vec2 pos	�����ʒu
	*/
	explicit Goal(const Vec2& pos);
	//! �X�}�[�g�|�C���^
	typedef std::shared_ptr<Goal> SP;
	/**
	*@brief	:�X�V����
	*/
	void UpDate() override;
	/**
	*@brief	:�`�揈��
	*/
	void Render2D() override;
public:
	/**
	*@brief	:destructor
	*/
	virtual ~Goal();
	/**
	*@brief	:�S�[���̃J���[��o�^����
	*@param	:Paint::PaintColor color	�w�肵�����F���
	*/
	void SetColor(const Paint::PaintColor& color);
	/**
	*@brief	:�o�^����Ă���J���[��Ԃ�
	*@return:Paint::PaintColor �J���[���
	*/
	Paint::PaintColor GetColor() const;
	/**
	*@brief	:�o�^����Ă���F�ƌ��݂̐F�������������肷��
	*@return:bool �����Ȃ��true
	*/
	bool ColorCheck() const;
	/**
	*@brief	:�N���A�󋵂�Ԃ�
	*@return:bool �N���A���Ă���Ȃ��true
	*/
	bool GetClear() const;
	/**
	*@brief	:�g�p�摜��o�^����
	*@param	:Texture* tex	�摜�̃|�C���^
	*/
	void SetTexture(Texture*);
	/**
	*@brief	:���Ƃ̔�����s��
	*@return:bool �������Ă����true
	*/
	bool WaterHit();
	/**
	*@brief	:�J�����̌Œ�󋵂�Ԃ�
	*@return:�Œ肵�Ă���Ȃ��true
	*/
	bool GetLock() const;
	/**
	*@brief	:��ID��Ԃ�
	*@return:unsigned int ��ID
	*/
	unsigned int GetID() const;	
	/**
	*@brief	:�^�X�N����
	*@param	:Vec2 pos �ʒu
	*@return:Goal �����Ɏ��s�����ꍇnullptr��Ԃ�
	*/
	static SP Create(const Vec2& pos);	
	Sound sound;     //�T�E���h����
	bool lightCreate;
	Vec2 lightscale;
};