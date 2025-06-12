#pragma once
#include "Field.h"

class BuyableField : public Field
{
protected:
	MyString name;
	SharedPtr<Player> owner;
	unsigned price;
	unsigned rent;
public:
	BuyableField(const MyString& name, unsigned price, unsigned rent);
	virtual unsigned calculateTotalRent() const = 0;

	void buy(SharedPtr<Player>& player);
	void action(SharedPtr<Player>& player) override;

	bool belongsToPlayer(const SharedPtr<Player>& player);
	bool isFree() const;

	void printFieldInfo() const;
};

