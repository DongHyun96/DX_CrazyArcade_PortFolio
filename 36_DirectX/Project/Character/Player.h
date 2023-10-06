#pragma once
class Player : public Character
{
public:
	Player(const CharacterType& cType);
	~Player();

	virtual void Move() override;

private:

	virtual void DeployBalloon() override;


};
