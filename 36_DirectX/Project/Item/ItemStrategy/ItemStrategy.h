#pragma once

/* INTERFACE */
class ItemStrategy
{
public:
	ItemStrategy();
	virtual ~ItemStrategy() = default;

	/// <summary>
	/// Strategy pattern's pure-virtual method
	/// </summary>
	/// <param name="itemUser"> : �������� ����� character </param>
	/// <returns> : ������ ����� ���������� �̷�����ٸ� return true </returns>
	virtual bool UseStrategy(class Character* itemUser) = 0;
	
};

/* CONCRETE CLASS */
class RollerStrategy : public ItemStrategy
{
public:
	RollerStrategy();
	~RollerStrategy();

	virtual bool UseStrategy(Character* itemUser) override;
};

/* CONCRETE CLASS */
class RedDevilStrategy :public ItemStrategy
{
public:
	RedDevilStrategy();
	~RedDevilStrategy();

	virtual bool UseStrategy(Character* itemUser) override;

};

/* CONCRETE CLASS */
class FluidStrategy : public ItemStrategy
{
public:
	FluidStrategy();
	~FluidStrategy();

	virtual bool UseStrategy(Character* itemUser) override;
};

/* CONCRETE CLASS */
class FluidUltraStrategy : public ItemStrategy
{
public:
	FluidUltraStrategy();
	~FluidUltraStrategy();

	virtual bool UseStrategy(Character* itemUser) override;

};

/* CONCRETE CLASS */
class BubbleStrategy : public ItemStrategy
{
public:
	BubbleStrategy();
	~BubbleStrategy();

	virtual bool UseStrategy(Character* itemUser) override;
};

/* CONCRETE CLASS */
class SpaceStrategy : public ItemStrategy
{
public:
	SpaceStrategy();
	~SpaceStrategy();

	virtual bool UseStrategy(Character* itemUser) override;

};

/* CONCRETE CLASS */
class OwlStrategy : public ItemStrategy
{
public:
	OwlStrategy();
	~OwlStrategy();

	virtual bool UseStrategy(Character* itemUser) override;

};

/* CONCRETE CLASS */
class TurtleStrategy : public ItemStrategy
{
public:
	TurtleStrategy();
	~TurtleStrategy();

	virtual bool UseStrategy(Character* itemUser) override;

};

/* CONCRETE CLASS */
class NeedleStrategy : public ItemStrategy
{
public:
	NeedleStrategy();
	~NeedleStrategy();

	virtual bool UseStrategy(Character* itemUser) override;

};

/* CONCRETE CLASS */
class DartStrategy : public ItemStrategy
{
public:
	DartStrategy();
	~DartStrategy();

	virtual bool UseStrategy(Character* itemUser) override;

};

/* CONCRETE CLASS */
class TimerBalloonStrategy : public ItemStrategy
{
public:
	TimerBalloonStrategy();
	~TimerBalloonStrategy();

	virtual bool UseStrategy(Character* itemUser) override;

};
