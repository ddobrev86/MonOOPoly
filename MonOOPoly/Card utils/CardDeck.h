#pragma once
#include "MyQueue.hpp"
#include "Card.h"
#include "UniquePtr.hpp"

class CardDeck
{
private:
	MyQueue<SharedPtr<Card>> cards;

public:
	CardDeck() = default;

	void addCard(const SharedPtr<Card>& card);
	const SharedPtr<Card>& drawCard();
};

