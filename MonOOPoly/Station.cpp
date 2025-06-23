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
	return rent * twoToPower(ownersipMap[owner] - 1) * multiplier;
}

BuyableField* Station::clone() const
{
	return new Station(*this);
}

void Station::printLandingMessage() const
{
	multiplier++;
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
		std::cout << "\nRent: " << calculateTotalRent() << '\n';
	}
}
