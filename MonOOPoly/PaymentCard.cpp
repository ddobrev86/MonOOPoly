#include "PaymentCard.h"

PaymentCard::PaymentCard(int balanceChange)
{
	this->balanceChange = balanceChange;
}

void PaymentCard::applyEffect(SharedPtr<Player>& player) const
{
	if (balanceChange < 0)
		player->removeFromBalance(-balanceChange);
	else
		player->addToBalance(balanceChange);
}
