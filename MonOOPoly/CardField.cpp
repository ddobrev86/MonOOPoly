#include "CardField.h"

CardField::CardField(const SharedPtr<CardDeck>& deck)
{
	this->deck = deck;
}

void CardField::printFieldInfo() const
{
	std::cout << "You have landed on a card field\n";
}

bool CardField::action(SharedPtr<Player>& player)
{
	SharedPtr<Card> drawnCard = deck->drawCard();
	drawnCard->applyEffect(player);
	deck->addCard(drawnCard);

	return true;
}