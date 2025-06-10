#include "Property.h"

Property::Property(unsigned price, unsigned cottageCost, unsigned castleCost, unsigned rent)
{
	this->price = price;
	this->cottageCost = cottageCost;
	this->castleCost = castleCost;
	this->rent = rent;
}

bool Property::belongsToPlayer(const SharedPtr<Player>& player)
{
	return owner.compareWith(player);
}
