#include "PaymentCard.h"
#include "Bank.h"

PaymentCard::PaymentCard(int balanceChange)
{
	this->balanceChange = balanceChange;
}

void PaymentCard::printCardInfo() const
{
	std::cout << "You drew a Payment Card\n";
	if (balanceChange < 0)
		std::cout << "You have to give " << balanceChange;
	else
		std::cout << "You get " << balanceChange;
}

bool PaymentCard::applyEffect(SharedPtr<Player>& player) const
{
	if (balanceChange < 0)
		Bank::getFrom(player, -balanceChange);
	else
		Bank::giveTo(player, balanceChange);

	return true;
}
