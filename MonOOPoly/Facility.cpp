#include "Facility.h"
#include "InputProcessor.h"

Facility::Facility(const MyString& name, 
    unsigned price) : SpecialField(name, price, 20)
{
    multiplier = 1;
}

unsigned Facility::calculateTotalRent() const
{   
    return rent;
}

BuyableField* Facility::clone() const
{
    return new Facility(*this);
}

bool Facility::action(SharedPtr<Player>& player)
{
	if (isFree())
	{
		std::cout << "Do you want to buy this property?(y|n): ";
		if (InputProcessor::askYesOrNo() == 'y')
			buy(player);

		system("cls");
	}
	else
	{
		if (!belongsToPlayer(player))
		{
			std::cout << "\nYou have to give " << multiplier * 5 << "% of your balance\n";
			player->removePercent(multiplier * 0.05);
			printTaxingMessage();
			//TODO add warning when exceeding balance
		}
		else
		{
			std::cout << "You are the owner\n";
		}

		system("pause");
		system("cls");
	}

	return true;
}

void Facility::printLandingMessage() const
{
	std::cout << "You have landed on " << name << '\n';

	if (isFree())
	{
		std::cout << "No one owns this facility. You can buy it!\n";
		std::cout << "It costs " << price << '\n';
	}
	else
	{
		std::cout << "This facility belongs to ";
		owner->printUsernameInColor();

		if(multiplier < 18)
			multiplier++;
	}
}
