#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Paint\Paint.h"

class Goal : public GameObject, public TaskObject
{
	class CameraAnim
	{
		Vec2 startPos;
		Vec2 endPos;
		unsigned int time;
		Easing easing_x;
		Easing easing_y;
	public:
		void Set(const Vec2& start, const Vec2& end, const unsigned int time);
		Vec2 Move();
		bool isPlay();
	};
	enum Mode
	{
		Non,	//����
		Form1,	//�J�����ړ�
		Form2,	//�ԍ炫
		Form3,	//�J�����߂�
		End,	//�I��
	};
	bool isClear;
	bool isCheck;
	bool cameraLock;
	unsigned int animCnt;
	unsigned int ID;
	Texture* image;
	Texture lightTex;
	GameObject foot;
	Box2D draw;
	Box2D src;
	Paint::PaintColor color;
	Paint::PaintColor termsColor;
	Mode mode;
	CameraAnim cm_Pos;
	CameraAnim cm_Size;
	Vec2* precmPos;
	Vec2* precmSize;
	bool isGoalCheck();
	std::string soundname;   //�T�E���h�̃t�@�C�����i�[
	bool testClear;
public:
	explicit Goal(const Vec2& pos);
	virtual ~Goal();
	void SetColor(const Paint::PaintColor&);	//�S�[���̃J���[���w�肷��
	Paint::PaintColor GetColor() const;			//�S�[���Ɏw�肳��Ă���F��Ԃ�
	bool ColorCheck() const;					//�F�����������𔻒肷��
	void UpDate() override;						//�X�V
	void Render2D() override;					//�`��
	bool GetClear() const;						//�N���A���Ă��邩��Ԃ�
	void SetTexture(Texture*);					//�`�悷��摜��o�^����
	bool WaterHit();							//���Ƃ̔�����s��
	bool GetLock() const;						//�J�����̌Œ�󋵂�Ԃ�
	unsigned int GetID() const;					//�o�^����Ă���ID��Ԃ�
	typedef std::shared_ptr<Goal> SP;			//�X�}�[�g�|�C���^
	static SP Create(const Vec2& pos, bool = true);	//��������
	Sound sound;     //�T�E���h����
	bool lightCreate;
	Vec2 lightscale;
	void TestGoal();
};