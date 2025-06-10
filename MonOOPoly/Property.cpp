#include "Property.h"
#include "InputProcessor.h"

Property::Property(unsigned price, unsigned cottageCost, unsigned castleCost, unsigned rent)
{
	this->price = price;
	this->cottageCost = cottageCost;
	this->castleCost = castleCost;
	this->rent = rent;
}

bool Property::belongsToPlayer(const SharedPtr<Player>& player)
{
	if (isFree)
		return false;

	return owner.compareWith(player);
}

bool Property::isFree() const
{
	return !owner.isInitalized();
}

void Property::printFieldInfo() const
{
	if (isFree())
	{
		std::cout << "No one owns this property. You can buy it!\n";
		std::cout << "It costs " << price << '\n';
	}
	else
	{
		std::cout << "This property belongs to " << owner->getUsername() << '\n';
		std::cout << "Rent: " << rent << '\n';
	}
}

void Property::action(SharedPtr<Player>& player)
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
			player->removeFromBalance(rent);
			std::cout << "You have been taxed\n";
		}
		//TODO add option to buy houses
	}
}

void Property::buy(SharedPtr<Player>& player)
{
	owner = player;
	if (player->canAfford(price))
		player->removeFromBalance(price);
	else
		throw std::runtime_error("You cannot afford to buy this property");
}
