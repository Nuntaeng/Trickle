#include "OGSystem\OGsystem.h"

class GameManager : public TaskObject
{
	unsigned int Seconds;
	unsigned int Minute;
	unsigned int timeCnt;
	bool isMaxTime();
	bool OutData();
public:
	bool isClear();
	unsigned int SecondsTime() const;
	unsigned int MinuteTime() const;
	explicit GameManager();
	void UpDate() override;
	virtual ~GameManager();
	typedef std::shared_ptr<GameManager> SP;
	static SP Create(bool = true);
};