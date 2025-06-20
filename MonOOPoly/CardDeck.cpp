#include "CardDeck.h"
#include <utility>

void CardDeck::addCard(const SharedPtr<Card>& card)
{
	cards.push(SharedPtr<Card>(card));
}

void CardDeck::addCard(SharedPtr<Card>&& card)
{
	cards.push(SharedPtr<Card>(card));
}

const SharedPtr<Card>& CardDeck::drawCard()
{
	const SharedPtr<Card>& cardToReturn = cards.peek();
	cards.pop();

	return cardToReturn;
}

bool CardDeck::isEmpty() const
{
	return cards.isEmpty();
}
