#include "Trade.h"
#include "InputProcessor.h"

void Trade::sellToPlayer(SharedPtr<Player>& sender,
	SharedPtr<Player>& receiver, SharedPtr<BuyableField>& field)
{
	unsigned sellPrice = field->sellPriceToPlayer();
	std::cout << field->getName() << " goes for " << sellPrice << '\n';
	std::cout << receiver->getUsername() << " do you accept this offer(y|n): ";

	if (InputProcessor::askYesOrNo() == 'y')
	{
		Bank::getFrom(receiver, sellPrice);
		Bank::giveTo(sender, sellPrice);
		field->sell();
		//field->changeOwner(receiver);

		return;
	}
	
	throw std::runtime_error("Deal is cancelled");
}

void Trade::sellToBank(SharedPtr<Player>& sender, SharedPtr<BuyableField>& field)
{
	unsigned sellPrice = field->sellPriceToBank();

	std::cout << field->getName() << " goes for " << sellPrice << '\n';
	std::cout << sender->getUsername() << " do you accept this offer(y|n): ";

	if (InputProcessor::askYesOrNo() == 'y')
	{
		Bank::giveTo(sender, sellPrice);
		field->sell();
		//field->changeOwner(receiver);
		return;
	}

	throw std::runtime_error("Deal is cancelled");

}
