#include "Station.h"
#include "InputProcessor.h"
#include "utilities.h"

MyDictionary<SharedPtr<Player>, size_t> Station::ownersipMap;

Station::Station(const MyString& name,
	unsigned price, unsigned rent) : SpecialField(name, price, rent)
{
	multiplier = 0;
}

void Station::buy(SharedPtr<Player>&player)
{
	BuyableField::buy(player);

	if (!ownersipMap.containsKey(player))
		ownersipMap.addPair(MyPair<SharedPtr<Player>, size_t>(player, 0));

	ownersipMap[player]++;
}

unsigned Station::calculateTotalRent() const
{
	if (!ownersipMap.containsKey(owner))
		return 0;

	multiplier++;
	return rent * twoToPower(ownersipMap[owner] - 1) * multiplier;
}

BuyableField* Station::clone() const
{
	return new Station(*this);
}