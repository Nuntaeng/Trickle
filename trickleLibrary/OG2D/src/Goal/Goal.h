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
		Non,	//初期
		Form1,	//カメラ移動
		Form2,	//花咲き
		Form3,	//カメラ戻り
		End,	//終了
	};
	bool isClear;
	bool isCheck;
	bool cameraLock;
	unsigned int animCnt;
	Texture* image;
	GameObject foot;
	Box2D draw;
	Box2D src;
	Paint::PaintColor color;
	Mode mode;
	CameraAnim cm_Pos;
	CameraAnim cm_Size;
	Vec2* precmPos;
	Vec2* precmSize;
public:
	explicit Goal(const Vec2& pos);
	virtual ~Goal();
	void UpDate() override;
	void Render2D() override;
	bool GetClear() const;
	void SetTexture(Texture*);
	bool WaterHit();
	bool GetLock() const;
	typedef std::shared_ptr<Goal> SP;
	static SP Create(const Vec2& pos, bool = true);
};