#pragma once

/* CONCRETE CLASS */
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

	const vector<Balloon*>& GetNormalBalloons() { return normalBalloons; } // Collision 때문에 뚫어둠
	const vector<TimerBalloon*>& GetTimerBalloons() { return timerBalloons; }

private:

	const UINT POOL_CNT = 60;
	const UINT TIMERB_POOL_CNT = 18;

	vector<Balloon*> normalBalloons{}; // 일반 벌룬

	vector<TimerBalloon*> timerBalloons{}; // 타이머 벌룬

};
