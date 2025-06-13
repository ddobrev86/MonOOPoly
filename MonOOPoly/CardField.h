#pragma once
#include "Field.h"
#include "CardDeck.h"

class CardField : public Field
{
private:
	SharedPtr<CardDeck> deck;

public:
	CardField(const SharedPtr<CardDeck>& deck);

	void printFieldInfo() const override;
	bool action(SharedPtr<Player>& player) override;
};

