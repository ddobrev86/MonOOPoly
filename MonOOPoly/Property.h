#pragma once
#include "Field.h"

class Property : public Field
{
private:
	SharedPtr<Player> owner;
	unsigned price;
	unsigned cottageCost;
	unsigned castleCost;
	unsigned rent;
public:
	Property(unsigned price, unsigned cottageCost,
		unsigned castleCost, unsigned rent);

	bool belongsToPlayer(const SharedPtr<Player>& player);
	bool isFree() const;

	void printFieldInfo() const override;
	void action(SharedPtr<Player>& player) override;

	void buy(SharedPtr<Player>& player);
};

