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


	// ItemStrategy��(��) ���� ��ӵ�
	virtual void UseStrategy(Character* itemUser) override;

};


class RedDeamonStrategy
{
public:
	RedDeamonStrategy();
	~RedDeamonStrategy();

private:

};

