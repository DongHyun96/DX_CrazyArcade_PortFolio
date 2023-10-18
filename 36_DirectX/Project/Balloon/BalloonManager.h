#pragma once


class BalloonManager
{
public:
	BalloonManager();
	~BalloonManager();

	void Update();
	void Render();

	bool Spawn(const Util::Coord& spawnCoord, Character* owner, const bool& isNormalBalloon = true);

	void Init();

 public:

	const vector<Balloon*>& GetNormalBalloons() { return normalBalloons; } // Collision ¶§¹®¿¡ ¶Õ¾îµÒ
	const vector<TimerBalloon*>& GetTimerBalloons() { return timerBalloons; }

private:

	const UINT POOL_CNT = 60;
	const UINT TIMERB_POOL_CNT = 18;

	vector<Balloon*> normalBalloons{}; // ÀÏ¹Ý ¹ú·é

	vector<TimerBalloon*> timerBalloons{}; // Å¸ÀÌ¸Ó ¹ú·é

};
