#pragma once

/*
CONCRETE CLASS
*/
class TimerBalloon : public Balloon
{
public:
	TimerBalloon(Animation* animation);
	~TimerBalloon();

	virtual bool Spawn(const Util::Coord& spawnCoord, Character* owner) override;

	virtual void Explode() override;


private:

	virtual void HandleExplode() override;

};
