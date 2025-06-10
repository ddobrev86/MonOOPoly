#include "CardDeck.h"
#include <utility>

void CardDeck::addCard(const UniquePtr<Card>& card)
{
	cards.push(card);
}

const UniquePtr<Card>& CardDeck::drawCard()
{
	const UniquePtr<Card>& cardToReturn = cards.peek();
	cards.pop();

	return cardToReturn;
}
