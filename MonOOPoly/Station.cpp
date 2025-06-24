#include "Station.h"
#include "InputProcessor.h"
#include "utilities.h"

MyDictionary<SharedPtr<Player>, size_t> Station::ownersipMap;

Station::Station(const MyString& name,
	unsigned price, unsigned rent) : SpecialField(name, price, rent)
{
	multiplier = 1;
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

	return rent * twoToPower(ownersipMap[owner] - 1) * multiplier;
}

BuyableField* Station::clone() const
{
	return new Station(*this);
}

void Station::printLandingMessage() const
{
	std::cout << "You have landed on " << name << '\n';

	if (isFree())
	{
		std::cout << "No one owns this station. You can buy it!\n";
		std::cout << "It costs " << price << '\n';
	}
	else
	{
		std::cout << "This station belongs to ";
		owner->printUsernameInColor();

		if (multiplier < 18)
			multiplier++;
	}
}

void Station::sell()
{
	ownersipMap[owner]--;
	owner = nullptr;
}

void Station::sellTo(const SharedPtr<Player>& newOwner)
{
	ownersipMap[owner]--;

	if (!ownersipMap.containsKey(newOwner))
		ownersipMap.addPair(MyPair<SharedPtr<Player>, size_t>(newOwner, 0));

	ownersipMap[newOwner]++;
	owner = newOwner;
}
