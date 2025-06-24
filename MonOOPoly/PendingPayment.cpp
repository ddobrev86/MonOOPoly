#include "PendingPayment.h"

MyVector<SharedPtr<Player>> PendingPayment::playersToPay;
unsigned PendingPayment::neededAmount;
SharedPtr<Player> PendingPayment::payer;

void PendingPayment::pay()
{
	size_t playerCount = playersToPay.getSize();

	if (!playerCount)
	{
		payer->removeFromBalance(neededAmount);
		clear();
		return;
	}

	unsigned amountPerPlayer = neededAmount / playerCount;

	for (size_t i = 0; i < playerCount; i++)
		playersToPay[i]->addToBalance(amountPerPlayer);

	payer->removeFromBalance(neededAmount);
	clear();
}

void PendingPayment::clear()
{
	playersToPay.clear();
}

void PendingPayment::setPayer(const SharedPtr<Player>& payer)
{
	PendingPayment::payer = payer;
}

void PendingPayment::addReceiver(const SharedPtr<Player>& player)
{
	playersToPay.push_back(player);
}

void PendingPayment::setNeededAmount(unsigned neededAmount)
{
	PendingPayment::neededAmount = neededAmount;
}
