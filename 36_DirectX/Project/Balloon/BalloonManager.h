#pragma once


class BalloonManager
{
public:
	BalloonManager();
	~BalloonManager();

	void Update();
	void Render();

	bool Spawn(const Util::Coord& spawnCoord, Character* owner);

public:

	const vector<Balloon*>& GetBalloons() { return balloons; } // Collision ¶§¹®¿¡ ¶Õ¾îµÒ

private:

	const UINT POOL_CNT = 100;

	vector<Balloon*> balloons{};

};
