#include "CardField.h"

CardField::CardField(const SharedPtr<CardDeck>& deck)
{
	this->deck = deck;
}

void CardField::printLandingMessage() const
{
	std::cout << "You have landed on a card field\n";
}

bool CardField::action(SharedPtr<Player>& player)
{
	SharedPtr<Card> drawnCard = deck->drawCard();
	drawnCard->printCardInfo();
	bool canContinue = drawnCard->applyEffect(player);
	deck->addCard(drawnCard);

	return canContinue;
}

void CardField::printFieldInfo() const
{
	std::cout << "Card Field";
}
