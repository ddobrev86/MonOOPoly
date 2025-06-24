#include "Trade.h"
#include "InputProcessor.h"

void Trade::sellToPlayer(SharedPtr<Player>& receiver, 
	SharedPtr<BuyableField>& field, int& neededAmount)
{
	unsigned sellPrice = field->sellPriceToPlayer();
	std::cout << "\n\t";
	receiver->printUsernameInColor();
	std::cout << " do you accept this offer(y|n): ";

	if (InputProcessor::askYesOrNo() == 'y')
	{
		Bank::getFrom(receiver, sellPrice, false);
		Bank::giveTo(field->getOwner(), sellPrice);
		field->sellTo(receiver);

		neededAmount -= sellPrice;

		system("cls");
		return;
	}
	
	throw std::runtime_error("Deal is cancelled");
}

void Trade::sellToBank(SharedPtr<BuyableField>& field, int& neededAmount)
{
	unsigned sellPrice = field->sellPriceToBank();

	//std::cout << field->getName() << " goes for " << sellPrice << '\n';
	//std::cout << sender->getUsername() << " do you accept this offer(y|n): ";

	Bank::giveTo(field->getOwner(), sellPrice);
	field->sell();
	neededAmount -= sellPrice;
	//field->changeOwner(receiver);
	/*return;

	if (InputProcessor::askYesOrNo() == 'y')
	{
		
	}

	throw std::runtime_error("Deal is cancelled");*/

}
