#pragma once


class BalloonManager
{
public:
	BalloonManager();
	~BalloonManager();

	void Update();
	void Render();

	bool Spawn(const Util::Coord& spawnCoord);
	bool Spawn(const Vector2& spawnPos);

public:

	const vector<Balloon*>& GetBalloons() { return balloons; }

private:

	const UINT POOL_CNT = 100;

	vector<Balloon*> balloons{};

};
