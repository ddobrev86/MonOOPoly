#include "Station.h"
#include "InputProcessor.h"
#include "utilities.h"

MyDictionary<SharedPtr<Player>, size_t> Station::ownersipMap;

Station::Station(const MyString& name, unsigned price, unsigned rent) : BuyableField(name, price, rent)
{}

void Station::buy(SharedPtr<Player>&player)
{
	if (!ownersipMap.containsKey(player))
		ownersipMap.addPair(MyPair<SharedPtr<Player>, size_t>(player, 0));

	ownersipMap[player]++;
}

size_t Station::calculateTotalRent() const
{
	if (!ownersipMap.containsKey(owner))
		return 0;

	return rent * twoToPower(ownersipMap[owner] - 1);
}

BuyableField* Station::clone() const
{
	return new Station(*this);
}

void Station::setUpMortgages(const SharedPtr<Mortgage>& castle, const SharedPtr<Mortgage>& cottage){}

bool Station::canBuyMortgages() const
{
	return false;
}

bool Station::action(SharedPtr<Player>& player)
{
	if (isFree())
	{
		std::cout << "Do you want to buy this property?(y|n): ";
		if (InputProcessor::askYesOrNo() == 'y')
			buy(player);
	}
	else
	{
		if (!belongsToPlayer(player))
		{
			player->removeFromBalance(calculateTotalRent());
			std::cout << "You have been taxed\n";

			player->moveTo(player->getPosition() + 3);
			return false;
		}
	}
	
	return true;
}
