#include "BuyableField.h"
#include "InputProcessor.h"

BuyableField::BuyableField(const MyString& name, unsigned price, unsigned rent)
{
	this->name = name;
	this->price = price;
	this->rent = rent;
}

void BuyableField::buy(SharedPtr<Player>& player)
{
	if (!player->canAfford(price))
		throw std::runtime_error("You cannot afford to buy this property");

	owner = player;
	player->removeFromBalance(price);
}

bool BuyableField::action(SharedPtr<Player>& player)
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
			//TODO add warning when exceeding balance
		}
	}

	return true;
}

bool BuyableField::belongsToPlayer(const SharedPtr<Player>& player)
{
	if (isFree())
		return false;

	return owner.compareWith(player);
}

bool BuyableField::isFree() const
{
	return !owner.isInitalized();
}

void BuyableField::printLandingMessage() const
{
	std::cout << "You have landed on " << name << '\n';

	if (isFree())
	{
		std::cout << "No one owns this property. You can buy it!\n";
		std::cout << "It costs " << price << '\n';
	}
	else
	{
		std::cout << "This property belongs to " << owner->getUsername() << '\n';
		std::cout << "Rent: " << calculateTotalRent() << '\n';
	}
}

void BuyableField::printFieldInfo() const
{
	std::cout << name;
}

bool BuyableField::compareName(const MyString& name) const
{
	return this->name == name;
}
