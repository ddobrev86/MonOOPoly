#include "Facility.h"
#include "InputProcessor.h"

Facility::Facility(const MyString& name, 
    unsigned price) : SpecialField(name, price, 0)
{
    multiplier = 1;
}

unsigned Facility::calculateTotalRent() const
{   
    return 0;
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
	}
	else
	{
		if (!belongsToPlayer(player))
		{
			std::cout << "You have to give " << ++multiplier * 5 << "% of your balance";
			player->removePercent(multiplier * 0.05);
			std::cout << "You have been taxed\n";
			//TODO add warning when exceeding balance
		}
	}

	return true;
}
