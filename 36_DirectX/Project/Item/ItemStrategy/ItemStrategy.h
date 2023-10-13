#pragma once

class ItemStrategy // Interface
{
public:
	ItemStrategy();
	virtual ~ItemStrategy() = default;

	virtual bool UseStrategy(class Character* itemUser) = 0;
	
};

class RollerStrategy : public ItemStrategy
{
public:
	RollerStrategy();
	~RollerStrategy();

	// ItemStrategy을(를) 통해 상속됨
	virtual bool UseStrategy(Character* itemUser) override;

};


class RedDevilStrategy :public ItemStrategy
{
public:
	RedDevilStrategy();
	~RedDevilStrategy();

	virtual bool UseStrategy(Character* itemUser) override;

};

class FluidStrategy : public ItemStrategy
{
public:
	FluidStrategy();
	~FluidStrategy();

	virtual bool UseStrategy(Character* itemUser) override;
};

class FluidUltraStrategy : public ItemStrategy
{
public:
	FluidUltraStrategy();
	~FluidUltraStrategy();

	virtual bool UseStrategy(Character* itemUser) override;

};

class BubbleStrategy : public ItemStrategy
{
public:
	BubbleStrategy();
	~BubbleStrategy();

	virtual bool UseStrategy(Character* itemUser) override;
};

class SpaceStrategy : public ItemStrategy
{
public:
	SpaceStrategy();
	~SpaceStrategy();

	virtual bool UseStrategy(Character* itemUser) override;

};

class OwlStrategy : public ItemStrategy
{
public:
	OwlStrategy();
	~OwlStrategy();

	virtual bool UseStrategy(Character* itemUser) override;

};

class TurtleStrategy : public ItemStrategy
{
public:
	TurtleStrategy();
	~TurtleStrategy();

	virtual bool UseStrategy(Character* itemUser) override;

};


class NeedleStrategy : public ItemStrategy
{
public:
	NeedleStrategy();
	~NeedleStrategy();

	virtual bool UseStrategy(Character* itemUser) override;

};

class DartStrategy : public ItemStrategy
{
public:
	DartStrategy();
	~DartStrategy();

	virtual bool UseStrategy(Character* itemUser) override;

};

class TimerBalloonStrategy : public ItemStrategy
{
public:
	TimerBalloonStrategy();
	~TimerBalloonStrategy();

	virtual bool UseStrategy(Character* itemUser) override;

};
