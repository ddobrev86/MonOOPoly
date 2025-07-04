#include "BuyableField.h"
#include "InputProcessor.h"
#include "Bank.h"
#include "PendingPayment.h"

BuyableField::BuyableField(const MyString& name, unsigned price, unsigned rent)
{
	this->name = name;
	this->price = price;
	this->rent = rent;
}

unsigned BuyableField::sellPriceToBank() const
{
	unsigned result = calculateTotalRent() / 3;
	return result;
}

unsigned BuyableField::sellPriceToPlayer() const
{
	unsigned result = 2 * calculateTotalRent() / 3;
	return result;
}

void BuyableField::sell()
{
	owner = nullptr;
}

void BuyableField::sellTo(const SharedPtr<Player>& newOwner)
{
	owner = newOwner;
}

void BuyableField::buy(SharedPtr<Player>& player)
{
	if (!player->canAfford(price))
		throw std::runtime_error("You cannot afford to buy this property");

	Bank::getFrom(player, price, false);
	owner = player;
}

bool BuyableField::action(SharedPtr<Player>& player)
{
	if (isFree())
	{
		std::cout << "\nYour balance: " << player->getBalance() << '\n';
		std::cout << "\nDo you want to buy this property?(y|n): ";
		if (InputProcessor::askYesOrNo() == 'y')
			buy(player);
		system("cls");
	}
	else
	{
		unsigned totalRent = calculateTotalRent();
		if (!belongsToPlayer(player))
		{
			std::cout << "\nRent: " << calculateTotalRent() << '\n';

			PendingPayment::clear();
			PendingPayment::addReceiver(owner);
			PendingPayment::setPayer(player);

			Bank::getFrom(player, totalRent, true);

			printTaxingMessage();

			Bank::giveTo(owner, totalRent);
			//TODO add warning when exceeding balance
		}
		else
		{
			std::cout << "\nYou are the owner\n";
		}

		system("pause");
		system("cls");
	}

	return true;
}

bool BuyableField::belongsToPlayer(const SharedPtr<Player>& player) const
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
	//std::cout << "Price: " << price << "\tRent: " << rent << '\n';

	if (isFree())
	{
		std::cout << "No one owns this property. You can buy it!\n";
		std::cout << "It costs " << price << '\n';
	}
	else
	{
		std::cout << "This property belongs to ";
		owner->printUsernameInColor();
	}
}

void BuyableField::printFieldInfo() const
{
	if (owner.isInitalized())
		setColor(owner->getColor());
	std::cout << name;

	resetColor();
}

//void BuyableField::printFieldInfo() const
//{
//	std::cout << name << "\tPrice: " << price << "\tRent: " << rent << '\n';
//}

bool BuyableField::compareName(const MyString& name) const
{
	return this->name == name;
}

const MyString& BuyableField::getName() const
{
	return name;
}

SharedPtr<Player>& BuyableField::getOwner()
{
	return owner;
}

void BuyableField::printUpForSaleMessage() const
{
	std::cout << name << '\n';
	std::cout << "\tPrice to bank: " << sellPriceToBank()
		<< "\tPrice to player: " << sellPriceToPlayer() << '\n';
}
