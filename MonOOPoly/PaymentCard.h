#pragma once
#include "Card.h"

class PaymentCard : public Card
{
private:
	int balanceChange;
public:
	PaymentCard(int balanceChange);

	void printCardInfo() const override;
	void applyEffect(SharedPtr<Player>& player) const override;
};

