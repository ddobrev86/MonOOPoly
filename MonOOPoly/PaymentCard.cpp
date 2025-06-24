#include "PaymentCard.h"
#include "Bank.h"
#include "PendingPayment.h"

PaymentCard::PaymentCard(int balanceChange)
{
	this->balanceChange = balanceChange;
}

void PaymentCard::printCardInfo() const
{
	std::cout << "You drew a Payment Card\n";
	if (balanceChange < 0)
		std::cout << "You have to give " << -balanceChange << '\n';
	else
		std::cout << "You get " << balanceChange << '\n';

	system("pause");
	system("cls");
}

bool PaymentCard::applyEffect(SharedPtr<Player>& player) const
{
	if (balanceChange < 0)
	{
		PendingPayment::clear();
		PendingPayment::setPayer(player);

		Bank::getFrom(player, -balanceChange, true);
	}
	else
		Bank::giveTo(player, balanceChange);

	return true;
}
