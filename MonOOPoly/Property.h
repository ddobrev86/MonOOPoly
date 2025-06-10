#pragma once
#include "Field.h"
#include "SharedPtr.hpp"
#include "Player.h"

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
};

