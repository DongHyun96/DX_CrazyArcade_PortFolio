#pragma once

class ItemStrategy // Interface
{
public:
	ItemStrategy();
	virtual ~ItemStrategy() = default;

	virtual void UseStrategy(class Character* itemUser) = 0;
	
};

class RollerStrategy : public ItemStrategy
{
public:
	RollerStrategy();
	~RollerStrategy();


	// ItemStrategy을(를) 통해 상속됨
	virtual void UseStrategy(Character* itemUser) override;

};


class RedDeamonStrategy
{
public:
	RedDeamonStrategy();
	~RedDeamonStrategy();

private:

};

