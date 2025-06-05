#pragma once
#include "Card.h"

class PaymentCard : public Card
{
private:
	int balanceChange;
public:
	PaymentCard(int balanceChange);

	void applyEffect(Player& player) const override;
};

