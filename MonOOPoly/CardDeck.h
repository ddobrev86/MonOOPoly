#pragma once
#include "MyQueue.hpp"
#include "Card.h"
#include "UniquePtr.hpp"

class CardDeck
{
private:
	MyQueue<UniquePtr<Card>> cards;

public:
	void addCard(const UniquePtr<Card>& card);
	const UniquePtr<Card>& drawCard();
};

