#include "PaymentCard.h"
#include "Bank.h"

PaymentCard::PaymentCard(int balanceChange)
{
	this->balanceChange = balanceChange;
}

void PaymentCard::applyEffect(SharedPtr<Player>& player) const
{
	if (balanceChange < 0)
		Bank::getFrom(player, -balanceChange);
	else
		Bank::giveTo(player, balanceChange);
}
